#ifndef  Q_PREDATOR_H
#define Q_PREDATOR_H

#include "QDynamicObject.h"
#include "Attributes.h"

// La classe QPredator interagit avec 
class QPredator : public QDynamicObject
{
public:
	// TO-DO: constructeur avec des paramètres (par défaut)
	QPredator();
	~QPredator();

	// Mutateurs
	void setDamage(int damage);
	void resetTimeNoKill();
	void incrementTimeNoKill();
	void setNextAttributes(int damage, int timeNoKill, qreal scaleFactor);
	
	// Accesseurs
	int getDamage() const;
	int getTimeNoKill() const;

	// Clone (fonction abstraite de QDynamicObject - doit être "overridée")
	void clone() override;

	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut être "overridée") : fait un tick de simulation
	void advance(int phase) override;

private:
	// Le dommage que le prédateur inflige
	int mDamage;
	// Le temps depuis sa dernière victime
	int mTimeNoKill;
	// Les prochains attributs
	PredatorAttributes mNextAttributes;

	// Élimine l'entité avec laquelle elle entre en contact
	void kill(QDynamicObject* object);

};

#endif // !Q_PREDATOR_H




