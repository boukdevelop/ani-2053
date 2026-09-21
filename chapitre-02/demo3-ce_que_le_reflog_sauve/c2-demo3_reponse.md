> # Ce que le `reflog` sauve

***Énoncé :*** 
Détruisez un travail par un reset --hard volontaire, faites constater la perte, puis retrouvez-le par le reflog.
--

## Après l'emploi de `git reset --hard`

Après le git reset --hard on voit que le dernier commit a été enlené et un message du genre ***d67cf45 (HEAD -> main) HEAD@{0}: reset: moving to HEAD*** s'affiche en double dans mon cas, car j'ai taper la commande deux fois de suite. Le commit est certe encore visible dans le `git log --oneline`, mais le contenu du fichier est revenu à l'étape d'avant le dit commit d'avant :

```bash
FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git reset --hard
HEAD is now at d67cf45 Modification après le git reflog

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git log --oneline
d67cf45 (HEAD -> main) Modification après le git reflog
eb22bce Modification qui seras perdue par le reset hard
2a12837 (origin/main, origin/HEAD) Modification avant le hard reset
530df2a (origin/personneB) Premier commit concernant ce fichier de test de conflit
173a554 Suppression multiple
b070811 Suppression du fichier 3D
c0bc1e2 Object 3D
07abea3 .
5c73678 :wq
a35d63f Ajout d'un fichier de 19707Ko donc 19Mo
d72fe54 feat: ajout de la fonction 2
82acfa6 Merge branch 'feature-merge'
bd93c13 fix: mise à jour sur main
25ed2d1 feat: ajout de la fonction 1
cdfef82 Résolution du conflit
2311eb1 Mmodification apportée par le developpeur 2
320a6ff Modification du développeur N°1
11cebc2 Commit initial de ce fichier
c6316b9 COmmit d'erreur
37af9c8 Modification sur le status
6307c09 Revert "Commit push par erreur"
ee1a12e Commit push par erreur
e1bb5c4 .
a4fa090 Ajout de top.cpp
aeab9f3 Derniere modif
849bf07 Suppression en court
07c0a49 Ajout de la première modification
da73efd Suppression
ce3be57 Ajout d'un fichier test
c1e4d6c Suppression de tous les éléments du dépôt
9b0b228 Merge pull request #1 from boukdevelop/branch
3d3ef71 Ajout du premrier commit du conflit
017a749 Modification principale
8012737 Ajout du bloc N2 au niveau du bloc3{} c'est juste le nom qui change, mais c'est bien le bloc 2
3507503 Ajout du premier bloc
385b5a3 Ajout du premier bloc
3589453 Modification du file1.txt
ef292a7 Add of file 3
efe006d Add of file 2
4d094e6 Ajout du file 1
02a7c3e Initial commit

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git reset --hard
HEAD is now at d67cf45 Modification après le git reflog

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ gi log --oneline
bash: gi: command not found

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git log --oneline
d67cf45 (HEAD -> main) Modification après le git reflog
eb22bce Modification qui seras perdue par le reset hard
2a12837 (origin/main, origin/HEAD) Modification avant le hard reset
530df2a (origin/personneB) Premier commit concernant ce fichier de test de conflit
173a554 Suppression multiple
b070811 Suppression du fichier 3D
c0bc1e2 Object 3D
07abea3 .
5c73678 :wq
a35d63f Ajout d'un fichier de 19707Ko donc 19Mo
d72fe54 feat: ajout de la fonction 2
82acfa6 Merge branch 'feature-merge'
bd93c13 fix: mise à jour sur main
25ed2d1 feat: ajout de la fonction 1
cdfef82 Résolution du conflit
2311eb1 Mmodification apportée par le developpeur 2
320a6ff Modification du développeur N°1
11cebc2 Commit initial de ce fichier
c6316b9 COmmit d'erreur
37af9c8 Modification sur le status
6307c09 Revert "Commit push par erreur"
ee1a12e Commit push par erreur
e1bb5c4 .
a4fa090 Ajout de top.cpp
aeab9f3 Derniere modif
849bf07 Suppression en court
07c0a49 Ajout de la première modification
da73efd Suppression
ce3be57 Ajout d'un fichier test
c1e4d6c Suppression de tous les éléments du dépôt
9b0b228 Merge pull request #1 from boukdevelop/branch
3d3ef71 Ajout du premrier commit du conflit
017a749 Modification principale
8012737 Ajout du bloc N2 au niveau du bloc3{} c'est juste le nom qui change, mais c'est bien le bloc 2
3507503 Ajout du premier bloc
385b5a3 Ajout du premier bloc
3589453 Modification du file1.txt
ef292a7 Add of file 3
efe006d Add of file 2
4d094e6 Ajout du file 1
02a7c3e Initial commit

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git reflog --oneline
d67cf45 (HEAD -> main) HEAD@{0}: reset: moving to HEAD
d67cf45 (HEAD -> main) HEAD@{1}: reset: moving to HEAD
d67cf45 (HEAD -> main) HEAD@{2}: reset: moving to d67cf45
c0bc1e2 HEAD@{3}: reset: moving to c0bc1e2
d67cf45 (HEAD -> main) HEAD@{4}: reset: moving to d67cf45
e185468 HEAD@{5}: reset: moving to e185468
e185468 HEAD@{6}: commit: Suppression de fichier indésirable
3af0ee4 HEAD@{7}: reset: moving to HEAD
3af0ee4 HEAD@{8}: reset: moving to HEAD
3af0ee4 HEAD@{9}: commit: Nouvelle modification avant le git reset --hard
d67cf45 (HEAD -> main) HEAD@{10}: reset: moving to HEAD
d67cf45 (HEAD -> main) HEAD@{11}: commit: Modification après le git reflog
eb22bce HEAD@{12}: reset: moving to HEAD
eb22bce HEAD@{13}: commit: Modification qui seras perdue par le reset hard
2a12837 (origin/main, origin/HEAD) HEAD@{14}: commit: Modification avant le hard reset
530df2a (origin/personneB) HEAD@{15}: reset: moving to HEAD
530df2a (origin/personneB) HEAD@{16}: reset: moving to HEAD
530df2a (origin/personneB) HEAD@{17}: reset: moving to HEAD
530df2a (origin/personneB) HEAD@{18}: checkout: moving from personneA to main
db281b0 (origin/personneA, personneA) HEAD@{19}: commit (merge): feat: Merge final de tout le travail, et suppression du travail des deux personnes
a6f750d HEAD@{20}: checkout: moving from personneB to personneA
a65cccd (personneB) HEAD@{21}: commit: Modification apportée par la première personne (B)
530df2a (origin/personneB) HEAD@{22}: checkout: moving from main to personneB
530df2a (origin/personneB) HEAD@{23}: checkout: moving from personneA to main
a6f750d HEAD@{24}: commit: Modification apportée par la première personne (A)
530df2a (origin/personneB) HEAD@{25}: checkout: moving from main to personneA
530df2a (origin/personneB) HEAD@{26}: commit: Premier commit concernant ce fichier de test de conflit
173a554 HEAD@{27}: commit: Suppression multiple
b070811 HEAD@{28}: checkout: moving from main to main
b070811 HEAD@{29}: commit: Suppression du fichier 3D
c0bc1e2 HEAD@{30}: commit: Object 3D
07abea3 HEAD@{31}: commit: .
5c73678 HEAD@{32}: pull origin main: Merge made by the 'ort' strategy.
a35d63f HEAD@{33}: commit: Ajout d'un fichier de 19707Ko donc 19Mo
d72fe54 HEAD@{34}: merge feature-rebase: Fast-forward
82acfa6 HEAD@{35}: checkout: moving from feature-rebase to main
d72fe54 HEAD@{36}: commit: feat: ajout de la fonction 2
82acfa6 HEAD@{37}: checkout: moving from main to feature-rebase
82acfa6 HEAD@{38}: merge feature-merge: Merge made by the 'ort' strategy.
bd93c13 HEAD@{39}: commit: fix: mise à jour sur main
11cebc2 HEAD@{40}: checkout: moving from feature-merge to main
25ed2d1 HEAD@{41}: commit: feat: ajout de la fonction 1
11cebc2 HEAD@{42}: checkout: moving from main to feature-merge
11cebc2 HEAD@{43}: checkout: moving from dev2 to main
cdfef82 HEAD@{44}: commit (merge): Résolution du conflit
2311eb1 HEAD@{45}: commit: Mmodification apportée par le developpeur 2
11cebc2 HEAD@{46}: checkout: moving from dev1 to dev2
320a6ff HEAD@{47}: commit: Modification du développeur N°1
11cebc2 HEAD@{48}: checkout: moving from main to dev1
11cebc2 HEAD@{49}: commit: Commit initial de ce fichier
c6316b9 HEAD@{50}: clone: from https://github.com/boukdevelop/cassures.git
```

---

Pour annuler les effets du reset hard, j'ai pris le commit visé ainsi :

```bash
FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git reset --hard HEAD@{0}
HEAD is now at d67cf45 Modification après le git reflog
```

Et le fichier est redevenue comme neuf.

***REMARQUE :*** `git reset --hard` détruit complètement les midifications qi n'ont pas été commités, contrairement à celle qui l'ont été car l'emprunte de ces modifications seras toujours visibles à l'aide de `git reflog`.s