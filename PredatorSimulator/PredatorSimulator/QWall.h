#ifndef Q_WALL_H
#define Q_WALL_H

#include "QBasicItem.h"

class QPredator;
class QRunner;
class QSuicideBomber;

class QWall : public QBasicItem<QRectF>
{
public:
	QWall(QPointF const & topLeft = QPointF(), qreal width = 0, qreal height = 0,
		  QBrush const & brush = Qt::darkRed, QGraphicsItem * parent = nullptr);

	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : retourne la taille de l'item
	QRectF boundingRect() const override;

	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut être "overridée") : fait un tick de simulation
	void advance(int phase) override;


protected:
	qreal mWallOrientation;
};


#endif // !Q_WALL_H


