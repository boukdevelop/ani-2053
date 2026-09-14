# Votre premier projet



```bash
============================================================
Summary
============================================================

  Project:      MonEssai
  Type:         console
  Language:     C++ (C++17)
  Location:     .
  Jenga file:   separate (.jenga inclus)
  Directories:  Yes
  Starter files:Yes

  Structure:
  MonEssai/
  +-- MonEssai.jenga   (projet inclus via include)
  +-- src/
  |   +-- main.cpp
  +-- include/

```

## Vérification via ***jenga info*** :

```bash

$ jenga info

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

[NKCode] ATTENTION : aucun wheel Jenga trouve (dist/*.whl) -> le paquet n'aura PAS de Jenga embarque, et les boutons Construire/Executer seront inoperants. Produisez-le avec ./cri.sh dans le d
epot Jenga.
========================== Jenga Workspace: Nkentseu ===========================

Location: ...\Nkentseu
Entry file: ...\Nkentseu\Nkentseu.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows, Linux, macOS, Android, iOS, Web, HarmonyOS, XboxSeries, XboxOne
Target Architectures: x86_64, arm64, wasm32
Start project: Sandbox


Projects
------------------------------------------------------------
Name                         Kind          Language   Test   External
=====================================================================
__Unitest__                  StaticLib     C++        No     No
.                                  .       .           .     .
.                                  .       .           .     .
.                                  .       .           .     .
.                                  .       .           .     .
MonEssai                     ConsoleApp    C++        No     Yes

.
.
.
```