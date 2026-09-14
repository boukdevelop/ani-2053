# Nkentseu.jenga — Fichier de projet annoté

> **But** : Expliquer aussi clairement un fichir `.jenga` à d'autres personnes.
>
> **Grille de lecture** : `Types`, `Sources`, `Dépendances`, `Filtres`, `Tests`, puis `?` dès qu'un élément reste incompréhensible ou doit être confirmé.
>
> **Référence d'inspiration** : documentation Jenga consacrée au workspace, aux projets, aux toolchains, aux filtres, aux tests et aux dépendances. Voir notamment le guide complet et le guide développeur. ([Guide complet](https://github.com/Rihen-Universe/Jenga/blob/main/Jenga/Docs/GUIDE_COMPLET_JENGA.md), [Developer Guide](https://github.com/Rihen-Universe/Jenga/blob/main/Jenga/Docs/Jenga_Developer_Guide.md))

## 1. Légende

| Annotation | Signification |
|---|---|
| `[TYPE]` | Type/nature du bloc Jenga ou Python. |
| `[SOURCE]` | Fichier ou ressource externe consommé(e). |
| `[DEPENDENCY]` | Dépendance ou ordre nécessaire au build. |
| `[FILTER]` | Condition, option ou sélection qui modifie le graphe actif. |
| `[TEST]` | Test, banc, vérification ou mécanisme de validation. |
| `[NOTE]` | Observation explicative. |
| `[RISK]` | Point présentant un risque technique ou de reproductibilité. |
| `[?]` / `?` | Élément qui nécessite une clarification ou une vérification dans le code Jenga réel. |

## 2. Synthèse de l'analyse

### 2.1 Questionnements principaux à conserver

1. **Types** : la sémantique exacte de certaines fonctions Nkentseu (`nkentseutoolchain`, `dutc`, `dute`) n'est pas définie dans ce fichier.
2. **Sources** : plusieurs `useconfig()` chargent des fichiers externes, mais le fichier ne documente pas leur contrat, leurs variables exportées ni leur ordre de précédence.
3. **Dépendances** : une partie de l'ordre est explicitée par les commentaires, mais la totalité du graphe n'est pas visible ici. Il faut distinguer dépendance déclarée dans chaque `.jenga` et simple ordre d'inclusion du workspace.
4. **Filtres** : `newoption()`, `if False`, `if os.path.isfile(...)` et certains commentaires de plateforme modifient la sélection. Il faut vérifier si le graphe final dépend de l'état local du clone.
5. **Tests** : `Unitest` est déclaré, mais ce fichier ne suffit pas à identifier toutes les suites exécutées ni leurs critères de réussite.
6. **Reproductibilité** : l'inclusion conditionnelle de `Gemcrush` montre explicitement qu'un clone peut avoir un graphe différent selon les fichiers présents.

## 3. Points à vérifier avant de considérer l'annotation comme définitive

- [ ] Documenter précisément `dutc()`.
- [ ] Documenter précisément `dute()`.
- [ ] Relier chaque `useconfig()` à la liste des variables/fonctions qu'il fournit.
- [ ] Vérifier que l'ordre des `include()` est imposé par les dépendances réelles et pas seulement par convention.
- [ ] Vérifier le rôle exact de `u.Compile()` dans Unitest.
- [ ] Décider si `if False:` doit devenir un filtre Jenga officiel.
- [ ] Décider si les inclusions conditionnelles par `os.path.isfile()` doivent être considérées comme une feature ou un contournement de workspace cassé.
- [ ] Vérifier la cohérence entre les plateformes annoncées dans les commentaires et celles réellement supportées par les builders/toolchains disponibles.

## 4. Lecture d'un `.jenga` réel : déclarer, filtrer, déléguer

> **Question directrice :** quand je lis ce workspace, puis-je dire précisément ce qu'il déclare, ce qu'il filtre et ce qu'il délègue ? Et surtout : **où est décidé le type du projet ?**

### 4.1 Ce que ce fichier déclare réellement

Ce fichier est avant tout un **workspace**. Il ne contient pas, dans l'extrait fourni, une série de blocs `with project("..."):` qui définiraient directement les artefacts de chaque module.

Il déclare néanmoins plusieurs éléments globaux :

| Élément | Où | Rôle | Niveau |
|---|---|---|---|
| `workspace("Nkentseu", location=".")` | bloc principal | crée/ouvre le workspace racine | Workspace |
| `nkentseutoolchain()` | bloc principal | initialise la toolchain propre à Nkentseu | Toolchain |
| `configurations(["Debug", "Release"])` | bloc principal | déclare les configurations | Workspace |
| `targetoses([...])` | bloc principal | déclare les OS cibles | Workspace |
| `targetarchs([...])` | bloc principal | déclare les architectures cibles | Workspace |
| `unitest()` / `u.Compile()` | bloc principal | enregistre une validation/test de compilation | Test |
| `startproject("Sandbox")` | bloc principal | désigne le projet de démarrage | Workspace |
| `include("...")` | tout au long du fichier | enregistre/import les `.jenga` des modules et applications | Délégation |

**Questionnement :** ce fichier déclare-t-il des projets au sens Jenga (`project(...)`) ou se contente-t-il d'enregistrer des projets déclarés ailleurs ?

**Réponse à partir du fichier fourni :** il fait principalement la seconde chose. Les projets sont délégués aux `.jenga` inclus.

---

### 4.2 Ce qu'il filtre réellement

Le mot « filtre » doit être utilisé avec précision. Dans ce fichier, on trouve plusieurs mécanismes de sélection, mais ils n'ont pas tous la même nature.

#### Filtrage par option Jenga

```py
newoption(
    trigger="linux-backend",
    value="BACKEND",
    allowed=[
        ["xlib", "X11/XLib (defaut, le plus compatible)"],
        ["xcb", "X11/XCB (plus leger, asynchrone)"],
        ["wayland", "Wayland (compositeurs modernes, sans X11)"],
        ["headless", "Pas de fenetre (CI, serveurs, WSL sans ecran)"],
    ],
    default="xlib",
    description="Backend de fenetrage Linux"
)
```

**Annotation : `[FILTER]`**

Ce bloc ne choisit pas directement une bibliothèque statique ou partagée. Il introduit une **option de contexte** qui pourra ensuite être consommée par les modules inclus.

Même logique pour :

```py
newoption(
    trigger="windows-runtime",
    value="RUNTIME",
    allowed=[
        ["desktop", "Windows desktop classique (Win32)"],
        ["uwp", "Windows Runtime (UWP)"],
    ],
    default="desktop",
    description="Runtime Windows cible (desktop ou UWP)"
)
```

**Questionnement :** où ces options sont-elles réellement consommées ?

**Réponse visible ici :** le fichier indique que `config/modules.jenga` participe à l'émission des defines du backend Linux, mais le détail de la sélection des sources, librairies ou types de projets est délégué à cette configuration et aux `.jenga` des modules.

#### Filtrage par Python

Le cas `Songoo` :

```py
if False:
    with include("Applications/Songoo/Songoo.jenga"):
        pass
```

**Annotation : `[FILTER] [NOTE]`**

Le projet est ici explicitement désactivé par Python. Ce n'est pas une décision du type `StaticLib`/`SharedLib`.

Le cas `Gemcrush` :

