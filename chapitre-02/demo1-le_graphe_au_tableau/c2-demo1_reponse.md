> # Démonstrations — Vivre dans le dépôt des autres

# Le graphe au tableau

***Énoncé :***
Dessinez, au tableau, le graphe des commits d'un dépôt réel : les branches, un point de divergence, une fusion. Puis montrez le même graphe avec git log -{}-graph et faites correspondre les deux.
--

### 1. Schéma conceptuel du graphe des commits

Voici la représentation visuelle avec les **branches**, le **point de divergence** et la **fusion (merge)** issus du dépôt :

```txt
BRANCH MAIN                      BRANCH FEATURE
         O (Commit initial)
         |
         O (Ajout du README)
         | \
         |  \ (Point de divergence)
         |   O (Premièr travail de la branche feature)
         |   |
         O   O (Ajout de la fonctionnalité)
         |  /
         | / (Point de fusion / Merge)
         O (Commit de fusion final - HEAD)
```

---

Ce qu'affiche la commande `git log --oneline --graph -n 45` :
-

```bash
$ git log --oneline --graph -n 45
* 6fb634fc (HEAD -> main, origin/main, origin/HEAD) NKCode : le web sort du polissage et devient la phase 14, avec une echeance reelle
* 860e9d7f Refonte NK3DModeler : a jour avec main, et NKCode signe sur certificat (#85)
* c1c815ff CI : les huit epinglages de Jenga passent par JENGA_VERSION (#87)
* addf709d NKCode beta.8 a beta.11 : la ligne publiee rejoint enfin main (#86)
* 43285010 (origin/fix/nktraits-portable) NkTraits : demander a la primitive si elle existe, pas au compilateur qui il est
* 0d50a971 NKCode 0.1.0-beta.6 : version bumpee avant publication
*   7c3e84a0 Merge remote-tracking branch 'origin/main'
|\
| * cc41ca45 GemCrush : le jeu complet -- menu, aventure 30 niveaux, 3 modes, audio synthetise (#84)
* | 4c7d66b5 Distribution : refuser de livrer un exe dont une DLL importee manque
* | ad0779cb NKCode : runtime MinGW en statique — l'exe ne depend plus du msys64 du testeur
* | 5fc605de Vulkan : la garde headless existait UNIQUEMENT sous Windows -- segfault sur les trois dorsales Linux
* | 56b0ed67 wiki : les mesures Vulkan sont CONFIRMEES par contre-verification -- et un 5e piege, celui qui a permis le desaccord
* | ecfb57cb wiki maintenabilite : quelle garde rougirait AUJOURD HUI -- reponse mesuree, et c est << aucune ici >>
* | b4cdf3cc wiki pieges : l avertissement sur CreateWithFallback est MAINTENU -- mesure a l appui -- et gagne le corollaire sur les bancs
* | 92cf625a wiki : je retire << 18 shaders casses >> -- c etait mon cache, pas le depot ; + les 4 pieges d instrument et la validation de G1
* | 7ddd10ce NKRenderer : garde G1 -- l ordre de frame devient bruyant au lieu d etre silencieux
* | 5e2d56ab wiki NKRenderer/NKRHI : le contrat de frame mesure, la surface publique, la divergence des backends -- et deux corrections datees de mes propres chiffres
* | 3b79729b NKRenderer : Present() avant EndFrame() sur les 3 sites inverses, et le commentaire qui enseignait l inverse
* |   d45a78d4 Merge branch 'feat/design-nodal'
|\ \
| * | ab2ba781 verifie_planches : deux controles sur la TABLE du 13, et un \b qui n en etait pas un
| * | 20648f12 Planche 08 : le panneau 3 ne dit plus  CE QUE LE MODELE NE PERMET PAS AUJOURD HUI  -- c est code, et date
| * | 70f78561 NKGraph specification : le 19.3 est FAUX par la mesure, le 19.9 gagne une quatrieme raison, et le 20 cesse de decrire un code d hier
| * | d266cd56 NKGraph specification : les trois contradictions signalees par le chantier voisin, et une famille de defaut nommee
| * | 4ec71d47 NKGraph : le fichier Lunacy de Rodolf rejoint la branche design, et il est ENFIN suivi
| * | 645d4e6b NKGraph : l acyclicite reste universelle -- et ca coute le Portail, ce qu on ecrit au lieu de le taire
| * | 43d8df92 NKGraph : trois decisions de Rodolf -- et la premiere fait tomber un mur que j avais decrit le matin meme
| * | 95259b8a NKGraph : les trois attributions du sequenceur etaient un MOT pour deux choses -- une phrase par couche, et personne ne perd
| * | f110c845 NKGraph : p01 passe par ecrire() -- et un controle empeche la quatrieme occurrence
| * | afd0d02d NKGraph : NKScena a un domaine mais pas de mode -- et « un seul DCC » disait le contraire de la decision
| * | 9fd3cb1c NKGraph : les huit planches sont rangees en groupes nommes -- et les huit PNG sont identiques au pixel
| * | 4afc1b67 NKGraph : quel graphe ouvre quelle application -- et le tableau fait apparaitre trois choses qu aucune planche ne montrait
| * | a3c77865 NKGraph : le SVG n emploie plus ce que Lunacy lit mal -- l ombre retiree, les motifs redessines
| * | 52094452 NKGraph : les deux conventions que les sept planches contredisaient -- le geste, fait expres, en un seul endroit
| * | d52e64d5 NKGraph : la police n etait que sur la racine du SVG -- l heritage marche dans un navigateur, pas a l import Lunacy
| * | ddf42806 NKGraph : les types composes -- ils ne demandent pas quatre choses au modele, ils en demandent deux
| * | 514b235b NKGraph : une ligne du recap disait DEUX etats a la fois -- et le controle renvoyait le defaut a l humain
| * | 7606491d NKGraph : la boucle d execution est un mur, mesure -- et le refus tombe plus tot que je ne le croyais
| * | 21162bc6 NKGraph : la planche 08 debordait en bas -- et le controle le disait deja
| * | 2c328f19 Point de reprise apres coupure : planche 08 (execution) non commitee
| * | d9cafb04 NKGraph : la planche 01 etait perimee -- et le controle qui aurait du le dire regardait a cote
| * | 8c0ffa74 NKGraph : point de reprise -- le travail non commite de la session precedente, tel quel
| * | 05741850 NKGraph : « 148 lignes » etait un nombre ecrit de memoire, et la premiere correction est tombee dans le piege suivant
| * | 206b3a2b NKGraph : le dernier trou est ferme -- NkMatGraphCheck lu en entier, et il contredit huit de mes regles
| * | a66cbf36 NKGraph : la nuit du 22 au 23/08 -- sept points tranches, deux planches neuves, trois controles
| * | 91ee3617 NKGraph : le cadre ne teinte QUE le filet du corps (tranche par Rodolf le 22/08) -- l en-tete porte la CATEGORIE, seule information qui survit au dezoom ; a 25 % il ne reste que
 ce rectangle de couleur, et le cadre dit deja l appartenance en entourant les noeuds. Plus : gen.rendre() refuse mecaniquement les deux pieges du rendu (URL absolue imposee, poids du PNG veri
fie) et la REGLE passe en tete du LISEZMOI
(END)

```
Voici le schéma conceptuel du graphe (arbre des commits) suivi de la correspondance détaillée avec la sortie textuelle de `git log --oneline --graph -n 45`.

