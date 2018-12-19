#include "QSuicideBomber.h"
#include <QtMath>
#include <QPainter>

QSuicideBomber::QSuicideBomber(QPointF const & initialPosition, qreal initialOrientationDegrees, qreal initialSpeed, qreal scale, qreal damage, QBrush const & brush, QGraphicsItem * parent)
	: QDynamicObject(initialSpeed, brush, parent),
	  mDamage{ damage }
{
	mShape << QPointF(0, 0)
		<< QPointF(-0.25, 0.5)
		<< QPointF(1, 0)
		<< QPointF(-0.25, -0.5);

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
	// N'est pas cloné.
}

QRectF QSuicideBomber::boundingRect() const
{
	return QRectF(-0.25 * scale(), -0.5 * scale(), 1.0 * scale(), 1.25 * scale());
}

void QSuicideBomber::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(mBrush);
	painter->drawPolygon(mShape);
}

void QSuicideBomber::advance(int phase)
{
	if (phase == 0) {
		// do nothing
	}
	else if (phase == 1) {
		// Détermine la nouvelle position selon la nouvelle orientation et la vitesse
		QPointF newPosition(pos() + QPointF(0, 1) * mSpeed);
		setPos(newPosition);
	}
}
