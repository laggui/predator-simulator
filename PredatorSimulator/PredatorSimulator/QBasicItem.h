#ifndef Q_BASIC_ITEM_H
#define Q_BASIC_ITEM_H

#include <QGraphicsItem>
#include <QBrush>

// QBasicItem est une classe abstraite de base qui définie des attributs et méthodes
// communs pour les entités du projet (vivantes et statiques)
class QBasicItem : public QGraphicsItem
{
public:
	QBasicItem();
	~QBasicItem();

	//QBrush getBrushColor(); fonction existe deja : const QColor &QBrush::color() const // pas bien defini ??
	//Returns the brush color

	// Mutateur de couleur
	void setColor(QBrush const & brush);

protected:
	// La couleur de fond
	QBrush mBrush;
	// La forme
	QPolygonF mShape;
};


#endif // !Q_BASIC_ITEM_H

