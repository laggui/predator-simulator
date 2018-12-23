#ifndef Q_CLONING_ZONE
#define Q_CLONING_ZONE

#include "QWall.h"
class QCloningZone : public QWall
{
public:
	QCloningZone(QPointF const & topLeft = QPointF(), qreal width = 0, qreal height = 0, qreal orientation = 0,
		qreal yStartPos = 0, QBrush const & brush = Qt::yellow, QGraphicsItem * parent = nullptr);

	// Fonction virtuelle de QGraphicsItem (peut �tre "overrid�e") : fait un tick de simulation
	void advance(int phase) override;

	// Les fonctions boundingRect et paint sont les m�mes que QWall, donc pas besoin d'override

	// Fonction qui d�place et clone un objet dynamique
	void cloneAndWarp(QRunner * runner);
protected:
	// Position de d�part o� les objets sont clon�s
	qreal mYStartPos;
};


#endif // !Q_CLONING_ZONE


