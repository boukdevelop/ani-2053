# Le commit partiel

***Énoncé :***
Modifiez deux choses sans rapport dans le même fichier, puis faites-en deux commits séparés avec git add -p. Vérifiez dans l'historique que chacun ne contient que son sujet.

---

Avant de faire quoi que se soit comme ajout ou push, j'ai biensûr fait un `git status`.

## La première sortie de `git add -p` est :
```bash
warning: in the working copy of 'file1.txt', LF will be replaced by CRLF the nex
t time Git touches it
diff --git a/file1.txt b/file1.txt
index 936c671..3d27350 100644
--- a/file1.txt
+++ b/file1.txt
@@ -1,2 +1,14 @@
 Modification du premier fichier

+# Le commit partiel
+
+***Énoncé :***
+Modifiez deux choses sans rapport dans le même fichier, puis faites-en deux com
mits séparés avec git add -p. Vérifiez dans l'historique que chacun ne contient
que son sujet.
+
+Top départ sur le devoir,
+
+Bloc deux su rle fichier test de départ
+
+---
+
+
(1/1) Stage this hunk [y,n,q,a,d,e,p,?]?

```
Dans cette sortie j'ai remarqué `y,n,q,a,d,e,p,?`, qui veulent chacun dire :
* y (yes) : Ajouter ce morceau à l'index.

* n (no) : Ne pas ajouter ce morceau pour l'instant.

* s (split) : Diviser ce morceau en sous-morceaux plus petits si le bloc est trop gros.

* e (edit) : Éditer manuellement le morceau directement dans votre éditeur de texte.
* q (quit) : Quitter et annuler les sélections en cours.
* ? : Afficher la liste complète de toutes les options disponibles.

```bash
$ git add -p
warning: in the working copy of 'file1.txt', LF will be replaced by CRLF the nex
t time Git touches it
warning: in the working copy of 'file1.txt', LF will be replaced by CRLF the nex
t time Git touches it
diff --git a/file1.txt b/file1.txt
index 3d27350..3f242a8 100644
--- a/file1.txt
+++ b/file1.txt
@@ -11,4 +11,7 @@ Bloc deux su rle fichier test de départ

 ---

+Bloc 2{
+Bavardage du bloc N°2
+}

(1/1) Stage this hunk [y,n,q,a,d,e,p,?]? y


FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git commit -m "Ajout du premier bloc"
[main 3507503] Ajout du premier bloc
 1 file changed, 3 insertions(+)
```

---

```bash
$ nano file1.txt

FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git add -p
warning: in the working copy of 'file1.txt', LF will be replaced by CRLF the nex
t time Git touches it
warning: in the working copy of 'file1.txt', LF will be replaced by CRLF the nex
t time Git touches it
diff --git a/file1.txt b/file1.txt
index 3f242a8..22f2417 100644
--- a/file1.txt
+++ b/file1.txt
@@ -15,3 +15,6 @@ Bloc 2{
 Bavardage du bloc N°2
 }

+Bloc 3{
+Bla bla Numero 2
+}
(1/1) Stage this hunk [y,n,q,a,d,e,p,?]? y


FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/cassure/cassures (main)
$ git commit -m "Ajout du bloc N2 au niveau du bloc3{} c'est juste le nom qui change, mais c'est bien le bloc 2"
[main 8012737] Ajout du bloc N2 au niveau du bloc3{} c'est juste le nom qui chan
ge, mais c'est bien le bloc 2
 1 file changed, 3 insertions(+)

```

---

Pour vérifier dans l'historique que chacun ne contient que son sujet, j'ai utilisé la commande `git log -p -n 2`

```bash
$ git log -p -n 2
commit 80127377c1be3716263b9efb26d22c199af41c8b (HEAD -> main)
Author: FRANCK <boukalafranck0@gmail.com>
Date:   Thu Sep 17 08:45:44 2026 +0200

    Ajout du bloc N2 au niveau du bloc3{} c'est juste le nom qui change, mais c'
est bien le bloc 2

diff --git a/file1.txt b/file1.txt
index 3f242a8..22f2417 100644
--- a/file1.txt
+++ b/file1.txt
@@ -15,3 +15,6 @@ Bloc 2{
 Bavardage du bloc N°2
 }
commit 80127377c1be3716263b9efb26d22c199af41c8b (HEAD -> main)
Author: FRANCK <boukalafranck0@gmail.com>
Date:   Thu Sep 17 08:45:44 2026 +0200

    Ajout du bloc N2 au niveau du bloc3{} c'est juste le nom qui change, mais c'
est bien le bloc 2

diff --git a/file1.txt b/file1.txt
index 3f242a8..22f2417 100644
--- a/file1.txt
+++ b/file1.txt
@@ -15,3 +15,6 @@ Bloc 2{
 Bavardage du bloc N°2
 }

+Bloc 3{
+Bla bla Numero 2
+}

commit 3507503c4911002ca5f0544059f83012e03e76c1
Author: FRANCK <boukalafranck0@gmail.com>
Date:   Thu Sep 17 08:43:51 2026 +0200

    Ajout du premier bloc

diff --git a/file1.txt b/file1.txt
index 3d27350..3f242a8 100644
--- a/file1.txt
+++ b/file1.txt
@@ -11,4 +11,7 @@ Bloc deux su rle fichier test de départ

 ---

+Bloc 2{
+Bavardage du bloc N°2
+}

(END)
```

**CONCLUSION :** Chacun est bien dans son bloc.