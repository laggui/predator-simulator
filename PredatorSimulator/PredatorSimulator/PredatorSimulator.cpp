#include "PredatorSimulator.h"

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QGraphicsRectItem>
#include <QRandomGenerator>
#include "QControlBar.h"
#include "QParameters.h"
#include "QPredator.h"
#include "QSuicideBomber.h"
#include "QRunner.h"
#include "QWall.h"
#include "QCloningZone.h"
#include "QEcosystem.h"
#include "Random.h"

const size_t PredatorSimulator::sMaxNbrOfItems{ 100 };
const QSize PredatorSimulator::sSceneSize(600, 600);
const QColor PredatorSimulator::sSceneBackgroundColor(16, 32, 64);
const int PredatorSimulator::sTimerInterval{ 30 };

PredatorSimulator::PredatorSimulator(QWidget *parent)
	: QMainWindow(parent),
	mSimulationView{ new QGraphicsView(&mGraphicsScene) },
	mParametersQRunners{ new QParameters(sMaxNbrOfItems,"QRunners") },
	mParametersQPredators{ new QParameters(sMaxNbrOfItems,"QPredators") },
	mParametersQSuicideBombers{ new QParameters(sMaxNbrOfItems,"QSuicideBombers") },
	mControlBar{ new QControlBar(Qt::Vertical) }
{
	ui.setupUi(this);

	mControlBar->setReady();
	mControlBar->setText("Start new simulation", "End simulation", "Pause simulation", "Resume simulation", "One step simulation");
	mControlBar->setColor(QColor(0, 255, 0), QColor(255, 255, 0), QColor(255, 0, 0), QColor(230, 230, 230), QColor(128, 128, 128));
	mGraphicsScene.setSceneRect(-sSceneSize.width() / 2, -sSceneSize.height() / 2, sSceneSize.width(), sSceneSize.height());

	QWidget * controlWidget{ new QWidget };
	QVBoxLayout * controlLayout{ new QVBoxLayout };
	controlWidget->setLayout(controlLayout);
	controlLayout->addWidget(mParametersQRunners);
	controlLayout->addWidget(mParametersQPredators);
	controlLayout->addWidget(mParametersQSuicideBombers);
	controlLayout->addStretch();
	controlLayout->addWidget(mControlBar);

	QWidget * centralWidget{ new QWidget };
	QHBoxLayout * centralLayout{ new QHBoxLayout };
	centralWidget->setLayout(centralLayout);

	centralLayout->addWidget(mSimulationView);
	centralLayout->addWidget(controlWidget);

	setCentralWidget(centralWidget);

	connect(mControlBar, &QControlBar::started, this, &PredatorSimulator::startSimulation);
	connect(mControlBar, &QControlBar::stopped, this, &PredatorSimulator::stopSimulation);
	connect(mControlBar, &QControlBar::paused, this, &PredatorSimulator::pauseSimulation);
	connect(mControlBar, &QControlBar::resumed, this, &PredatorSimulator::resumeSimulation);
	connect(mControlBar, &QControlBar::stepped, this, &PredatorSimulator::stepSimulation);

	connect(&mTimer, &QTimer::timeout, &mGraphicsScene, &QGraphicsScene::advance);
}

