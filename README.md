# TP1: Chemins de Dyck"

## Description :bookmark_tabs: ##

Ce travail est réalisée dans le cardre du cours INF3135 - Construction et maintenance de logiciel 
donnée a l'UQAM par Mr. Serge Dogny. Le but étant de s'initier au language de **programmation C**,
au fichier markdown ainsi qu'au bonne pratique de devellopement dans cet environnement.

Le but de ce TP est d'implementer un programme nommée **Mot de Dyck**. Concretement, 
cela consiste a definir un alphabet binaire a deux caracteres alpha numerique qu'on appelera dans ce 
document des token. Le premier token ce dit 'haut' et le deuxième 'bas'. Ensuite, l'utilisateur definit une chaine de caracteres ( ou mot ) constitue uniquement de ces deux token. On dit alors que ce mot est defini sur cette alphabet.

Pour que ce mot soit un **Mot de Dyck**, il doit respecter deux proprietes :

  1. il existe autant de token 'haut' que de token 'bas' dans le mot.
  2. Pour chaque sous mot du mot choisi par l'utilisateur, il existe au minimum autant de token 'haut' que de token bas.

Voici un Exemple tirée de l'énoncée du travail

![](misc/figure1.png)

**Figure 1** – _Représentation graphique (a) du chemin de Dyck décrit par le mot aabaabbb et (b) d’un chemin décrit par le mot aababbba qui n’est pas un mot de Dyck, car le préfixe aababbb viole la condition (ii)_.

Ce programme a donc pour but de prendre en entrée les informations relatives au **Mot de Dyck** et verifier grace a un algorithme si celui-ci est valide ou pas. L'utilisateur pourra alors choisir de connaitre la hauteur maximale du mot, l'aire sous la courbe ou par default visualiser la représentation ASCII du mot tel qui suit :

![](misc/figure2.png)

**Figure 2** – _Représentation ASCII du mot de Dyck aabaabbb. Hauteur = 3 ; Aire = 12._


lien vers le [sujet du travail](sujet.md).
Les photos dans ce documents sont prise de l'énoncé du travail rédigé par Mr. Serge Dogny.

## Auteur :pencil2:

Nadir Hadji (HADN08069703)

## Fonctionnement :wrench: ##

Il est préferable d'éxecuter ce projet dans un environnement Unix (Linux ou MacOS :heavy_check_mark:).
Des alternatives existe tout de meme sur Windows. Vous pouvez utiliser une machine virtuel, l'application Ubuntu ou plus simplement git bash.

Faire fonctionner ce projet en 3 étapes :

0. Telechargement (wget requis)
1. Compilation (GCC requis)
2. Execution

### Télechargement ###
Pour télecharger le projet taper les commandes suivantes :

```sh
$ wget https://gitlab.info.uqam.ca/hadji.nadir/h22-inf3135-tp1
$ cd ./h22-inf3135-tp1
```

Vous vous trouverez dans le repertoire du projet.

### Compilation ###
Pour compiler le projet taper le commande : 

```sh
$ make
```

Ci vous n'avez par le programme GCC installer sur votre machine taper : 

```sh
$ sudo apt-get install gcc
```

### Execution ###

Pour afficher le manuel d'utilisation du projet taper la commande suivante apres la compilation:

```sh
$ ./motdedyck
```

Vous pouvez ecrire vos entrée en parametres comme suit :

```sh
$ ./motdedyck a b aabb
```

```sh
$ ./motdedyck hauteur a b aabb
```

```sh
$ ./motdedyck aire a b aabb
```

Vous pouvez ecrire vos entrée dans un fichier et rediriger l'entrée standard comme suit : 

```sh
$ ./motdedyck < monFichier.txt
```

Finalement vous pouvez specifier des options comme suit : 

```sh
$ ./motdedyck hauteur < monFichier.txt
```

## Tests :hammer: ##

Pour executer les testes automatiques, il est imperatif d'installer Bats sur ca machine. Pour cela ci ce n'est pas deja fait, vous pouvez lancer la commande : 

```sh
$ sudo apt-get install bats
```

Tout les testes sont en status 'ok' sauf le #8.


## Dépendances :books: ##

Les dépendances de projets sont : 

* GCC
* [Bats] (https://github.com/bats-core/bats-core)
* string.h (librairie standard)
* ctype.h (libraire standard)

## Références :sos: ##

Indiquez ici les références que vous avez utilisées pour compléter le projet,
avec l'hyperlien vers la référence. Pas besoin de mentionner les diapositives
du cours, mais si vous avez eu recours à un site d'aide, un fragment de code ou
une discussion sur un forum, mentionnez-le.
