#include "QCloningZone.h"

#include "QPredator.h"
#include "QRunner.h"
#include "QSuicideBomber.h"
#include <QPainter>


QCloningZone::QCloningZone( QPointF const & topLeft, qreal width, qreal height, qreal orientation,
	qreal yStartPos, QBrush const & brush,  QGraphicsItem * parent)
	: QWall(topLeft, width, height, orientation, brush, parent), mYStartPos{ yStartPos }
{
	mWallOrientation = orientation;
	mShape.setRect(-width / 2, -height / 2, width, height);
	setPos(topLeft.x() + width / 2, topLeft.y() + height / 2);
}

void QCloningZone::cloneAndWarp(QRunner * runner)
{
	runner->setNextPos(runner->pos().x(), mYStartPos);
	runner->clone();
}

void QCloningZone::advance(int phase)
{
	if (phase == 0) {
		// Récupérer les items qui sont en collision
		QList<QGraphicsItem *> collidingObjects = collidingItems();

		// Itérer à travers les objets en collision
		foreach(QGraphicsItem *item, collidingObjects) {
			if (auto predatorObj = dynamic_cast<QPredator*>(item)) {
				// Les QPredator ne devraient jamais entrés en collision avec la clonning zone
			}
			else if (auto runnerObj = dynamic_cast<QRunner*>(item)) {
				cloneAndWarp(dynamic_cast<QRunner*>(item));
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