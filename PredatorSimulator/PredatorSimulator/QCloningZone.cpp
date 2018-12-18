#include "QCloningZone.h"

QCloningZone::QCloningZone(QPointF const & topLeft, qreal width, qreal height, QBrush const & brush, QGraphicsItem * parent)
	: QWall(topLeft, width, height, brush, parent)
{
}
