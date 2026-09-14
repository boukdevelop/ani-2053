# ***Le fichier de projet annoté***

Annoter un fichier ``.jenga`` :
* Types;
* Sources;
* Dépendances;
* Filtres;
* Tets;

Marquer d'un `?` tout ce qui est incompréhensible.

# NKIlyana.jenga — fichier `.jenga` annoté

> **Grille d'annotation demandée** : `Types`, `Sources`, `Dépendances`, `Filtres`, `Tests`.
>
> Toute partie non démontrable à partir de l'extrait fourni est marquée `?`.
>
> L'objectif est de pouvoir répondre à une question comme : **« où est décidé que ce module est une bibliothèque statique ? »** sans confondre déclaration du projet, dépendances, filtrage et linking.

---

## 1. Vue d'ensemble

`NKIlyana.jenga` décrit le projet **NKIlyana**, présenté par son en-tête comme un modèle consacré à la préparation de données, à l'entraînement et au dialogue.

### Classification rapide

| Élément | Observation |
|---|---|
| **Type** | `consoleapp()` → application console |
| **Sources** | `src/main.cpp` |
| **Dépendances** | `nkentseudependson(...)` avec une longue liste de modules |
| **Filtres** | filtre Windows visible, avec exclusions UWP/XboxSeries et une condition tronquée |
| **Tests** | `?` aucun test visible dans l'extrait |
| **Toolchain** | `usetoolchain(TC_WINDOWS)` dans le filtre Windows |
| **Linking** | `libdirs(...)` et `_WIN_LINKS` visibles, mais la fin de l'extrait est absente |
| **Static library ?** | **Non démontré pour NKIlyana ; au contraire `consoleapp()` indique une application console** |

---

## 2. En-tête et imports

```py
"""NKIlyana — le modele de Rihen : preparation des donnees, entrainement, dialogue."""
from Jenga import *
from jengaconfig import *
import os
```

### Annotation

**Type :** configuration / DSL Jenga / dépendances Python.

**Sources :** aucune source C++ déclarée ici.

**Dépendances :**
- `Jenga` : API du DSL utilisé pour définir le projet ;
- `jengaconfig` : configuration partagée ;
- `os` : accès aux variables d'environnement.

**Filtre :** aucun.

**Tests :** aucun.

### Questionnement

> `?` Quelles variables sont réellement fournies par `jengaconfig` ?
>
> Le fichier utilise plus loin `TC_WINDOWS`, `VULKAN_INCLUDE`, `VULKAN_LIB` et `WANT_VULKAN`, mais leur définition n'est pas visible dans cet extrait.

---

## 3. Liste des bibliothèques GLSLang Windows

```py
_GLSLANG_LIBS_WINDOWS = [
    "glslang", "SPIRV", "MachineIndependent", "GenericCodeGen",
    "glslang-default-resource-limits",
]
```

### Annotation

**Type :** variable Python contenant une liste de bibliothèques.

**Sources :** aucune.

**Dépendances :** bibliothèques GLSLang/SPIR-V destinées au linking si cette liste est consommée plus loin.

**Filtre :** le nom de la variable indique Windows, mais le filtre effectif n'est pas ici.

**Tests :** aucun.

### Attention

Cette déclaration **ne signifie pas à elle seule que les bibliothèques sont liées**. C'est seulement une liste Python.

> `?` L'extrait ne montre pas où `_GLSLANG_LIBS_WINDOWS` est effectivement utilisé.

---

## 4. Détection de MinGW

```py
_IS_MINGW = "mingw" in TC_WINDOWS.lower()
```

### Annotation

**Type :** variable de configuration calculée en Python.

**Dépendance :** `TC_WINDOWS`.

**Filtre :** aucun `filter()` ici.

**Effet :** détermine si la toolchain Windows contient `mingw` dans son nom.

### Questionnement

> `?` Où `_IS_MINGW` est-il utilisé ensuite ?
>
> Son usage n'est pas visible dans l'extrait fourni.

---

## 5. Activation conditionnelle de TLS

```py
_TLS_ON = os.getenv("NK_ENABLE_TLS", "").strip().lower() in ("1", "true", "on", "yes", "mbedt>")
```

### Annotation

**Type :** option de configuration obtenue depuis l'environnement.

**Source de décision :** variable d'environnement `NK_ENABLE_TLS`.

**Dépendances conditionnelles :** TLS / mbed-TLS.

