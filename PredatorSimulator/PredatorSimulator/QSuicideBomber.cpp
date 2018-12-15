#include "QSuicideBomber.h"



QSuicideBomber::QSuicideBomber()
{
}


QSuicideBomber::~QSuicideBomber()
{
}

void QSuicideBomber::setDamage(qreal damage)
{
	if (damage > 0 && damage < 1) {
		mDamage = damage;
	}
	else {
		mDamage = 0.9; // valeur par défaut si la valeur spécifiée est invalide
	}
}

void QSuicideBomber::setNextpos(qreal x, qreal y)
{
	mNextPos.x = x;
	mNextPos.y = y;
}

qreal QSuicideBomber::getDamage() const
{
	return mDamage;
}

void QSuicideBomber::clone()
{
}

QRectF QSuicideBomber::boundingRect() const
{
	return QRectF();
}

void QSuicideBomber::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
}

void QSuicideBomber::advance(int phase)
{
}
