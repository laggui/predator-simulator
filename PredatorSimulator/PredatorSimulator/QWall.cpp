#include "QWall.h"

#include "QPredator.h"
#include "QRunner.h"
#include "QSuicideBomber.h"
#include <QPainter>



QWall::QWall(QPointF const & topLeft, qreal width, qreal height, qreal orientation, QBrush const & brush, QGraphicsItem * parent)
	: QBasicItem(brush, parent)
{
	
		mWallOrientation = orientation;
		mShape.setRect(-width / 2, -height / 2, width, height);
		setPos(topLeft.x() + width / 2, topLeft.y() + height / 2);
	
}

QRectF QWall::boundingRect() const
{
	return mShape;
}

void QWall::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(mBrush);
	painter->drawRect(mShape);
}

void QWall::advance(int phase)
{
	if (phase == 0) {
		// Récupérer les items qui sont en collision
		QList<QGraphicsItem *> collidingObjects = collidingItems();

		// Itérer à travers les objets en collision
		foreach(QGraphicsItem *item, collidingObjects) {
			if (auto predatorObj = dynamic_cast<QPredator*>(item)) {
				predatorObj->bounce(mWallOrientation);
			}
			else if (auto runnerObj = dynamic_cast<QRunner*>(item)) {
				runnerObj->bounce(mWallOrientation);
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