**Filtre :** pas encore un `filter()` Jenga ; c'est une condition Python.

### Point à marquer `?`

La dernière valeur visible :

```text
"mbedt>"
```

semble tronquée dans l'extrait reçu.

> `?` **Ne pas corriger silencieusement cette valeur.** Il faut retrouver le fichier original pour connaître la valeur complète.

---

## 6. Dépendance TLS conditionnelle

```py
_TLS_DEPS = ["NKMbedTLS"] if _TLS_ON else []
```

### Annotation

**Type :** liste Python de dépendances.

**Dépendances :**
- si TLS activé → `NKMbedTLS` ;
- sinon → aucune dépendance TLS dans cette variable.

**Filtre :** condition Python, pas `filter()` Jenga.

**Sources :** aucune source C++ directe.

### Lecture logique

```text
NK_ENABLE_TLS
      ↓
   _TLS_ON
      ↓
 _TLS_DEPS
      ↓
NKMbedTLS si activé
```

> `?` Où `_TLS_DEPS` est-il injecté dans la configuration du projet ?

---

## 7. Bibliothèques Windows liées au TLS

```py
_TLS_WIN_LINKS = ["bcrypt"] if _TLS_ON else []
```

### Annotation

**Type :** liste Python de bibliothèques de linking.

**Dépendance système :** `bcrypt` si TLS est activé.

**Filtre :** condition Python via `_TLS_ON`.

**Tests :** aucun.

> `?` L'extrait fourni ne montre pas l'appel `links(_TLS_WIN_LINKS)` éventuel. Il faut donc distinguer **préparer une liste** et **effectivement la lier**.

---

# 8. Déclaration du projet

```py
with project("NKIlyana"):
```

## Annotation principale

C'est l'ouverture du **projet Jenga** nommé `NKIlyana`.

### Type

`project(...)` crée le contexte du projet, mais **ne suffit pas à déterminer son type final**.

Le type est déterminé par la primitive utilisée dans ce bloc : ici, `consoleapp()`.

### Réponse à la question centrale

> **« Où est décidé que NKIlyana est une bibliothèque statique ? »**

Dans l'extrait fourni : **nulle part**.

Le fichier contient :

```py
consoleapp()
```

et ne contient pas :

```py
staticlib()
```

Donc, pour **NKIlyana lui-même**, la lecture correcte est :

```text
project("NKIlyana")
        ↓
   consoleapp()
        ↓
application console
```

---

# 9. Type réel du projet

```py
consoleapp()
```

## Annotation

### **TYPE**

Le projet est déclaré comme une **application console**.

### Ce que cela exclut

Cette ligne ne déclare pas :

```py
staticlib()
```

ni :

```py
sharedlib()
```

### Questionnement

> `?` Pour une dépendance comme `NKTensor`, le type doit être cherché dans **son propre `.jenga`**, pas dans `nkentseudependson(...)`.

---

# 10. Langage

```py
language("C++")
```

### Annotation

**Type :** propriété du projet.

**Sources :** les sources déclarées ensuite sont C++.

**Dépendances :** aucune par cette ligne.

**Filtre :** aucun.

**Tests :** aucun.

---

# 11. Standard C++

```py
cppdialect("C++17")
```

### Annotation

**Type :** configuration de compilation.

Le projet utilise le dialecte :

```text
C++17
```

### Délégation

Le fichier impose le dialecte au projet, mais le compilateur concret dépend de la toolchain sélectionnée.

> `?` L'identité exacte du compilateur pour chaque plateforme n'est pas définie ici.

---

# 12. Emplacement du projet

```py
location(".")
```

### Annotation

**Type :** emplacement logique du projet.

Cela ne définit **ni** le dossier des objets, **ni** le dossier du binaire. Ces deux éléments sont déclarés plus loin par `objdir()` et `targetdir()`.

---

# 13. Sources

```py
files(["src/main.cpp"])
```

## Annotation

### **SOURCES**

Source locale explicitement déclarée :

```text
src/main.cpp
```

### Dépendances indirectes

Les autres modules ne sont pas ajoutés comme sources locales ; ils sont référencés via `nkentseudependson(...)`.

### Questionnement

> `?` Y a-t-il d'autres sources ajoutées plus loin ?
>
> L'extrait fourni ne le permet pas de l'affirmer.

---

# 14. Dépendances Nkentseu

