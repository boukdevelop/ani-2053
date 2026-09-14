# NKIlyana.jenga — analyse annotée

> **Objectif de cette fiche**
>
> Présenter un véritable fichier `.jenga` en répondant systématiquement à :
> - **Qu'est-ce que ce fichier déclare ?**
> - **Qu'est-ce qu'il filtre ?**
> - **Qu'est-ce qu'il délègue ?**
> - **Quelles sont ses dépendances ?**
> - **Où est décidé le type du projet ?**
> - **Où serait décidé qu'un module est une bibliothèque statique ?**
> - **Qu'est-ce qui reste incompréhensible ou doit être vérifié ?**
>
> **Source analysée :** `NKIlyana.jenga`
>
> **Important :** le contenu fourni est tronqué à la fin, dans le bloc Windows. Les éléments absents du texte fourni ne sont donc pas inventés ici.

---

## 1. Lecture rapide du fichier

`NKIlyana.jenga` déclare un **projet Jenga nommé `NKIlyana`** qui est une **application console C++**, compilée en **C++17**.

Il :

- déclare le type du projet avec `consoleapp()` ;
- fixe le langage avec `language("C++")` ;
- fixe le dialecte avec `cppdialect("C++17")` ;
- indique son répertoire avec `location(".")` ;
- déclare sa source principale avec `files(["src/main.cpp"])` ;
- délègue une grande partie de sa configuration et de ses dépendances à `nkentseudependson(...)` ;
- utilise des variables globales de configuration comme `TC_WINDOWS`, `VULKAN_INCLUDE`, `VULKAN_LIB` et `WANT_VULKAN` ;
- conditionne certaines options au système cible avec `filter(...)` ;
- conditionne TLS par variable d'environnement avant même d'entrer dans le projet.

### Réponse immédiate à la question centrale

> **« Où est décidé que `NKIlyana` est une bibliothèque statique ? »**

**Nulle part dans le fichier fourni.**

Au contraire, le projet est explicitement déclaré comme une application console :

```py
with project("NKIlyana"):
    consoleapp()
```

Dans le DSL Jenga, `project()` représente une unité de compilation et `consoleapp()` choisit le genre **application console**. La bibliothèque statique serait explicitement déclarée avec `staticlib()`. Le guide Jenga donne précisément cette distinction dans la structure d'un `.jenga`.

**Conclusion :**

```text
NKIlyana
└── project("NKIlyana")
    └── consoleapp()      ← type décidé ici
```

Donc :

```text
staticlib()              ← ABSENT
```

Il n'y a aucune base, dans le contenu fourni, pour conclure que `NKIlyana` est une bibliothèque statique.

---

# 2. En-tête et imports

```py
"""NKIlyana — le modele de Rihen : preparation des donnees, entrainement, dialogue."""
from Jenga import *
from jengaconfig import *
import os
```

## Ce que cela déclare

Le fichier est un script Python utilisant :

- l'API DSL de Jenga via `from Jenga import *` ;
- la configuration partagée via `from jengaconfig import *` ;
- le module `os` pour lire des variables d'environnement.

### Annotation

**Type :** configuration / DSL Jenga.

**Questionnement :**

- `jengaconfig` fournit-il `TC_WINDOWS`, `VULKAN_INCLUDE`, `VULKAN_LIB`, `WANT_VULKAN` ?
- Le fichier dépend-il implicitement de l'ordre d'exécution des `.jenga` et des `useconfig()` précédents ?
- Quelles autres valeurs globales sont injectées par `jengaconfig` ?

> `?` **À vérifier dans `jengaconfig`**, car le présent fichier les consomme mais ne les définit pas.

---

# 3. Bibliothèques GLSLang spécifiques Windows

```py
_GLSLANG_LIBS_WINDOWS = [
    "glslang", "SPIRV", "MachineIndependent", "GenericCodeGen",
    "glslang-default-resource-limits",
]
```

## Ce que cela déclare

Une liste Python de bibliothèques liées à GLSLang pour Windows.

## Ce que cela ne fait PAS

Cette ligne, à elle seule :

```py
_GLSLANG_LIBS_WINDOWS = [...]
```

**ne lie rien au projet**.

Ce n'est qu'une donnée Python.

Pour produire un effet Jenga, la liste devrait être utilisée plus loin dans une instruction comme :

```py
links(_GLSLANG_LIBS_WINDOWS)
```

ou équivalent.

### Annotation

**Type :** donnée préparatoire.

