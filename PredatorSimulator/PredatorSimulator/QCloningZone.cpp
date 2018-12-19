#include "QCloningZone.h"

QCloningZone::QCloningZone( QPointF const & topLeft, qreal width, qreal height, qreal orientation, QBrush const & brush, QGraphicsItem * parent)
	: QWall(topLeft, width, height, orientation ,brush, parent)
{
}
