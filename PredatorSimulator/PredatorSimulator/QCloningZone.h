#ifndef Q_CLONING_ZONE
#define Q_CLONING_ZONE

#include "QWall.h"
class QCloningZone : public QWall
{
public:
	QCloningZone(QPointF const & topLeft = QPointF(), qreal width = 0, qreal height = 0,
				 QBrush const & brush = Qt::yellow, QGraphicsItem * parent = nullptr);
};


#endif // !Q_CLONING_ZONE


