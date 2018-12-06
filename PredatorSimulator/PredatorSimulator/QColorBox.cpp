#include "QColorBox.h"


#include <QResizeEvent>


QColorBox::QColorBox(QPen const & pen, QBrush const & brush, QWidget * parent)
	: QLabel(parent)
{
	set(pen, brush);
}

void QColorBox::set(QPen const & pen)
{
	mPen = pen;
}

void QColorBox::set(QBrush const & brush)
{
	mBrush = brush;
}

void QColorBox::set(QPen const & pen, QBrush const & brush)
{
	set(pen);
	set(brush);
}

void QColorBox::paintEvent(QPaintEvent * event)
{
	QPainter painter(this);
	painter.setPen(mPen);
	painter.setBrush(mBrush);
	painter.drawRect(rect());
}

