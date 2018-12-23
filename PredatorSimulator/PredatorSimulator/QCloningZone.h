#ifndef Q_CLONING_ZONE
#define Q_CLONING_ZONE

#include "QWall.h"
class QCloningZone : public QWall
{
public:
	QCloningZone(QPointF const & topLeft = QPointF(), qreal width = 0, qreal height = 0, qreal orientation = 0,
		qreal yStartPos = 0, QBrush const & brush = Qt::yellow, QGraphicsItem * parent = nullptr);

	// Fonction virtuelle de QGraphicsItem (peut être "overridée") : fait un tick de simulation
	void advance(int phase) override;

	// Les fonctions boundingRect et paint sont les mêmes que QWall, donc pas besoin d'override

	// Fonction qui déplace et clone un objet dynamique
	void cloneAndWarp(QRunner * runner);
protected:
	// Position de départ où les objets sont clonés
	qreal mYStartPos;
};


#endif // !Q_CLONING_ZONE


