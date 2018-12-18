#include "QParameters.h"


#include <QSpinBox>
#include <QFormLayout>
#include <QtMath>


QParameters::QParameters(size_t maxItems, QString nom, QWidget * parent)
	: QWidget(parent),
	mNbrOfItems{ new QSpinBox }
{
	const size_t minMaxNbr{ 10 };

	mNbrOfItems->setRange(1, qMax(static_cast<size_t>(minMaxNbr), maxItems));
	mNbrOfItems->setValue(minMaxNbr);

	QFormLayout * layout{ new QFormLayout };
	layout->addRow(nom, mNbrOfItems);
	
	setLayout(layout);
}

size_t QParameters::nbrOfItems() const
{
	return static_cast<size_t>(mNbrOfItems->value());
}
