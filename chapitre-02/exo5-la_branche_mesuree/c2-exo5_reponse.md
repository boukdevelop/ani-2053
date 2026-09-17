# La branche mesurée

***Énoncé :***
Créez une branche, faites trois commits dessus, et mesurez la place que le dépôt a gagnée sur le disque. Expliquez le résultat.

---

## Création d'une branche
Je crée une branche nommée **second** via la commande`git branch second` et je me redirige vers elle via `git switch second` :

```bash
$ git branch -a
* main
  remotes/origin/HEAD -> origin/main
  remotes/origin/main

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git branch second

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git branch -a
* main
  second
  remotes/origin/HEAD -> origin/main
  remotes/origin/main

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git switch second
Switched to branch 'second'

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (second)
$

```

## Création de trois commit par la création de trois fichiers

J'utilise la commande `touch` pour créer diretement trois ficheirs vides :
```bash
$ touch second1.txt second2.txt second3.cpp

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (second)
$ ls
README.md  file2.dart  second1.txt  second3.cpp
file1.txt  file3.cpp   second2.txt
```

On y voit très clairement les fichiers qui ont été ajoutés. Avant faire quoi que se soit, je vérifie d'abord l'état d'avancement.

Puis je fais un pull request directement sur *GitHub*

```bash
$ git add second1.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (second)
$ git commit -m "Premier commit"
[second ba27a6d] Premier commit
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 second1.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (second)
$ git add second2.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (second)
$ git commit -m "Second commit"
[second b80c9fc] Second commit
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 second2.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (second)
$ git add second3.cpp

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (second)
$ git commit -m "Troisième commit"
[second 68f1da8] Troisième commit
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 second3.cpp

```

> la commande `du -sh .git` Affiche la taille totale occupée par l'historique de mon projet sur le disque.
```bash
$ du -sh .git
121K    .git
```
Le projet pèse donc 121Ko sur le disque.

**CONCLUSION :** Un commit ne pèse quasi rien dans un projet de même que la créationd'une branche, car la création d'une branche n'est que la création d'un pointeur textuels.