#include "QRunner.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>
#include "QWall.h"
#include "Random.h"

QRunner::QRunner(QPointF const & initialPosition, qreal initialOrientationDegrees, qreal initialSpeed, qreal size, quint8 initialHealth, QBrush const & brush, QGraphicsItem * parent)
	: QDynamicObject(initialSpeed, brush, parent),
	  mHealthPoints{ initialHealth }
{
	setSize(size);
	setPos(initialPosition);
	setRotation(initialOrientationDegrees);
	mShape.setRect(-mSize / 2, -mSize / 2, mSize, mSize);
	setNextPos(initialPosition.x(), initialPosition.y());
}

QRunner::QRunner(const QRunner & runner)
{
	setPos(runner.pos());
	setRotation(runner.rotation());
	mSpeed = runner.mSpeed;	
	mHealthPoints = runner.mHealthPoints;
	mBrush = runner.mBrush;
	mNextAttributes = runner.mNextAttributes;
	// Changer l'orientation
	mNextAttributes.orientation = runner.mNextAttributes.orientation + random(-5, 5);
	mShape = QRectF(runner.mShape);
}

void QRunner::setHP(quint8 hp)
{
	QBrush nextColor;
	const QColor red(Qt::red);
	const QColor green(Qt::green);
	const QColor yellow(Qt::yellow);

	mHealthPoints = hp;
	switch (mHealthPoints) {
	case 1:
		nextColor.setColor(red);
		setColor(nextColor);
		break;
	case 2:
		nextColor.setColor(yellow);
		setColor(nextColor);
		break;
	case 3:
		nextColor.setColor(green);
		setColor(nextColor);
		break;
	}
}

void QRunner::setSize(qreal size)
{
	mSize = qMax(1.0, size);
}



void QRunner::setNextPos(qreal x, qreal y)
{
	mNextAttributes.x = x;
	mNextAttributes.y = y;
}

void QRunner::setNextOrientation(qreal orientation)
{
	mNextAttributes.orientation = orientation;
}

void QRunner::setNextHP(quint8 hp)
{
	mNextAttributes.healthPoints = hp;
}

quint8 QRunner::HP() const
{
	return mHealthPoints;
}

qreal QRunner::size() const
{
	return mSize;
}

void QRunner::clone()
{
	QRunner * newRunner{ new QRunner(*this) };
	scene()->addItem(newRunner);
}

QRectF QRunner::boundingRect() const
{
	return mShape;
}

void QRunner::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(mBrush);
	painter->drawEllipse(mShape);
}

void QRunner::advance(int phase)
{
	if (phase == 0) {
		// V�rifier si la position a d�j� �t� modifi�e (collision avec un mur)
		if (mNextAttributes.x == pos().x() && mNextAttributes.y == pos().y()) {
			//calcul de la prochaine position
			QPointF newPosition(pos() + QPointF(qCos(qDegreesToRadians(rotation()))*mSpeed, qSin(qDegreesToRadians(rotation())) * mSpeed));
			// assignation de la nouvelle orientation et de la nouvelle position en attendant la phase 1
			setNextPos(newPosition.x(), newPosition.y());
			setNextOrientation(rotation());
		}
	}
	else if (phase == 1) {
		//applique les attributs calcul� dans la phase 0
		setPos(mNextAttributes.x, mNextAttributes.y);
		setRotation(mNextAttributes.orientation);
		setHP(mNextAttributes.healthPoints);
	}
}
