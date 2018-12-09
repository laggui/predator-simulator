#include "QBasicItem.h"

#include <QBrush>


QBasicItem::QBasicItem()
{
}

QBasicItem::~QBasicItem()
{
}

//QBasicItem::getBrushColor()
//{
//	return mBrush;
//}

void QBasicItem::setColor(QBrush const & brush)
{
	mBrush = brush;
}
