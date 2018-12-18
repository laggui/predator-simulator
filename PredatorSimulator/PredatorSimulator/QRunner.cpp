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

void QRunner::setHp(int hp)
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
	}
	else if (phase == 1) {
		static constexpr const qreal maxDeltaOrientation{ 12.5 }; // in °
		// Détermine la nouvelle orientation selon une variation aléatoire dans l'intervalle [-maxDeltaOrientation, maxDeltaOrientation]
		qreal newOrientationDegrees{ rotation() + QRandomGenerator::global()->bounded(2.0 * maxDeltaOrientation) - maxDeltaOrientation };
		qreal newOrientationRadians{ qDegreesToRadians(newOrientationDegrees) };
		// Détermine la nouvelle position selon la nouvelle orientation et la vitesse
		QPointF newPosition(pos() + QPointF(qCos(newOrientationRadians), qSin(newOrientationRadians)) * mSpeed);
		// Si la nouvelle position est à l'extérieur de la scène, la nouvelle position est téléportée à la région opposée de la scène
		//warp(newPosition);

		// Applique la nouvelle orientation et la nouvelle position
		setRotation(newOrientationDegrees);
		setPos(newPosition);
	}
}