```py
if os.path.isfile(
    os.path.join(_WORKSPACE_ROOT, "Applications", "Gemcrush", "GemCrush.jenga")
):
    with include("Applications/Gemcrush/GemCrush.jenga"):
        pass
```

**Annotation : `[FILTER] [RISK]`**

Ici, la présence physique du fichier `.jenga` décide si le projet entre dans le workspace. Le graphe du workspace peut donc varier selon le contenu du clone.

---

### 4.3 Ce que le fichier délègue

Le mécanisme central est :

```py
with include("Kernel/Foundation/NKCore/NKCore.jenga"):
    pass
```

ou :

```py
with include("Kernel/Runtime/NKRenderer/NKRenderer.jenga"):
    pass
```

ou encore :

```py
with include("Engine/Noge/Noge.jenga"):
    pass
```

**Annotation : `[DELEGATION]`**

Le workspace dit essentiellement :

> « ce projet/module fait partie du workspace ; va lire son propre fichier `.jenga` pour connaître sa configuration réelle. »

Cela implique une distinction essentielle :

```text
Nkentseu.jenga
    │
    ├── déclare le workspace
    ├── déclare les configurations
    ├── déclare les OS/architectures
    ├── définit des options globales
    └── inclut les projets
             │
             ├── NKCore.jenga
             ├── NKMath.jenga
             ├── NKRenderer.jenga
             ├── Noge.jenga
             └── ...
                    │
                    ├── project(...)
                    ├── staticlib() / sharedlib() / consoleapp() / ...
                    ├── files(...)
                    ├── includedirs(...)
                    ├── links(...)
                    ├── dependson(...)
                    └── filter(...)
```

Le guide Jenga présente précisément `project()` comme l'unité de compilation et `staticlib()` comme le moyen de déclarer une bibliothèque statique. Il décrit aussi `filter()` comme le mécanisme de configuration conditionnelle. citeturn186918search0

---

## 5. Réponse à la question clé : « où est décidé que ce module est une bibliothèque statique ? »

### 5.1 Ce que l'on peut prouver à partir de `Nkentseu.jenga`

**Nulle part dans ce fichier.**

Une recherche du fichier fourni ne fait apparaître ni :

```py
staticlib()
```

ni un bloc de projet du type :

```py
with project("NKCore"):
    staticlib()
```

Le workspace contient au contraire des `include()` vers les `.jenga` des différents modules.

### 5.2 Ce que cela signifie

Le type réel du module est donc **délégué**.

Pour pouvoir répondre sans ambiguïté à :

> « NKCore est-il une bibliothèque statique ? Où est-ce décidé ? »

il faut ouvrir :

```text
Kernel/Foundation/NKCore/NKCore.jenga
```

et rechercher quelque chose de cette forme :

```py
with project("NKCore"):
    staticlib()
```

Si `staticlib()` n'est pas dans ce fichier, il faut ensuite suivre les configurations qu'il charge :

```py
useconfig("...")
```

puis les éventuelles fonctions abstraites comme une fonction interne de Nkentseu qui encapsulerait la création du projet.

### 5.3 Ce qu'il ne faut surtout pas confondre

```py
with include("Kernel/Foundation/NKCore/NKCore.jenga"):
    pass
```

**ne signifie pas :**

> « NKCore est une bibliothèque statique. »

Cela signifie uniquement :

> « charge la description Jenga de NKCore dans le workspace courant. »

Le type `StaticLib`, `SharedLib`, `ConsoleApp`, `WindowedApp` ou `TestSuite` est une propriété du **projet enregistré par le DSL Jenga**, pas du simple fait qu'il soit inclus. Le guide développeur expose d'ailleurs ces catégories dans `ProjectKind`, notamment `STATIC_LIB`, `SHARED_LIB` et `TEST_SUITE`. citeturn186918search1

---

## 6. Exemple minimal d'un `.jenga` qui répond réellement à la question

Voici le niveau de détail que l'on doit rechercher dans le fichier du module :

```py
with project("NKCore"):
    staticlib()
    language("C++")
    cppdialect("C++20")
    files([
        "src/**.cpp",
    ])
    includedirs([
        "include",
    ])
```

### Lecture de cet exemple

| Question | Réponse |
|---|---|
| Quel est le projet ? | `NKCore` |
| Quel est son type ? | `staticlib()` → bibliothèque statique |
| Quel langage ? | C++ |
| Quelle norme ? | C++20 |
| Quelles sources ? | `src/**.cpp` |
| Quels includes ? | `include` |
| Est-ce que `include()` décide du type ? | Non |
| Est-ce que `staticlib()` décide du type ? | Oui |

La documentation Jenga donne cette même logique : `project(...)` crée l'unité de compilation et `staticlib()` la qualifie comme bibliothèque statique. citeturn186918search0

---

## 7. Grille d'annotation à appliquer à chaque vrai `.jenga` de module

Pour chaque fichier inclus par `Nkentseu.jenga`, l'annotation doit maintenant permettre de répondre aux questions suivantes :

### TYPE

```text
Quel objet ce fichier crée-t-il ?
[ ] StaticLib
[ ] SharedLib
[ ] ConsoleApp
[ ] WindowedApp
[ ] TestSuite
[ ] Autre / abstrait ?
```

### SOURCES

```text
Quels fichiers sont compilés ?
- files(...)
- generated files ?
- sources conditionnelles ?
```

### DÉPENDANCES

```text
De quels projets dépend-il ?
- dependson(...)
- links(...)
- includes indirects ?
```

### FILTRES

```text
Qu'est-ce qui change selon :
- system:Windows ?
- system:Linux ?
- config:Debug ?
- config:Release ?
- arch:arm64 ?
- options:...? 
```

### DÉLÉGATION

```text
Qu'est-ce que ce fichier ne décide pas lui-même ?
- toolchain ?
- type de dépendance ?
- backend ?
- configuration commune ?
- options globales ?
```

### TESTS

```text
Quel mécanisme vérifie ce projet ?
- unitest() ?
- test dédié ?
- benchmark ?
- application de démonstration ?
```

### QUESTION `?`

```text
Si l'on ne peut pas répondre en lisant uniquement ce fichier :
→ marquer `?`
→ indiquer précisément quel fichier doit être ouvert pour lever le doute.
```

---

## 8. Conclusion méthodologique

La bonne lecture d'un `.jenga` n'est donc pas seulement :

> « Que trouve-t-on dans ce fichier ? »

mais plutôt :

> **« Qu'est-ce que ce fichier décide, qu'est-ce qu'il conditionne et qu'est-ce qu'il transmet à un autre `.jenga` ? »**

Pour `Nkentseu.jenga`, la réponse actuelle est :

- **Il déclare** : le workspace, les configurations, les cibles, les options et l'organisation générale du build.
- **Il filtre** : certains comportements via les options Jenga et certaines inclusions via Python (`if False`, `os.path.isfile(...)`).
- **Il délègue** : la description concrète des modules à leurs propres fichiers `.jenga`.
- **Il ne prouve pas** : qu'un module est `StaticLib` ou `SharedLib`.
- **Pour savoir où `StaticLib` est décidé** : ouvrir le `.jenga` du module concerné et chercher `project(...)` + `staticlib()`, ou suivre la fonction/configuration qui encapsule cette déclaration.

> **Règle d'or :** `include()` enregistre un projet dans le workspace ; `staticlib()` qualifie le projet comme bibliothèque statique. Ne jamais attribuer au premier la responsabilité du second sans voir le `.jenga` réellement inclus.

