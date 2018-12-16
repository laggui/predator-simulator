#include "QWall.h"

#include <QPainter>

QWall::QWall(QPointF const & initialPosition, QBrush const & brush, QGraphicsItem * parent)
	: QBasicItem<QRectF>(brush, parent)
{
	//mShape << QPointF(0, 0) // shape de mur devrait etre QRectF
	//	<< QPointF(0, -600)
	//	<< QPointF(20, -600)
	//	<< QPointF(20, 0)
	//	<< QPointF(0, 0);

	setPos(initialPosition);
}

void QWall::setColor(QBrush const & brush)
{
	mBrush = brush;
}

QRectF QWall::boundingRect() const
{
	return QRectF(-0.25 * scale(), -0.5 * scale(), 1.0 * scale(), 1.25 * scale());
}

void QWall::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(mBrush);
	painter->drawPolygon(mShape);
}

void QWall::advance(int phase)
{
	if (phase == 0) {
		// do nothing
	}
	else if (phase == 1) {
		// do nothing
	}
}