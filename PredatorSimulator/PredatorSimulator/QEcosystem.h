#ifndef Q_ECOSYSTEM_H
#define Q_ECOSYSTEM_H

#include "QBasicItem.h"

// Ecosyst�me = le background de la sc�ne pour interagir avec les entit�s en place
class QEcosystem : public QBasicItem<QRectF>
{
public:
	QEcosystem(QSize spawnSize, unsigned int timerInterval, unsigned int timeAlive = 0, QPointF const & sceneCenter = QPointF(),
			   qreal width = 0, qreal height = 0, QBrush const & brush = Qt::darkBlue, QGraphicsItem * parent = nullptr);

	// Mutateur
	unsigned int timeAlive();

	// Incr�mentation du temps de vie de l'�cosyst�me
	void tick();
	// Actions d'�volution
	void evolve();

	// Fonction abstraite de QGraphicsItem (DOIT �tre "overrid�e") : retourne la taille de l'item
	QRectF boundingRect() const override;

	// Fonction abstraite de QGraphicsItem (DOIT �tre "overrid�e") : dessine la forme
	void paint(QPainter * painter, const QStyleOptionGraphicsItem *option, QWidget * widget) override;

	// Fonction virtuelle de QGraphicsItem (peut �tre "overrid�e") : fait un tick de simulation
	void advance(int phase) override;
private:
	// Le temps depuis que l'�cosyst�me est en vie
	unsigned int mTimeAlive;
	// L'intervalle de temps auquel l'�cosyst�me �volue
	unsigned int mEvolveTime;
	// La taille de la sc�ne pour que l'�cosyst�me puisse g�n�rer des items au bon endroit
	QSize mSpawnSize;
	// Les constantes pour la g�n�ration des entit�s
	static const qreal sMembersSize;
	static const qreal sMembersSpeed;
	static const quint8 sRunnerHP;
	static const qreal sRunnersOrientationOffset;
	static const qreal sBomberDamage;
	static const qreal sBomberOrientation;
	static const qreal sPredatorDecrement;
};

#endif // !Q_ECOSYSTEM_H