> # Le conflit qui n'en est pas un

**Énoncé :**
Deux personnes modifient le même fichier, mais à deux endroits éloignés. Montrez que git assemble les deux sans rien demander.

---

### Création d'un fichier de test

```bash
$ touch hello.dart
```
### Création d'une branche

```bash
$ git checkout -b top1
Switched to a new branch 'top1'

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (top1)
$

```

* Sur cette branche, édite `hello.dart` en ajoutant quelques lignes dans ce fichier ;
* Enregistrer et faire `git add hello.dart`
* Commit avec ``git commit -m "Ajout de la première modification"``

```bash
$ git add hello.dart
warning: in the working copy of 'hello.dart', LF will be replaced by CRLF the ne
xt time Git touches it

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (top1)
$ git commit -m "Ajout de la première modification"
[top1 07c0a49] Ajout de la première modification
 1 file changed, 4 insertions(+)
```

### Création d'une deuxième branche

Je simule la deuxième personne qui modifie le fichier ailleurs.
``git checkout -b top2 main`` pour repartir de la branche principale.
* Modification de ``hello.dart`` mais cette fois en bas du fichier
* J'enregistre et je fais ``git add hello.dart``
* Commit avec ``git commit -m "Ajout de la deuxième modification"``.

```bash
$ git add hello.dart
warning: in the working copy of 'hello.dart', LF will be replaced by CRLF the ne
xt time Git touches it

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (top2)
$ git commit -m "Ajout de la deuxième modification"
[top2 7e06da4] Ajout de la deuxième modification
 1 file changed, 5 insertions(+)
```

### Fusionner les modifications

J'assemble les deux contributions pour voir si Git gère automatiquement. ``git checkout main`` pour revenir sur le main.

* Je fusionne la première branche : ``git merge top1``
* Je fusionne ensuite la deuxième : ``git merge top2``
* Git détecte que les modifications sont dans des zones distinctes et fusionne automatiquement sans conflit

```bash
$ git merge top1
Updating da73efd..07c0a49
Fast-forward
 hello.dart | 4 ++++
 1 file changed, 4 insertions(+)

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git merge top2
Auto-merging hello.dart
CONFLICT (content): Merge conflict in hello.dart
Automatic merge failed; fix conflicts and then commit the result.

```

***CONCLUSION :*** Cette ligne "CONFLICT (content): Merge conflict in hello.dart" fais savoir qu'il y'a eu un conflit entre ces différents fichiers. On peut très bien le voir dans le fichier via ces deux indicateurs :

```dart
<<<<<<< HEAD (Current Chnage)
void main(){
        print("Hello le monde en dart!");
        return 0;
=======
enum Top{
        MAUVAIS,
        BON,
        NEUTRE
>>>>>>> top2 (Incoming Change)
}
```