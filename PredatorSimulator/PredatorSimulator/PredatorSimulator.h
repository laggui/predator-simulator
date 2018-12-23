#ifndef PREDATOR_SIMULATOR_H
#define PREDATOR_SIMULATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_PredatorSimulator.h"

#include <QGraphicsScene>
#include <QTimer>

class QPushButton;
class QGraphicsView;
class QControlBar;
class QParameters;
class QEcosystem;

class PredatorSimulator : public QMainWindow
{
	Q_OBJECT

public:
	PredatorSimulator(QWidget *parent = Q_NULLPTR);

private:
	Ui::PredatorSimulatorClass ui;

	// Les éléments graphiques de la simulation
	QGraphicsScene mGraphicsScene;
	QGraphicsView * mSimulationView;
	QParameters * mParametersQRunners;
	QParameters * mParametersQPredators;
	QParameters * mParametersQSuicideBombers;
	QControlBar * mControlBar;
	QPushButton * mActOfGod;

	// Timer
	QTimer mTimer;
	// L'écosystème associé à la simulation
	QEcosystem * mEcosystem;

	// Les constantes de la simulation
	static const size_t sMaxNbrOfItems;
	static const QSize sSceneSize;
	static const QColor sSceneBackgroundColor;
	static const int sTimerInterval;
	static const int sActOfGodFreezeTime;

private slots:
	void startSimulation();
	void stepSimulation();
	void pauseSimulation();
	void resumeSimulation();
	void stopSimulation();
	void actOfGod();

};

#endif // !PREDATOR_SIMULATOR_H


