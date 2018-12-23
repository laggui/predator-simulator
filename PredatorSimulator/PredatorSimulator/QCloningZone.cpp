#include "QCloningZone.h"

#include "QRunner.h"
#include "QSuicideBomber.h"
#include <QPainter>


QCloningZone::QCloningZone( QPointF const & topLeft, qreal width, qreal height, qreal orientation,
	qreal yStartPos, QBrush const & brush,  QGraphicsItem * parent)
	: QWall(topLeft, width, height, orientation, brush, parent), mYStartPos{ yStartPos }
{
}

void QCloningZone::cloneAndWarp(QRunner * runner)
{
	if (runner) {
		runner->setNextPos(runner->pos().x(), mYStartPos + runner->size());
		runner->clone();
	}
}

void QCloningZone::advance(int phase)
{
	if (phase == 0) {
		// Récupérer les items qui sont en collision
		QList<QGraphicsItem *> collidingObjects = collidingItems();

		// Itérer à travers les objets en collision
		foreach(QGraphicsItem *item, collidingObjects) {
			if (auto runnerObj = dynamic_cast<QRunner*>(item)) {
				// Cloner et amener au début de la scène
				cloneAndWarp(runnerObj);
			}
			else if (auto bomberObj = dynamic_cast<QSuicideBomber*>(item)) {
				// Faire rebondir, un bomber ne peut pas être cloné
				bomberObj->bounce(mWallOrientation);
			}
		}
	}
}