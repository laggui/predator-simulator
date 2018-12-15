#ifndef Q_SUICIDE_BOMBER_H
#define Q_SUICIDE_BOMBER_H

#include "QDynamicObject.h"
#include "Attributes.h"

class QSuicideBomber : public QDynamicObject
{
public:
	QSuicideBomber();
	~QSuicideBomber();

	// Mutateurs
	void setDamage(qreal damage);
	void setNextpos(qreal x, qreal y);

	// Accesseurs
	qreal getDamage() const;

	// Clone (fonction abstraite de QDynamicObject - doit être "overridée")
	void clone() override;

	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut être "overridée") : fait un tick de simulation
	void advance(int phase) override;

private:
	// Le dommage (influence la grosseur d'un QPredator - doit être entre ]0, 1[)
	qreal mDamage;
	// La prochaine position
	Position mNextPos;
};

#endif // !Q_SUICIDE_BOMBER_H



