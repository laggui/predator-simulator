#include "QPredator.h"
#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

#include <QGraphicsScene>

QPredator::QPredator(QPointF const & initialPosition, qreal initialOrientationDegrees, qreal initialSpeed, qreal scale, quint8 damage, quint8 timeNoKill, QBrush const & brush, QGraphicsItem * parent)
	: QDynamicObject(initialSpeed, brush, parent),
	  mDamage{ damage },
	  mTimeNoKill{ timeNoKill }
{
	mShape.setRect(2, 2, 4, 4);
	setPos(initialPosition);
	setRotation(initialOrientationDegrees);
	setScale(scale);
}

void QPredator::setDamage(quint8 damage)
{
	mDamage = damage;
}

void QPredator::resetTimeNoKill()
{
	mTimeNoKill = 0;
}

void QPredator::incrementTimeNoKill()
{
	++mTimeNoKill;
}

void QPredator::setNextPos(qreal x, qreal y)
{
	mNextAttributes.x = x;
	mNextAttributes.y = y;
}

void QPredator::setNextOrientation(qreal orientation)
{
	mNextAttributes.orientation = orientation;
}

void QPredator::setNextTimeNoKill(quint8 timeNoKill)
{
	mNextAttributes.timeNoKill = timeNoKill;
}

void QPredator::setNextScale(qreal scale)
{
	mNextAttributes.scaleFactor = scale;
}

quint8 QPredator::getDamage() const
{
	return mDamage;
}

quint8 QPredator::getTimeNoKill() const
{
	return mTimeNoKill;
}

void QPredator::clone()
{
}

QRectF QPredator::boundingRect() const
{
	return QRectF(mShape);
}

void QPredator::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(mBrush);
	painter->drawEllipse(mShape);
}

void QPredator::advance(int phase)
{
	if (phase == 0) {
		// do nothing
	}
	else if (phase == 1) {
		//static constexpr const qreal maxDeltaOrientation{ 12.5 }; // in °
		// Détermine la nouvelle orientation selon une variation aléatoire dans l'intervalle [-maxDeltaOrientation, maxDeltaOrientation]
		//qreal newOrientationDegrees{ rotation() + QRandomGenerator::global()->bounded(2.0 * maxDeltaOrientation) - maxDeltaOrientation };
		//qreal newOrientationRadians{ qDegreesToRadians(newOrientationDegrees) };
		// Détermine la nouvelle position selon la nouvelle orientation et la vitesse
		//QPointF newPosition(pos() + QPointF(qCos(newOrientationRadians), qSin(newOrientationRadians)) * mSpeed);
		qreal rot = rotation();
		QPointF newPosition(pos() + QPointF(qCos(rotation()), qSin(rotation())) * mSpeed);
		// Si la nouvelle position est à l'extérieur de la scène, la nouvelle position est téléportée à la région opposée de la scène
		warp(newPosition);

		// Applique la nouvelle orientation et la nouvelle position
		//setRotation(newOrientationDegrees);
		setPos(newPosition);
	}
}

void QPredator::kill(QDynamicObject * object)
{
}

qreal QPredator::warp(qreal value, qreal begin, qreal end) {
	const qreal width = end - begin;
	return value - qFloor((value - begin) / width) * width;
}

void QPredator::warp(QPointF & point) {
	point.setX(warp(point.x(), scene()->sceneRect().left(), scene()->sceneRect().right()));
	point.setY(warp(point.y(), scene()->sceneRect().top(), scene()->sceneRect().bottom()));
}
