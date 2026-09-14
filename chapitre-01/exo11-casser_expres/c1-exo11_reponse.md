# Casser exprès

***Énoncé :***
Introduisez une faute de syntaxe dans un fichier de NKMath et reconstruisez. ``Notez`` : combien de temps met la construction à s'arrêter, quels projets ont quand même été construits, et ce que le message d'erreur vous apprend sur l'ordre de construction. Remettez ensuite le fichier en état.

## Arborscence propre à `NKMath` :

```txt
...\Nkentseu\Kernel\Foundation\NKMath>tree /F

C:.
│   NKMath.jenga
│   NKMathSIMD.jenga
│   Readme.md
│   ROADMAP.md
│
├───pch
│       pch.cpp
│       pch.h
│
├───src
│   └───NKMath
│           NkAngle.cpp
│           NkAngle.h
│           NkColor.cpp
│           NkColor.h
│           NkEulerAngle.cpp
│           NkEulerAngle.h
│           NkFunctions.cpp
│           NkFunctions.h
│           NkLegacySystem.h
│           NkMat.cpp
│           NkMat.h
│           NKMath.h
│           NkMathApi.h
│           NkMathFormat.h
│           NkQuat.cpp
│           NkQuat.h
│           NkRandom.cpp
│           NkRandom.h
│           NkRange.cpp
│           NkRange.h
│           NkRectangle.cpp
│           NkRectangle.h
│           NkSegment.cpp
│           NkSegment.h
│           NkSIMD.cpp
│           NkSIMD.h
│           NkVec.cpp
│           NkVec.h
│
└───tests
        benchmark_smoke.cpp
        test_smoke.cpp
```

## Constrution erronée

Afin de mener à bien l'exercice, je suis partie fauter la **ligne 2** de **NkSIMD.cpp** :
```cpp
#include "pch.h"
#include "NkSIMD.h; /* Erreur*/

namespace nkentseu {}
```

---

Temps d'exécution du projet : `5m15.3s`.

projets construits :
* NKPlatform;
* NKGlad;
* NKGLSlang;
* NKSPIRVCross;
* NKMbedTLS (mais avec 31 Warnings);
* pybind11;
* NKCore;
* NKMemory;
* NKContainers;
* NKThreading;
* NKMath.

Mon interprétation de cette erreur est que 10 projets sur 212 ont été construit à cause d'un échec. Pour un code erreur : `Not reached : 201`. Le status **✗ FAILURE**.

Enfin, l'erreur à corriger est très bien expliqué dans :
```txt
╔═══════════════════════════════════════════════════════════════════════════════════
║                                Compilation Error: NkSIMD.cpp                      
╠═══════════════════════════════════════════════════════════════════════════════════
║ C:\Users\FRANCK\Desktop\dossier\ENSPY\polytech_L2\GAP\Nkentseu\Kernel\Foundation\N
║ NKMath\NkSIMD.cpp:2:10: warning: missing terminating '"' character [-Winvalid-pp-t
║     2 | #include "NkSIMD.h;                                                       
║       |          ^                                                                
║ C:\Users\FRANCK\Desktop\dossier\ENSPY\polytech_L2\GAP\Nkentseu\Kernel\Foundation\N
║ NKMath\NkSIMD.cpp:2:10: error: expected "FILENAME" or <FILENAME>                  
║ 1 warning and 1 error generated.                                                  
╚═══════════════════════════════════════════════════════════════════════════════════
```
On nous avertit d'une mauvaise annotation à la ligne 2.

## Construction correcte

Malheureusement, ma machine ne supporte pas la construction complète de ``NKMath``. Donc en attendant de trouver une machine de qualité pouvant supporter cette activité je m'arreterai d'abord à ce niveau.
