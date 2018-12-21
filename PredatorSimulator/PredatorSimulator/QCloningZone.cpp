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
	runner->setNextPos(runner->pos().x(), mYStartPos + runner->scale());
	runner->clone();
}

void QCloningZone::advance(int phase)
{
	if (phase == 0) {
		// Récupérer les items qui sont en collision
		QList<QGraphicsItem *> collidingObjects = collidingItems();

		// Itérer à travers les objets en collision
		foreach(QGraphicsItem *item, collidingObjects) {
			if (auto runnerObj = dynamic_cast<QRunner*>(item)) {
				cloneAndWarp(runnerObj);
			}
			else if (auto bomberObj = dynamic_cast<QSuicideBomber*>(item)) {
				bomberObj->bounce(mWallOrientation);
			}
		}
	}
	else if (phase == 1) {
		// do nothing
	}
}