---

### 1. Schéma conceptuel du graphe des commits

Voici la représentation visuelle avec les **branches**, le **point de divergence** et la **fusion (merge)** issus du dépôt :

```text
                                [ main, origin/main, HEAD ]
                                           commit
                                              │
                                           commit
                                              │
                                           commit
                                              │
                                           commit
                                              │
                       [origin/fix/nktraits-portable]
                                           commit
                                              │
                                           commit
                                              │
                                           commit  ◄── (Fusion 1 : origin/main + branche locale)
                                         /         \
   (Branche locale principal)           /           \  (Branche origin/main distante)
                             commit                   commit
                                 │                      │
                               commit                   │
                                 │                      │
                               commit                   │
                                 │                      │
                               commit                   │
                                 │                      │
                               commit                   │
                                 │                      │
                               commit                   │
                                 │                      │
                               commit                   │
                                 │                      │
                               commit                   │
                                 │                      │
                               commit                   │
                                 │                      │
                               commit                   │
                                 │                      │
                               commit ◄─────────────────┘  (Fusion 2 : feat/design-nodal)
                            /        \
  (Branche locale)         /          \  [feat/design-nodal]
                       [... ]            commit
                         │                 │
                         │               commit
                         │                 │
                        ...               ... (22 commits)
                         │                 │
                         │               commit ◄── Point de divergence
                         \                /
                          \              /
                           \            /
                             [Commit Ancêtre Commun]

```

