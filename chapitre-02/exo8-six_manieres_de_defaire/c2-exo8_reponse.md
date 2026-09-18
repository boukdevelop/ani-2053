> # Six manières de défaire

***Énoncé :***
Provoquez, puis défaites, ces six situations : une modification non voulue, un add de trop, un commit de trop, un commit poussé qu'il faut annuler, un travail en cours qu'il faut mettre de côté, et un commit « perdu » à retrouver par le reflog.

## 1. Une modification non voulue (dans le répertoire de travail) :

* Je fais un `git status` après avoir modifier mon fichier :
```bash
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   hello.dart

no changes added to commit (use "git add" and/or "git commit -a")

```
Pour annuler les modification non-indexées j'utilise la commande `git restore <nom_du_fichier>` :

```bash
$ git restore hello.dart

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git status
On branch main
Your branch is up to date with 'origin/main'.

nothing to commit, working tree clean
```

On remarque que le git status n'affiche rien comme modification et mentionne que tout est à jour.

---

## 2. Un `add` de trop (fichier indexé par erreur)

Je vais d'abord créer un fichier et apporter des modifications au précédent fichier.

```bash
$ ls
hello.dart  top.cpp

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   hello.dart

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        top.cpp

no changes added to commit (use "git add" and/or "git commit -a")

```
On voit bien dans la sortie de l'état que les fichiers ajoutés viennent d'être modifiés. Après avoir fait un git add, le status affichait tout en vert hors je voulais seulement envoyer le deuxième fichier **top.cpp**. Pour y remedier je ferai un `git restore --staged <NAME_FILE>`.

```bash
$ git restore --staged hello.dart

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        new file:   top.cpp

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   hello.dart
```
Ainsi donc, **hello.dart** redevient en rouge et **top.cpp** reste en vert. Preuve que la commande a fonctionnée.

---

## 3. Un commit de trop (en local, non poussé)

J'ai modifier le fichier **top.cpp** et j'ai fais un commit trop top, mais heureusement je suis revenue en arrière via `git reset --soft HEAD^` :
```bash
$ git add top.cpp
warning: in the working copy of 'top.cpp', LF will be replaced by CRLF the next
time Git touches it

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git commit -m "Commit erroné"
[main 1cf4322] Commit erroné
 1 file changed, 5 insertions(+)

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git status
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git reset --soft HEAD^

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Changes to be committed:
  (use "git restore --staged <file>..." to unstage)
        modified:   top.cpp

```

---

## 4. Un commit poussé qu'il faut annuler (sur un dépôt distant)

Afin de mener à bien cette exercice, je dois d'abord push une modification. Et afficher l'historique des deux derniers commits sur une ligne.

```bash
$ git log --oneline -n 2
c6316b9 (HEAD -> main, origin/main, origin/HEAD) COmmit d'erreur
37af9c8 Modification sur le status
```

Pour annuler le derniers commit push, j'utilise ces différentes commandes pour revenire en arrière et push le nouveau commit :

```bash
git revert HEAD
git push origin main
```

On peut très clairement voir à la première ligne que le dernier commit a changer.

```bash
$ git log --oneline -n 3
71ecd15 (HEAD -> main) Revert "COmmit d'erreur"
c6316b9 (origin/main, origin/HEAD) COmmit d'erreur
37af9c8 Modification sur le status
```

## 5. Un travail en cours qu'il faut mettre de côté (Stash)

Pour défaire la situation je mets d'abord de coté ce travail avec ``git stash``.

```bash
$ git status
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   hello.dart

no changes added to commit (use "git add" and/or "git commit -a")

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git stash
Saved working directory and index state WIP on main: 71ecd15 Revert "COmmit d'er
reur"

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git status
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

nothing to commit, working tree clean

```

On peut constater que le fichier que j'ai modifier n'est plus visible via le `git status`. L'espace de travail est propre. Une fois le travail urgent terminé, Je récupères mes modifications via : `git stash pop` :

```bash
$ git stash pop
On branch main
Your branch is ahead of 'origin/main' by 1 commit.
  (use "git push" to publish your local commits)

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   hello.dart

no changes added to commit (use "git add" and/or "git commit -a")
Dropped refs/stash@{0} (3cbb0c78857375d72dca25eb58df4e2782b6949e)
```

## 6. Un commit « perdu » à retrouver par le `reflog`

Dans une situation où j'ai fait un commit puis je l'ai perdu via un `git reset --hard` par exemple, le dernier commit peut être recupéré via `git reflog -n 3` en repérant le numéro de la ligne juste avant l'action destructrice (ex: HEAD@{1} ou le hash du commit), puis je le récupère :

```txt
git checkout <hash_du_commit_perdu>
# ou recréez une branche par sécurité :
git checkout -b branche-sauvee <hash_du_commit_perdu>
```

### Création du problème

```bash
$ git reset --hard
HEAD is now at c1020e6 Commit à recherche après le git resst --hard
```

### Relistage des trois derniers commit

```bash
$ git reflog -n 3
c1020e6 (HEAD -> main) HEAD@{0}: reset: moving to HEAD
c1020e6 (HEAD -> main) HEAD@{1}: commit: Commit à recherche après le git resst -
-hard
71ecd15 HEAD@{2}: reset: moving to HEAD
```

### Récupération du commit perdu :

```bash
$ git checkout HEAD@{1}
Note: switching to 'HEAD@{1}'.

You are in 'detached HEAD' state. You can look around, make experimental
changes and commit them, and you can discard any commits you make in this
state without impacting any branches by switching back to a branch.

If you want to create a new branch to retain commits you create, you may
do so (now or later) by using -c with the switch command. Example:

  git switch -c <new-branch-name>

Or undo this operation with:

  git switch -

Turn off this advice by setting config variable advice.detachedHead to false

HEAD is now at c1020e6 Commit à recherche après le git resst --hard

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures ((c1020e6...))
$ git log
commit c1020e674554f77593c0618882973fc7a6737d61 (HEAD, main)
Author: FRANCK <boukalafranck0@gmail.com>
Date:   Fri Sep 18 13:18:24 2026 +0200

    Commit à recherche après le git resst --hard
```