#include "QEcosystem.h"

#include "Random.h"
#include "QPredator.h"
#include "QRunner.h"
#include "QSuicideBomber.h"
#include <QGraphicsScene>
#include <QPainter>

const qreal QEcosystem::sMembersSize{ 10 };
const qreal QEcosystem::sMembersSpeed{ 5 };
const quint8 QEcosystem::sRunnerHP{ 3 };
const qreal QEcosystem::sRunnersOrientationOffset{ 20 };
const qreal QEcosystem::sBomberDamage{ 5 };
const qreal QEcosystem::sBomberOrientation{ 90 };
const qreal QEcosystem::sPredatorDecrement{ 5 };

QEcosystem::QEcosystem(QSize spawnSize, unsigned int timerInterval, unsigned int timeAlive, QPointF const & sceneCenter, qreal width,
					   qreal height, QBrush const & brush, QGraphicsItem * parent)
	: QBasicItem(brush, parent),
	  mTimeAlive{ timeAlive },
	  mEvolveTime{ timerInterval },
	  mSpawnSize { spawnSize }
{
	// Initialisation de la forme et position
	mShape.setRect(sceneCenter.x() - width / 2, sceneCenter.y() - height / 2, width, height);
	setPos(sceneCenter);
}

unsigned int QEcosystem::timeAlive() const
{
	return mTimeAlive;
}

unsigned int QEcosystem::evolveTime() const
{
	return mEvolveTime;
}

void QEcosystem::resetTimeAlive()
{
	mTimeAlive = 0;
}

void QEcosystem::setEvolveTime(unsigned int time)
{
	mEvolveTime = time;
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
		// Mettre � jour mTimeAlive
		tick();
		// R�cup�rer les items qui font parti de l'�cosyst�me (dans la sc�ne)
		QList<QGraphicsItem *> sceneItems = scene()->items();
		 //It�rer � travers les objets et v�rifier les pr�dateurs
		foreach(QGraphicsItem *item, sceneItems) {
			if (auto predatorObj = dynamic_cast<QPredator*>(item)) {
				if (predatorObj->timeNoKill() == mEvolveTime) {
					// Diminuer la grosseur du pr�dateur
					predatorObj->setNextSize(predatorObj->size() - sPredatorDecrement);
					predatorObj->setNextTimeNoKill(0);
				}
			}
		}

		if ((mTimeAlive %  (mEvolveTime/2)) == 0) {
			// Un runner ou bomber nait (choix al�atoire, avec plus de chance que ce soit un runner)
			if (random(3)) {
				scene()->addItem(
							new QRunner(
							QPointF(random(-mSpawnSize.width()/2 + sMembersSize, mSpawnSize.width() / 2 - sMembersSize), -mSpawnSize.height()/2 + sMembersSize), // position
							random(0 + sRunnersOrientationOffset, 180 - sRunnersOrientationOffset),	// orientation
							sMembersSpeed, // vitesse
							sMembersSize, // taille
							sRunnerHP, // vie
							Qt::green)); // couleur
			}
			else {
				scene()->addItem(
					// Tous les lit�raux ici devraient �tre cr��s dans des constantes symboliques!
					new QSuicideBomber(
						QPointF(random(-mSpawnSize.width() / 2 + sMembersSize, mSpawnSize.width() / 2 - sMembersSize), -mSpawnSize.height() / 2 + sMembersSize), // position
						sBomberOrientation, // orientation
						sMembersSpeed, // vitesse
						sMembersSize, // taille
						sBomberDamage, // dommage
						Qt::white)); // couleur
			}
		}
	}
}