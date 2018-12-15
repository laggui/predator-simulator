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
	int healthPoints;
	QBrush brush;
};

struct PredatorAttributes : public Position
{
	int damage;
	int timeNoKill;
	qreal scaleFactor;
};

#endif // !ATTRIBUTES_H