**Filtre :** pas encore de filtre.

**Délégation :** aucune à ce stade.

### Questionnement

> `?` **Cette variable est-elle utilisée plus bas ?**

Dans l'extrait fourni, son utilisation n'apparaît pas encore.

---

# 4. Détection de MinGW

```py
_IS_MINGW = "mingw" in TC_WINDOWS.lower()
```

## Ce que cela fait

Cette expression détermine si le nom de la toolchain Windows contient `mingw`.

Exemple :

```text
clang-mingw
→ "mingw" in "clang-mingw"
→ True
```

### Attention

`_IS_MINGW` est une **variable Python**, pas un filtre Jenga.

Elle devient utile seulement si elle est réutilisée dans une condition :

```py
if _IS_MINGW:
    ...
```

ou indirectement pour construire une configuration.

### Questionnement

> `?` **Pourquoi distinguer MinGW ici ?**

Probablement pour adapter le linking Windows ou les bibliothèques système, mais l'extrait fourni ne permet pas encore de connaître la raison exacte.

---

# 5. Activation conditionnelle de TLS

```py
_TLS_ON = os.getenv("NK_ENABLE_TLS", "").strip().lower() in (
    "1", "true", "on", "yes", "mbedt>"
)
```

## Ce que cela fait

Le fichier lit la variable d'environnement :

```text
NK_ENABLE_TLS
```

et transforme certaines valeurs en activation de TLS.

Les valeurs reconnues sont celles visibles dans l'extrait fourni.

### Point suspect

La dernière valeur :

```text
"mbedt>"
```

semble tronquée ou anormale.

**Annotation obligatoire :**

> `?` **Valeur probablement tronquée dans le texte fourni.**

Il ne faut pas corriger silencieusement cette valeur dans la documentation sans retrouver le `.jenga` original.

---

# 6. Dépendance TLS conditionnelle

```py
_TLS_DEPS = ["NKMbedTLS"] if _TLS_ON else []
```

## Ce que cela signifie

Si TLS est activé :

```text
_TLS_DEPS = ["NKMbedTLS"]
```

Sinon :

```text
_TLS_DEPS = []
```

### Très important

Encore une fois, ceci est du **Python exécuté dans le script `.jenga`**.

Ce n'est pas encore un `filter()` Jenga.

La décision est ici :

```text
variable d'environnement
        ↓
_TLS_ON
        ↓
_TLS_DEPS
```

Puis cette variable doit normalement être injectée dans une configuration Jenga ultérieure.

### Questionnement

> `?` **Où `_TLS_DEPS` est-il consommé ?**

Il faut suivre cette variable plus loin dans le fichier.

---

# 7. Dépendance système TLS Windows

```py
_TLS_WIN_LINKS = ["bcrypt"] if _TLS_ON else []
```

## Ce que cela signifie

Lorsque TLS est actif sous Windows, la bibliothèque système :

```text
bcrypt
```

semble destinée à être liée.

Mais dans l'extrait fourni, aucune instruction `links(...)` ne montre encore cette utilisation.

### Annotation

**Dépendance potentielle :**

```text
TLS
└── bcrypt
```

### Questionnement

> `?` **Le `bcrypt` est-il injecté plus bas dans un `links()` filtré Windows ?**

Le texte fourni est incomplet, donc cette utilisation n'est pas vérifiable ici.

---

# 8. Déclaration principale du projet

```py
with project("NKIlyana"):
```

## C'est ici que commence le projet Jenga

Le projet est enregistré sous le nom :

```text
NKIlyana
```

### Type

Un `project(...)` est une **unité de compilation** Jenga : application, bibliothèque statique, bibliothèque partagée ou suite de tests.

Mais `project()` seul ne précise pas le type final.

Le type est donné par les appels placés à l'intérieur.

---

# 9. Type du projet

```py
consoleapp()
```

## Décision fondamentale

Cette instruction déclare :

```text
NKIlyana = Console Application
```

### Donc

Le projet **n'est pas une StaticLib**.

Pour comparer :

```py
staticlib()
```

aurait signifié :

```text
NKIlyana = bibliothèque statique
```

Mais cette instruction n'existe pas ici.

### Réponse à mémoriser

> **Le type du projet est décidé par la primitive de type utilisée à l'intérieur de `project()`.**

Ici :

```py
consoleapp()
```

Donc :

```text
ProjectKind.CONSOLE_APP
```

et non :

```text
ProjectKind.STATIC_LIB
```

