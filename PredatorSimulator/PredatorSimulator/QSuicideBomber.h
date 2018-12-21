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
	void setNextPos(qreal x, qreal y) override;
	void setNextOrientation(qreal orientation) override;

	// Accesseurs
	qreal damage() const;

	// Clone (fonction abstraite de QDynamicObject - doit être "overridée")
	void clone() override;

	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut être "overridée") : fait un tick de simulation
	void advance(int phase) override;

private:
	// Le dommage (influence la grosseur d'un QPredator)
	qreal mDamage;
	// La prochaine position
	Attributes mNextAttributes;
};

#endif // !Q_SUICIDE_BOMBER_H



