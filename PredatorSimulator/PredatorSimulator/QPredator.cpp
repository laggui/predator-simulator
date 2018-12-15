#include "QPredator.h"



QPredator::QPredator()
{
}


QPredator::~QPredator()
{
}

void QPredator::setDamage(int damage)
{
	mDamage = damage;
}

void QPredator::resetTimeNoKill()
{
	mTimeNoKill = 0;
}

void QPredator::incrementTimeNoKill()
{
	++mTimeNoKill;
}

void QPredator::setNextAttributes(int damage, int timeNoKill, qreal scaleFactor)
{
	mNextAttributes.damage = damage;
	mNextAttributes.timeNoKill = timeNoKill;
	mNextAttributes.scaleFactor = scaleFactor;
}

int QPredator::getDamage() const
{
	return mDamage;
}

int QPredator::getTimeNoKill() const
{
	return mTimeNoKill;
}

void QPredator::clone()
{
}

QRectF QPredator::boundingRect() const
{
	return QRectF();
}

void QPredator::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
}

void QPredator::advance(int phase)
{
}

void QPredator::kill(QDynamicObject * object)
{
}
