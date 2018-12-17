#include "QWall.h"

#include <QPainter>

QWall::QWall(QPointF const & topLeft, qreal width, qreal height, WallOrientation orientation, QBrush const & brush, QGraphicsItem * parent)
	: QBasicItem(brush, parent)
{
	//switch (orientation) {

	//case WallOrientation::Horizontal:
	//	mShape << QPointF(0, 0) // shape de mur top 
	//		<< QPointF(0, -20)
	//		<< QPointF(1000, -20)
	//		<< QPointF(1000, 0)
	//		<< QPointF(0, 0);
	//	break;

	//case WallOrientation::Vertical:
	//	mShape << QPointF(0, 0) // shape mur de cote 
	//		<< QPointF(0, -600)
	//		<< QPointF(20, -600)
	//		<< QPointF(20, 0)
	//		<< QPointF(0, 0);
	//	break;

	//}
	mShape.setRect(-width/2, -height/2, width, height);
	setPos(topLeft.x() + width / 2, topLeft.y() + height / 2);
}

void QWall::setColor(QBrush const & brush)
{
	mBrush = brush;
}

QRectF QWall::boundingRect() const
{
	return QRectF(-0.25 * scale(), -0.5 * scale(), 1.0 * scale(), 1.25 * scale()); // ou juste return mShape?
}

void QWall::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	painter->setPen(Qt::NoPen);
	painter->setBrush(mBrush);
	painter->drawRect(mShape);
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