```py
nkentseudependson(
    ["NKGpt", "NKTrain", "NKNN", "NKData", "NKOptim", "NKAutograd", "NKTensor", "NKRHI",
     "NKWindow", "NKGlad", "NKMath", "NKTime", "NKStream", "NKFileSystem",
     "NKLogger", "NKContainers", "NKMemory", "NKCore", "NKPlatform",
     "NKThreading", "NKGLSlang", "NKSPIRVCross", "NKImage", "NKMedia", "NKFont", "NKNetwo..."],
    extra_includes=["src", "%{NKGlad.location}/include"]
                   + ([VULKAN_INCLUDE] if VULKAN_INCLUDE else []),
    extra_defines=[f"NKENTSEU_ENABLE_VULKAN_BACKEND={1 if WANT_VULKAN else 0}"],
)
```

## Annotation

### **DÉPENDANCES**

Le projet consomme notamment :

```text
NKGpt
NKTrain
NKNN
NKData
NKOptim
NKAutograd
NKTensor
NKRHI
NKWindow
NKGlad
NKMath
NKTime
NKStream
NKFileSystem
NKLogger
NKContainers
NKMemory
NKCore
NKPlatform
NKThreading
NKGLSlang
NKSPIRVCross
NKImage
NKMedia
NKFont
NKNetwork ?
```

La fin de la liste est tronquée (`NKNetwo...`).

> `?` **Nom exact de la dernière dépendance à confirmer.**

### Ce que ce bloc décide

Il décide que `NKIlyana` **dépend** de ces modules.

### Ce qu'il ne décide pas

Il ne permet pas, à lui seul, de conclure :

```text
NKTensor = StaticLib
NKNN = StaticLib
NKGpt = StaticLib
```

Pour répondre à cette question, il faut ouvrir le `.jenga` de chaque dépendance et chercher son propre `project(...)` et sa primitive de type :

```py
staticlib()
```

ou :

```py
sharedlib()
```

ou :

```py
consoleapp()
```

etc.

---

# 15. Includes supplémentaires

```py
extra_includes=["src", "%{NKGlad.location}/include"]
```

### Annotation

**Type :** chemins d'inclusion supplémentaires.

**Sources :**
- `src`
- le dossier `include` de `NKGlad` via `%{NKGlad.location}`.

**Dépendance :** `NKGlad` apparaît explicitement dans les dépendances.

### Délégation

La résolution de :

```text
%{NKGlad.location}
```

est laissée au système de variables/projets Jenga.

> `?` La valeur physique exacte de `NKGlad.location` n'est pas visible ici.

---

# 16. Include Vulkan conditionnel

```py
+ ([VULKAN_INCLUDE] if VULKAN_INCLUDE else [])
```

### Annotation

**Type :** condition Python.

Si `VULKAN_INCLUDE` existe :

```text
→ ajout du chemin Vulkan
```

Sinon :

```text
→ aucun chemin Vulkan ajouté
```

### Important

Ce n'est pas un filtre Jenga de plateforme.

Il faut distinguer :

```py
if VULKAN_INCLUDE:
```

et :

```py
with filter(...):
```

---

# 17. Define Vulkan

```py
extra_defines=[f"NKENTSEU_ENABLE_VULKAN_BACKEND={1 if WANT_VULKAN else 0}"]
```

### Annotation

**Type :** macro C/C++ de compilation.

Deux valeurs possibles :

```text
WANT_VULKAN = vrai  → NKENTSEU_ENABLE_VULKAN_BACKEND=1
WANT_VULKAN = faux  → NKENTSEU_ENABLE_VULKAN_BACKEND=0
```

### Délégation

La définition de `WANT_VULKAN` n'est pas dans cet extrait.

> `?` **Origine de `WANT_VULKAN` à rechercher dans `jengaconfig` ou la configuration globale.**

---

# 18. Répertoire des objets

```py
objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
```

### Annotation

**Type :** sortie intermédiaire de compilation.

**Variables utilisées :**

- `%{wks.location}` → workspace ;
- `%{cfg.buildcfg}` → configuration ;
- `%{cfg.system}` → système ;
- `%{prj.name}` → projet.

### Délégation

Jenga résout ces variables pendant la génération/construction.

---

# 19. Répertoire de sortie

```py
targetdir("%{wks.location}/Build/Bin/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
```

### Annotation

**Type :** destination de l'artefact final.

Comme le projet est un `consoleapp()`, l'artefact attendu est un exécutable adapté à la plateforme de compilation.

---

# 20. Filtre Windows

L'extrait montre :

```py
with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !sys... "):
```

