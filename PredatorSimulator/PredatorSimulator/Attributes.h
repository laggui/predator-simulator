#ifndef ATTRIBUTES_H
#define ATTRIBUTES_H

#include <QtGlobal>
#include <QBrush>

struct Position
{
	qreal x;
	qreal y;
};


struct RunnerAttributes : public Position
{
	quint8 healthPoints;
	QBrush brush;
};

struct PredatorAttributes : public Position
{
	quint8 damage;
	quint8 timeNoKill;
	qreal scaleFactor;
};

#endif // !ATTRIBUTES_H
