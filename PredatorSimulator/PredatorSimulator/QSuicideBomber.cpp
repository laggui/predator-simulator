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
	bounce(180); // On le fait plutôt rebondir dans le sens opposé.
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
		// Détermine la nouvelle position selon la nouvelle orientation et la vitesse
		QPointF newPosition(pos() + QPointF(qCos(qDegreesToRadians(rotation()))*mSpeed, qSin(qDegreesToRadians(rotation())) * mSpeed));
		// store la nouvelle orientation et la nouvelle position en attendant la phase 1
		setNextPos(newPosition.x(), newPosition.y());
		setNextOrientation(rotation());
	}
	else if (phase == 1) {
		// Détermine la nouvelle position selon la nouvelle orientation et la vitesse
		setPos(mNextAttributes.x, mNextAttributes.y);
		setRotation(mNextAttributes.orientation);
	}
}
