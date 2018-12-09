#ifndef Q_BASIC_ITEM_H
#define Q_BASIC_ITEM_H

#include <QGraphicsItem>
#include <QBrush>


class QBasicItem : public QGraphicsItem
{
public:
	QBasicItem();
	~QBasicItem();

	//QBrush getBrushColor(); fonction existe deja : const QColor &QBrush::color() const // pas bien defini ??
	//Returns the brush color

	void setColor(QBrush const & brush);

private:
	QBrush mBrush;
	//QGraphicsEllipseItem mShape; pas s�r que �a va ici

};


#endif // !Q_BASIC_ITEM_H

