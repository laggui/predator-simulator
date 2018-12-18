#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QtGlobal>
#include <QBrush>

struct Attributes
{
	qreal x;
	qreal y;
	qreal orientation;
};


struct RunnerAttributes : public Attributes
{
	quint8 healthPoints;
};

struct PredatorAttributes : public Attributes
{
	quint8 damage;
	quint8 timeNoKill;
	qreal scaleFactor;
};

#endif // !ATTRIBUTES_H
