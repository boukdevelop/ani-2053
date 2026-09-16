# Les deux erreurs de dépendances

A la base : `MonEssai.jenga`

```py
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# MonEssai - Jenga Project (inclus dans le workspace via include())

from Jenga import *

with project("MonEssai"):
    consoleapp()
    language("C++")
    cppdialect("C++17")
    location(".")
    files(["src/**.cpp", "include/**.hpp"])

```

## Après le retrait des **dependson** :

J'ai retirer la dépendances au C++ et j'ai utiliser la commande `jenga b --project MonEssai`

```py
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# MonEssai - Jenga Project (inclus dans le workspace via include())

from Jenga import *

with project("MonEssai"):
    consoleapp()
    cppdialect("C++17")
    location(".")
    files(["src/**.cpp", "include/**.hpp"])

```

Le message de sortie :

```bash

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
[NKCode] ATTENTION : aucun wheel Jenga trouve (dist/*.whl) -> le paquet n'aura PAS de Jenga embarque, et les boutons Construire/Executer seront inoperants. Produisez-le avec ./cri.sh dans le depot Jenga.

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. MonEssai [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonEssai                                                        Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\MonEssai\MonEssai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 15.45s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           15.50s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

```

## Après le retrait des **links** :

Etant donné qu'il n'y avait pas de liens, j'ai d'abord ajouté des liens pour faire l'exercice, biensûr avant de reconstruire le projet j'ai fait un `jenga c --project MonEssai` puis `jenga b --project MonEssai` :
```py
#!/usr/bin/env python3
# -*- coding: utf-8 -*-

# MonEssai - Jenga Project (inclus dans le workspace via include())

from Jenga import *

with project("MonEssai"):
    consoleapp()
    language("C++")
    cppdialect("C++17")
    location(".")
    files(["src/**.cpp", "include/**.hpp"])

    links([
        "user32",
        "gdi32",
        "opengl32"
    ])
```

---
Le message de sortie :
```bash
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
[NKCode] ATTENTION : aucun wheel Jenga trouve (dist/*.whl) -> le paquet n'aura PAS de Jenga embarque, et les boutons Construire/Executer seront inoperants. Produisez-le avec ./cri.sh dans le depot Jenga.

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. MonEssai [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: MonEssai                                                        Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\MonEssai\MonEssai.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 6.48s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           6.49s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

```

---
**REMARQUE :** Je remarque que la construction du projet a pris plus de temps que la dernière construction. Mais après reflexion, j'ai décidé de renettoyer le project et d'enlever de nouveau les links pour le reconstruire et le temps s'est encore réduis (je suis quitté de 6.49s à 5.26s ).

Bref de mon point de vue il n'y a pas de différence !