#include "QRunner.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>
#include "QWall.h"
#include "Random.h"

const qreal QRunner::sSize = 4;

QRunner::QRunner(QPointF const & initialPosition, qreal initialOrientationDegrees, qreal initialSpeed, qreal scale, quint8 initialHealth, QBrush const & brush, QGraphicsItem * parent)
	: QDynamicObject(initialSpeed, brush, parent),
	  mHealthPoints{ initialHealth }
{
	setPos(initialPosition);
	setRotation(initialOrientationDegrees);
	setScale(scale);
	mShape.setRect(-sSize / 2, -sSize / 2, sSize, sSize);

}

QRunner& QRunner::operator=(QRunner & runnerToCopy)
{
	if (&runnerToCopy != this) {
		setPos(runnerToCopy.pos());
		setRotation(runnerToCopy.rotation());
		mSpeed = runnerToCopy.mSpeed;
		setScale(runnerToCopy.scale());
		mHealthPoints = runnerToCopy.mHealthPoints;
		mBrush = runnerToCopy.mBrush;
		mNextAttributes = runnerToCopy.mNextAttributes;
	}
	return *this;
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

quint8 QRunner::getHP() const
{
	return mHealthPoints;
}

void QRunner::clone()
{
	qreal rotationModifier = 90.0;
	QGraphicsScene * gScene = scene();
	QRunner * newRunner{ new QRunner };
	*newRunner = *this;
	newRunner->setPos(mNextAttributes.x, mNextAttributes.y);
	newRunner->bounce(rotationModifier);
	gScene->addItem(newRunner);
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
		//calcul de la prochaine position
		QPointF newPosition(pos() + QPointF(qCos(qDegreesToRadians(rotation()))*mSpeed, qSin(qDegreesToRadians(rotation())) * mSpeed));
		// assignation de la nouvelle orientation et de la nouvelle position en attendant la phase 1
		setNextPos(newPosition.x(), newPosition.y());
		setNextOrientation(rotation());

	}
	else if (phase == 1) {
		//applique les attributs calculé dans la phase 0
		setPos(mNextAttributes.x, mNextAttributes.y);
		setRotation(mNextAttributes.orientation);
	}
}
