#include "QParameters.h"

#include <QSpinBox>
#include <QFormLayout>
#include <QtMath>


QParameters::QParameters(size_t maxItems, QString nom, QWidget * parent)
	: QWidget(parent),
	mNbrOfItems{ new QSpinBox }
{
	const size_t minMaxNbr{ 5 };

	mNbrOfItems->setFixedWidth(50);
	mNbrOfItems->setRange(1, qMax(static_cast<size_t>(minMaxNbr), maxItems));
	mNbrOfItems->setValue(minMaxNbr);

	QHBoxLayout * horizLayout{ new QHBoxLayout };
	QFormLayout * layout{ new QFormLayout };
	layout->addRow(nom, mNbrOfItems);
	horizLayout->setAlignment(Qt::AlignRight);
	horizLayout->addLayout(layout);
	setLayout(horizLayout);
}

size_t QParameters::nbrOfItems() const
{
	return static_cast<size_t>(mNbrOfItems->value());
}
