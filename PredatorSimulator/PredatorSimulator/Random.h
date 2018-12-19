#ifndef RANDOM_H
#define RANDOM_H

#include <QtGlobal>
#include <QColor>

// Fonctions utilitaires de g�n�ration de valeurs al�atoires : devraient �tre ailleurs.
double random(qreal maxValue);
int random(int maxValue);
double random(qreal minValue, qreal maxValue);
QColor randomColor();

#endif // !RANDOM_H