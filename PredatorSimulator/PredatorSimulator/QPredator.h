#ifndef  Q_PREDATOR_H
#define Q_PREDATOR_H

#include "QDynamicObject.h"
#include "Attributes.h"

// La classe QPredator interagit avec 
class QPredator : public QDynamicObject
{
public:
	// TO-DO: constructeur avec des param�tres (par d�faut)
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

	// Clone (fonction abstraite de QDynamicObject - doit �tre "overrid�e")
	void clone() override;

	// Fonction abstraite de QGraphicsItem (DOIT �tre "overrid�e") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT �tre "overrid�e") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut �tre "overrid�e") : fait un tick de simulation
	void advance(int phase) override;

private:
	// Le dommage que le pr�dateur inflige
	int mDamage;
	// Le temps depuis sa derni�re victime
	int mTimeNoKill;
	// Les prochains attributs
	PredatorAttributes mNextAttributes;

	// �limine l'entit� avec laquelle elle entre en contact
	void kill(QDynamicObject* object);

};

#endif // !Q_PREDATOR_H