## 4. Fichier source annoté

Les commentaires `[ANNOTATION]` ci-dessous sont **des annotations d'analyse**. Ils ne doivent pas être interprétés comme des instructions supplémentaires à Jenga.

```python
#!/usr/bin/env python3

# -*- coding: utf-8 -*-

"""

=============================================================================

Nkentseu.jenga => Workspace principal du framework Nkentseu

=============================================================================





Framework C++ multi-plateforme de gestion de fenetres, d'evenements

et de rendu pixel. Namespace : nkentseu





Architecture et ordre de dependances :





  NKPlatform  => Detection OS/arch/compilateur/CPU         (C++20)

       ↓

  NKCore      => Types, macros, assertions, bits            (C++20)

       ↓            ↓

  NKMath      => Types géométriques (Vec2, Rect, …)        (C++17)

  NKLogger    => Journalisation asynchrone multi-sink       (C++17)

       ↓            ↓                   ↓

  NKTime      => Gestion du temps / chrono                  (C++17)

  NKStream    => Flux de données (fichier, binaire…)        (C++17)

  NKMemory    => Gestion mémoire + smart pointers           (C++17)

       ↓

  NKWindow    => Fenetrage, evenements, entrees             (C++17)

       ↓

  NKRenderer  => Rendu graphique (Software, OpenGL…)        (C++17)

       ↓

  Sandbox     => Application de demonstration (tous OS)     (C++17)





Chaque projet possède son propre fichier .jenga dans son répertoire.

Ce fichier workspace les réunit via include().





Plateformes supportees :

  Windows     => Backend Win32                   (clang-mingw)

  Linux XLib  => Backend X11/XLib (defaut)       (clang-native / WSL2)

  Linux XCB   => Backend X11/XCB                 (clang-native / WSL2)

  Linux Wayland => Backend Wayland + xdg-shell   (clang-native / WSL2)

  Linux NOOP  => Backend headless (CI/WSL)        (clang-native / WSL2)

  macOS       => Backend Cocoa                   (clang-native)

  Android     => NativeActivity+EGL              (android-ndk)

  iOS         => Backend UIKit

  Web         => Emscripten+Canvas               (emscripten)

  HarmonyOS   => ArkUI Native

  XboxSeries  => UWP GameCore                    (xbox-clang)

  XboxOne     => UWP GameCore                    (xbox-clang)





Usage :

  jenga build                                                   # Hote (XLib)

  jenga build --platform windows                                # Windows

  jenga build --platform linux                                  # Linux XLib (defaut)

  jenga build --platform linux --linux-backend xcb

  jenga build --platform linux --linux-backend wayland

  jenga build --platform linux --linux-backend headless         # Linux headless

  jenga build --platform macos                                  # macOS Cocoa

  jenga build --platform android                                # Android (NDK)

  jenga build --platform ios                                    # iOS (UIKit)

  jenga build --platform web                                    # Web (Emscripten)

  jenga build --platform windows --windows-runtime desktop      # Windows desktop (Win32)

  jenga build --platform windows --windows-runtime uwp          # UWP (Windows Runtime)

  jenga build --platform xboxseries                             # Xbox Series

  jenga build --platform xboxone                                # Xbox One

  jenga build --config Release                                  # Build Release





=============================================================================

PACKAGING (jenga package) -- creer des installers distribuables

=============================================================================





Une fois le build OK, on peut empaqueter le binaire dans 3 formats Windows :





  jenga package --platform windows --project Pong --type zip --config Release

                --output ./dist

        => Pong.zip : archive portable (decompresser + lancer .exe)





  jenga package --platform windows --project Pong --type exe --config Release

                --output ./dist

        => Pong_setup.exe : installer Inno Setup avec wizard complet

           (EULA + choix dossier + raccourcis bureau/menu)





  jenga package --platform windows --project Pong --type msi --config Release

                --output ./dist

        => Pong.msi : Windows Installer officiel (WiX 5), idem fonctions





Linux : --type deb (dpkg-deb), --type rpm/appimage/snap (stubs)

macOS : --type pkg (pkgbuild), --type dmg (create-dmg)

Web   : --type zip (favicon + html + wasm + assets)





\-----------------------------------------------------------------------------

PREREQUIS A INSTALLER avant de packager (Windows)

\-----------------------------------------------------------------------------





  ZIP : aucun (Python stdlib seulement)





  EXE (Inno Setup) :

    winget install JRSoftware.InnoSetup

    -> installe iscc dans %LOCALAPPDATA%\\\Programs\\\Inno Setup 6\\

    -> jenga le detecte auto (pas besoin de toucher au PATH)





  MSI (WiX Toolset) :

    dotnet tool install --global wix --version 5.0.2

    -> ATTENTION : ne pas installer WiX 7+ qui demande l'OSMF EULA payante.

    -> jenga ajoute auto WiX a son PATH session





  Pillow (pour conversion icones PNG -> .ico/.icns/mipmap) :

    pip install Pillow>=10.0

    -> deja installe normalement (dep jenga via requirements.txt)





=============================================================================

ICONES D'APPLICATION (DSL Jenga, voir Core/IconConverter.py)

=============================================================================





  Dans un .jenga de projet (ex: Pong.jenga, hors filter) :





  appicon("Resources/MyApp/icon.png")

        # Source UNIQUE, dispatchee a TOUTES les plateformes :

        #   - Windows : convertit en .ico embedded via .res

        #   - macOS   : convertit en .icns dans bundle .app

        #   - Android : genere hierarchie res/mipmap-* (ldpi..xxxhdpi)

        #   - iOS     : copie + reference dans Info.plist

        #   - Web     : favicon.ico + favicon-{16,32,180,192,512}.png





  # Overrides par plateforme (gagnent sur appicon) :

  androidappicon("path.png")    # accepte PNG ou dossier res/mipmap-*/

  windowsicon   ("path.ico")    # accepte PNG ou .ico natif

  macosicon     ("path.icns")   # accepte PNG ou .icns natif

  iosappicon    ("path.png")    # ou dossier AppIcon.appiconset

  webfavicon    ("path.png")    # PNG converti automatiquement





  Note : Pong.exe affiche son icone correctement dans la taskbar/titre/

  Alt+Tab grace a un AppUserModelID stable defini dans NKWindow Win32

  (Rihen.Nkentseu.\<NomApp>). Sans ca, Windows utilise un AUMID auto

  base sur le ProductCode MSI -> icone generique cassee.





=============================================================================

METADONNEES INSTALLER (MSI/EXE/DEB/PKG)

=============================================================================





  Dans un .jenga de projet (hors filter) :





  appversion           ("1.0.0")                  # affichee dans Programs & Features

  apppublisher         ("Rihen Universe")         # nom editeur

  licensefile          ("../../LICENSE")          # .txt/.md (auto-converti en RTF pour WiX), ou .rtf direct

  createdesktopshortcut(True)                     # toggle raccourci bureau





  # Bag d'options libres (extensible) pour les besoins avances :

  installeroption("autostart_on_login", True)

  installeroption("registry_entry",     r\\"HKLM\\\Software\\\Pong")

  installeroption("autoupdate_url",     "https\://updates.example.com")





  # Ressources runtime a embarquer dans le package :

  dependfiles(["../../Resources/MyApp"])          # dossier ou fichier

        # Preserve la hierarchie relative au workspace.

        # Auto-inclut aussi les SHARED_LIB declarees via dependson().





=============================================================================

CYCLE DE BUILD + PACKAGE TYPIQUE (Pong exemple)

=============================================================================





  # 1. Build optimise

  jenga build --target Pong --config Release





  # 2. Generer les 3 packages Windows

  jenga package --platform windows --project Pong --type zip --config Release

  jenga package --platform windows --project Pong --type exe --config Release

  jenga package --platform windows --project Pong --type msi --config Release





  # 3. (optionnel) Build + APK Android

  jenga build --target Pong --config Release --platform android

  jenga deploy --platform android --project Pong --config Release \\

               --apk path/to/Pong-Release.apk --force-stop --run





  Distribution typique pour testeurs : envoyer Pong_setup.exe (Inno EXE)

  car wizard plus convivial que MSI. ZIP comme alternative sans install.





=============================================================================

IDE auto-config (jenga ide-setup)

=============================================================================





  jenga le fait automatiquement au premier `jenga build` :

    - VSCode/Cursor/Windsurf : .vscode/settings.json (associations .jenga

      = Python, extraPaths Jenga, diagnostics)

    - pyrightconfig.json universel (Neovim+pyright, Helix, Emacs+lsp-mode,

      Sublime+LSP, Zed)

  Merge non-destructif : preserve toutes vos prefs IDE existantes.

  Desactiver : JENGA_NO_IDE_CONFIG=1





  Reload editor apres premiere installation pour activer la coloration

  Python + autocomplete sur les .jenga.





  Notes Wayland :

    Prerequis : libwayland-dev, libxkbcommon-dev, wayland-protocols, libdecor-0-dev

    Generer xdg-shell-client-protocol.h :

      wayland-scanner client-header

        /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml

        Kernel/Runtime/NKWindow/src/NKWindow/Platform/Wayland/xdg-shell-client-protocol.h

      wayland-scanner private-code

        /usr/share/wayland-protocols/stable/xdg-shell/xdg-shell.xml

        Kernel/Runtime/NKWindow/src/NKWindow/Platform/Wayland/xdg-shell-protocol.c





Auteur : Rihen

Date   : 2026

=============================================================================

"""





import os

import sys

import shutil

from Jenga import *

from jengaconfig import *





# Ensure workspace root is in sys.path so '' works in all .jenga files

_WORKSPACE_ROOT = os.path.dirname(os.path.abspath(__file__)) if "__file__" in dir() else os.getcwd()

if _WORKSPACE_ROOT not in sys.path:

    sys.path.insert(0, _WORKSPACE_ROOT)





# Config partagee (registre des modules : kind static/shared + dependances).

# Chargee UNE fois ici via useconfig() et propagee a TOUS les .jenga inclus

# (feature Jenga 2.0.5) -> fini le bloc config inline (\~285 lignes).

# [ANNOTATION] [SOURCE] Fichier de configuration externe chargé puis propagé aux `.jenga` inclus. [DEPENDENCY] Le workspace dépend de ce fichier pour la configuration partagée.
useconfig("config/modules.jenga")

# [ANNOTATION] [SOURCE] Fichier de configuration externe chargé puis propagé aux `.jenga` inclus. [DEPENDENCY] Le workspace dépend de ce fichier pour la configuration partagée.
useconfig("config/toolchain.jenga")

# [ANNOTATION] [SOURCE] Fichier de configuration externe chargé puis propagé aux `.jenga` inclus. [DEPENDENCY] Le workspace dépend de ce fichier pour la configuration partagée.
useconfig("config/graphics.jenga")   # Vulkan SDK / glslang / SPIRV-Cross (partage)

# [ANNOTATION] [SOURCE] Fichier de configuration externe chargé puis propagé aux `.jenga` inclus. [DEPENDENCY] Le workspace dépend de ce fichier pour la configuration partagée.
useconfig("config/wayland.jenga")    # backend Wayland Linux (partage)





# [ANNOTATION] [TYPE] Workspace principal. [DEPENDENCY] Conteneur racine des projets inclus. [QUESTION] La stratégie de workspace unique est-elle définitive ou certains sous-workspaces doivent-ils être isolés ?
with workspace("Nkentseu", location="."):

# [ANNOTATION] [TYPE] Sélection/configuration de toolchain spécialisée Nkentseu. [QUESTION] La fonction est-elle un wrapper interne, et quelles toolchains exactes enregistre-t-elle ?
    nkentseutoolchain()





# [ANNOTATION] [?] API `dutc()` non expliquée dans ce fichier. [QUESTION] Signification exacte, effet sur le graphe de build et justification de `enable=True` ?
    dutc(enable=True)       # ========================= ?????

                            #   Je ne comprends pas très bien 

# [ANNOTATION] [?] API `dute()` non expliquée dans ce fichier. [QUESTION] Signification exacte et interaction avec Unitest/build ?
    dute(enable=True)       # ========================= ?????





# [ANNOTATION] [TYPE] Configurations globales du workspace. [NOTE] `Debug` et `Release` sont explicitement déclarées.
    configurations(["Debug", "Release"])





    # ===== Options Linux : choix du backend de fenetrage ========================

# [ANNOTATION] [FILTER] Déclaration d’une option CLI influençant le build/configuration. [QUESTION] Quels autres fichiers consomment cette option et comment sa valeur est-elle propagée ?
    newoption(

        trigger="linux-backend",

        value="BACKEND",

        allowed=[

            ["xlib",     "X11/XLib  (defaut, le plus compatible)"],

            ["xcb",      "X11/XCB   (plus leger, asynchrone)"],

            ["wayland",  "Wayland   (compositeurs modernes, sans X11)"],

            ["headless", "Pas de fenetre (CI, serveurs, WSL sans ecran)"],

        ],

        default="xlib",

        description="Backend de fenetrage Linux"

    )





# [ANNOTATION] [FILTER] Déclaration d’une option CLI influençant le build/configuration. [QUESTION] Quels autres fichiers consomment cette option et comment sa valeur est-elle propagée ?
    newoption(

        trigger="headless",

        description="[Obsolete] Utiliser --options linux-backend=headless"

    )





    # ===== Option Windows : Desktop vs UWP ====================================

    # Jenga v2.0.1 n'expose pas TargetOS.UWP; on route UWP via une option.

# [ANNOTATION] [FILTER] Déclaration d’une option CLI influençant le build/configuration. [QUESTION] Quels autres fichiers consomment cette option et comment sa valeur est-elle propagée ?
    newoption(

        trigger="windows-runtime",

        value="RUNTIME",

        allowed=[

            ["desktop", "Windows desktop classique (Win32)"],

            ["uwp",     "Windows Runtime (UWP)"],

        ],

        default="desktop",

        description="Runtime Windows cible (desktop ou UWP)"

    )





    # ===== Plateformes et architectures cibles ==================================

# [ANNOTATION] [TYPE] Ensemble des OS cibles du workspace.
    targetoses([

        TargetOS.WINDOWS,

        TargetOS.LINUX,

        TargetOS.MACOS,

        TargetOS.ANDROID,

        TargetOS.IOS,

        TargetOS.WEB,

        TargetOS.HARMONYOS,

        TargetOS.XBOX_SERIES,

        TargetOS.XBOX_ONE,

    ])





# [ANNOTATION] [TYPE] Ensemble des architectures cibles du workspace. [QUESTION] Le mapping OS ↔ architecture est-il strictement validé ailleurs ?
    targetarchs([

        TargetArch.X86_64,   # Desktop (Windows, Linux, macOS, Xbox)

        TargetArch.ARM64,    # Mobile  (Android, iOS)

        TargetArch.WASM32,   # Web     (Emscripten)

    ])





# [ANNOTATION] [TEST] Bloc de tests Unitest. [QUESTION] `u.Compile()` compile-t-il seulement le runner de tests ou déclenche-t-il également leur exécution ailleurs ?
    with unitest() as u:

        u.Compile()





# [ANNOTATION] [TYPE] Projet lancé par défaut. [DEPENDENCY] `Sandbox` doit être présent et correctement enregistré pour `jenga run`.
    startproject("Sandbox")





    # Backend de fenetrage Linux : le define NKENTSEU_FORCE_WINDOWING_*_ONLY est

    # emis par _emit_linux_backend_defines() dans config/modules.jenga, appele

    # par nkentseudependson() — donc par CHAQUE projet. Ne pas le poser ici :

    # hors projet, defines() est ignore silencieusement par Jenga (essaye, sans

    # effet ; l'explication complete est dans config/modules.jenga).





    # =========================================================================

    # Inclusion de chaque projet depuis son propre fichier .jenga

    # L'ordre respecte la chaine de dependances.

    # =========================================================================





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Foundation/NKPlatform/NKPlatform.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Foundation/NKPlatform/NKPlatform.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Foundation/NKCore/NKCore.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Foundation/NKCore/NKCore.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/System/NKLogger/NKLogger.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/System/NKLogger/NKLogger.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Foundation/NKMath/NKMath.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Foundation/NKMath/NKMath.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Foundation/NKMemory/NKMemory.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Foundation/NKMemory/NKMemory.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Foundation/NKContainers/NKContainers.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Foundation/NKContainers/NKContainers.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKImage/NKImage.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKImage/NKImage.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKFont/NKFont.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKFont/NKFont.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKAudio/NKAudio.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKAudio/NKAudio.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKMedia/NKMedia.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKMedia/NKMedia.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/System/NKTime/NKTime.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/System/NKTime/NKTime.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/System/NKStream/NKStream.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/System/NKStream/NKStream.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/System/NKThreading/NKThreading.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/System/NKThreading/NKThreading.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/System/NKFileSystem/NKFileSystem.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/System/NKFileSystem/NKFileSystem.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/System/NKReflection/NKReflection.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/System/NKReflection/NKReflection.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/System/NKNetwork/NKNetwork.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/System/NKNetwork/NKNetwork.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/System/NKSerialization/NKSerialization.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/System/NKSerialization/NKSerialization.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Externals/Libs/NKGlad/NKGlad.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Externals/Libs/NKGlad/NKGlad.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Externals/Libs/NKGLSlang/NKGLSlang.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Externals/Libs/NKGLSlang/NKGLSlang.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Externals/Libs/NKSPIRVCross/NKSPIRVCross.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Externals/Libs/NKSPIRVCross/NKSPIRVCross.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Externals/Libs/NKMbedTLS/NKMbedTLS.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Externals/Libs/NKMbedTLS/NKMbedTLS.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Externals/Libs/pybind11/pybind11.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Externals/Libs/pybind11/pybind11.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKEvent/NKEvent.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKEvent/NKEvent.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKWindow/NKWindow\.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKWindow/NKWindow\.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKSL/NKSL.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKSL/NKSL.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKCanvas/NKCanvas.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKCanvas/NKCanvas.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKRHI/NKRHI.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKRHI/NKRHI.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKUI/NKUI.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKUI/NKUI.jenga"):

        pass





    # NKGui (framework UI immediat) + NKEditorKit (coquille d'editeur) : requis par NKCode.

# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKGui/NKGui.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKGui/NKGui.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Engine/NKEditorKit/NKEditorKit.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Engine/NKEditorKit/NKEditorKit.jenga"):

        pass

    # Unkeny — moteur de jeu 2D sur NKCanvas. Il COMPOSE NKECS, NKCollision

    # et NKPhysics ; il n'en reecrit rien. Son editeur vit dans

    # Applications/UnkenyEditor : un moteur ne contient pas son outil.

# [ANNOTATION] [SOURCE] Inclus : `Engine/Unkeny/Unkeny.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Engine/Unkeny/Unkeny.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKCode/NKCode.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKCode/NKCode.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NK3DModeler/NK3DModeler.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NK3DModeler/NK3DModeler.jenga"):

        pass





    # Integrations decouplees (ImGui / NKUI -> NKCanvas/NKRHI). Optionnelles :

    # une app les lie seulement si elle en a besoin (ImGui n'est PAS tire dans

    # le coeur de NKCanvas/NKRHI).