## Annotation

### **FILTRE**

Ce bloc s'applique à une cible Windows avec des exclusions explicites.

Conditions visibles :

```text
system:Windows
```

ET :

```text
!options:windows-runtime=uwp
```

ET :

```text
!system:XboxSeries
```

La suite du filtre est tronquée.

> `?` **Condition complète à retrouver dans le fichier original.**

### Ce que filtre ce bloc

Il ne configure pas toutes les plateformes de `NKIlyana`. Il ne s'applique qu'au sous-ensemble correspondant à la condition.

---

# 21. Toolchain Windows

```py
usetoolchain(TC_WINDOWS)
```

### Annotation

**Type :** sélection de toolchain.

**Dépendance/configuration externe :** `TC_WINDOWS`.

### Délégation

Le fichier dit en substance :

```text
« Dans ce contexte Windows, utilise la toolchain définie par TC_WINDOWS. »
```

Mais il ne dit pas ici quelle valeur concrète possède `TC_WINDOWS`.

> `?` Origine de `TC_WINDOWS` à rechercher dans la configuration globale.

---

# 22. Defines Windows

```py
defines(["WIN32_LEAN_AND_MEAN", "_UNICODE", "UNICODE"])
```

### Annotation

**Type :** macros de compilation.

**Filtre :** actives à l'intérieur du filtre Windows visible.

### Lecture

```text
Windows
  ↓
defines Windows
```

Ils ne sont pas nécessairement appliqués aux autres plateformes.

---

# 23. Répertoire des bibliothèques Vulkan

```py
if VULKAN_LIB:
    libdirs([VULKAN_LIB])
```

### Annotation

**Type :** chemin de recherche de bibliothèques pour le linker.

**Condition :** Python `if` sur `VULKAN_LIB`.

### Très important

`libdirs()` **n'est pas** `staticlib()`.

Il faut distinguer :

```text
libdirs(...)   → où chercher les bibliothèques
links(...)     → quelles bibliothèques lier
staticlib()    → quel type de projet construire
```

Cette distinction est centrale pour éviter une mauvaise annotation du fichier.

---

# 24. Préparation des liens Windows

```py
_WIN_LINKS = [
    "NKGLSlang", "NKSPIRVCross",
```

### Annotation

**Type :** liste Python destinée au linking.

Bibliothèques visibles :

```text
NKGLSlang
NKSPIRVCross
```

La suite du bloc est absente de l'extrait fourni.

> `?` **Liste complète des bibliothèques Windows à confirmer.**

> `?` **Présence d'un `links(_WIN_LINKS)` à confirmer dans la suite.**

---

# 25. Table de lecture globale

| Catégorie | Dans `NKIlyana.jenga` | Commentaire |
|---|---|---|
| **Type** | `consoleapp()` | Décision explicite : application console |
| **Sources** | `src/main.cpp` | Source locale visible |
| **Dépendances** | `nkentseudependson(...)` | Nombreux modules Nkentseu |
| **Filtres** | `filter("system:Windows ...")` | Configuration conditionnelle Windows |
| **Tests** | `?` | Aucun test visible dans l'extrait |
| **Toolchain** | `usetoolchain(TC_WINDOWS)` | Déléguée à une variable externe |
| **Includes** | `extra_includes` | `src`, `NKGlad/include`, Vulkan éventuel |
| **Defines** | `extra_defines`, `defines` | Vulkan + Windows |
| **Lib search path** | `libdirs(VULKAN_LIB)` | Répertoire de recherche du linker |
| **Linking** | `_WIN_LINKS` | Liste amorcée, suite absente |
| **StaticLib** | `?` pour les dépendances | À vérifier dans leurs propres `.jenga` |

---

# 26. Ce que le fichier **déclare**

NKIlyana déclare directement :

1. un projet nommé `NKIlyana` ;
2. un type de projet : `consoleapp()` ;
3. le langage C++ ;
4. le standard C++17 ;
5. son emplacement ;
6. `src/main.cpp` comme source ;
7. ses dépendances Nkentseu ;
8. des includes supplémentaires ;
9. des defines ;
10. des répertoires de sortie ;
11. une configuration Windows ;
12. une toolchain Windows via `TC_WINDOWS`.

---

# 27. Ce que le fichier **filtre**

Le fichier applique un filtre Windows visible :

```text
system:Windows
```

avec au moins :

```text
!options:windows-runtime=uwp
!system:XboxSeries
```

