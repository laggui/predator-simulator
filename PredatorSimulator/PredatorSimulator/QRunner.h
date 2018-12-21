#ifndef Q_RUNNER_H
#define Q_RUNNER_H

#include "QDynamicObject.h"
#include "Attributes.h"

class QRunner : public QDynamicObject<QRectF>
{
public:
	// TO-DO: constructeur avec des paramètres (par défaut)
	QRunner(QPointF const & initialPosition = QPointF(), qreal initialOrientationDegrees = 0.0, qreal initialSpeed = 1.0, qreal scale = 1.0,
			quint8 initialHealth = 3, QBrush const & brush = Qt::green, QGraphicsItem * parent = nullptr);
	// Constructeur de copie
	QRunner(const QRunner & runner);

	// Mutateurs
	void setHP(quint8 hp);
	void setSize(qreal size);
	void setImmuneTime(quint8 time);
	void setNextHP(quint8 hp);
	void setNextPos(qreal x, qreal y) override;
	void setNextOrientation(qreal orientation) override;

	// Accesseur
	quint8 HP() const;
	qreal size() const;
	quint8 immuneTime() const;

	// Clone (fonction abstraite de QDynamicObject - doit être "overridée")
	void clone() override;

	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut être "overridée") : fait un tick de simulation
	void advance(int phase) override;

private:
	// Les points de vie
	quint8 mHealthPoints;
	// La grosseur
	qreal mSize;
	// Le temps d'immunisation
	quint8 mImmuneTime;
	// Les prochains attributs
	RunnerAttributes mNextAttributes;
};

#endif // !Q_RUNNER_H



