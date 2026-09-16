# Exercices — Vivre dans le dépôt des autres

Afin de mener à bien cette exercice, j'ai fait dans l'ordre ces différentes commandes :

## `git init` : afin d'initialiser mon depôt;
## Puis, j'ai ajouter trois fichiers : 
```bash
(venv) PS C:\Users\FRANCK\Desktop\ANI-2053\ani-2053\chapitre-02\exo1-le_depot_d_essai> ls


    Répertoire : C:\Users\FRANCK\Desktop\ANI-2053\ani-2053\chapitre-02\exo1-le_depot_d_essai


Mode                 LastWriteTime         Length Name                                                                                       
----                 -------------         ------ ----                                                                                       
-a----         9/16/2026  11:06 PM            246 c2-exo1_reponse.md                                                                         
-a----         9/16/2026  11:05 PM              0 fichier_1.dart                                                                             
-a----         9/16/2026  11:05 PM              0 Fichier_2.cpp

```
## J'ai vérifier l'état avec `git status` :

```bash
(venv) PS C:\Users\FRANCK\Desktop\ANI-2053\ani-2053\chapitre-02\exo1-le_depot_d_essai> git status
On branch master

No commits yet

Untracked files:
  (use "git add <file>..." to include in what will be committed)
        Fichier_2.cpp
        c2-exo1_reponse.md
        fichier_1.dart

nothing added to commit but untracked files present (use "git add" to track)
```

## Je fais des ajout consécutif avec `git add Nom_fichier`;

## Suivi du commit adéquat `git commit -m "le message que je mets`

***Récapitulatif :***

---
### #1

```bash
(venv) PS C:\Users\FRANCK\Desktop\ANI-2053\ani-2053\chapitre-02\exo1-le_depot_d_essai> git add .\fichier_1.dart
(venv) PS C:\Users\FRANCK\Desktop\ANI-2053\ani-2053\chapitre-02\exo1-le_depot_d_essai> git commit -m "Ajout du premier fichier"
[master (root-commit) 2d98c55] Ajout du premier fichier
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 fichier_1.dart
```

### #2
```bash
(venv) PS C:\Users\FRANCK\Desktop\ANI-2053\ani-2053\chapitre-02\exo1-le_depot_d_essai> git add .\c2-exo1_reponse.md
(venv) PS C:\Users\FRANCK\Desktop\ANI-2053\ani-2053\chapitre-02\exo1-le_depot_d_essai> git commit -m "Ajout du deuxième fichier"
[master 75e6d6c] Ajout du deuxième fichier
 1 file changed, 57 insertions(+)
 create mode 100644 c2-exo1_reponse.md
```

### #3
```bash
(venv) PS C:\Users\FRANCK\Desktop\ANI-2053\ani-2053\chapitre-02\exo1-le_depot_d_essai> git add .\Fichier_2.cpp 
(venv) PS C:\Users\FRANCK\Desktop\ANI-2053\ani-2053\chapitre-02\exo1-le_depot_d_essai> git commit -m "Ajout du troisième fichier"
[master af3d2bc] Ajout du troisième fichier
 1 file changed, 0 insertions(+), 0 deletions(-)
 create mode 100644 Fichier_2.cpp
```

## Afin d'fficher l'historique en une ligne par commit. Puis affichez le graphe j'ai fait ces différentes commandes :

* > `git log --oneline` pour afficher l'historique en une ligne :
```bash
(venv) PS C:\Users\FRANCK\Desktop\ANI-2053\ani-2053\chapitre-02\exo1-le_depot_d_essai> git log --oneline --graph
* af3d2bc (HEAD -> master) Ajout du troisième fichier
* 75e6d6c Ajout du deuxième fichier
* 2d98c55 Ajout du premier fichier
```

* > `git log --graph` pour afficher le graph :

```bash
(venv) PS C:\Users\FRANCK\Desktop\ANI-2053\ani-2053\chapitre-02\exo1-le_depot_d_essai> git log --graph
* commit af3d2bc9379d9481aa10c4d1d5c2c08b09542a08 (HEAD -> master)
| Author: FRANCK <boukalafranck0@gmail.com>
| Date:   Wed Sep 16 23:16:54 2026 +0200
| 
|     Ajout du troisième fichier
| 
* commit 75e6d6c0b48bd872751954f2789b6167915e9584
| Author: FRANCK <boukalafranck0@gmail.com>
| Date:   Wed Sep 16 23:15:55 2026 +0200
| 
|     Ajout du deuxième fichier
| 
* commit 2d98c557c31b9e6f7e3a8743567d25ef1697f0d4
  Author: FRANCK <boukalafranck0@gmail.com>
  Date:   Wed Sep 16 23:13:49 2026 +0200
  
      Ajout du premier fichier
(END)
* commit af3d2bc9379d9481aa10c4d1d5c2c08b09542a08 (HEAD -> master)
| Author: FRANCK <boukalafranck0@gmail.com>
| Date:   Wed Sep 16 23:16:54 2026 +0200
| 
|     Ajout du troisième fichier
| 
* commit 75e6d6c0b48bd872751954f2789b6167915e9584
| Author: FRANCK <boukalafranck0@gmail.com>
| Date:   Wed Sep 16 23:15:55 2026 +0200
| 
|     Ajout du deuxième fichier
| 
* commit 2d98c557c31b9e6f7e3a8743567d25ef1697f0d4
  Author: FRANCK <boukalafranck0@gmail.com>
  Date:   Wed Sep 16 23:13:49 2026 +0200
  
      Ajout du premier fichier
(END)

```