Le reste du filtre est tronqué.

Il filtre donc **l'application de certaines configurations**, et non le type général du projet.

---

# 28. Ce que le fichier **délègue**

NKIlyana délègue plusieurs décisions à d'autres couches :

```text
jengaconfig
   ├── TC_WINDOWS ?
   ├── VULKAN_INCLUDE ?
   ├── VULKAN_LIB ?
   └── WANT_VULKAN ?

projets dépendants
   ├── NKTensor.jenga
   ├── NKNN.jenga
   ├── NKTrain.jenga
   ├── NKGpt.jenga
   └── ...

toolchain
   └── usetoolchain(TC_WINDOWS)
```

---

# 29. La question `StaticLib` : réponse précise

## Pour `NKIlyana`

La réponse est :

```text
NKIlyana n'est pas déclaré comme StaticLib ici.
```

La déclaration réelle est :

```py
with project("NKIlyana"):
    consoleapp()
```

## Pour `NKTensor`, `NKNN`, etc.

La réponse n'est **pas donnée par** :

```py
nkentseudependson(["NKTensor", "NKNN", ...])
```

Il faut ouvrir les fichiers correspondants et chercher :

```py
with project("NKTensor"):
    staticlib()
```

ou une autre déclaration de type.

### Règle d'analyse

```text
nom dans une dépendance
        ≠
type de projet
```

Le type se trouve dans la déclaration du projet concerné.

---

# 30. Tests

### **TESTS**

Aucun bloc de test n'est visible dans l'extrait fourni.

On ne doit donc pas écrire :

```text
test = absent du dépôt
```

mais seulement :

```text
? Aucun test visible dans l'extrait fourni.
```

### Questionnement

- Existe-t-il un `unitest()` dans une autre partie du fichier ?
- `NKIlyana` possède-t-il un projet de test séparé ?
- Les modules `NKTrain`, `NKGpt`, etc. ont-ils leurs propres tests ?

---

# 31. Checklist d'audit pour la suite

Pour compléter l'analyse du module sans rien inventer :

```text
[ ] Lire la fin exacte du filtre Windows
[ ] Lire la fin de la liste _WIN_LINKS
[ ] Vérifier si _WIN_LINKS est passé à links(...)
[ ] Vérifier où _TLS_DEPS est utilisé
[ ] Vérifier où _TLS_WIN_LINKS est utilisé
[ ] Identifier la définition de TC_WINDOWS
[ ] Identifier la définition de WANT_VULKAN
[ ] Identifier la définition de VULKAN_INCLUDE
[ ] Identifier la définition de VULKAN_LIB
[ ] Ouvrir NKTensor.jenga
[ ] Ouvrir NKNN.jenga
[ ] Ouvrir NKTrain.jenga
[ ] Ouvrir NKGpt.jenga
[ ] Rechercher staticlib() dans les dépendances
[ ] Rechercher sharedlib() dans les dépendances
[ ] Rechercher les tests associés
```

---

# 32. Verdict final

```text
NKIlyana.jenga
│
├── TYPE
│   └── consoleapp()
│       └── application console
│
├── SOURCES
│   └── src/main.cpp
│
├── DÉPENDANCES
│   └── nkentseudependson(...)
│       ├── NKGpt
│       ├── NKTrain
│       ├── NKNN
│       ├── NKTensor
│       └── ...
│
├── FILTRES
│   └── Windows
│       ├── pas UWP
│       ├── pas XboxSeries
│       └── reste du filtre : ?
│
├── CONFIGURATION DÉLÉGUÉE
│   ├── TC_WINDOWS ?
│   ├── WANT_VULKAN ?
│   ├── VULKAN_INCLUDE ?
│   └── VULKAN_LIB ?
│
├── TESTS
│   └── ? non visibles dans l'extrait
│
└── STATICLIB
    └── pas pour NKIlyana
        └── ses dépendances doivent être inspectées séparément
```

## Conclusion

> **NKIlyana.jenga est un excellent exemple de fichier qui orchestre un exécutable plutôt qu'un fichier qui définit à lui seul toute la nature du graphe de modules.**
>
> Il décide directement de son propre type (`consoleapp()`), de ses sources et d'une partie de sa configuration. Pour le type des modules qu'il consomme, il **délègue** aux `.jenga` de ces modules et/ou à la configuration centrale.
>
> `?` est conservé partout où le texte fourni est tronqué ou où une définition externe est nécessaire pour conclure.
