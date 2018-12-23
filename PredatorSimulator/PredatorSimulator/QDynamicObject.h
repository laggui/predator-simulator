#ifndef Q_DYNAMIC_OBJECT_H
#define Q_DYNAMIC_OBJECT_H

#include "QBasicItem.h"
#include <QtMath>

// QDynamicObject est une classe template abstraite qui définie des attributs et méthodes
// communs pour les entités vivantes de la simulation
template <typename T>
class QDynamicObject : public QBasicItem<T>
{
public:
	QDynamicObject(qreal initialSpeed = 1.0, QBrush const & brush = Qt::white, QGraphicsItem * parent = nullptr) : QBasicItem<T>(brush, parent), mSpeed{ initialSpeed } {}

	// Mutateur et accesseur de vitesse
	void setSpeed(qreal speed) { mSpeed = speed; }
	qreal speed() const { return mSpeed; }

	// Fonctions virtuelles pures, à redéfinir dans les enfants
	virtual void clone() = 0;
	virtual void setNextPos(qreal x, qreal y) = 0;
	virtual void setNextOrientation(qreal orientation) = 0;

	// Fonction qui fait rebondir un objet QDynamicObject
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


