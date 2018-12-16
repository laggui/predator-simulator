#include "PredatorSimulator.h"

#include <QGraphicsView>
#include <QHBoxLayout>
#include <QGraphicsRectItem>
#include <QRandomGenerator>
#include "QControlBar.h"
#include "QParameters.h"
#include "QPredator.h"
#include "QWall.h"
#include "Random.h"

const size_t PredatorSimulator::sMaxNbrOfItems{ 1000 };
const QSize PredatorSimulator::sSceneSize(1000, 600);
const QColor PredatorSimulator::sSceneBackgroundColor(16, 32, 64);

PredatorSimulator::PredatorSimulator(QWidget *parent)
	: QMainWindow(parent),
	mSimulationView{ new QGraphicsView(&mGraphicsScene) },
	mParameters{ new QParameters(sMaxNbrOfItems) },
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
	controlLayout->addWidget(mParameters);
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
	// Vide la sc�ne pour d�marrer une nouvelle d�mo
	mGraphicsScene.clear();


	// Met un item rectangulaire pour bien voir les limites de la sc�ne
	QGraphicsRectItem * background{ new QGraphicsRectItem(mGraphicsScene.sceneRect()) };
	background->setPen(Qt::NoPen);
	background->setBrush(sSceneBackgroundColor);

	mGraphicsScene.addItem(background);

	//mGraphicsScene.addItem(
	//	new QWall(
	//		QPointF(-sSceneSize.width() / 2, sSceneSize.height() / 2)));

	//mGraphicsScene.addItem(
	//	new QWall(
	//		QPointF(sSceneSize.width() / 2, sSceneSize.height() / 2)));

	for (int i{ 0 }; i < mParameters->nbrOfItems(); ++i) {
		mGraphicsScene.addItem(
			// Tous les lit�raux ici devraient �tre cr��s dans des constantes symboliques!
			new QPredator(
				QPointF(),					// ils sont tous � l'origine au d�part!
				random(360.0),				// orientation al�atoire
				random(1.0, 10.0),			// vitesse al�atoire entre 1 et 10
				random(5.0, 15.0),			// taille al�atoire entre 5 et 15
				25,							// dommage
				0,							// timeNoKill
				randomColor()));			// couleur al�atoire
	}
	mTimer.start(30);

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
	mTimer.start(30);
}

void PredatorSimulator::stopSimulation()
{
	mTimer.stop();
}