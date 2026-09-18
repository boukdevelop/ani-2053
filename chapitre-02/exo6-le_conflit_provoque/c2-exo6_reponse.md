> # Le conflit provoqué

***Énoncé :***
Depuis deux répertoires de travail, ou deux clones, modifiez la même ligne d'un même fichier et poussez l'un des deux. Provoquez le refus, puis le conflit, puis résolvez-le. Rendez chaque message affiché.

---

Pour simuler deux machines/développeurs sur le même dépôt local tout en simulant le comportement distant (push/refus/conflit), nous allons créer **deux branches (`dev1` et `dev2`) qui poussent vers la même branche distante (`main`)**.

#### 1. Préparation du fichier initial sur `main`

Création du fichier de départ et effectuation d'un premier push pour établir la base commune.

```bash
$ echo "Ligne 1 : La ligen originale de ce ficheir que je vais changer au fur et à mesure" > file.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git add file.txt
warning: in the working copy of 'file.txt', LF will be replaced by CRLF the next
 time Git touches it

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git commit -m "Commit initial de ce fichier"
[main 11cebc2] Commit initial de ce fichier
 1 file changed, 1 insertion(+)
 create mode 100644 file.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (main)
$ git push origin main
Enumerating objects: 4, done.
Counting objects: 100% (4/4), done.
Delta compression using up to 4 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 394 bytes | 131.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/boukdevelop/cassures.git
   c6316b9..11cebc2  main -> main
```

---

#### 2. Simulation du Développeur 1 (Modification + Push réussi)

```bash
$ git checkout -b dev1 main
Switched to a new branch 'dev1'

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (dev1)
$ echo "Ligne 1 : Modification apportée par le développeur 1" > file.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (dev1)
$ git add file.txt
warning: in the working copy of 'file.txt', LF will be replaced by CRLF the next
 time Git touches it

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (dev1)
$ git commit -m "Modification du développeur N°1"
[dev1 320a6ff] Modification du développeur N°1
 1 file changed, 1 insertion(+), 1 deletion(-)

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (dev1)
$ git push origin dev1:main
Enumerating objects: 5, done.
Counting objects: 100% (5/5), done.
Delta compression using up to 4 threads
Compressing objects: 100% (3/3), done.
Writing objects: 100% (3/3), 393 bytes | 131.00 KiB/s, done.
Total 3 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/boukdevelop/cassures.git
   11cebc2..320a6ff  dev1 -> main
```

---

#### 3. Simulation du Développeur 2 (Modification + Refus du Push)

Le deuxième développeur travaille en parallèle à partir de la version initiale (sans avoir récupéré le travail de Dev1).

```bash
$ git checkout -b dev2 11cebc2
Switched to a new branch 'dev2'

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (dev2)
$ echo "Ligne 1 : Modification apportée par le développeur N°2" > file.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (dev2)
$ git add file.txt
warning: in the working copy of 'file.txt', LF will be replaced by CRLF the next
 time Git touches it

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (dev2)
$ git commit -m "Mmodification apportée par le developpeur 2"
[dev2 2311eb1] Mmodification apportée par le developpeur 2
 1 file changed, 1 insertion(+), 1 deletion(-)

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (dev2)
$ git push origin dev2:main
To https://github.com/boukdevelop/cassures.git
 ! [rejected]        dev2 -> main (non-fast-forward)
error: failed to push some refs to 'https://github.com/boukdevelop/cassures.git'
hint: Updates were rejected because a pushed branch tip is behind its remote
hint: counterpart. If you want to integrate the remote changes, use 'git pull'
hint: before pushing again.
hint: See the 'Note about fast-forwards' in 'git push --help' for details.


```

---

#### 4. Provoquer le Conflit avec `git pull`

Suite au refus, Dev2 doit récupérer les modifications distantes. C'est ici que le conflit se déclare.

```bash
FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (dev2)
$ git pull origin main
From https://github.com/boukdevelop/cassures
 * branch            main       -> FETCH_HEAD
Auto-merging file.txt
CONFLICT (content): Merge conflict in file.txt
Automatic merge failed; fix conflicts and then commit the result.
```

---

#### 5. Résolution du Conflit

On ouvre `top.txt`. Git y a inséré les marqueurs de conflit :

```text
<<<<<<< HEAD
Ligne 1 : Modification apportée par le développeur N°2
=======
Ligne 1 : Modification apportée par le développeur 1
>>>>>>> 320a6ffa2e04f614916173cf4b2996b45abbcdea
```

maintenant on change son contenue pour avoir le contenu final voulue :

```text
Ligne 1 : Modification finale resolue (Dev1 + Dev2)

```

Validez la résolution et poussez :

```bash
$ git add file.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (dev2|MERGING)
$ git status
On branch dev2
All conflicts fixed but you are still merging.
  (use "git commit" to conclude merge)

Changes to be committed:
        modified:   file.txt


FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (dev2|MERGING)
$ git commit -m "Résolution du conflit"
[dev2 cdfef82] Résolution du conflit

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassures/cassures (dev2)
$ git push origin dev2:main
Enumerating objects: 10, done.
Counting objects: 100% (10/10), done.
Delta compression using up to 4 threads
Compressing objects: 100% (6/6), done.
Writing objects: 100% (6/6), 842 bytes | 168.00 KiB/s, done.
Total 6 (delta 0), reused 0 (delta 0), pack-reused 0 (from 0)
To https://github.com/boukdevelop/cassures.git
   320a6ff..cdfef82  dev2 -> main

```