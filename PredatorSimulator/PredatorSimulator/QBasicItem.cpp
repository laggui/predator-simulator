#include "QBasicItem.h"

#include <QBrush>


QBasicItem::QBasicItem()
{
}

QBasicItem::~QBasicItem()
{
}

void QBasicItem::setColor(QBrush const & brush)
{
	mBrush = brush;
}
