> # Fusionner ou rejouer

***Énoncé :***
Sur votre dépôt d'essai, faites deux fois la même intégration : une fois par fusion, une fois en rejouant. Comparez les deux graphes, et dites lequel vous préférez lire, avec un argument.
--

Voici la séquence de commandes pas à pas pour réaliser les deux types d'intégrations sur deux branches de fonctionnalités distinctes (feature-merge et feature-rebase).

## Méthode 1 : Intégration par fusion (git merge)

Cette méthode conserve les deux branches parallèles et crée un commit de fusion.

* Créer et se placer sur une nouvelle branche :

```bash
git checkout -b feature-merge
Ajouter un commit sur la branche :

echo "Code feature 1" > feature1.txt
git add feature1.txt
git commit -m "feat: ajout de la fonction 1"
Revenir sur main et simuler un travail parallèle (optionnel mais illustratif) :
```

```bash
git checkout main
echo "Code main" > main.txt
git add main.txt
git commit -m "fix: mise a jour sur main"
Réaliser la fusion :
```

```bash
git merge feature-merge
(Un message de commit de fusion s'ouvre dans votre éditeur, validez-le).
```

* Visualiser le graphe :

```bash
git log --graph --oneline --all
```

### ***bref :***

```bash
$ git checkout -b feature-merge
Switched to a new branch 'feature-merge'

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (feature-merge)
$ echo "feat: ajout de la fonction 1 juste pour voir ce qui se passe, donc je pompes le fichier ci avec du texte" > feature1.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (feature-merge)
$ git add feature1.txt
warning: in the working copy of 'feature1.txt', LF will be replaced by CRLF the
next time Git touches it

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (feature-merge)
$ git commit -m "feat: ajout de la fonction 1"
[feature-merge 25ed2d1] feat: ajout de la fonction 1
 1 file changed, 1 insertion(+)
 create mode 100644 feature1.txt
























Merge made by the 'ort' strategy.
 feature1.txt | 1 +
 1 file changed, 1 insertion(+)
 create mode 100644 feature1.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git log --graph --oneline --all
*   82acfa6 (HEAD -> main) Merge branch 'feature-merge'
|\
| * 25ed2d1 (feature-merge) feat: ajout de la fonction 1
* | bd93c13 fix: mise à jour sur main
|/
| *   cdfef82 (origin/main, origin/HEAD) Résolution du conflit
| |\
| | * 320a6ff Modification du développeur N°1
| |/
|/|
| * 2311eb1 Mmodification apportée par le developpeur 2
|/
* 11cebc2 Commit initial de ce fichier
* c6316b9 COmmit d'erreur
* 37af9c8 Modification sur le status
* 6307c09 Revert "Commit push par erreur"
* ee1a12e Commit push par erreur
* e1bb5c4 .
* a4fa090 Ajout de top.cpp
* aeab9f3 Derniere modif
* 849bf07 Suppression en court
* 07c0a49 Ajout de la première modification
* da73efd Suppression
*   ce3be57 Ajout d'un fichier test
|\
| *   9b0b228 Merge pull request #1 from boukdevelop/branch
| |\
| | * 3d3ef71 Ajout du premrier commit du conflit
| |/
* / c1e4d6c Suppression de tous les éléments du dépôt
|/
* 017a749 Modification principale
* 8012737 Ajout du bloc N2 au niveau du bloc3{} c'est juste le nom qui change, m
ais c'est bien le bloc 2
* 3507503 Ajout du premier bloc
* 385b5a3 Ajout du premier bloc
* 3589453 Modification du file1.txt
* ef292a7 Add of file 3
* efe006d Add of file 2
* 4d094e6 Ajout du file 1
* 02a7c3e Initial commit
(END)
```

## Méthode 2 : Intégration en rejouant (git rebase)

Cette méthode réaligne l'historique de la branche par-dessus main avant de l'intégrer, pour obtenir un graphe linéaire.

