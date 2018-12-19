#include "QRunner.h"
#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

QRunner::QRunner(QPointF const & initialPosition, qreal initialOrientationDegrees, qreal initialSpeed, qreal scale, quint8 initialHealth, QBrush const & brush, QGraphicsItem * parent)
	: QDynamicObject(initialSpeed, brush, parent),
	  mHealthPoints{ initialHealth }
{
	setPos(initialPosition);
	setRotation(initialOrientationDegrees);
	setScale(scale);
	mShape.setRect(2, 2, 4, 4);

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
}

QRectF QRunner::boundingRect() const
{
	return QRectF(mShape);
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
		// do nothing
		static constexpr const qreal maxDeltaOrientation{ 12.5 }; // in �
		// D�termine la nouvelle orientation selon une variation al�atoire dans l'intervalle [-maxDeltaOrientation, maxDeltaOrientation]
		qreal newOrientationDegrees{ rotation() + QRandomGenerator::global()->bounded(2.0 * maxDeltaOrientation) - maxDeltaOrientation };

		//S'assure que le runner ne remonte pas en limitant la rotation a 180-0
		if (newOrientationDegrees < 0)
		{
			newOrientationDegrees = 0 + (0 - newOrientationDegrees);
		}
		if (newOrientationDegrees > 180)
		{
			newOrientationDegrees = 180 - (newOrientationDegrees - 180);
		}
		qreal newOrientationRadians{ qDegreesToRadians(newOrientationDegrees) };
		// D�termine la nouvelle position selon la nouvelle orientation et la vitesse
		QPointF newPosition(pos() + QPointF(qCos(newOrientationRadians), qSin(newOrientationRadians)) * mSpeed);
		// Si la nouvelle position est � l'ext�rieur de la sc�ne, la nouvelle position est t�l�port�e � la r�gion oppos�e de la sc�ne
		//warp(newPosition);
		//setPos(newPosition.x(), newPosition.y());
		//setRotation(newOrientationDegrees);
		// store la nouvelle orientation et la nouvelle position en attendant la phase 1
		setNextPos(newPosition.x(), newPosition.y());
		setNextOrientation(newOrientationDegrees);
	
	}
	else if (phase == 1) {
		//applique les attributs calcul� dans la phase 0
		setPos(mNextAttributes.x, mNextAttributes.y);
		setRotation(mNextAttributes.orientation);
	}
}
