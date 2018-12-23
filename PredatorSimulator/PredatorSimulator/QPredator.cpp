#include "QPredator.h"

#include "QRunner.h"
#include "QSuicideBomber.h"

#include <QPainter>
#include <QtMath>
#include <QRandomGenerator>
#include <QGraphicsScene>

const qreal QPredator::sMinSize{ 5 };
const qreal QPredator::sMaxSize{ 75 };
const qreal QPredator::sSizeIncrement{ 5 };

QPredator::QPredator(QPointF const & initialPosition, qreal initialOrientationDegrees, qreal initialSpeed, qreal size, quint8 damage, quint8 timeNoKill, QBrush const & brush, QGraphicsItem * parent)
	: QDynamicObject(initialSpeed, brush, parent),
	  mDamage{ damage },
	  mTimeNoKill{ timeNoKill },
	  mFrozen{ 0 }
{
	// Initialisation des attributs
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
	mSize = qMax(sMinSize, size);
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

void QPredator::setFrozen(quint8 freezeTime)
{
	mFrozen = freezeTime;
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
	// Pr�dateur ne se clone pas. Il ne devrait m�me pas entrer en contact avec la zone de clonage.
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
		// Ne pas mettre � jour la position si le pr�dateur est gel�
		if (!mFrozen) {
			// V�rifier si la position a d�j� �t� modifi�e (collision avec un mur)
			if (mNextAttributes.x == pos().x() && mNextAttributes.y == pos().y()) {
				// D�termine la nouvelle position selon la nouvelle orientation et la vitesse
				QPointF newPosition(pos().x() + qCos(qDegreesToRadians(rotation()))*mSpeed, pos().y());
				// store la nouvelle orientation et la nouvelle position en attendant la phase 1
				setNextPos(newPosition.x(), newPosition.y());
				setNextOrientation(rotation());
			}
		}
		else {
			--mFrozen;
		}
		// R�cup�rer les items qui sont en collision
		QList<QGraphicsItem *> collidingObjects = collidingItems();

		// It�rer � travers les objets en collision
		foreach(QGraphicsItem *item, collidingObjects) {
			if (auto runnerObj = dynamic_cast<QRunner*>(item)) {
				// Calcul du prochain niveau de vie du runner
				quint8 nextHP = runnerObj->HP() - mDamage;
				// V�rifier que le runner n'est pas immunis� (emp�che les collisions r�p�t�s)
				if (runnerObj->immuneTime() == 0) {
					const quint8 pixelOffset = 2;
					// Endommager le runner s'il a plus de 0 HP apr�s avoir �t� endommag�
					if (nextHP > 0) {
						runnerObj->setNextHP(nextHP);
						// Calcul du temps d'immunisation afin d'emp�cher les collisions r�p�t�es lorsque le runner passe � travers un pr�dateur
						quint8 immuneTime = (pos().y() + mSize / 2 + runnerObj->size() / 2 + pixelOffset - runnerObj->pos().y()) / (qSin(qDegreesToRadians(runnerObj->rotation())) * runnerObj->speed());
						runnerObj->setImmuneTime(immuneTime + 1);
					}
					else {
						// Tuer le runner s'il a moins de 0 HP apr�s avoir �t� endommag�
						kill(runnerObj);
						// Prendre en note la taille pr�c�dente
						qreal prevSize = mSize;
						// Augmenter la taille du pr�dateur
						if (mSize + sSizeIncrement < sMaxSize) {
							setNextSize(mSize + sSizeIncrement);
						}
						else {
							setNextSize(sMaxSize);
						}
						// On red�fini la prochaine position en fonction de la diff�rence de taille,
						// ce qui devrait emp�cher le cas ou un pr�dateur tue un runner (et donc grossit) avant d'entrer en collision
						// avec un mur. Sans cette modification, le pr�dateur se retrouvait dans le mur, et ne pouvait pu se d�placer (collisions r�p�t�es)
						setNextPos(mNextAttributes.x - qCos(qDegreesToRadians(rotation()))*((mSize - prevSize) / 2), mNextAttributes.y);
					}
				}

			}
			else if (auto bomberObj = dynamic_cast<QSuicideBomber*>(item)) {
				// Si c'est un bomber, le pr�dateur re�oit du dommage
				setNextSize(mSize - bomberObj->damage());
				// Tuer le bomber
				kill(bomberObj);
			}
		}
	}
	else if (phase == 1) {
		//applique les attributs calcul� dans la phase 0
		setPos(mNextAttributes.x, mNextAttributes.y);
		setRotation(mNextAttributes.orientation);
		setSize(mNextAttributes.size);
		incrementTimeNoKill();
	}
}

void QPredator::kill(QGraphicsItem * item)
{
	scene()->removeItem(item);  // on retire l'item de la liste de la scene
	delete item; // on supprime la m�moire allou�e dynamiquement li�e � l'item
	resetTimeNoKill();
}