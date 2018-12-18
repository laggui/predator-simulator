#include "QSuicideBomber.h"
#include <QPainter>

QSuicideBomber::QSuicideBomber(QPointF const & initialPosition, qreal initialOrientationDegrees, qreal initialSpeed, qreal scale, qreal damage, QBrush const & brush, QGraphicsItem * parent)
	: QDynamicObject(initialSpeed, brush, parent),
	  mDamage{ damage }
{
	setPos(initialPosition);
	setRotation(initialOrientationDegrees);
	setScale(scale);
}

void QSuicideBomber::setDamage(qreal damage)
{
	if (damage > 0 && damage <= 1) {
		mDamage = damage;
	}
	else {
		mDamage = 0.9; // valeur par défaut si la valeur spécifiée est invalide
	}
}

void QSuicideBomber::setNextPos(qreal x, qreal y)
{
	mNextAttributes.x = x;
	mNextAttributes.y = y;
}

void QSuicideBomber::setNextOrientation(qreal orientation)
{
	mNextAttributes.orientation = orientation;
}

qreal QSuicideBomber::getDamage() const
{
	return mDamage;
}

void QSuicideBomber::clone()
{
}

QRectF QSuicideBomber::boundingRect() const
{
	return QRectF();
}

void QSuicideBomber::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(mBrush);
	painter->drawPolygon(mShape);
}

void QSuicideBomber::advance(int phase)
{
}
