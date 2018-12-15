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

Exemple sua' coche: http://doc.qt.io/qt-5/qtwidgets-graphicsview-collidingmice-example.html
