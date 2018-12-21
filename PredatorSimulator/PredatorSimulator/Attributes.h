#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QtGlobal>

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
	quint32 timeNoKill;
	qreal size;
};

#endif // !ATTRIBUTES_H
