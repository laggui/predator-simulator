#include "QPredator.h"
#include "QRunner.h"
#include "QSuicideBomber.h"
#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

#include <QGraphicsScene>

const qreal QPredator::minScale{ 5 };
const qreal QPredator::maxScale{ 25 };

QPredator::QPredator(QPointF const & initialPosition, qreal initialOrientationDegrees, qreal initialSpeed, qreal scale, quint8 damage, quint8 timeNoKill, QBrush const & brush, QGraphicsItem * parent)
	: QDynamicObject(initialSpeed, brush, parent),
	  mDamage{ damage },
	  mTimeNoKill{ timeNoKill }
{
	mShape.setRect(2, 2, 4, 4);
	setPos(initialPosition);
	setRotation(initialOrientationDegrees);
	setScale(scale);
	setNextScale(scale);
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
		// Détermine la nouvelle position selon la nouvelle orientation et la vitesse
		QPointF newPosition(pos() + QPointF(qCos(qDegreesToRadians(rotation()))*mSpeed, qSin(qDegreesToRadians(rotation())) * mSpeed));
		// store la nouvelle orientation et la nouvelle position en attendant la phase 1
		setNextPos(newPosition.x(), newPosition.y());
		setNextOrientation(rotation());

		// Récupérer les items qui sont en collision
		QList<QGraphicsItem *> collidingObjects = collidingItems();

		// Itérer à travers les objets en collision
		foreach(QGraphicsItem *item, collidingObjects) {
			if (auto runnerObj = dynamic_cast<QRunner*>(item)) {
				runnerObj->setHP(runnerObj->getHP() - mDamage);
				if (scale() < maxScale) { setNextScale(scale() + 1); }
			}
			else if (auto bomberObj = dynamic_cast<QSuicideBomber*>(item)) {
				setNextScale(scale() * bomberObj->getDamage());
				if (mNextAttributes.scaleFactor < minScale) { setNextScale(minScale); }
			}
		}
	}
	else if (phase == 1) {
		//applique les attributs calculé dans la phase 0
		setPos(mNextAttributes.x, mNextAttributes.y);
		setRotation(mNextAttributes.orientation);
		setScale(mNextAttributes.scaleFactor);
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
