#include "QRunner.h"
#include <QPainter>

QRunner::QRunner(QPointF const & initialPosition, qreal initialOrientationDegrees, qreal initialSpeed, qreal scale, quint8 initialHealth, QBrush const & brush, QGraphicsItem * parent)
	: QDynamicObject(initialSpeed, brush, parent),
	  mHealthPoints{ initialHealth }
{
	setPos(initialPosition);
	setRotation(initialOrientationDegrees);
	setScale(scale);
}

void QRunner::setHP(quint8 hp)
{
	mHealthPoints = hp;
}

void QRunner::setNextAttributes(quint8 hp, QBrush const & brush)
{
	mNextAttributes.healthPoints = hp;
	mNextAttributes.brush = brush;
}

quint8 QRunner::getHP() const
{
	return mHealthPoints;
}

void QRunner::clone()
{
}

QRectF QRunner::boundingRect() const
{
	return QRectF();
}

void QRunner::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(mBrush);
	painter->drawEllipse(mShape);
}

void QRunner::advance(int phase)
{
}