Le guide développeur Jenga décrit `ProjectKind.STATIC_LIB`, `ProjectKind.CONSOLE_APP`, etc., et le guide utilisateur montre `staticlib()` comme déclaration explicite d'une bibliothèque statique.

---

# 10. Langage

```py
language("C++")
```

## Déclare

Le langage principal du projet :

```text
C++
```

### Questionnement

> `?` Cette déclaration pilote-t-elle directement le compilateur ou dépend-elle de la toolchain sélectionnée ?

Elle renseigne le modèle du projet ; le choix du compilateur concret est délégué à la toolchain.

---

# 11. Dialecte C++

```py
cppdialect("C++17")
```

## Déclare

Le standard C++ utilisé :

```text
C++17
```

### Annotation

**Type :** propriété du projet.

**Filtre :** aucun dans l'extrait.

**Délégation :** la génération de compilation déléguera à la toolchain l'émission du flag approprié.

---

# 12. Localisation du projet

```py
location(".")
```

## Déclare

Le répertoire logique du projet est le répertoire courant.

### Attention

Cela ne dit pas :

```text
où se trouvent les binaires.
```

Les répertoires de build sont spécifiés plus loin avec :

```py
objdir(...)
targetdir(...)
```

---

# 13. Sources du projet

```py
files(["src/main.cpp"])
```

## Déclare

Le projet compile :

```text
src/main.cpp
```

### Important

Le fichier ne déclare pas ici les sources de toutes les dépendances.

Il les **réutilise** via :

```py
nkentseudependson(...)
```

Donc il faut distinguer :

```text
NKIlyana
└── source locale
    └── src/main.cpp
```

et :

```text
NKIlyana
└── dépendances
    ├── NKGpt
    ├── NKTrain
    ├── NKNN
    └── ...
```

---

# 14. Bloc central de dépendances

```py
nkentseudependson(
    [
        "NKGpt", "NKTrain", "NKNN", "NKData", "NKOptim",
        "NKAutograd", "NKTensor", "NKRHI", "NKWindow", "NKGlad", "NKMath", "NKTime", "NKStream", "NKFileSystem",
        "NKLogger", "NKContainers", "NKMemory", "NKCore", "NKPlatform",
        "NKThreading", "NKGLSlang", "NKSPIRVCross", "NKImage", "NKMedia", "NKFont", "NKNetwork", ...
    ],
    extra_includes=["src", "%{NKGlad.location}/include"]
                   + ([VULKAN_INCLUDE] if VULKAN_INCLUDE else []),
    extra_defines=[f"NKENTSEU_ENABLE_VULKAN_BACKEND={1 if WANT_VULKAN else 0}"],
)
```

## C'est le point le plus important après `consoleapp()`

Ce bloc **ne déclare pas le type de `NKIlyana`**.

Il configure surtout :

1. les dépendances du projet ;
2. des chemins d'inclusion supplémentaires ;
3. un define conditionnel.

### Dépendances visibles

L'extrait montre notamment :

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
NKNetwork
```

### Lecture architecturale

```text
NKIlyana
    ↓
    dépend de nombreux modules Nkentseu
```

### Questionnement essentiel

> **`nkentseudependson()` décide-t-il si les dépendances sont statiques ou dynamiques ?**

**Pas d'après ce fichier seul.**

Il demande à NKIlyana de dépendre de ces projets/modules.

La nature de chaque module doit être cherchée dans :

```text
Le .jenga du module
```

ou dans une configuration centrale appelée par celui-ci.

Par exemple :

```text
NKTensor
└── NKTensor.jenga
    └── project("NKTensor")
        └── staticlib()
