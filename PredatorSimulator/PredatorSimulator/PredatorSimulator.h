#ifndef PREDATOR_SIMULATOR_H
#define PREDATOR_SIMULATOR_H

#include <QtWidgets/QMainWindow>
#include "ui_PredatorSimulator.h"

#include <QGraphicsScene>
#include <QTimer>

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

	QGraphicsScene mGraphicsScene;
	QGraphicsView * mSimulationView;
	QParameters * mParametersQRunners;
	QParameters * mParametersQPredators;
	QParameters * mParametersQSuicideBombers;
	QControlBar * mControlBar;

	QTimer mTimer;
	QEcosystem * mEcosystem;

	static const size_t sMaxNbrOfItems;
	static const QSize sSceneSize;
	static const QColor sSceneBackgroundColor;
	static const int sTimerInterval;

private slots:
	void startSimulation();
	void stepSimulation();
	void pauseSimulation();
	void resumeSimulation();
	void stopSimulation();

};

#endif // !PREDATOR_SIMULATOR_H


