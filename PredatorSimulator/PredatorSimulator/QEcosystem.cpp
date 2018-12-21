#include "QEcosystem.h"

#include "Random.h"
#include "QPredator.h"
#include "QRunner.h"
#include "QSuicideBomber.h"
#include <QGraphicsScene>
#include <QPainter>

QEcosystem::QEcosystem(unsigned int timerInterval, unsigned int timeAlive, QPointF const & sceneCenter, qreal width,
					   qreal height, QBrush const & brush, QGraphicsItem * parent)
	: QBasicItem(brush, parent),
	  mTimeAlive{ timeAlive },
	  mEvolveTime{ timerInterval }
{
	mShape.setRect(sceneCenter.x() - width / 2, sceneCenter.y() - height / 2, width, height);
	setPos(sceneCenter);
}

unsigned int QEcosystem::timeAlive()
{
	return mTimeAlive;
}

void QEcosystem::tick()
{
	++mTimeAlive;
}

QRectF QEcosystem::boundingRect() const
{
	return mShape;
}

void QEcosystem::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(mBrush);
	painter->drawRect(mShape);
}

void QEcosystem::advance(int phase)
{
	if (phase == 0) {
		//met � jour mTimeAlive
		tick();
		// R�cup�rer les items qui font parti de l'�cosyst�me (dans la sc�ne)
		QList<QGraphicsItem *> sceneItems = scene()->items();
		 //It�rer � travers les objets et v�rifier les pr�dateurs
		foreach(QGraphicsItem *item, sceneItems) {
			if (auto predatorObj = dynamic_cast<QPredator*>(item)) {
				if (predatorObj->timeNoKill() == (mEvolveTime/5)) {
					// Diminuer la grosseur du pr�dateur
					predatorObj->setNextSize(predatorObj->size() - 1);
					predatorObj->setNextTimeNoKill(0);
				}
			}
		}

		if ((mTimeAlive %  (mEvolveTime/10)) == 0) {
			// Un runner ou bomber nait (choix al�atoire, avec plus de chance que ce soit un runner)
			if (random(5)) {
				scene()->addItem(
							new QRunner(
							QPointF(random(-250,250), -270),		// position En haut de la boites
							random(20, 160),						// Orient� vers le bas rotation 0 = vers la droite
							5,		//vitesse
							10,		//size
							3, // hp
							Qt::green));
			}
			else {
			/*	scene()->addItem(
					new QSuicideBomber();*/
			}
		}
	}
	else if (phase == 1) {

	}
}