```

Ce serait là que serait prise la décision.

---

# 15. Includes supplémentaires

```py
extra_includes=["src", "%{NKGlad.location}/include"]
```

## Ajoute

Deux chemins d'inclusion :

```text
src
NKGlad/include
```

### Délégation

`%{NKGlad.location}` est une variable dynamique liée au projet `NKGlad`.

Cela signifie que NKIlyana ne connaît pas nécessairement le chemin physique en dur.

Il délègue la résolution du chemin à Jenga.

### Questionnement

> `?` Que vaut exactement `%{NKGlad.location}` au moment de la génération ?

Il faut consulter le projet `NKGlad` dans le workspace.

---

# 16. Include Vulkan conditionnel

```py
+ ([VULKAN_INCLUDE] if VULKAN_INCLUDE else [])
```

## Ce que cela fait

Si :

```text
VULKAN_INCLUDE
```

est défini et non vide, il est ajouté aux includes.

Sinon rien n'est ajouté.

### Ce n'est pas un `filter()`

C'est une condition Python.

Distinction importante :

```text
if VULKAN_INCLUDE
```

≠

```py
with filter("system:Windows"):
```

Le premier est évalué comme code Python du `.jenga`.

Le second est une condition du DSL de build.

---

# 17. Define Vulkan

```py
extra_defines=[f"NKENTSEU_ENABLE_VULKAN_BACKEND={1 if WANT_VULKAN else 0}"]
```

## Déclare un macro C++

Selon `WANT_VULKAN` :

```text
NKENTSEU_ENABLE_VULKAN_BACKEND=1
```

ou :

```text
NKENTSEU_ENABLE_VULKAN_BACKEND=0
```

### Architecture de la décision

```text
WANT_VULKAN
    ↓
condition Python
    ↓
define C++
    ↓