### Créer et se placer sur une autre branche :

```bash
git checkout main
git checkout -b feature-rebase
```

### Ajouter un commit sur cette branche :

```bash
echo "Code feature 2" > feature2.txt
git add feature2.txt
git commit -m "feat: ajout de la fonction 2"
```

### Rejouer les commits par-dessus main :

```bash
git rebase main
(Git applique vos commits un par un au sommet du commit actuesl de main).
```

### Intégrer sur main de façon linéaire (Fast-forward) :

```bash
git checkout main
git merge feature-rebase
```

### Visualiser le graphe linéaire final :

```bash
git log --graph --oneline --all
```

### ***bref :***

```bash
$ git checkout -b feature-rebase
Switched to a new branch 'feature-rebase'

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (feature-rebase)
$ echo "Code pour la deuxième configuration donc le feature, je remplis encore le fichier de texte juste pour avoir beaucoup de caractères" > feature2.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (feature-rebase)
$ git add feature2.txt
warning: in the working copy of 'feature2.txt', LF will be replaced by CRLF the
next time Git touches it

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (feature-rebase)
$ git commit -m "feat: ajout de la fonction 2"
[feature-rebase d72fe54] feat: ajout de la fonction 2
 1 file changed, 1 insertion(+)
 create mode 100644 feature2.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (feature-rebase)
$ git rebase main
Current branch feature-rebase is up to date.

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (feature-rebase)
$ git checkout main
Switched to branch 'main'
Your branch and 'origin/main' have diverged,
and have 3 and 3 different commits each, respectively.
  (use "git pull" if you want to integrate the remote branch with yours)

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git merge feature-rebase
Updating 82acfa6..d72fe54
Fast-forward
 feature2.txt | 1 +
 1 file changed, 1 insertion(+)
 create mode 100644 feature2.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git log --graph --oneline --all
* d72fe54 (HEAD -> main, feature-rebase) feat: ajout de la fonction 2
*   82acfa6 Merge branch 'feature-merge'
|\
| * 25ed2d1 (feature-merge) feat: ajout de la fonction 1
* | bd93c13 fix: mise à jour sur main
|/
| *   cdfef82 (origin/main, origin/HEAD) Résolution du conflit
| |\
| | * 320a6ff Modification du développeur N°1
| |/
|/|
| * 2311eb1 Mmodification apportée par le developpeur 2
|/
* 11cebc2 Commit initial de ce fichier
* c6316b9 COmmit d'erreur
* 37af9c8 Modification sur le status
* 6307c09 Revert "Commit push par erreur"
* ee1a12e Commit push par erreur
* e1bb5c4 .
* a4fa090 Ajout de top.cpp
* aeab9f3 Derniere modif
* 849bf07 Suppression en court
* 07c0a49 Ajout de la première modification
* da73efd Suppression
*   ce3be57 Ajout d'un fichier test
|\
| *   9b0b228 Merge pull request #1 from boukdevelop/branch
| |\
| | * 3d3ef71 Ajout du premrier commit du conflit
| |/
* / c1e4d6c Suppression de tous les éléments du dépôt
|/
* 017a749 Modification principale
* 8012737 Ajout du bloc N2 au niveau du bloc3{} c'est juste le nom qui change, m
ais c'est bien le bloc 2
* 3507503 Ajout du premier bloc
* 385b5a3 Ajout du premier bloc
* 3589453 Modification du file1.txt
* ef292a7 Add of file 3
* efe006d Add of file 2
* 4d094e6 Ajout du file 1
* 02a7c3e Initial commit
(END)
```

> Argument : Le graphe linéaire améliore la lisibilité et la traçabilité. Un historique rectiligne facilite grandement la lecture chronologique des fonctionnalités, simplifie l'utilisation d'outils comme git log ou git bisect (pour retrouver l'origine d'un bug), et évite la pollution inutile du graphe par des dizaines de commits de fusion intermédiaires.