void PredatorSimulator::startSimulation()
{
	const quint8 wallWidth{ 20 };
	const qreal membersSize{ 10 };
	const qreal membersSpeedMin{ 1 };
	const qreal membersSpeedMax{ 5 };
	const qreal bombersDamage{ 5 };
	const quint8 predatorsDamage{ 1 };
	const quint8 runnersHP{ 3 };
	const qreal runnersOrientationOffset{ 20 };
	const qreal verticalOrientation{ 90 };
	const qreal horizontalOrientation{ 0 };
	// Vide la scène pour démarrer une nouvelle démo
	mGraphicsScene.clear();


	// Met un item rectangulaire pour bien voir les limites de la scène
	mEcosystem =  new QEcosystem(sTimerInterval*10, 0, QPointF(0,0), sSceneSize.width(), sSceneSize.height());
	mGraphicsScene.addItem(mEcosystem);

	// Ajout des murs
	mGraphicsScene.addItem(
		new QWall(
			QPointF(-sSceneSize.width() / 2, -sSceneSize.height() / 2),
			wallWidth,
			sSceneSize.height(),
			verticalOrientation)); // Gauche

	mGraphicsScene.addItem(
		new QWall(
			QPointF(sSceneSize.width() / 2 - wallWidth, -sSceneSize.height() / 2),
			wallWidth,
			sSceneSize.height(),
			verticalOrientation)); // Droite

	mGraphicsScene.addItem(
		new QWall(
			QPointF(-sSceneSize.width() / 2, -sSceneSize.height() / 2),
			sSceneSize.width(),
			wallWidth,
			horizontalOrientation)); // En haut

	mGraphicsScene.addItem(
		new QCloningZone(
			QPointF(-sSceneSize.width() / 2, sSceneSize.height() / 2),
			sSceneSize.width(),
			wallWidth,
			horizontalOrientation,
			-sSceneSize.height() / 2 + wallWidth)); // En bas

	for (int i{ 0 }; i < mParametersQPredators->nbrOfItems(); ++i) {
		mGraphicsScene.addItem(
			new QPredator(
				QPointF(0, -(sSceneSize.height()/2 - wallWidth * 2) + i * (static_cast<qreal>(sSceneSize.height() - wallWidth * 2) / (mParametersQPredators->nbrOfItems()))),	// distribués uniformément sur l'axe y
				(i % 2) * 180,			// orientation aléatoire
				random(membersSpeedMin, membersSpeedMax),			// vitesse aléatoire entre 1 et 5
				random(membersSize, 2 * membersSize),			// taille aléatoire entre 2 et 10
				predatorsDamage,							// dommage
				0,							// timeNoKill
				Qt::red));			// couleur aléatoire
	}

	for (int i{ 0 }; i < mParametersQSuicideBombers->nbrOfItems(); ++i) {
		mGraphicsScene.addItem(
			new QSuicideBomber(
				QPointF(random(-sSceneSize.width() / 2 + wallWidth, sSceneSize.width() / 2 - wallWidth), (-sSceneSize.height() / 2) + wallWidth + membersSize),	// En haut de la boites
				verticalOrientation,																										// Orienté vers le bas
				random(membersSpeedMin, membersSpeedMax),																						// vitesse aléatoire entre 1 et 10
				membersSize,																										// Taille
				bombersDamage,																									// dommage
				Qt::white));																								// bleu
	}

	for (int i{ 0 }; i < mParametersQRunners->nbrOfItems(); ++i) {
		mGraphicsScene.addItem(
			new QRunner(
				QPointF(random(-sSceneSize.width() / 2  + wallWidth + membersSize, sSceneSize.width() / 2 - wallWidth - membersSize), (-sSceneSize.height() / 2) + wallWidth + membersSize),		// position En haut de la boites
				random(0 + runnersOrientationOffset, 180 - runnersOrientationOffset),						// Orienté vers le bas rotation 0 = vers la droite
				membersSpeedMax,		//vitesse
				membersSize,		//size
				runnersHP, // hp
				Qt::green
			));

	}
	mTimer.start(sTimerInterval);

}

QSize PredatorSimulator::sceneSize() const
{
	return sSceneSize;
}

void PredatorSimulator::stepSimulation()
{
	mGraphicsScene.advance();
}

void PredatorSimulator::pauseSimulation()
{
	mTimer.stop();
}

void PredatorSimulator::resumeSimulation()
{
	mTimer.start(sTimerInterval);
}

void PredatorSimulator::stopSimulation()
{
	mTimer.stop();
}
