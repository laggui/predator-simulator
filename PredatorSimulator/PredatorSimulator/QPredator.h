#ifndef  Q_PREDATOR_H
#define Q_PREDATOR_H

#include "QDynamicObject.h"
#include "Attributes.h"

// La classe QPredator interagit avec 
class QPredator : public QDynamicObject<QRectF>
{
public:
	QPredator(QPointF const & initialPosition = QPointF(), qreal initialOrientationDegrees = 0.0, qreal initialSpeed = 1.0, qreal scale = 1.0,
			  quint8 damage = 25, quint8 timeNoKill = 0, QBrush const & brush = Qt::white, QGraphicsItem * parent = nullptr);

	// Mutateurs
	void setDamage(quint8 damage);
	void resetTimeNoKill();
	void incrementTimeNoKill();
	void setNextPos(qreal x, qreal y) override;
	void setNextOrientation(qreal orientation) override;
	void setNextTimeNoKill(quint8 timeNoKill);
	void setNextScale(qreal scale);
	
	// Accesseurs
	quint8 getDamage() const;
	quint8 getTimeNoKill() const;

	// Clone (fonction abstraite de QDynamicObject - doit être "overridée")
	void clone() override;

	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut être "overridée") : fait un tick de simulation
	void advance(int phase) override;

protected:
	// Le dommage que le prédateur inflige
	quint8 mDamage;
	// Le temps depuis sa dernière victime
	quint8 mTimeNoKill;
	// Les prochains attributs
	PredatorAttributes mNextAttributes;

	// Élimine l'entité avec laquelle elle entre en contact
	void kill(QDynamicObject* object);

	// Fonctions mathématiques utilitaires servant à réaliser la "téléportation" : devraient être ailleurs.
	static qreal warp(qreal value, qreal begin, qreal end);
	void warp(QPointF & point);
private:
	static const qreal minScale;
	static const qreal maxScale;
};

#endif // !Q_PREDATOR_H