---

### 2. Correspondance élément par élément avec `git log --oneline --graph -n 45`

Voici l'explication point par point de la manière dont la sortie terminal traduit ce graphe :

#### A. Les Branches et Références (`HEAD`, `main`, etc.)

* **Dans `* 6fb634fc (HEAD -> main, origin/main, origin/HEAD) NKCode : le web sort du polissage et devient la phase 14, avec une echeance reelle`
* **Signification :** Le commit `6fb634fc` est le sommet de la branche principale `main`. C'est le point où pointent la copie locale (`HEAD -> main`) et la version distante (`origin/main`).

* **Autre branche :** `4* 43285010 (origin/fix/nktraits-portable) NkTraits : demander a la primitive si elle existe, pas au compilateur qui il est` indique qu'une étiquette de branche distante pointe directement sur ce commit précis.

#### B. Les Points de Divergence (Bifurcations)

1. **La branche `feat/design-nodal` :**
* **Dans `git log --oneline --graph -n 45` :** L'étoile `*` du commit `91ee3617` est sur la branche de droite `| *`.
* **Signification :** À partir du commit parent de `91ee3617`, le développement s'est séparé en deux voies parallèles :
* La colonne de gauche (`* |`) continue le travail principal.
* La colonne de droite (`| *`) contient la suite des commits du projet étant donné que je me suis limité au 45 premières lignes.

2. **La divergence `origin/main` vs Local :**

* Au commit `| * cc41ca45 GemCrush : le jeu complet -- menu, aventure 30 niveaux, 3 modes, audio synthetise (#84)`, la branche distante a bifurqué par rapport aux travaux locaux menés entre `3b79729b` et `4c7d66b5`.

#### C. Les Fusions (Merge Commits)

Dans `git log --oneline --graph -n 45`, une fusion se repère par la ligne `|\` ou `|\ \` sous une étoile `*`.

1. **Première fusion : `* |   d45a78d4 Merge branch 'feat/design-nodal'`

* **Analyse de la ligne :**

```text
* | 3b79729b NKRenderer : Present() avant EndFrame() sur les 3 sites inverses, et le commentaire qui enseignait l inverse
* |   d45a78d4 Merge branch 'feat/design-nodal'
|\ \
| * | ab2ba781 verifie_planches : deux controles sur la TABLE du 13, et un \b qui n en etait pas un
```

* **Explication :** Ce commit possède **deux parents** :
* Le 1er parent : la branche principale (`3b79729b`).
* Le 2e parent : le dernier commit de la branche nodal (`ab2ba781`).

* **Sur le schéma :** C'est le point d'intersection où `feat/design-nodal` réintègre le troncs principal.

2. **Deuxième fusion : `7c3e84a0 Merge remote-tracking branch 'origin/main'**`
* **Analyse de la ligne :**
```text
*   7c3e84a0 Merge remote-tracking branch 'origin/main'
|\
| * cc41ca45 ...
* | 4c7d66b5 ...

```

* **Explication :** Le commit `7c3e84a0` rassemble le travail de la branche distante `origin/main` (`cc41ca45`) et le travail local (`4c7d66b5`).

---

### Résumé des symboles `git log --graph`

* `*` ou `commit` (dans ma représentation) : Représente un **commit**.
* `|` : Représente une **ligne d'historique/branche** active.
* `\` ou `/` : Représente le **croisement**, la **divergence** ou la **fusion** de deux lignes d'historique.