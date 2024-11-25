# MARC PRJ - *Pierre Raphaël Justin*

---

## Information

* Ce dépôt est un fork de [nicolas-flasque-efrei/MARC](https://github.com/nicolas-flasque-efrei/MARC)
* Le projet et sa description sont proposé par [@nicolas-flasqu-efrei](https://github.com/nicolas-flasque-efrei)

---

## Avant-propos

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
- Un module pour guider le robot à sa base `main.c` (fonctionnalité principale)

Le robot utilise la procédure suivante pour retrouver sa base :

- Piocher des mouvements **aléatoirement** parmi ses réserves `selMoves()`
- Construire toutes les **combinaisons possibles** `buildTree()`
- Trouver le **meilleur avancement** `minimalNode()`
- Retrouver la **combinaison de mouvement** associé `findNodePath()`

## Caractéristiques techniques

**Ce projet intègre :**

- Une fonction pour retrouver sa base `runRover()`.
- Un [rapport](complexity/times.md) sur le temps d'exécution du des différentes étapes clés cités plus haut.
- Une [explication](maps/maps.md) du fonctionnement des `.map`.
- Des cartes supplémentaires disponibles dans [/map](maps).
- L'option (activée par défaut) pour la reconnaissance des pentes (slopes).
    - Cela modifie le comportement de la fonction de génération de map `createMapFromFile()`.
    - Cela modifie le comportement de déplacement qui s'en retrouve impactée `move()`.

## Guide de démarrage

Pour exécuter ce programme vous aurez besoin d'un compilateur C.
<br>Le mode de compilation choisi est avec **cmake**.

**Démarrage rapide :**

1. Cloner le projet dans un répertoire local `git clone https://github.com/Balafre78/MARC-PRJ`.
2. L'outil conseillé pour la compilation est CLion sinon se référer à
   ce [gist](https://gist.github.com/sohukia/a65952b1e3ffae028b15a020402a6413).
3. Activer ou désactiver certaines options (voir ci-dessous).
4. Compile & Run !

| Option        | Type | Fonction                                            |
|---------------|------|-----------------------------------------------------|
| **SEED**      | int  | Définie une seed pour les test                      |
| **SLOPE_OPT** | bool | Active la prise en charge des slopes                |
| **MAX_DEPTH** | int  | Nombre maximal de mouvements séléctionnés par phase |
| **LEN_MOVE**  | int  | Nombre de mouvements disponibles par phase          |
| **DEBUG**     | bool | Active les options de débbuggage                    |
