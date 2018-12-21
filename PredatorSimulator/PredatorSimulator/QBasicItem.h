#ifndef Q_BASIC_ITEM_H
#define Q_BASIC_ITEM_H

#include <QGraphicsItem>
#include <QBrush>

// QBasicItem est une classe template abstraite de base qui d�finie des attributs et m�thodes
// communs pour les entit�s du projet (vivantes et statiques)
template <typename T>
class QBasicItem : public QGraphicsItem
{
public:
	QBasicItem(QBrush const & brush, QGraphicsItem * parent = nullptr) : QGraphicsItem(parent), mBrush{ brush } {}

	//QBrush getBrushColor(); fonction existe deja : const QColor &QBrush::color() const // pas bien defini ??
	//Returns the brush color

	// Mutateur de couleur
	void setColor(QBrush const & brush) { mBrush = brush; }

protected:
	// La couleur de fond
	QBrush mBrush;
	// La forme (attribut template)
	T mShape;
};


#endif // !Q_BASIC_ITEM_H

