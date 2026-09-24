> # Les trois endroits

***Énoncé :***
Modifiez un fichier, et affichez git status après chaque étape : modification, add, commit. Rendez les trois sorties et dites ce qui change entre elles.

---

## Modification d'un fichier :

```bash
$ nano file1.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git status
On branch main
Your branch is up to date with 'origin/main'.

Changes not staged for commit:
  (use "git add <file>..." to update what will be committed)
  (use "git restore <file>..." to discard changes in working directory)
        modified:   file1.txt

no changes added to commit (use "git add" and/or "git commit -a")

```
## Ajout du fichier modifier par `git add file1.txt` :

```bash
$ git add file1.txt
warning: in the working copy of 'file1.txt', LF will be replaced by CRLF the nex
t time Git touches it
```
**NB :** Le `warning` est lié à un passage à la ligne, Git me prévient qu'il convertit automatiquement les fins de ligne de mes fichiers pour qu'ils soient au format Windows (CRLF).

## Commit :

```bash
$ git commit -m "Modification du file1.txt"
[main 3589453] Modification du file1.txt
 1 file changed, 2 insertions(+)

```

**REMARQUE :** Ce qui change entre toutes ces lignes est le message qui me dit si un fichier a été modifié, signé ou pas.
