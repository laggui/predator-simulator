#ifndef Q_SUICIDE_BOMBER_H
#define Q_SUICIDE_BOMBER_H

#include "QDynamicObject.h"
#include "Attributes.h"

class QSuicideBomber : public QDynamicObject<QPolygonF>
{
public:
	QSuicideBomber(QPointF const & initialPosition = QPointF(), qreal initialOrientationDegrees = 0.0, qreal initialSpeed = 1.0, qreal scale = 1.0,
				   qreal damage = 0.1, QBrush const & brush = Qt::white, QGraphicsItem * parent = nullptr);

	// Mutateurs
	void setDamage(qreal damage);
	void setNextpos(qreal x, qreal y);

	// Accesseurs
	qreal getDamage() const;

	// Clone (fonction abstraite de QDynamicObject - doit �tre "overrid�e")
	void clone() override;

	// Fonction abstraite de QGraphicsItem (DOIT �tre "overrid�e") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT �tre "overrid�e") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut �tre "overrid�e") : fait un tick de simulation
	void advance(int phase) override;

private:
	// Le dommage (influence la grosseur d'un QPredator - doit �tre entre ]0, 1])
	qreal mDamage;
	// La prochaine position
	Position mNextPos;
};

#endif // !Q_SUICIDE_BOMBER_H



