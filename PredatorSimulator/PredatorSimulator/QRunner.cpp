#include "QRunner.h"

#include "Random.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QtMath>

QRunner::QRunner(QPointF const & initialPosition, qreal initialOrientationDegrees, qreal initialSpeed, qreal size, quint8 initialHealth, QBrush const & brush, QGraphicsItem * parent)
	: QDynamicObject(initialSpeed, brush, parent),
	  mHealthPoints{ initialHealth },
	  mImmuneTime{ 0 }
{
	// Initialisation des attributs du runner
	setSize(size);
	setPos(initialPosition);
	setRotation(initialOrientationDegrees);
	setNextHP(initialHealth);
	setNextPos(initialPosition.x(), initialPosition.y());
	setNextOrientation(initialOrientationDegrees);
}

QRunner::QRunner(const QRunner & runner)
{
	// Le constructeur de copie duplique l'information d'un runner, tout en modifiant son orientation
	setPos(runner.pos());
	setRotation(runner.rotation());
	mSpeed = runner.mSpeed;	
	mHealthPoints = runner.mHealthPoints;
	mImmuneTime = runner.mImmuneTime;
	mBrush = runner.mBrush;
	mNextAttributes = runner.mNextAttributes;
	// Changer l'orientation
	mNextAttributes.orientation = qMin(355.0, 180.0 - runner.mNextAttributes.orientation + random(25.0));
	//mNextAttributes.x = 
	mShape = QRectF(runner.mShape);
}

void QRunner::setHP(quint8 hp)
{
	// Le plus bas niveau de vie d'un runner est 1, sinon cela signifie qu'il meurt
	mHealthPoints = qMax(static_cast<quint8>(1), hp);
	// Le niveau de vie du runner change aussi sa couleur (automatiquement)
	switch (mHealthPoints) {
	case 1:
		setColor(Qt::red);
		break;
	case 2:
		setColor(Qt::yellow);
		break;
	default:
		setColor(Qt::green);
		break;
	}
}

void QRunner::setSize(qreal size)
{
	// Taille minimum est 1
	mSize = qMax(1.0, size);
	// Changer la forme
	mShape.setRect(-mSize / 2, -mSize / 2, mSize, mSize);
}

void QRunner::setImmuneTime(quint8 time)
{
	mImmuneTime = qMax(static_cast<quint8>(0), time);
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

quint8 QRunner::immuneTime() const
{
	return mImmuneTime;
}

void QRunner::clone()
{
	// On ajoute un clone (constructeur de copie) du runner à la scène
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
		// Vérifier si la position a déjà été modifiée (collision avec un mur)
		if (mNextAttributes.x == pos().x() && mNextAttributes.y == pos().y()) {
			//calcul de la prochaine position
			QPointF newPosition(pos() + QPointF(qCos(qDegreesToRadians(rotation()))*mSpeed, qSin(qDegreesToRadians(rotation())) * mSpeed));
			// assignation de la nouvelle orientation et de la nouvelle position en attendant la phase 1
			setNextPos(newPosition.x(), newPosition.y());
			setNextOrientation(rotation());
		}
	}
	else if (phase == 1) {
		// Applique les attributs calculés dans la phase 0
		setPos(mNextAttributes.x, mNextAttributes.y);
		setRotation(mNextAttributes.orientation);
		setHP(mNextAttributes.healthPoints);
		if (mImmuneTime > 0) setImmuneTime(mImmuneTime - 1);
	}
}