# [ANNOTATION] [SOURCE] Inclus : `Integrations/ImGui/NKImGuiIntegration.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Integrations/ImGui/NKImGuiIntegration.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Integrations/NKUI/NKUIIntegration.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Integrations/NKUI/NKUIIntegration.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Integrations/NKGui/NKGuiIntegration.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Integrations/NKGui/NKGuiIntegration.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKCamera/NKCamera.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKCamera/NKCamera.jenga"):

        pass





    # NKCollision (collision 2D+3D, zero-STL).

# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKCollision/NKCollision.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKCollision/NKCollision.jenga"):

        pass





    # NKPhysics (dynamique corps rigide 2D+3D, sur NKCollision).

# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKPhysics/NKPhysics.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKPhysics/NKPhysics.jenga"):

        pass





    # NKAnimPhysics (pose physiquement correcte : masse/COM, equilibre, contacts,

    # correction de pose et de clip). Extrait de NKRenderer/Tools/Animation le

    # 2026-08-14 -- bloc de decision "substrats animation" du CLAUDE.md parent.

    # CPU pur, headless, Foundation seule. NE depend PAS de NKPhysics aujourd hui :

    # voir l en-tete de NKAnimPhysics.jenga, qui dit pourquoi, et ou brancher le

    # pont le jour venu (NkRagdoll, jamais un second pont).

# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKAnimPhysics/NKAnimPhysics.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKAnimPhysics/NKAnimPhysics.jenga"):

        pass





    # NKAnimation (substrat d animation : clips, blend 1D/2D, HFSM, reciblage,

    # motion path, edition de pose-cles). Extrait de NKRenderer/Tools/Animation

    # le 2026-08-14. Foundation seule ; le renderer n en garde que la facade

    # de rendu et le debug-draw, et les CONSOMME.

# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKAnimation/NKAnimation.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKAnimation/NKAnimation.jenga"):

        pass





    # NKNavigation (NavMesh + pathfinding A*, sur NKCollision -- raycast reel

    # de sondage walkable). Voir Engine/Noge/ROADMAP.md, pilier Navigation IA.

# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKNavigation/NKNavigation.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKNavigation/NKNavigation.jenga"):

        pass





    # NKXR (runtime VR/AR/XR : sessions, espaces, poses, entrees par actions,

    # swapchains par oeil ; backend n°1 = simulateur desktop). Etage 0 de la

    # mission XR_MISSION_IA.md.

# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKXR/NKXR.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKXR/NKXR.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/Sandbox/Sandbox.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/Sandbox/Sandbox.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/ConquerorProto/ConquerorProto.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/ConquerorProto/ConquerorProto.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkAudioDemo/NkAudioDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkAudioDemo/NkAudioDemo.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkCameraDemos/NkCameraDemos.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkCameraDemos/NkCameraDemos.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Sandbox/System/NKFileSystem/NKFileSystemSandbox.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Sandbox/System/NKFileSystem/NKFileSystemSandbox.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Sandbox/System/NKLogger/NKLoggerSandbox.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Sandbox/System/NKLogger/NKLoggerSandbox.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Sandbox/System/NKReflection/NKReflectionSandbox.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Sandbox/System/NKReflection/NKReflectionSandbox.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Sandbox/System/NKNetwork/NKNetworkSandbox.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Sandbox/System/NKNetwork/NKNetworkSandbox.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKRenderer/NKRenderer.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKRenderer/NKRenderer.jenga"):

        pass





    # ===== Sous-systeme IA (Kernel/AI) — construit bottom-up =====

# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKTensor/NKTensor.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKTensor/NKTensor.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKAutograd/NKAutograd.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKAutograd/NKAutograd.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKNN/NKNN.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKNN/NKNN.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKOptim/NKOptim.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKOptim/NKOptim.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKData/NKData.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKData/NKData.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKTrain/NKTrain.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKTrain/NKTrain.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKInfer/NKInfer.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKInfer/NKInfer.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKRL/NKRL.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKRL/NKRL.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKAgent/NKAgent.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKAgent/NKAgent.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKEvolve/NKEvolve.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKEvolve/NKEvolve.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKCivilization/NKCivilization.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKCivilization/NKCivilization.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKEmbodied/NKEmbodied.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKEmbodied/NKEmbodied.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKGen/NKGen.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKGen/NKGen.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKGpt/NKGpt.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKGpt/NKGpt.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Kernel/AI/NKSpeech/NKSpeech.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/AI/NKSpeech/NKSpeech.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKTensorDemo/NKTensorDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKTensorDemo/NKTensorDemo.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkSLComputeCheck/NkSLComputeCheck.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkSLComputeCheck/NkSLComputeCheck.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkGpuProbe/NkGpuProbe.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkGpuProbe/NkGpuProbe.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkComputeNkSL/NkComputeNkSL.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkComputeNkSL/NkComputeNkSL.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkTensorGpuTest/NkTensorGpuTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkTensorGpuTest/NkTensorGpuTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKGpuBenchTest/NKGpuBenchTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKGpuBenchTest/NKGpuBenchTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKConvBenchTest/NKConvBenchTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKConvBenchTest/NKConvBenchTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKConvResidentBench/NKConvResidentBench.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKConvResidentBench/NKConvResidentBench.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKMlpResidentBench/NKMlpResidentBench.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKMlpResidentBench/NKMlpResidentBench.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKMnistGpuTrain/NKMnistGpuTrain.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKMnistGpuTrain/NKMnistGpuTrain.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKRebasinTest/NKRebasinTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKRebasinTest/NKRebasinTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKMnistCnnGpuTrain/NKMnistCnnGpuTrain.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKMnistCnnGpuTrain/NKMnistCnnGpuTrain.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKTransformerTest/NKTransformerTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKTransformerTest/NKTransformerTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKGptTrain/NKGptTrain.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKGptTrain/NKGptTrain.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKIlyana/NKIlyana.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKIlyana/NKIlyana.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKAutogradTest/NKAutogradTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKAutogradTest/NKAutogradTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKNNTest/NKNNTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKNNTest/NKNNTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKConvTest/NKConvTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKConvTest/NKConvTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKDataTest/NKDataTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKDataTest/NKDataTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKBpeTest/NKBpeTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKBpeTest/NKBpeTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKLlamaBlockTest/NKLlamaBlockTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKLlamaBlockTest/NKLlamaBlockTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKRebasinTransformer/NKRebasinTransformer.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKRebasinTransformer/NKRebasinTransformer.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKTrainTest/NKTrainTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKTrainTest/NKTrainTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKFp16Test/NKFp16Test.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKFp16Test/NKFp16Test.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKRnnCtcTest/NKRnnCtcTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKRnnCtcTest/NKRnnCtcTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKASRTest/NKASRTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKASRTest/NKASRTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKImageCodecTest/NKImageCodecTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKImageCodecTest/NKImageCodecTest.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkEditableMeshDemo/NkEditableMeshDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkEditableMeshDemo/NkEditableMeshDemo.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkLocomotionDemo/NkLocomotionDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkLocomotionDemo/NkLocomotionDemo.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkAssetIODemo/NkAssetIODemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkAssetIODemo/NkAssetIODemo.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkFBXParityDemo/NkFBXParityDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkFBXParityDemo/NkFBXParityDemo.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkSVGImportDemo/NkSVGImportDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkSVGImportDemo/NkSVGImportDemo.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NKMeshAITest/NKMeshAITest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKMeshAITest/NKMeshAITest.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NKEditMeshHarness/NKEditMeshHarness.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKEditMeshHarness/NKEditMeshHarness.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkAnimPhysTest/NkAnimPhysTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkAnimPhysTest/NkAnimPhysTest.jenga"):

        pass

    # NkMatInventaireTest : banc ARRETE (cc6aba5b), RETIRE du workspace le 17/08.

    # Il echoue au lien PAR CONSTRUCTION -- 118 symboles Demo3DHost* definis dans

    # NkDemo3D.cpp, jamais compile ici -- et c'etait documente dans son en-tete

    # d'arret : ces 118 symboles SONT la mesure de la dette C (lire un .nkmat

    # tire toute la pile d'interface). Le laisser enregistre faisait echouer le

    # build complet de main pour tout le monde (trouve par l'agent Ilyana).

    # NE PAS le « reparer » en ajoutant NkDemo3D.cpp a ses sources : compiler

    # toute la pile d'interface a chaque build est precisement le cout qui a

    # fait arreter ce banc. Ses sources restent dans Applications/ avec leur

    # en-tete d'arret ; il se re-enregistre le jour ou Demo3DHost devient une

    # bibliotheque -- il linkera alors sans une ligne de plus.

