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
#include "QEcosystem.h"
#include "Random.h"

const size_t PredatorSimulator::sMaxNbrOfItems{ 1000 };
const QSize PredatorSimulator::sSceneSize(1000, 600);
const QColor PredatorSimulator::sSceneBackgroundColor(16, 32, 64);
const int PredatorSimulator::sTimerInterval{ 30 };

PredatorSimulator::PredatorSimulator(QWidget *parent)
	: QMainWindow(parent),
	mSimulationView{ new QGraphicsView(&mGraphicsScene) },
	mParametersQRunners{ new QParameters(sMaxNbrOfItems,"QRunners") },
	mParametersQPredators{ new QParameters(sMaxNbrOfItems,"QPredators") },
	mParametersQSuicideBombers{ new QParameters(sMaxNbrOfItems,"QSuicideBombers") },
	mControlBar{ new QControlBar(Qt::Vertical) },
	mEcosystem{ new QEcosystem(sTimerInterval, 0, QPointF(0,0), sSceneSize.width(), sSceneSize.height()) }
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
	// Vide la scène pour démarrer une nouvelle démo
	mGraphicsScene.clear();


	// Met un item rectangulaire pour bien voir les limites de la scène
	// TO-DO: remplacer le background par mEcosystem [DONE]
	//QGraphicsRectItem * background{ new QGraphicsRectItem(mGraphicsScene.sceneRect()) };
	//background->setPen(Qt::NoPen);
	//background->setBrush(sSceneBackgroundColor);

	mGraphicsScene.addItem(mEcosystem);

	// Ajout des murs
	mGraphicsScene.addItem(
		new QWall(
			QPointF(-sSceneSize.width() / 2, -sSceneSize.height() / 2),
			wallWidth,
			sSceneSize.height(),
			90
			)); // Gauche

	mGraphicsScene.addItem(
		new QWall(
			QPointF(sSceneSize.width() / 2 - wallWidth, -sSceneSize.height() / 2),
			wallWidth,
			sSceneSize.height(),
			90)); // Droite

	//mGraphicsScene.addItem(
	//	new QWall(
	//		QPointF(-sSceneSize.width() / 2, -sSceneSize.height() / 2),
	//		sSceneSize.width(),
	//		wallWidth)); // En haut

	//for (int i{ 0 }; i < mParametersQPredators->nbrOfItems(); ++i) {
	//	mGraphicsScene.addItem(
	//		// Tous les litéraux ici devraient être créés dans des constantes symboliques!
	//		new QPredator(
	//			QPointF(0, -sSceneSize.height() / 2 + (i + 1) * (sSceneSize.height() / (mParametersQPredators->nbrOfItems() + 1))),	// ils sont tous à l'origine au départ!
	//			i%2*180,			// orientation aléatoire
	//			random(1.0, 10.0),			// vitesse aléatoire entre 1 et 10
	//			random(5.0, 15.0),			// taille aléatoire entre 5 et 15
	//			25,							// dommage
	//			0,							// timeNoKill
	//			Qt::red));			// couleur aléatoire
	//}

	//for (int i{ 0 }; i < mParametersQSuicideBombers->nbrOfItems(); ++i) {
	//	mGraphicsScene.addItem(
	//		// Tous les litéraux ici devraient être créés dans des constantes symboliques!
	//		new QSuicideBomber(
	//			QPointF(random(-sSceneSize.width() / 2, sSceneSize.width() / 2 - wallWidth), -sSceneSize.height() / 2),	// En haut de la boites
	//			90.0,																										// Orienté vers le bas
	//			random(1.0, 10.0),																						// vitesse aléatoire entre 1 et 10
	//			20.0,																										// Taille
	//			0.5,																									// dommage
	//			Qt::white));																								// bleu
	//}

	for (int i{ 0 }; i < mParametersQRunners->nbrOfItems(); ++i) {
		mGraphicsScene.addItem(
			// Tous les litéraux ici devraient être créés dans des constantes symboliques!
			new QRunner(
				QPointF(random(-sSceneSize.width() / 2, sSceneSize.width() / 2 - wallWidth), (-sSceneSize.height() / 2)+20),		// position En haut de la boites
				random(20, 160),						// Orienté vers le bas rotation 0 = vers la droite
				1,		//vitesse
				3.0,		//scale
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
