#ifndef Q_DYNAMIC_OBJECT_H
#define Q_DYNAMIC_OBJECT_H

#include "QBasicItem.h"

// QDynamicObject est une classe abstraite qui d�finie des attributs et m�thodes
// communs pour les entit�s vivantes
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

	void bounce(qreal bounceAngle) { setNextOrientation(2 * bounceAngle - rotation()); }
protected:
	// La vitesse
	qreal mSpeed;
};


#endif // !Q_DYNAMIC_OBJECT_H


