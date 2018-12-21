#include "QPredator.h"
#include "QRunner.h"
#include "QSuicideBomber.h"
#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

#include <QGraphicsScene>

const qreal QPredator::sMinSize{ 10 };
const qreal QPredator::sMaxSize{ 75 };
const qreal QPredator::sSizeIncrement{ 5 };

QPredator::QPredator(QPointF const & initialPosition, qreal initialOrientationDegrees, qreal initialSpeed, qreal size, quint8 damage, quint8 timeNoKill, QBrush const & brush, QGraphicsItem * parent)
	: QDynamicObject(initialSpeed, brush, parent),
	  mDamage{ damage },
	  mTimeNoKill{ timeNoKill }
{
	setSize(size);
	setPos(initialPosition);
	setRotation(initialOrientationDegrees);
	setNextSize(mSize);
	setNextPos(initialPosition.x(), initialPosition.y());
}

void QPredator::setDamage(quint8 damage)
{
	mDamage = damage;
}

void QPredator::setSize(qreal size)
{
	mSize = qMax(1.0, size);
	mShape.setRect(-mSize / 2, -mSize / 2, mSize, mSize);
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

void QPredator::setNextTimeNoKill(quint32 timeNoKill)
{
	mNextAttributes.timeNoKill = timeNoKill;
}

void QPredator::setNextSize(qreal size)
{
	mNextAttributes.size = size;
}

quint8 QPredator::damage() const
{
	return mDamage;
}

quint32 QPredator::timeNoKill() const
{
	return mTimeNoKill;
}

qreal QPredator::size() const
{
	return mSize;
}

void QPredator::clone()
{
	// Prédateur ne se clone pas. Il ne devrait même pas entrer en contact avec la zone de clonage.
}

QRectF QPredator::boundingRect() const
{
	return mShape;
}

void QPredator::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(mBrush);
	painter->drawRect(mShape);
}

void QPredator::advance(int phase)
{
	if (phase == 0) {
		// Vérifier si la position a déjà été modifiée (collision avec un mur)
		if (mNextAttributes.x == pos().x() && mNextAttributes.y == pos().y()) {
			// Détermine la nouvelle position selon la nouvelle orientation et la vitesse
			QPointF newPosition(pos().x() + qCos(qDegreesToRadians(rotation()))*mSpeed, pos().y());
			// store la nouvelle orientation et la nouvelle position en attendant la phase 1
			setNextPos(newPosition.x(), newPosition.y());
			setNextOrientation(rotation());
		}
		// Récupérer les items qui sont en collision
		QList<QGraphicsItem *> collidingObjects = collidingItems();

		// Itérer à travers les objets en collision
		foreach(QGraphicsItem *item, collidingObjects) {
			if (auto runnerObj = dynamic_cast<QRunner*>(item)) {
				quint8 nextHP =  runnerObj->HP() - mDamage;
				if (runnerObj->immuneTime() == 0) {
					const quint8 pixelOffset = 2;
					if (nextHP > 0) {
						runnerObj->setNextHP(nextHP);
						// Calcul du temps d'immunisation afin d'empêcher les collisions répétées lorsque le runner passe à travers un prédateur
						quint8 immuneTime = (pos().y() + mSize / 2 + runnerObj->size() / 2 + pixelOffset  - runnerObj->pos().y()) / (qSin(qDegreesToRadians(runnerObj->rotation())) * runnerObj->speed());
						runnerObj->setImmuneTime(immuneTime + 1);
					}
					else {
						kill(runnerObj);
						if (mSize < sMaxSize) setNextSize(mSize + sSizeIncrement);
					}
				}
				
			}
			else if (auto bomberObj = dynamic_cast<QSuicideBomber*>(item)) {
				setNextSize(mSize - bomberObj->damage());
				kill(bomberObj);
				if (mNextAttributes.size < sMinSize) { setNextSize(sMinSize); }
			}
		}
	}
	else if (phase == 1) {
		//applique les attributs calculé dans la phase 0
		setPos(mNextAttributes.x, mNextAttributes.y);
		setRotation(mNextAttributes.orientation);
		setSize(mNextAttributes.size);
		incrementTimeNoKill();
	}
}

void QPredator::kill(QGraphicsItem * item)
{
	// remove from scene mGraphicsScene
	scene()->removeItem(item);  // on retire l'item de la liste de la scene
	delete item; // on supprime la mémoire allouée dynamiquement liée à l'item
	resetTimeNoKill();
}