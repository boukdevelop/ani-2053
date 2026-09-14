# Votre premier projet

```txt
Structure du projet Applications
C:.
├───.jenga
└───Applications
    ├───.jenga
    ├───Build
    │   ├───Bin
    │   │   └───Debug-Windows
    │   │       └───MonEssai
    │   └───Obj
    │       └───Debug-Windows
    │           └───MonEssai
    └───MonEssai
        ├───include
        └───src
```

## Vérification via ***jenga info*** :

```txt


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

======================== Jenga Workspace: Applications =========================

Location: ...\Applications
Entry file: ...\Applications\Applications.jenga
Configurations: Debug, Release
Platforms: Windows
Target OSes: Windows
Target Architectures: x86_64


Projects
------------------------------------------------------------
Name       Kind         Language   Test   External
==================================================
MonEssai   ConsoleApp   C++        No     Yes


Available Toolchains
------------------------------------------------------------
Name                Family   Target OS   Arch     Env  
=======================================================
host-clang          clang    Windows     x86_64   mingw
host-gcc            gcc      Windows     x86_64   mingw
clang-mingw         clang    Windows     x86_64   mingw
mingw               gcc      Windows     x86_64   mingw
clang-cross-linux   clang    Linux       x86_64   gnu


```