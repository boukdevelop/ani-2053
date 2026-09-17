# Exercices — Vivre dans le dépôt des autres

Afin de mener à bien cette exercice, j'ai fait dans l'ordre ces différentes commandes :

## `git init` : afin d'initialiser mon depôt;

```bash
FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure
$ git init
Initialized empty Git repository in C:/Users/FRANCK/Desktop/cassure/.git/
```

## Avant de commencer quoi que se soit, j'ai d'abord cloné mon depôt :

```bash
$ git clone https://github.com/boukdevelop/cassures.git
Cloning into 'cassures'...
remote: Enumerating objects: 3, done.
remote: Counting objects: 100% (3/3), done.
remote: Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
Receiving objects: 100% (3/3), done.

```

## Puis, j'ai ajouter trois fichiers : 
```bash
FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ touch file1.txt file2.dart file3.cpp

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ ls
README.md  file1.txt  file2.dart  file3.cpp
```

## J'ai vérifier l'état avec `git status` :

```bash
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        file1.txt
        file2.dart
        file3.cpp

nothing added to commit but untracked files present (use "git add" to track)
```

## Je fais des ajout consécutif avec `git add Nom_fichier`;

## Suivi du commit adéquat `git commit -m "le message que je mets`

***Récapitulatif :***

---
### #1

```bash
FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git add file1.txt
$ git commit -m "Ajout du file 1"
[main 4d094e6] Ajout du file 1
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 file1.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git push
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 4 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (3/3), 284 bytes | 284.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/boukdevelop/cassures.git
   02a7c3e..4d094e6  main -> main

```

### #2

```bash
FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git add file2.dart
$ git commit -m "Add of file 2"
[main efe006d] Add of file 2
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 file2.dart

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git push
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Delta compression using up to 4 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (2/2), 284 bytes | 284.00 KiB/s, done.
Total 2 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/boukdevelop/cassures.git
   4d094e6..efe006d  main -> main

```

### #3

```bash
$ git add file3.cpp

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git commit -m "Add of file 3"
[main ef292a7] Add of file 3
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 file3.cpp

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git push
Enumerating objects: 3, done.
Counting objects: 100% (3/3), done.
Delta compression using up to 4 threads
Compressing objects: 100% (2/2), done.
Writing objects: 100% (2/2), 259 bytes | 259.00 KiB/s, done.
Total 2 (delta 1), reused 0 (delta 0), pack-reused 0 (from 0)
remote: Resolving deltas: 100% (1/1), completed with 1 local object.
To https://github.com/boukdevelop/cassures.git
   efe006d..ef292a7  main -> main


```

## Afin d'fficher l'historique en une ligne par commit. Puis affichez le graphe j'ai fait ces différentes commandes :

* > `git log --oneline` pour afficher l'historique en une ligne :
```bash
$ git log --oneline
ef292a7 (HEAD -> main, origin/main, origin/HEAD) Add of file 3
efe006d Add of file 2
4d094e6 Ajout du file 1
02a7c3e Initial commit

```

* > `git log --graph` pour afficher le graph :

```bash
* commit ef292a725eb08581478b9e5d77ba344af2a1f8d7 (HEAD -> main, origin/main, or
igin/HEAD)
| Author: FRANCK <boukalafranck0@gmail.com>
| Date:   Thu Sep 17 06:51:46 2026 +0200
|
|     Add of file 3
|
* commit efe006d88817c273dd3e12a081c73a92266f3f72
| Author: FRANCK <boukalafranck0@gmail.com>
| Date:   Thu Sep 17 06:51:03 2026 +0200
|
|     Add of file 2
|
* commit 4d094e6d610e84b2dffa59c580df2c6863fedc88
| Author: FRANCK <boukalafranck0@gmail.com>
| Date:   Thu Sep 17 06:49:35 2026 +0200
|
|     Ajout du file 1
|
* commit 02a7c3edb28f97f2e4b4d98e1a68bd07d5e3875e
  Author: FRANCK <boukalafranck0@gmail.com>
  Date:   Thu Sep 17 12:12:49 2026 +0200

      Initial commit

```

**NB :** Je tiens à préciser que ce sont des fichiers vides !