# [ANNOTATION] [FILTER] Projet volontairement retiré du graphe actif. [QUESTION] Quelle condition permettrait officiellement sa réactivation ?
    # with include("Applications/NkMatInventaireTest/NkMatInventaireTest.jenga"):

    #     pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkMicRecord/NkMicRecord.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkMicRecord/NkMicRecord.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NKSpeechTest/NKSpeechTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKSpeechTest/NKSpeechTest.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NKTTSTrain/NKTTSTrain.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKTTSTrain/NKTTSTrain.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkVoiceLoopDemo/NkVoiceLoopDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkVoiceLoopDemo/NkVoiceLoopDemo.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NKSpeechFeatureDemo/NKSpeechFeatureDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKSpeechFeatureDemo/NKSpeechFeatureDemo.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NKMediaTest/NKMediaTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKMediaTest/NKMediaTest.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkVideoReadTest/NkVideoReadTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkVideoReadTest/NkVideoReadTest.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkAudioPlayer/NkAudioPlayer.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkAudioPlayer/NkAudioPlayer.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkVideoPlayer/NkVideoPlayer.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkVideoPlayer/NkVideoPlayer.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NKOpusRef/NKOpusRef.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKOpusRef/NKOpusRef.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NKVideoTest/NKVideoTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKVideoTest/NKVideoTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKInferTest/NKInferTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKInferTest/NKInferTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKGGUFInspectTest/NKGGUFInspectTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKGGUFInspectTest/NKGGUFInspectTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKLLMInferTest/NKLLMInferTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKLLMInferTest/NKLLMInferTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKQwenTokenizerTest/NKQwenTokenizerTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKQwenTokenizerTest/NKQwenTokenizerTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKQwen2BackwardTest/NKQwen2BackwardTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKQwen2BackwardTest/NKQwen2BackwardTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKQwen2SftTest/NKQwen2SftTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKQwen2SftTest/NKQwen2SftTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKQ4MatmulTest/NKQ4MatmulTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKQ4MatmulTest/NKQ4MatmulTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKQwen2GpuTest/NKQwen2GpuTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKQwen2GpuTest/NKQwen2GpuTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKQwen2Chat/NKQwen2Chat.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKQwen2Chat/NKQwen2Chat.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKQwen2SftGpuTest/NKQwen2SftGpuTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKQwen2SftGpuTest/NKQwen2SftGpuTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKQwen2Train/NKQwen2Train.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKQwen2Train/NKQwen2Train.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKQwen2Ask/NKQwen2Ask.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKQwen2Ask/NKQwen2Ask.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKRLTest/NKRLTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKRLTest/NKRLTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKAgentTest/NKAgentTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKAgentTest/NKAgentTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKAgentLLMTest/NKAgentLLMTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKAgentLLMTest/NKAgentLLMTest.jenga"):

        pass



# [ANNOTATION] [SOURCE] Inclus : `Applications/NkAgentEcsDemo/NkAgentEcsDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkAgentEcsDemo/NkAgentEcsDemo.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKEmbodiedTest/NKEmbodiedTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKEmbodiedTest/NKEmbodiedTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKEvolveTest/NKEvolveTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKEvolveTest/NKEvolveTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKEvolveNNTest/NKEvolveNNTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKEvolveNNTest/NKEvolveNNTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKCivilizationTest/NKCivilizationTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKCivilizationTest/NKCivilizationTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKCivilizationSocialTest/NKCivilizationSocialTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKCivilizationSocialTest/NKCivilizationSocialTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKCivilizationScaleTest/NKCivilizationScaleTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKCivilizationScaleTest/NKCivilizationScaleTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKGenTest/NKGenTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKGenTest/NKGenTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKVAETest/NKVAETest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKVAETest/NKVAETest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKMnistVAETest/NKMnistVAETest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKMnistVAETest/NKMnistVAETest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKMnistConvVAETest/NKMnistConvVAETest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKMnistConvVAETest/NKMnistConvVAETest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKConvVAETest/NKConvVAETest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKConvVAETest/NKConvVAETest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKDiffusionTest/NKDiffusionTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKDiffusionTest/NKDiffusionTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKVoxelGenTest/NKVoxelGenTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKVoxelGenTest/NKVoxelGenTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKObjectGenTest/NKObjectGenTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKObjectGenTest/NKObjectGenTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKGen3DTest/NKGen3DTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKGen3DTest/NKGen3DTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKGenMeshTest/NKGenMeshTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKGenMeshTest/NKGenMeshTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKSmoothMeshTest/NKSmoothMeshTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKSmoothMeshTest/NKSmoothMeshTest.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NKMatTypeResetTest/NKMatTypeResetTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKMatTypeResetTest/NKMatTypeResetTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKEditTargetTest/NKEditTargetTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKEditTargetTest/NKEditTargetTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKMeshRenderTest/NKMeshRenderTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKMeshRenderTest/NKMeshRenderTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/Model/Model.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/Model/Model.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkSLCheck/NkSLCheck.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkSLCheck/NkSLCheck.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKPA/NKPA.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKPA/NKPA.jenga"):

        pass





    # NKECS (ECS bas niveau archetypes) — DOIT etre enregistre AVANT Noge qui en

    # depend (sinon %{NKECS.location} vide -> includes NKECS/* introuvables).

# [ANNOTATION] [SOURCE] Inclus : `Kernel/Runtime/NKECS/NKECS.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Kernel/Runtime/NKECS/NKECS.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Engine/Noge/Noge.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Engine/Noge/Noge.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/Nogee/Nogee.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/Nogee/Nogee.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKEditorKitDemo/NKEditorKitDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKEditorKitDemo/NKEditorKitDemo.jenga"):

        pass





    # Banc SANS FENETRE de NKEditorKit : resolution des roles de theme (le

    # magenta du 18/08) et vocabulaire du backend graphique (Metal compris).

    # Console, aucun GPU, code de sortie 0/1 -- il peut donc tourner partout.

# [ANNOTATION] [SOURCE] Inclus : `Applications/NKEditorKitTest/NKEditorKitTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKEditorKitTest/NKEditorKitTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKUIDesign/NKUIDesign.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKUIDesign/NKUIDesign.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/ConquerorLab/ConquerorLab.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/ConquerorLab/ConquerorLab.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkRef/NkRef.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkRef/NkRef.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkAnimaEditor/NkAnimaEditor.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkAnimaEditor/NkAnimaEditor.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/ImGuiRef/ImGuiRef.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/ImGuiRef/ImGuiRef.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKGuiDrawTest/NKGuiDrawTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKGuiDrawTest/NKGuiDrawTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKGuiDemo/NKGuiDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKGuiDemo/NKGuiDemo.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NKViewportDemo/NKViewportDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKViewportDemo/NKViewportDemo.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/PV3DE/PV3DE.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/PV3DE/PV3DE.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/Pong/Pong.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/Pong/Pong.jenga"):

        pass





    # TODO(Songoo) : migration rendu GL -> NKCanvas a FINIR (12 scenes UI utilisent encore

    # Render/GLContext|GLRenderer2D|Texture2D|FontAtlas supprimes). Desactive du build pour

    # ne pas casser `jenga build`. Le code source reste dans main ; reactiver apres migration.

# [ANNOTATION] [FILTER] Projet volontairement retiré du graphe actif. [QUESTION] Quelle condition permettrait officiellement sa réactivation ?
    # with include("Applications/Songoo/Songoo.jenga"):

    #     pass

# [ANNOTATION] [FILTER] Inclusion explicitement désactivée. [QUESTION] Cette désactivation est-elle temporaire ou doit-elle devenir une vraie option de build ?
    if False:

# [ANNOTATION] [SOURCE] Inclus : `Applications/Songoo/Songoo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
        with include("Applications/Songoo/Songoo.jenga"):

            pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/Nkoung/Nkoung.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/Nkoung/Nkoung.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/Mou/Mou.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/Mou/Mou.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkImeTest/NkImeTest.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkImeTest/NkImeTest.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkImageDemo/NkImageDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkImageDemo/NkImageDemo.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/RihenDefi/RihenDefi.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/RihenDefi/RihenDefi.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkAudioECSDemo/NkAudioECSDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkAudioECSDemo/NkAudioECSDemo.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkNetWorldDemo/NkNetWorldDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkNetWorldDemo/NkNetWorldDemo.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkNavDemo/NkNavDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkNavDemo/NkNavDemo.jenga"):

        pass





