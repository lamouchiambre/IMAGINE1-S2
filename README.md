# IMAGINE1-S2


 Edition et compilation
========================

Pour organiser correctement vos fichiers, créez un répertoire "TpX" pour chacun des Tps et sauvegardez-y vos programmes.

Edition d'un fichier source
---------------------------
pour editer un fichier source (*.cpp), utilisez la syntaxe suivante :

```$ nom_editeur nom_prog.cpp```

Un exemple d'éditeur est gedit :

```$ gedit nom_prog.cpp```
Pour que le terminal n'attende pas la fin de l'édition pour reprendre la main, il faut demander à l'éditeur de s'exécuter en tâche de fond (avec &)

```$ gedit nom_prog.cpp &```

Compilation d'un programme simple
---------------------------------

Pour compiler un programme simple (1 seul fichier source), utilisez la commande suivante :

```$ g++ nom_prog.cpp -o nom_prog```

On demande au compilateur g++ de compiler le fichier source nom_prog.cpp et de créer le fichier executable nom_prog.
**Remarque :** si on ne précise pas -o nom_prog, le compilateur créera un executable nommé a.out.

Compilation d'un programme complexe
-----------------------------------

Pour compiler un programme composé de 2 fichiers sources (fonc.cpp et test_fonc.cpp), utilisez les commandes suivantes :

```
$ g++ -c fonc.cpp
$ g++ -c test_fonc.cpp
$ g++ -o test_fonc fonc.o test_fonc.o
```
