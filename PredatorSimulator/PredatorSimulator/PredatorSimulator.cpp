#include "PredatorSimulator.h"

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QRandomGenerator>
#include <QPushButton>

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
const int PredatorSimulator::sActOfGodFreezeTime{ sTimerInterval * 15 };

PredatorSimulator::PredatorSimulator(QWidget *parent)
	: QMainWindow(parent),
	mSimulationView{ new QGraphicsView(&mGraphicsScene) },
	mParametersQRunners{ new QParameters(sMaxNbrOfItems,"QRunners") },
	mParametersQPredators{ new QParameters(sMaxNbrOfItems,"QPredators") },
	mParametersQSuicideBombers{ new QParameters(sMaxNbrOfItems,"QSuicideBombers") },
	mControlBar{ new QControlBar(Qt::Vertical) },
	mActOfGod{ new QPushButton(tr("Act of God"))}
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
	mActOfGod->setEnabled(false);
	controlLayout->addWidget(mActOfGod);
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
	connect(mActOfGod, &QPushButton::clicked, this, &PredatorSimulator::actOfGod);
}

void PredatorSimulator::startSimulation()
{
	// Constantes de simulation
	const quint8 wallWidth{ 20 };
	const qreal membersSize{ 10 };
	const qreal membersSpeedMin{ 1 };
	const qreal membersSpeedMax{ 5 };
	const qreal bombersDamage{ 5 };
	const quint8 predatorsDamage{ 1 };
	const qreal predatorsOrientation{ 180 };
	const quint8 runnersHP{ 3 };
	const qreal runnersOrientationOffset{ 20 };
	const qreal verticalOrientation{ 90 };
	const qreal horizontalOrientation{ 0 };
	// Vide la scène pour démarrer une nouvelle démo
	mGraphicsScene.clear();
	mActOfGod->setEnabled(true);

	// On ajoute l'écosystème comme l'arrière-plan de notre scène
	mEcosystem =  new QEcosystem(QSize(sSceneSize.width() - 2 * wallWidth, sSceneSize.height() - 2 * wallWidth), sTimerInterval*10, 0, QPointF(0,0), sSceneSize.width(), sSceneSize.height());
	mGraphicsScene.addItem(mEcosystem);

	// Mur à gauche
	mGraphicsScene.addItem(
		new QWall(
			QPointF(-sSceneSize.width() / 2, -sSceneSize.height() / 2), // position
			wallWidth, // largeur
			sSceneSize.height(), // hauteur
			verticalOrientation)); // orientation

	// Mur à droite
	mGraphicsScene.addItem(
		new QWall(
			QPointF(sSceneSize.width() / 2 - wallWidth, -sSceneSize.height() / 2), // position
			wallWidth, // largeur
			sSceneSize.height(), // hauteur
			verticalOrientation)); // orientation

	// Mur en haut
	mGraphicsScene.addItem(
		new QWall(
			QPointF(-sSceneSize.width() / 2, -sSceneSize.height() / 2), // position
			sSceneSize.width(), // largeur
			wallWidth, // hauteur
			horizontalOrientation)); // orientation

	// Zone de clonage en bas
	mGraphicsScene.addItem(
		new QCloningZone(
			QPointF(-sSceneSize.width() / 2, sSceneSize.height() / 2), // position
			sSceneSize.width(), // largeur
			wallWidth, // hauteur
			horizontalOrientation, // orientation
			-sSceneSize.height() / 2 + wallWidth)); // position de départ pour le clonage

	for (int i{ 0 }; i < mParametersQPredators->nbrOfItems(); ++i) {
		// Prédateurs distribués uniformément sur l'axe y
		mGraphicsScene.addItem(
			new QPredator(
				QPointF(0, -(sSceneSize.height()/2 - wallWidth * 2) + i * (static_cast<qreal>(sSceneSize.height() - wallWidth * 2) / (mParametersQPredators->nbrOfItems()))),
				(i % 2) * predatorsOrientation, // orientation alternée (soit 0 ou 180)
				random(membersSpeedMin, membersSpeedMax), // vitesse aléatoire
				random(membersSize, 2 * membersSize), // taille aléatoire
				predatorsDamage, // dommage
				0, // timeNoKill
				Qt::red)); // couleur
	}

	for (int i{ 0 }; i < mParametersQSuicideBombers->nbrOfItems(); ++i) {
		mGraphicsScene.addItem(
			new QSuicideBomber(
				QPointF(random(-sSceneSize.width() / 2 + wallWidth, sSceneSize.width() / 2 - wallWidth),
						(-sSceneSize.height() / 2) + wallWidth + membersSize),	// position en haut de la scène, à l'intérieur des murs
				verticalOrientation, // orientation
				random(membersSpeedMin, membersSpeedMax), // vitesse aléatoire
				membersSize, // taille
				bombersDamage, // dommage
				Qt::white)); // couleur
	}

	for (int i{ 0 }; i < mParametersQRunners->nbrOfItems(); ++i) {
		mGraphicsScene.addItem(
			new QRunner(
				QPointF(random(-sSceneSize.width() / 2  + wallWidth + membersSize, sSceneSize.width() / 2 - wallWidth - membersSize),
						(-sSceneSize.height() / 2) + wallWidth + membersSize), // position en haut de la scène, à l'intérieur des murs
				random(0 + runnersOrientationOffset, 180 - runnersOrientationOffset), // orientation
				membersSpeedMax, // vitesse
				membersSize, // taille
				runnersHP, // vie
				Qt::green)); // couleur

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
	mActOfGod->setEnabled(false);
}

void PredatorSimulator::actOfGod()
{
	QList<QGraphicsItem *> sceneItems = mGraphicsScene.items();
	//Itérer à travers les objets et vérifier les prédateurs
	foreach(QGraphicsItem *item, sceneItems) {
		if (auto predatorObj = dynamic_cast<QPredator*>(item)) {
			predatorObj->setFrozen(sActOfGodFreezeTime);
		}
	}
}
