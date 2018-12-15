#ifndef Q_DYNAMIC_OBJECT_H
#define Q_DYNAMIC_OBJECT_H

#include "QBasicItem.h"

// QDynamicObject est une classe abstraite qui d�finie des attributs et m�thodes
// communs pour les entit�s vivantes
class QDynamicObject : public QBasicItem
{
public:
	QDynamicObject();
	~QDynamicObject();

	void setSpeed(qreal speed);
	// Fonction virtuelle pure
	virtual void clone() = 0;
protected:
	// La vitesse
	qreal mSpeed;
};


#endif // !Q_DYNAMIC_OBJECT_H


