#include "QPredator.h"
#include "QRunner.h"
#include "QSuicideBomber.h"
#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>

#include <QGraphicsScene>

const qreal QPredator::minSize{ 10 };
const qreal QPredator::maxSize{ 50 };

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
	painter->drawEllipse(mShape);
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
				if (nextHP > 0) {
					runnerObj->setNextHP(nextHP);
					// Changer sa position pour éviter les collisions multiples répétées
					/*runnerObj->setNextPos(runnerObj->pos().x() + qCos(qDegreesToRadians(runnerObj->rotation()))*(mSize+runnerObj->size()),
										  runnerObj->pos().y() + qSin(qDegreesToRadians(runnerObj->rotation()))*(mSize + runnerObj->size()));*/
				}
				else {
					kill(runnerObj);
					if (mSize < maxSize) setNextSize(++mSize);
				}
				
			}
			else if (auto bomberObj = dynamic_cast<QSuicideBomber*>(item)) {
				setNextSize(mSize - bomberObj->damage());
				kill(bomberObj);
				if (mNextAttributes.size < minSize) { setNextSize(minSize); }
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
	scene()->QGraphicsScene::removeItem(item);  // on retire l'item de la liste de la scene
	delete item; // on supprime la mémoire allouée dynamiquement liée à l'item
	resetTimeNoKill();
}