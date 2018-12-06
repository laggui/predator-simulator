#ifndef Q_PARAMETERS_H
#define Q_PARAMETERS_H


#include <QWidget>

class QSpinBox;


class QParameters : public QWidget
{
	Q_OBJECT

public:
	QParameters(size_t maxItems = 250, QWidget * parent = nullptr);

	size_t nbrOfItems() const;

protected:
	QSpinBox * mNbrOfItems;
};


#endif // Q_PARAMETERS_H