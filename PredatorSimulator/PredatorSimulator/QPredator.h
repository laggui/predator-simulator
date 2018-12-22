#ifndef  Q_PREDATOR_H
#define Q_PREDATOR_H

#include "QDynamicObject.h"
#include "Attributes.h"

// La classe QPredator interagit avec 
class QPredator : public QDynamicObject<QRectF>
{
public:
	QPredator(QPointF const & initialPosition = QPointF(), qreal initialOrientationDegrees = 0.0, qreal initialSpeed = 1.0, qreal scale = 1.0,
			  quint8 damage = 25, quint8 timeNoKill = 0, QBrush const & brush = Qt::white, QGraphicsItem * parent = nullptr);

	// Mutateurs
	void setDamage(quint8 damage);
	void setSize(qreal size);
	void resetTimeNoKill();
	void incrementTimeNoKill();
	void setFrozen(quint8 freezeTime);
	void setNextPos(qreal x, qreal y) override;
	void setNextOrientation(qreal orientation) override;
	void setNextTimeNoKill(quint32 timeNoKill);
	void setNextSize(qreal size);
	
	// Accesseurs
	quint8 damage() const;
	quint32 timeNoKill() const;
	qreal size() const;

	// Clone (fonction abstraite de QDynamicObject - doit �tre "overrid�e")
	void clone() override;

	// Fonction abstraite de QGraphicsItem (DOIT �tre "overrid�e") : retourne la taille de l'item
	QRectF boundingRect() const override;
	// Fonction abstraite de QGraphicsItem (DOIT �tre "overrid�e") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut �tre "overrid�e") : fait un tick de simulation
	void advance(int phase) override;

	// Constantes publiques
	static const qreal sMinSize;
	static const qreal sMaxSize;

protected:
	// Le dommage que le pr�dateur inflige
	quint8 mDamage;
	// Le temps depuis sa derni�re victime
	quint32 mTimeNoKill;
	// La grosseur
	qreal mSize;
	// Les prochains attributs
	PredatorAttributes mNextAttributes;

	// �limine l'entit� avec laquelle elle entre en contact
	void kill(QGraphicsItem * item);
private:
	// Propri�t�
	quint8 mFrozen;
	// Constante priv�e
	static const qreal sSizeIncrement;
};

#endif // !Q_PREDATOR_H