# [ANNOTATION] [SOURCE] Inclus : `Applications/NkNavCoreDemo/NkNavCoreDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkNavCoreDemo/NkNavCoreDemo.jenga"):

        pass



    # Jalon G2.3 Noge : scripting C++ natif hot-reload (DLL) — démo console

    # (compile un script en .dll a runtime, hot-reload avec etat preserve).

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkHotReloadDemo/NkHotReloadDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkHotReloadDemo/NkHotReloadDemo.jenga"):

        pass



    # Jalon G2.1 Noge : systeme ECS UI in-game (HUD) — demo console headless

    # (NKCanvas backend Software CPU + NKFont embarque, assertions de pixels).

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkUIHudDemo/NkUIHudDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkUIHudDemo/NkUIHudDemo.jenga"):

        pass





    # Serie d'apprentissage : concevoir une app 3D avec NKRenderer pas a pas

    # (5 etapes/projets : fenetre -> renderer -> scene -> camera -> meshes custom).

    # Voir Tutoriels3D/README.md.

# [ANNOTATION] [SOURCE] Inclus : `Tutoriels3D/Tutoriels3D.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Tutoriels3D/Tutoriels3D.jenga"):

        pass





    # Etage 0 XR : scene NKRenderer en stereo SIMULEE via NKXR (simulateur

    # desktop, souris = tete). Voir XR_MISSION_IA.md.

# [ANNOTATION] [SOURCE] Inclus : `Applications/NKXRDemo/NKXRDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKXRDemo/NKXRDemo.jenga"):

        pass





    # Etage 3 XR : realite augmentee a marqueurs (camera + NkArSession).

# [ANNOTATION] [SOURCE] Inclus : `Applications/NKARDemo/NKARDemo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NKARDemo/NKARDemo.jenga"):

        pass



    # GemCrush — SEULEMENT si son .jenga est la. Sur cette branche le dossier

    # n'a jamais ete commite (il l'est sur main) : depuis f9b68097 (2026-09-01)

    # un clone frais — donc tout runner GitHub Actions — echouait des le

    # chargement du workspace (« External file not found »), quelle que soit

    # la cible demandee. Constate le 2026-09-04 sur le build macOS de NKCode.

# [ANNOTATION] [FILTER] Inclusion conditionnelle selon la présence physique du fichier. [RISK] Deux clones du dépôt peuvent donc produire des graphes de workspace différents.
    if os.path.isfile(os.path.join(_WORKSPACE_ROOT, "Applications", "Gemcrush", "GemCrush.jenga")):

# [ANNOTATION] [SOURCE] Inclus : `Applications/Gemcrush/GemCrush.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
        with include("Applications/Gemcrush/GemCrush.jenga"):

            pass

    # Les trois jeux de plateau, batis sur la coquille moderne NkCanvasApp.

    # Ils servent aussi de PREUVE a cette coquille : une base qui n a qu un

    # seul consommateur ne prouve rien sur sa reutilisabilite.

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkDames/NkDames.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkDames/NkDames.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkEchecs/NkEchecs.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkEchecs/NkEchecs.jenga"):

        pass

# [ANNOTATION] [SOURCE] Inclus : `Applications/NkLudo/NkLudo.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/NkLudo/NkLudo.jenga"):

        pass

    # L'editeur d'Unkeny. Il vit ici, pas dans Engine : un moteur ne

    # contient pas son outil.

# [ANNOTATION] [SOURCE] Inclus : `Applications/UnkenyEditor/UnkenyEditor.jenga`. [DEPENDENCY] L’enregistrement crée une dépendance de workspace vers ce sous-projet.
    with include("Applications/UnkenyEditor/UnkenyEditor.jenga"):

        pass
```

## 5. Questions détaillées par domaine

### 5.1 Types

- Quels sont les types réellement créés par `workspace()`, `unitest()`, `include()` et les différentes fonctions de configuration ?
- `nkentseutoolchain()` crée-t-il une toolchain, sélectionne-t-il une toolchain existante, ou configure-t-il plusieurs toolchains par défaut ?
- Les projets inclus utilisent-ils tous le même dialecte C++ ou chaque `.jenga` peut-il le surcharger ?

### 5.2 Sources

- Quelle est la source de vérité pour `config/modules.jenga`, `config/toolchain.jenga`, `config/graphics.jenga` et `config/wayland.jenga` ?
- Quelle partie de la configuration est héritée du workspace et quelle partie est locale au projet ?
- Des fichiers `.jenga` inclus ajoutent-ils eux-mêmes d'autres `useconfig()` ?

### 5.3 Dépendances

- Les commentaires comme « `NKECS` doit être enregistré avant `Noge` » reflètent-ils une vraie dépendance du resolver ou uniquement une dépendance d'enregistrement ?
- Existe-t-il des cycles potentiels dans les dépendances des modules ?
- L'ordre des `include()` peut-il être réduit si le resolver effectue réellement un tri topologique comme décrit par le guide développeur ?
- Quels modules sont des feuilles de la chaîne, et lesquels sont réellement des bibliothèques partagées réutilisables ?

### 5.4 Filtres

- `linux-backend` agit-il uniquement sur Linux ou peut-il influencer la résolution de bibliothèques sur d'autres plateformes ?
- `windows-runtime` modifie-t-il seulement la génération du projet Windows ou également les bibliothèques liées ?
- `if os.path.isfile(...)` doit-il être remplacé par une option explicite afin de garantir un graphe reproductible en CI ?
- Les projets commentés/retirés sont-ils des artefacts obsolètes ou des travaux suspendus ?

### 5.5 Tests

- Quelle commande exacte lance les tests Unitest après `u.Compile()` ?
- Les applications nommées `*Test`, `*BenchTest`, `*Harness` sont-elles toutes des suites de test, des démonstrateurs ou des bancs de performance ?
- Quels tests sont obligatoires dans CI et lesquels sont optionnels ou expérimentaux ?

## 6. Constats particuliers

### `dutc(enable=True)` / `dute(enable=True)`

Ces deux éléments sont les plus explicitement marqués comme incompris dans le fichier d'origine. Ils doivent rester marqués `?` tant que leur implémentation ou leur documentation Jenga interne n'a pas été examinée.

### Projet `Songoo`

Le projet est volontairement désactivé via `if False`. L'annotation doit donc le classer comme **filtre/désactivation statique**, et non comme une simple dépendance manquante.

### Projet `Gemcrush`

Le test `os.path.isfile(...)` constitue une **condition de présence physique**. C'est utile pour éviter un échec du chargement sur une branche où le dossier n'est pas commité, mais cela signifie aussi que le workspace n'a pas exactement le même graphe sur tous les clones.

### `NkMatInventaireTest`

Le fichier explique explicitement pourquoi ce banc n'est plus enregistré : son lien casserait le build global et son problème est présenté comme une dette structurelle. Il faut donc le classer comme **test/banc suspendu documenté**, pas comme oubli.

## 7. Conclusion

Le fichier fourni est déjà riche en commentaires, mais il mélange plusieurs niveaux de documentation :

1. documentation fonctionnelle du framework ;
2. configuration du workspace ;
3. inventaire des modules ;
4. règles d'ordre de dépendances ;
5. historique de décisions techniques ;
6. exceptions temporaires ou permanentes.

La présente version les distingue sans supprimer le contenu original. Les zones marquées `?` sont volontairement conservées comme questions ouvertes, car le fichier seul ne permet pas de déduire avec certitude leur sémantique.
