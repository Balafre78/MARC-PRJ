# MARC PRJ - *PierreRaphaëlJustin*

---

## Acknowledgement

* Ce dépôt est un fork de [nicolas-flasque-efrei/MARC](https://github.com/nicolas-flasque-efrei/MARC)
* Le projet et sa description sont proposé par [@nicolas-flasqu-efrei](https://github.com/nicolas-flasque-efrei)

---

## Avant-propos - Mise en contexte

2028 : Une tempête solaire très intense vient de se produire… Le rover MARC – MArs Rover Cartograph, qui s’acquittait
fort bien de sa mission, a été victime d’un dysfonctionnement. Ses systèmes de programmation, de guidage et de
mouvements ont été fortement altérés…
L’ESTF, Efrei Space Task Force, a fait appel à des experts en programmation pour concevoir un nouveau logiciel de
déplacement pour MARC.
Votre mission est de réaliser ce logiciel de déplacement pour ramener MARC jusqu’à une station de base où il pourra être
remis en état.

MARC est un rover un peu rustique, il embarque un système Linux, et tous ses programmes sont écrits en langage C.
Il se repère par sa position, et la direction à laquelle il fait face, parmi Nord, Sud, Est et Ouest (même sur Mars).
Fort heureusement, son radar et son gyroscope fonctionnent encore et lui permettent de se situer.

## Comment fonctionne MARC PRJ ?

**MARC PRJ** est dépôt qui contient les sources de ce petit robot. Il est divisé en deux parties :

- Une suite de test préconfiguré `testunit.h`
- Un module pour guider le robot à sa base `main.c`

Le robot utilise la procédure suivante pour retrouver sa base :

- Piocher des mouvements parmi ses réserves `selMoves()`
- Tester toutes les combinaisons possibles `buildTree()`
- Trouver le celle la plus efficace `minimalNode()`
- Retrouver la combinaison de mouvement associé `findNodePath()`

## Caractéristiques techniques

Ce projet intègre :

- Une fonction pour retrouver sa base `runRover()`
- Un rapport détaillé sur le temps d'exécution du des différentes étapes clés cités plus haut.
- Des cartes supplémentaires disponibles dans `/map`
- L'option (désactivée par défaut) d'activée la reconnaissance des pentes (slopes)
    - Cela modifie le comportement de la fonction de génération de map `createMapFromFile()`
    - Cela modifie le comportement de déplacement qui s'en retrouve impactée `move()`

## Guide de démarrage

Pour exécuter ce programme vous aurez besoin d'un compilateur C.
Le mode de compilation choisi est avec **cmake**

Démarrage rapide :

1. Cloner le projet dans un répertoire local.
2. L'outil conseillé pour la compilation est CLion sinon se référer à
   ce [gist](https://gist.github.com/sohukia/a65952b1e3ffae028b15a020402a6413)
3. Activer ou désactiver certaines options (tel que `SLOPE_OPT` dans `slope.h` ou `SEED` dans `main.c`)
4. Compile & Run !




