#ifndef RANDOM_H
#define RANDOM_H

#include <QtGlobal>
#include <QColor>

// Fonctions utilitaires de génération de valeurs aléatoires : devraient être ailleurs.
double random(qreal maxValue);
double random(qreal minValue, qreal maxValue);
QColor randomColor();

#endif // !RANDOM_H