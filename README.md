# predator-simulator

## À PRENDRE EN CONSIDÉRATION QUAND VOUS "PULLEZ" LES CHANGEMENTS DU PROJET

Il semble y avoir un léger "fuck" avec la compatibilité du projet sur différentes machines. En gros, deux problèmes peuvent causer des problèmes à la compilation:
- Version SDK du projet. On a peut-être des versions différentes, donc changer dans les propriétés du projet: (right-click sur le projet) Properties > Configuration Properties > General > Windows SDK Version: sélectionnez la vôtre.
- Propriétés Qt.
	- Premièrement, sélectionnez la version de Qt que vous avez pour le projet: (right-click sur le projet) Qt Properties > Properties tab > Version: sélectionnez la vôtre.
	- Deuxièmement, sélectionnez les modules Qt à utiliser: (right-click sur le projet) Qt Properties > Qt Modules tab: cochez Core, GUI et Widgets.

## Entités Dynamiques

QRunner, QPredator et QSuicideBomber

## Entités Statiques

QWall et QCloningZone.

Commentaire: est-ce qu'on devrait avoir une classe pour notre écosystème?

## Act Of God

L'act of god va geler le déplacement des prédateurs pour un temps donné.

## Paramètres Initiaux

On doit avoir des sélecteurs qui permettent de définir le nombre de QRunner, QPredator et QSuicideBomber (au minimum). Si on veut, on peut aussi définir des attributs initiaux pour ces classes (ex: vitesse, dommage).

## Template

Liste template pour des QDynamicObjects?

## Gestion de collision (interaction)

Exemple sua' coche: http://doc.qt.io/qt-5/qtwidgets-graphicsview-collidingmice-example.html. Par contre, dans notre cas, on n'a pas besoin d'éviter les collisions donc on peut tout simplement vérifier quand une collision se passe et effectuer les changements dans ce cas-ci.

Pour ce faire, dans la méthode *advance()* des items à action dominante (ex: les prédateurs **endommagent** les runners - action dominante), on vérifie à l'aide de [QGraphicsItem::collidingItems](http://doc.qt.io/qt-5/qgraphicsitem.html#collidingItems).

Pseudo code:

```cpp
void NotreClasse::advance(int phase)
{
	// Récupérer les items qui sont en collision
	QList<QGraphicsItem *> collidingItems = collidingItems(); // Par défaut: les items qui overlap avec la shape de l'item et les items qui touchent au contour de l'item
	
	// Itérer à travers les items et vérifier leur type
	foreach (QGraphicsItem *item, collidingItems) {
		if (auto classeUn = dynamic_cast<NotreClasseUn*>(item)) {
			...
		}
		else if (auto classeDeux = dynamic_cast<NotreClasseDeux*>(item)) {
			...
		}
		...
	}

}
```

## TO-DO

- [ ] PredatorSimulator
- [x] QBasicItem
	- [x] QWall
		- [x] QCloningZone
	- [x] QDynamicObject
		- [x] QRunner (peut-être un fuck avec clone?)
		- [x] QPredator: manque kill()
		- [ ] QSuicideBomber : arranger la shape (semble avoir un fuck dans la simulation)
	- [ ] QEcosytem : manque génération de bombers dans advance (en commentaire)
	- [x] QEcosytem : manque génération de runners dans advance (en commentaire)
- [ ] QActOfGod: on a rien encore, il nous faut un bouton qui va faire une action


