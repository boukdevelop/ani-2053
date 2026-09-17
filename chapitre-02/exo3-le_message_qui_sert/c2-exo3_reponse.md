# Le message qui sert

***Énoncé***
Prenez trois commits du dépôt du moteur et jugez leurs messages : dit-il ce qu'il fait ? pourquoi ? porte-t-il un seul sujet ? Récrivez celui qui vous paraît le plus faible.

---

Afin d'afficher les différents commit j'ai fait `git log`. Mais j'ai eu le regret de constater que les commit étaient bien trop long, donc pour les réduire j'ai saisie `git log --oneline -n 10` pour afficher les 10 premier commit :

```bash
$ git log --oneline -n 10
6fb634fc (HEAD -> main, origin/main, origin/HEAD) NKCode : le web sort du polissage et devient la phase 14, avec une echeance reelle
860e9d7f Refonte NK3DModeler : a jour avec main, et NKCode signe sur certificat (#85)
c1c815ff CI : les huit epinglages de Jenga passent par JENGA_VERSION (#87)
addf709d NKCode beta.8 a beta.11 : la ligne publiee rejoint enfin main (#86)
43285010 (origin/fix/nktraits-portable) NkTraits : demander a la primitive si elle existe, pas au compilateur qui il est
0d50a971 NKCode 0.1.0-beta.6 : version bumpee avant publication
7c3e84a0 Merge remote-tracking branch 'origin/main'
4c7d66b5 Distribution : refuser de livrer un exe dont une DLL importee manque
ad0779cb NKCode : runtime MinGW en statique — l'exe ne depend plus du msys64 du testeur
cc41ca45 GemCrush : le jeu complet -- menu, aventure 30 niveaux, 3 modes, audio synthetise (#84)

```

---

Pour afficher des informations pertinentes, j'ai finalement fais le `git log <ADDRESS_DU_COMMIT>` :

## #1

```bash
$ git log 860e9d7f
commit 860e9d7f1f9ad11f7a238084eb7a86207af67368
Author: LeTeguis <69282466+LeTeguis@users.noreply.github.com>
Date:   Thu Sep 10 17:48:29 2026 +0100

    Refonte NK3DModeler : a jour avec main, et NKCode signe sur certificat (#85)
    .
    .
    .
    .

```

## #2

```bash
$ git log 43285010
commit 432850100b391c2251ec9bcb5a7e8d41afe0709e (origin/fix/nktraits-portable)
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Thu Sep 10 16:24:50 2026 +0100

    NkTraits : demander a la primitive si elle existe, pas au compilateur qui il est

```

## #3

```bash
$ git log ad0779cb
commit ad0779cb0dfa2ebecb6c58d13327643c1e317f9c
Author: LeTeguis <teuguiasederis@gmail.com>
Date:   Fri Aug 28 22:02:54 2026 +0100

    NKCode : runtime MinGW en statique — l'exe ne depend plus du msys64 du testeur
```

***GLOBALEMENT :***  Ces logs affichent :
* L'emprunte dudit commit;
* L'auteur dudit commit;
* La date dudit commit;
* Les détails lié au commit.
* Ces commit ne porte pas que sur un seul sujet;