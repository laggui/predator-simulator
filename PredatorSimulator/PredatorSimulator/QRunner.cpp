#include "QRunner.h"
#include "qgraphicsscene.h"
#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>
#include "QWall.h"
#include "Random.h"

QRunner::QRunner(QPointF const & initialPosition, qreal initialOrientationDegrees, qreal initialSpeed, qreal scale, quint8 initialHealth, QBrush const & brush, QGraphicsItem * parent)
	: QDynamicObject(initialSpeed, brush, parent),
	  mHealthPoints{ initialHealth }
{
	setPos(initialPosition);
	setRotation(initialOrientationDegrees);
	setScale(scale);
	mShape.setRect(2, 2, 4, 4);

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
	qreal test; 
	if (phase == 0) {
		// do nothing
		//static constexpr const qreal maxDeltaOrientation{ 12.5 }; // in °
		// Détermine la nouvelle orientation selon une variation aléatoire dans l'intervalle [-maxDeltaOrientation, maxDeltaOrientation]
		//qreal newOrientationDegrees{ rotation() + QRandomGenerator::global()->bounded(2.0 * maxDeltaOrientation) - maxDeltaOrientation };
//		test = random(0, 1);
		//S'assure que le runner ne remonte pas en limitant la rotation a 180-0
		//if (newOrientationDegrees < 0)
		//{
		//	newOrientationDegrees = 0 + (0 - newOrientationDegrees);
		//}
		//if (newOrientationDegrees > 180)
		//{
		//	newOrientationDegrees = 180 - (newOrientationDegrees - 180);
		//}
		//qreal orientationRadians{ qDegreesToRadians(newOrientationDegrees) };
		// Détermine la nouvelle position selon la nouvelle orientation et la vitesse
		QPointF newPosition(pos() + QPointF(qCos(qDegreesToRadians(rotation()))*mSpeed, qSin(qDegreesToRadians(rotation())) * mSpeed));
		// store la nouvelle orientation et la nouvelle position en attendant la phase 1
		setNextPos(newPosition.x(), newPosition.y());
		setNextOrientation(rotation());


	
		// Récupérer les items qui sont en collision
		QList<QGraphicsItem *> collidingItemsList = collidingItems(); // Par défaut: les items qui overlap avec la shape de l'item et les items qui touchent au contour de l'item

		// Itérer à travers les items et vérifier leur type
		/*foreach(QGraphicsItem *item, collidingItemsList) {
			if (auto classeUn = dynamic_cast<QWall*>(item)) {
				bounce(rotation()-90);
			}
			
		}
*/

	}
	else if (phase == 1) {
		//applique les attributs calculé dans la phase 0
		setPos(mNextAttributes.x, mNextAttributes.y);
		setRotation(mNextAttributes.orientation);
	}
}
