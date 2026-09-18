> Voici comment provoquer et défaire ces six situations courantes sous Git, expliquées simplement et étape par étape.

---

### 1. Une modification non voulue (dans le répertoire de travail)

* **Le problème :** Vous avez modifié un fichier, mais vous réalisez que ces modifications ne servent à rien et vous voulez revenir à la version propre précédente.
* **Provoquer la situation :** Modifiez un fichier existant sans l'ajouter (`git add`).
* **Défaire la situation :**
Utilisez la commande suivante pour annuler les modifications non indexées sur ce fichier :
```bash
git checkout -- <nom_du_fichier>
# ou la version moderne :
git restore <nom_du_fichier>

```


*Vérification :* Tapez `git status`, votre répertoire de travail doit redevenir propre.

---

### 2. Un `add` de trop (fichier indexé par erreur)

* **Le problème :** Vous avez fait un `git add <fichier>`, mais vous ne voulez pas inclure ce fichier dans votre prochain commit.
* **Prooquer la situation :** Créez ou modifiez un fichier, puis faites `git add <nom_du_fichier>`.
* **Défaire la situation :**
Retirez le fichier de la zone de staging (index) sans perdre vos modifications :
```bash
git restore --staged <nom_du_fichier>
# ou l'ancienne syntaxe :
git reset HEAD <nom_du_fichier>

```


*Vérification :* Tapez `git status`, le fichier apparaîtra de nouveau en rouge (non indexé).

---

### 3. Un commit de trop (en local, non poussé)

* **Le problème :** Vous avez fait un commit trop tôt ou avec une erreur, et il est le tout dernier de votre historique local.
* **Prooquer la situation :** Modifiez un fichier, faites `git add`, puis `git commit -m "Commit en trop"`.
* **Défaire la situation :**
Annulez le commit tout en gardant vos modifications dans votre espace de travail :
```bash
git reset --soft HEAD^

```


*Vérification :* Tapez `git status`, vos fichiers modifiés sont de nouveau prêts à être ajustés ou validés.

---

### 4. Un commit poussé qu'il faut annuler (sur un dépôt distant)

* **Le problème :** Vous avez poussé (`git push`) un commit sur GitHub/GitLab qui contient une erreur, et d'autres personnes travaillent peut-être dessus.
* **Prooquer la situation :** Faites un commit et poussez-le sur votre branche distante.
* **Défaire la situation :**
Pour ne pas perturber l'historique partagé, la bonne pratique est de créer un **nouveau commit** qui annule les modifications du commit problématique :
```bash
git revert <hash_du_commit>
git push origin <nom_de_la_branche>

```


*Vérification :* Tapez `git log`, un nouveau commit d'annulation apparaît dans l'historique et a été poussé.

---

### 5. Un travail en cours qu'il faut mettre de côté (Stash)

* **Le problème :** Vous êtes en train de coder sur une fonctionnalité, mais vous devez changer de branche en urgence pour corriger un bug, sans vouloir faire de commit brouillon.
* **Prooquer la situation :** Modifiez un fichier sans faire de commit ni de `git add`.
* **Défaire la situation :**
Mettez vos modifications de côté temporairement :
```bash
git stash

```


*Votre espace de travail est propre.* Une fois le travail urgent terminé, récupérez vos modifications :
```bash
git stash pop

```


*Vérification :* Tapez `git status`, vos modifications sont de retour.

---

### 6. Un commit « perdu » à retrouver par le `reflog`

* **Le problème :** Vous avez supprimé une branche ou fait un `git reset --hard` un peu trop brutal, et vous avez l'impression d'avoir perdu un commit.
* **Prooquer la situation :** Faites un commit, notez son empreinte (hash), puis faites un `git reset --hard HEAD^` pour l'effacer de votre historique visible.
* **Défaire la situation :**
Git garde une trace de toutes vos actions récentes. Affichez l'historique de tous vos mouvements :
```bash
git reflog

```


Repérez le numéro de la ligne juste avant l'action destructrice (ex: `HEAD@{1}` ou le hash du commit), puis récupérez-le :
```bash
git checkout <hash_du_commit_perdu>
# ou recréez une branche par sécurité :
git checkout -b branche-sauvee <hash_du_commit_perdu>

```


*Vérification :* Tapez `git log`, votre commit « perdu » est réapparu.