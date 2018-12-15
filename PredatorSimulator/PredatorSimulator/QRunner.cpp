#include "QRunner.h"



QRunner::QRunner()
{
}


QRunner::~QRunner()
{
}

void QRunner::setHP(int hp)
{
	mHealthPoints = hp;
}

void QRunner::setNextAttributes(int hp, QBrush const & brush)
{
	mNextAttributes.healthPoints = hp;
	mNextAttributes.brush = brush;
}

int QRunner::getHP() const
{
	return mHealthPoints;
}

void QRunner::clone()
{
}

QRectF QRunner::boundingRect() const
{
	return QRectF();
}

void QRunner::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
}

void QRunner::advance(int phase)
{
}
