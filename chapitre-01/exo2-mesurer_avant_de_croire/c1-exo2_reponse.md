# MESURER AVANT DE CROIRE

## **Taches**
Il nous est demandé de comparer nos projets, les différents fichiers `*.jenga` à ceux des ficheirs source.

### Observation propre à mon projet

```zsh
╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.6.2             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

=========================== Jenga Workspace: kodesi ============================

Location: ...\kodesi
Entry file: ...kodesi_jenga\kodesi\kodesi.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows
Target Architectures: x86_64


Projects
------------------------------------------------------------
Name         Kind         Language   Test   External
====================================================
test_jenga   ConsoleApp   C++        No     No


Available Toolchains
------------------------------------------------------------
Name                Family   Target OS   Arch     Env
=======================================================
host-clang          clang    Windows     x86_64   mingw
host-gcc            gcc      Windows     x86_64   mingw
clang-mingw         clang    Windows     x86_64   mingw
mingw               gcc      Windows     x86_64   mingw
clang-cross-linux   clang    Linux       x86_64   gnu


Daemon
------------------------------------------------------------
Status: Not running

```

|Num projet | Nom | Type| |
|-|-|-|-|
|*1*|*test_jenga*|*ConsoleApp*||
|1|||**Total**|

Racine du WOrksapce : `kodesi`

Dans mon projet j'ai `5 chaines de compilation`, qui sont entre autre :
* host-clang
* host-gcc
* clang-mingw
* mingw
* clang-cross-linux

### Observation propre aux fichiers sources du dépôts 

```zsh
╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.6.2             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

========================== Jenga Workspace: NKWindow ===========================

Location: ...\Exemples\27_nk_window
Entry file: ...\Exemples\27_nk_window\27_nk_window.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows, Linux, macOS, Android, Web, iOS, HarmonyOS
Target Architectures: x86_64, arm64, wasm32
Start project: Sandbox


Projects
------------------------------------------------------------
Name                Kind          Language   Test   External
============================================================
__Unitest__         StaticLib     C++        No     No
NKWindow            StaticLib     C++        No     No
NKWindow_Tests      TestSuite     C++        Yes    No
Sandbox             WindowedApp   C++        No     No
SandboxCamera       WindowedApp   C++        No     No
SandboxCameraFull   WindowedApp   C++        No     No


Available Toolchains
------------------------------------------------------------
Name                Family   Target OS   Arch     Env
=======================================================
host-clang          clang    Windows     x86_64   mingw
host-gcc            gcc      Windows     x86_64   mingw
clang-mingw         clang    Windows     x86_64   mingw
mingw               gcc      Windows     x86_64   mingw
clang-cross-linux   clang    Linux       x86_64   gnu


Daemon
------------------------------------------------------------
Status: Not running
```

## **Compte rendu**

Après observation, je me suis rendu compte que non seulement il y'a plus :
* De projets par type;
* De nombre de chaînes de compilation;
* De projet de démarrage;
Avec un projet en particulier `NKWindow_Tests` dont le test est réussi.

Alors que moi je n'avait qu'un seul projet dont la sortie de test est : `Test : No`.

