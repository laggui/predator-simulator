#ifndef Q_RUNNER_H
#define Q_RUNNER_H

#include "QDynamicObject.h"
#include "Attributes.h"

class QRunner : public QDynamicObject
{
public:
	// TO-DO: constructeur avec des param�tres (par d�faut)
	QRunner();
	~QRunner();

	// Mutateurs
	void setHP(int hp);
	void setNextAttributes(int hp, QBrush const & brush);

	// Accesseur
	int getHP() const;

	// Clone (fonction abstraite de QDynamicObject - doit �tre "overrid�e")
	void clone() override;

	// Fonction abstraite de QGraphicsItem (DOIT �tre "overrid�e") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT �tre "overrid�e") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut �tre "overrid�e") : fait un tick de simulation
	void advance(int phase) override;

private:
	// Les points de vie
	int mHealthPoints;
	// Les prochains attributs
	RunnerAttributes mNextAttributes;
};

#endif // !Q_RUNNER_H



