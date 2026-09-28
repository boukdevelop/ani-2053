# Le même programme sur deux systèmes

> ***Énoncé :***
Faites tourner le même binaire, ou la même source recompilée, sur deux systèmes différents. Relevez tout ce qui change sans que vous ayez rien écrit pour cela.

Afin de mener à bien cette exercice, j'utiliserai le code qui a servie à l'exercice 12 [l'inventaire des écrans](exo12-l_inventaire_des_ecrans/c3-exo12_reponse.md). Ce projet sera lancer respectivement sur `Windows` et sur `Zorin OS` un système de la **suite Debian**.

## Sur Windows

```bash
PS C:\Users\FRANCK\Desktop\bouk\FirstWindow> jenga c

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║             Multi-platform C/C++ Build System v2.8.0             ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Removed C:\Users\FRANCK\Desktop\bouk\FirstWindow\Build\Obj\Debug-Windows\Window\src_main.obj
Removed C:\Users\FRANCK\Desktop\bouk\FirstWindow\Build\Bin\Debug-Windows\Window\Window.exe
PS C:\Users\FRANCK\Desktop\bouk\FirstWindow> jenga b

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

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Window [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Window                                                          Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Window\Window.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                           Time: 1m23.7s  │

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           1m23.9s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

PS C:\Users\FRANCK\Desktop\bouk\FirstWindow> jenga run

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


━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ▶  EXECUTION  —  Window.exe
     C:\Users\FRANCK\Desktop\bouk\FirstWindow\Build\Bin\Debug-Windows\Window\Window.exe
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━

[2026-09-28 03:06:36.913] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:06:36.920] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1366x768 | physique 1366x768 | position (0, 0) | echelle x1.00 | primaire=oui
[2026-09-28 03:06:36.924] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.00
[2026-09-28 03:07:02.978] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:07:02.982] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1280x720 | physique 1280x720 | position (0, 0) | echelle x1.00 | primaire=oui
[2026-09-28 03:07:02.985] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.00
[2026-09-28 03:07:39.117] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:07:39.121] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1366x768 | physique 1366x768 | position (0, 0) | echelle x1.00 | primaire=oui
[2026-09-28 03:07:39.121] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.00
[2026-09-28 03:07:53.430] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:07:53.432] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1366x768 | physique 1366x768 | position (0, 0) | echelle x1.25 | primaire=oui
[2026-09-28 03:07:53.444] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.25
[2026-09-28 03:07:53.449] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:07:53.464] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1366x768 | physique 1366x768 | position (0, 0) | echelle x1.25 | primaire=oui
[2026-09-28 03:07:53.464] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.25
[2026-09-28 03:08:22.488] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:08:22.760] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1366x768 | physique 1366x768 | position (0, 0) | echelle x1.00 | primaire=oui
[2026-09-28 03:08:22.773] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.00
[2026-09-28 03:08:23.010] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:08:23.011] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1366x768 | physique 1366x768 | position (0, 0) | echelle x1.00 | primaire=oui
[2026-09-28 03:08:23.011] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.00

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (118.57s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\Users\FRANCK\Desktop\bouk\FirstWindow> 
```

## Sur Zorin OS