#ifndef Q_WALL_H
#define Q_WALL_H

#include "QBasicItem.h"

class QWall : public QBasicItem<QRectF>
{
public:
	QWall(QPointF const & initialPosition = QPointF(), QBrush const & brush = Qt::white, QGraphicsItem * parent = nullptr);

	// Mutateur de couleur
	void setColor(QBrush const & brush);

	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : retourne la taille de l'item
	QRectF boundingRect() const override;

	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut être "overridée") : fait un tick de simulation
	void advance(int phase) override;
	//bounce();
protected:
	//mBounceDirection;
};


#endif // !Q_WALL_H


