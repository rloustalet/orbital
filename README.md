# Astro Toolbox
 [![GitHub License](https://img.shields.io/github/license/rloustalet/orbital)
](https://simple.wikipedia.org/wiki/MIT_License) ![GitHub last commit (branch)](https://img.shields.io/github/last-commit/rloustalet/orbital/main)


Le projet intitulé orbital a été mené par Bellana Carme (@carmebella) et Romain Loustalet Palengat (@rloustalet). Ce projet a été réalisé dans le cadre de l'UE "modélisation numérique". Ce projet a été réalisé en programmation orienté objet.

## Installation

Pour installer le programme que nous avons réalisé, il suffit de cloner le répertoire sur votre disque dur `git clone https://github.com/rloustalet/orbital.git`
## Basic usage

Dans cette section nous vous présentons un usage basique du programme que nous avons réalisé.

**main.cpp**
```C++
#include  <vector>
#include  <iostream>
#include  <string>
#include  "src/object.h"
#include  "src/solarsystem.h"

int  main(){
long  int  h  =  1  *  24  *  3600L;
long  int  t  =  30  *  365  *  24  *  3600L;

SolarSystem  solarsystem("solar_system");

solarsystem.addObjectFromHorizons("Sun");
solarsystem.addObjectFromHorizons("Mercury");
solarsystem.addObjectFromHorizons("Venus");
solarsystem.addObjectFromHorizons("Earth");
solarsystem.addObjectFromHorizons("Mars");

solarsystem.solve("RK4",h, t);
}
```
Pour décrire ce script nous pouvons remarquer une première instance de la classe `SolarSystem` instance dont nous remplissons le vecteur objects à l'aide de la méthode `SolarSystem::addObjectFromHorizons` enfin nous utilisons la méthode `SolarSystem::solve` qui prend en argument `"euler"`, `"verlet"`, `"RK4"` qui correspondent à différents algorithmes de résolution. Cette méthode prend également en argument un pas de temps h et un temps total d'intégration t.

Lorsque l'on exécute le programme on voit une barre de progression apparaître comme ci-dessous qui vous indique bien sûr sur la progression, le temps écoulé, le temps d'exécution prédit et le temps d'exécution par itération temporelle.
`100% [||||||||||||||||||||||||||||||||||||||||||||||||||] 21.94s/21.94s, 2ms/iter`

Le fichier main.cpp se trouve à la racine `/` du projet vous pouvez le modifier à volonté pour faire les simulations que vous souhaitez. La commande `make run` vous permet de compiler et d'exécuter ce script.

## Documentation

La documentation est disponible en docstring dans le programme ou compilée sur le site web suivant [rloustalet.github.io/orbital](https://rloustalet.github.io/orbital/)

## License

Orbital est sous une licence MIT [LICENSE](https://github.com/rloustalet/orbital/blob/main/LICENSE) file.