NKENTSEU_ENABLE_VULKAN_BACKEND
```

### Questionnement

> `?` Où `WANT_VULKAN` est-il décidé ?

Pas dans l'extrait fourni.

Il vient probablement de `jengaconfig` ou d'une configuration incluse en amont, mais ce point doit être vérifié dans les sources du projet.

---

# 18. Répertoire des objets intermédiaires

```py
objdir("%{wks.location}/Build/Obj/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
```

## Déclare

Le dossier des fichiers objets compilés.

Structure visée :

```text
Build/
└── Obj/
    └── <configuration>-<système>/
        └── NKIlyana/
```

### Variables utilisées

```text
%{wks.location}
%{cfg.buildcfg}
%{cfg.system}
%{prj.name}
```

Ces variables sont résolues par Jenga lors de la génération/build.

---

# 19. Répertoire du binaire

```py
targetdir("%{wks.location}/Build/Bin/%{cfg.buildcfg}-%{cfg.system}/%{prj.name}")
```

## Déclare

L'emplacement final de l'artefact produit par `NKIlyana`.

Comme le projet est :

```py
consoleapp()
```

l'artefact attendu est un exécutable, selon la plateforme.

---

# 20. Filtre Windows

L'extrait fourni commence par :

```py
with filter("system:Windows && !options:windows-runtime=uwp && !system:XboxSeries && !sys..."):
```

## C'est un véritable filtre Jenga

Ici, contrairement aux `if` Python précédents, nous avons :

```py
with filter(...)
```

Le guide Jenga définit les filtres comme des blocs appliqués uniquement lorsque les conditions de build sont satisfaites. Les opérateurs `&&` et `!` sont notamment pris en charge.

### Conditions visibles

Le filtre semble demander notamment :

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

### Donc

Le bloc ne concerne pas :

- UWP ;
- Xbox Series ;

même si la cible générale du projet est Windows.

### Questionnement important

La condition est tronquée :

```text
&& !sys...
```

> `?` **Condition complète à retrouver dans le fichier original.**

Il ne faut pas inventer le reste du filtre.

---

# 21. Toolchain Windows

À l'intérieur du filtre :

```py
usetoolchain(TC_WINDOWS)
```

## Ce que cela délègue

Le projet ne choisit pas forcément directement le compilateur.

Il utilise la variable :

```text
TC_WINDOWS
```

qui doit contenir/identifier la toolchain Windows.

### Chaîne de responsabilité

```text
NKIlyana.jenga
    ↓
TC_WINDOWS
    ↓
usetoolchain(...)
    ↓
compilateur/linker concret
```

### Questionnement

> `?` Qui définit `TC_WINDOWS` ?

Le présent fichier ne le fait pas.

Il faut regarder `jengaconfig` ou la configuration globale du workspace.

---

# 22. Defines Windows

```py
defines(["WIN32_LEAN_AND_MEAN", "_UNICODE", "UNICODE"])
```

## Déclare

Des macros C/C++ spécifiques à Windows.

### Filtre

Elles sont actives uniquement dans le filtre Windows montré plus haut.

Donc :

```text
Windows
└── defines(...)
```

mais pas nécessairement :

```text
Linux
└── defines(...)
```

---

# 23. Répertoire des bibliothèques Vulkan

```py
if VULKAN_LIB:
    libdirs([VULKAN_LIB])
```

## Attention à la distinction

Ici on a encore un :

```py
if
```

Python.

Cela signifie :

> « si le chemin Vulkan existe, ajoute ce répertoire de bibliothèques ».

Ce n'est pas lui qui déclare une bibliothèque Jenga.

### Il faut distinguer

```text
libdirs(...)
```

de :

```text
staticlib()
```

Le premier dit **où chercher des bibliothèques**.

Le second dit **quel type de projet je construis**.

Cette distinction est essentielle pour comprendre le fichier.

---

# 24. `_WIN_LINKS`

Le texte fourni s'arrête sur :

```py
_WIN_LINKS = [
    "NKGLSlang", "NKSPIRVCross",
```

## Ce qui peut être affirmé

Le projet prépare une liste de bibliothèques à lier sous Windows.

Les deux premières visibles sont :

```text
NKGLSlang
NKSPIRVCross
```

## Ce qu'on ne doit PAS inventer

La suite de la liste n'est pas fournie.

> `?` **Lire la suite du fichier pour savoir quelles bibliothèques sont effectivement ajoutées.**

---

# 25. Déclarations, filtres et délégations

| Élément | Déclare | Filtre | Délègue |
|---|---|---|---|
| `project("NKIlyana")` | le projet | Non | au DSL Jenga |
| `consoleapp()` | type = application console | Non | au backend/build system |
| `language("C++")` | C++ | Non | à la toolchain |
| `cppdialect("C++17")` | standard C++17 | Non | à la toolchain |
| `location(".")` | emplacement logique | Non | résolution Jenga |
| `files(...)` | sources locales | Non | compilation |
| `nkentseudependson(...)` | dépendances Nkentseu | Non directement | projets dépendants |
| `extra_includes` | chemins d'include | Non | compilation |
| `extra_defines` | macros C++ | Non directement | compilation |
| `objdir(...)` | objets intermédiaires | via variables | générateur/build |
| `targetdir(...)` | sortie finale | via variables | générateur/build |
| `filter("system:Windows ...")` | configuration conditionnelle | **Oui** | contexte de build |
| `usetoolchain(TC_WINDOWS)` | toolchain du bloc | Windows seulement | configuration globale |
| `defines(...)` | macros Windows | Windows seulement | compilation |
| `libdirs(...)` | chemins de libs | Windows + `VULKAN_LIB` | linker |
| `_TLS_DEPS` | liste Python de dépendances | variable d'environnement | bloc de config ultérieur |
| `_TLS_WIN_LINKS` | liste Python de libs | variable d'environnement | bloc de config ultérieur |

---

# 26. La question fondamentale : où est décidé le `StaticLib` ?

## Cas 1 — NKIlyana lui-même

Le fichier fourni dit :

```py
with project("NKIlyana"):
    consoleapp()
```

Donc :

```text
NKIlyana = ConsoleApp
```

**Pas StaticLib.**

---

## Cas 2 — Une dépendance telle que `NKTensor`

Ici, NKIlyana écrit :

```py
nkentseudependson(["NKTensor", ...])
```

Cela signifie :

```text
NKIlyana
    ↓
NKTensor
```

Mais cela ne répond pas à :

```text
NKTensor = StaticLib ?
```

Pour répondre, il faut ouvrir :

```text
NKTensor.jenga
```

et chercher :

```py
with project("NKTensor"):
    staticlib()
```

ou une autre déclaration de type.

### Principe

```text
NKIlyana.jenga
    │
    ├── project("NKIlyana")
    │     └── consoleapp()
    │
    └── nkentseudependson(...)
             │
             ├── NKTensor
             ├── NKNN
             ├── NKTrain
             └── ...
                    │
                    └── leurs propres .jenga
                          └── staticlib() / sharedlib() / ...
```

---

# 27. Ce fichier est donc un bon exemple de délégation

`NKIlyana.jenga` décide directement :

- **son propre type** ;
- ses sources ;
- son standard C++ ;
- ses répertoires de sortie ;
- certaines dépendances ;
- certaines options.

Mais il **ne décide pas directement** :

- le type de chaque dépendance ;
- la définition de `TC_WINDOWS` ;
- l'origine de `VULKAN_INCLUDE` ;
- l'origine de `VULKAN_LIB` ;
- l'origine de `WANT_VULKAN` ;
- la totalité de la configuration TLS ;
- la définition complète du filtre Windows tronqué dans l'extrait fourni.

---

# 28. Questions à poser lors de l'analyse de chaque `.jenga`

### Identité

- Quel est le nom du `project()` ?
- Quel est son type ?
- Où est-il déclaré ?
- Est-ce `consoleapp()`, `windowedapp()`, `staticlib()`, `sharedlib()` ou `test()` ?

### Sources

- Quels fichiers compile-t-il ?
- Utilise-t-il des glob patterns ?
- Les sources sont-elles locales ou héritées ?

### Dépendances

- Quelles sont ses dépendances ?
- Utilise-t-il `dependson()` ?
- Utilise-t-il `links()` ?
- Utilise-t-il une fonction spécifique comme `nkentseudependson()` ?
- Les dépendances sont-elles des projets Jenga ou des bibliothèques système ?

### Filtres

- Quels systèmes sont ciblés ?
- Quelles architectures ?
- Quelles configurations Debug/Release ?
- Quelles options CLI ?
- Quels filtres combinent `&&`, `||` et `!` ?

### Toolchain

- Où est choisie la toolchain ?
- Est-elle locale ou globale ?
- Quelle variable fournit son nom ?

### Includes

- Quels `includedirs()` / `extra_includes()` sont ajoutés ?
- Certaines variables proviennent-elles d'un autre `.jenga` ?

### Linking

- Quels `links()` sont actifs ?
- Dans quel filtre ?
- Quels `libdirs()` sont nécessaires ?
- Le lien est-il conditionnel ?

### Tests

- Existe-t-il un `test()` ?
- Existe-t-il une suite `Unitest` ?
- Le test est-il séparé du projet ?

### Délégation

- Qu'est-ce que ce fichier décide ?
- Qu'est-ce qu'il laisse à une configuration externe ?
- Qu'est-ce qu'il laisse aux `.jenga` des dépendances ?

### Zones incompréhensibles

Marquer :

```text
?
```

et expliquer exactement pourquoi :

```text
? = variable externe non définie ici
? = fichier tronqué
? = logique non vérifiable depuis ce seul fichier
? = syntaxe à confirmer dans la version actuelle de Jenga
```

---

# 29. Verdict sur `NKIlyana.jenga`

```text
TYPE
└── Console Application
    └── consoleapp()

SOURCES
└── src/main.cpp

LANGAGE
└── C++17

DEPENDANCES
└── nombreuses bibliothèques/modules Nkentseu
    └── via nkentseudependson(...)

FILTRE
└── Windows
    ├── exclut UWP
    ├── exclut Xbox Series
    └── condition exacte tronquée dans le texte fourni

CONFIGURATION EXTERNE
├── TC_WINDOWS
├── VULKAN_INCLUDE
├── VULKAN_LIB
└── WANT_VULKAN

CONFIGURATION ENVIRONNEMENTALE
└── NK_ENABLE_TLS
    ├── NKMbedTLS si activé
    └── bcrypt Windows si activé

STATIC LIB ?
└── NON
    └── aucune instruction staticlib() dans ce fichier
```

---

# 30. Point à vérifier absolument dans le dépôt

Pour répondre complètement à la question :

> **« Est-ce que `NKTensor`, `NKTrain`, `NKNN`, etc. sont des bibliothèques statiques ? »**

il faut ouvrir leurs propres fichiers :

```text
NKTensor.jenga
NKAutograd.jenga
NKNN.jenga
NKOptim.jenga
NKData.jenga
NKTrain.jenga
NKGpt.jenga
...
```

et chercher la déclaration :

```py
with project("NomDuModule"):
    staticlib()
```

C'est **cette déclaration du projet dépendant**, et non le simple fait d'écrire son nom dans `nkentseudependson(...)`, qui permettra de répondre avec certitude.

---

## Annotation finale

> **`NKIlyana.jenga` est un projet consommateur/orchestrateur.**
>
> Il déclare son propre exécutable, ses sources, son langage, ses chemins de sortie et ses dépendances. Il applique également des configurations spécifiques à certaines plateformes.
>
> La nature exacte des modules qu'il consomme est **déléguée aux projets correspondants** et à la configuration globale du workspace.

> **`?` Le fichier fourni étant tronqué dans la partie Windows, toute analyse au-delà de `_WIN_LINKS = [...]` doit être complétée à partir du fichier `.jenga` intégral.**

---

## Référence Jenga

Cette analyse suit les concepts documentés par Jenga :

- `project()` = unité de compilation ;
- `staticlib()` = bibliothèque statique ;
- `consoleapp()` = application console ;
- `filter()` = configuration conditionnelle ;
- les variables `%{...}` = variables dynamiques de workspace/projet/configuration ;
- les dépendances servent à déterminer la relation et l'ordre de build entre projets.
