#ifndef Q_DYNAMIC_OBJECT_H
#define Q_DYNAMIC_OBJECT_H

#include "QBasicItem.h"
#include <QtMath>

// QDynamicObject est une classe abstraite qui définie des attributs et méthodes
// communs pour les entités vivantes
template <typename T>
class QDynamicObject : public QBasicItem<T>
{
public:
	QDynamicObject(qreal initialSpeed = 1.0, QBrush const & brush = Qt::white, QGraphicsItem * parent = nullptr) : QBasicItem<T>(brush, parent), mSpeed{ initialSpeed } {}

	void setSpeed(qreal speed) { mSpeed = speed; }
	// Fonction virtuelle pure
	virtual void clone() = 0;
	virtual void setNextPos(qreal x, qreal y) = 0;
	virtual void setNextOrientation(qreal orientation) = 0;

	void bounce(qreal bounceAngle) { qreal nextOrientation{ 2 * bounceAngle - rotation() };
									 QPointF nextPos{ pos().x() + qCos(qDegreesToRadians(nextOrientation)) * mSpeed, pos().y() + qSin(qDegreesToRadians(nextOrientation)) * mSpeed };
									 setNextOrientation(nextOrientation);
									 setNextPos(nextPos.x(), nextPos.y());
								   }
protected:
	// La vitesse
	qreal mSpeed;
};


#endif // !Q_DYNAMIC_OBJECT_H


