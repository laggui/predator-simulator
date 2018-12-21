#ifndef Q_ECOSYSTEM_H
#define Q_ECOSYSTEM_H

#include "QBasicItem.h"

// Ecosystème = le background de la scène pour interagir avec les entités en place
class QEcosystem : public QBasicItem<QRectF>
{
public:
	QEcosystem(QSize spawnSize, unsigned int timerInterval, unsigned int timeAlive = 0, QPointF const & sceneCenter = QPointF(),
			   qreal width = 0, qreal height = 0, QBrush const & brush = Qt::darkBlue, QGraphicsItem * parent = nullptr);

	// Mutateur
	unsigned int timeAlive();

	// Incrémentation du temps de vie de l'écosystème
	void tick();
	// Actions d'évolution
	void evolve();

	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : retourne la taille de l'item
	QRectF boundingRect() const override;

	// Fonction abstraite de QGraphicsItem (DOIT être "overridée") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut être "overridée") : fait un tick de simulation
	void advance(int phase) override;
private:
	// Le temps depuis que l'écosystème est en vie
	unsigned int mTimeAlive;
	// L'intervalle de temps auquel l'écosystème évolue
	unsigned int mEvolveTime;
	// La taille de la scène pour que l'écosystème puisse générer des items au bon endroit
	QSize mSpawnSize;
	// Les constantes pour la génération des entités
	static const qreal sMembersSize;
	static const qreal sMembersSpeed;
	static const quint8 sRunnerHP;
	static const qreal sRunnersOrientationOffset;
	static const qreal sBomberDamage;
	static const qreal sBomberOrientation;
	static const qreal sPredatorDecrement;
};

#endif // !Q_ECOSYSTEM_H