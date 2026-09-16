# Le tableau des temps

**Énoncé :**
Mesurez et présentez : construction complète à froid, construction complète à chaud, construction d'un seul module, construction après modification d'un seul fichier source, construction après modification d'un seul en-tête. Le dernier cas est le plus intéressant : expliquez-le.

## Construction du projet à froid

J'ai décider de construire le projet ***NkDames*** via la commande `jenga b --project NKDames` :

```bash
PS C:\Users\FRANCK\Desktop\Nkentseu> jenga b --project NkDames

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

Build Order (22 projects):
  1. NKPlatform [STATIC_LIB] → 
  2. NKGlad [STATIC_LIB] → 
  3. NKCore [STATIC_LIB] (depends: NKPlatform) → 
  4. NKMemory [STATIC_LIB] (depends: NKCore, NKPlatform) → 
  5. NKContainers [STATIC_LIB] (depends: NKCore, NKMemory, NKPlatform) → 
  6. NKMath [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform) → 
  7. NKThreading [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform) → 
  8. NKLogger [STATIC_LIB] (depends: NKContainers, NKCore, NKMemory, NKPlatform, NKThreading) → 
  9. NKReflection [STATIC_LIB] (depends: NKContainers, NKCore, NKLogger, NKMemory, NKPlatform, NKThreading) → 
  10. NKTime [STATIC_LIB] (depends: NKContainers, NKCore, NKLogger, NKMemory, NKPlatform, NKThreading) → 
  11. NKFont [STATIC_LIB] (depends: NKContainers, NKCore, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading) → 
  12. NKFileSystem [STATIC_LIB] (depends: NKContainers, NKCore, NKLogger, NKMemory, NKPlatform, NKThreading) → 
  13. NKEvent [STATIC_LIB] (depends: NKContainers, NKCore, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading, NKTime) → 
  14. NKSerialization [STATIC_LIB] (depends: NKContainers, NKCore, NKFileSystem, NKLogger, NKMemory, NKPlatform, NKReflection, NKThreading) → 
  15. NKStream [STATIC_LIB] (depends: NKContainers, NKCore, NKFileSystem, NKLogger, NKMemory, NKPlatform, NKThreading) → 
  16. NKWindow [STATIC_LIB] (depends: NKContainers, NKCore, NKEvent, NKFileSystem, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading, NKTime) → 
  17. NKImage [STATIC_LIB] (depends: NKContainers, NKCore, NKFileSystem, NKLogger, NKMath, NKMemory, NKPlatform, NKStream, NKThreading) → 
  18. NKCanvas [STATIC_LIB] (depends: NKContainers, NKCore, NKEvent, NKFileSystem, NKFont, NKGlad, NKImage, NKLogger, NKMath, NKMemory, NKPlatform, NKStream, NKThreading, NKTime, NKWindow) → 
  19. NKMedia [STATIC_LIB] (depends: NKContainers, NKCore, NKFileSystem, NKFont, NKImage, NKLogger, NKMath, NKMemory, NKPlatform, NKStream, NKThreading, NKTime) → 
  20. NKGui [STATIC_LIB] (depends: NKContainers, NKCore, NKEvent, NKFileSystem, NKFont, NKImage, NKLogger, NKMath, NKMemory, NKPlatform, NKThreading) → 
  21. NKAudio [STATIC_LIB] (depends: NKContainers, NKCore, NKFileSystem, NKImage, NKLogger, NKMath, NKMedia, NKMemory, NKPlatform, NKStream, NKThreading) → 
  22. NkDames [WINDOWED_APP] (depends: NKAudio, NKCanvas, NKContainers, NKCore, NKEvent, NKFileSystem, NKFont, NKGlad, NKGui, NKImage, NKLogger, NKMath, NKMemory, NKPlatform, NKReflection, NKSerialization, NKStream, NKThreading, NKTime, NKWindow)


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKPlatform                                                       Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 7 source file(s)
✓   [1/7] Compiled: NkArchDetect.cpp
✓   [2/7] Compiled: NkCGXDetect.cpp
✓   [3/7] Compiled: NkCompilerDetect.cpp
✓   [4/7] Compiled: NkEndianness.cpp
✓   [5/7] Compiled: NkEnv.cpp
✓   [6/7] Compiled: NkPlatformConfig.cpp
✓   [7/7] Compiled: NkCPUFeatures.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKPlatform.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 37.36s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKGlad                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 2 source file(s)
✓   [1/2] Compiled: wgl.c
✓   [2/2] Compiled: gl.c
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKGlad.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 9.61s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKCore                                                           Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 5 source file(s)
✓   [1/5] Compiled: NkAssert.cpp
✓   [2/5] Compiled: NkLimits.cpp
✓   [3/5] Compiled: NkTraits.cpp
✓   [4/5] Compiled: NkBits.cpp
✓   [5/5] Compiled: NkPlatform.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKCore.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 7.81s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKMemory                                                         Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 14 source file(s)
✓   [1/14] Compiled: NkFunction.cpp
✓   [2/14] Compiled: NkContainerAllocator.cpp
✓   [3/14] Compiled: NkGc.cpp
✓   [4/14] Compiled: NkFunctionSIMD.cpp
✓   [5/14] Compiled: NkGlobalOperators.cpp
✓   [6/14] Compiled: NkHash.cpp
✓   [7/14] Compiled: NkMemory.cpp
✓   [8/14] Compiled: NkPoolAllocator.cpp
✓   [9/14] Compiled: NkMultiLevelAllocator.cpp
✓   [10/14] Compiled: NkProfiler.cpp
✓   [11/14] Compiled: NkTracker.cpp
✓   [12/14] Compiled: NkTag.cpp
✓   [13/14] Compiled: NkUtils.cpp
✓   [14/14] Compiled: NkAllocator.cpp
ℹ Linking...
✓ Built: Build\Lib\Debug-Windows\NKMemory.lib

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                             Time: 8.77s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: NKContainers                                                     Kind: STATIC_LIB  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 43 source file(s)

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkBTree.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Associative\NkBTree.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: NkBinaryTree.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Associative\NkBinaryTree.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                               Compilation Error: NkHashMap.cpp                               ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Associative\NkHashMap.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                            Compilation Error: NkPriorityQueue.cpp                            ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Associative\NkPriorityQueue.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                 Compilation Error: NkSet.cpp                                 ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Associative\NkSet.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                 Compilation Error: NkMap.cpp                                 ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Associative\NkMap.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkTrie.cpp                                 ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Associative\NkTrie.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                            Compilation Error: NkUnorderedSet.cpp                             ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Associative\NkUnorderedSet.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                            Compilation Error: NkUnorderedMap.cpp                             ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Associative\NkUnorderedMap.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: NkRingBuffer.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\CacheFriendly\NkRingBuffer.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkArray.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\CacheFriendly\NkArray.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkPool.cpp                                 ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\CacheFriendly\NkPool.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkBind.cpp                                 ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Functional\NkBind.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                              Compilation Error: NkFunction.cpp                               ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Functional\NkFunction.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: NkFunctional.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Functional\NkFunctional.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkPair.cpp                                 ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Heterogeneous\NkPair.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                           Compilation Error: NkInitializerList.cpp                           ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Iterators\NkInitializerList.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkTuple.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Heterogeneous\NkTuple.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkDeque.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Sequential\NkDeque.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: NkContainers.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\NkContainers.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                              Compilation Error: NkIterator.cpp                               ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Iterators\NkIterator.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                               Compilation Error: NkVector.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Sequential\NkVector.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: NkDoubleList.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Sequential\NkDoubleList.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkList.cpp                                 ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Sequential\NkList.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkGraph.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Specialized\NkGraph.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                              Compilation Error: NkQuadTree.cpp                               ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Specialized\NkQuadTree.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                               Compilation Error: NkBase64.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\Encoding\NkBase64.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                              Compilation Error: NkEncoding.cpp                               ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\Encoding\NkEncoding.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkASCII.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\Encoding\NkASCII.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkUTF16.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\Encoding\NkUTF16.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkUTF8.cpp                                 ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\Encoding\NkUTF8.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkUTF32.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\Encoding\NkUTF32.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: NkBasicString.cpp                             ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\NkBasicString.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                               Compilation Error: NkFormat.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\NkFormat.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                               Compilation Error: NkString.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\NkString.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: NkStringUtils.cpp                             ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\NkStringUtils.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                            Compilation Error: NkStringBuilder.cpp                            ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\NkStringBuilder.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: NkStringHash.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\NkStringHash.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                             Compilation Error: NkStringView.cpp                              ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\String\NkStringView.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                              Compilation Error: NkOptional.cpp                               ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Utilities\NkOptional.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                               Compilation Error: NkResult.cpp                                ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Utilities\NkResult.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                               Compilation Error: NkVariant.cpp                               ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Utilities\NkVariant.cpp

╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║                                Compilation Error: NkSpan.cpp                                 ║
╠══════════════════════════════════════════════════════════════════════════════════════════════╣
║ fatal error: malformed or corrupted precompiled file: 'could not find file                   ║
║ 'C:/Users/FRANCK/Desktop/dossier/ENSPY/polytech_L2/GAP/Nkentseu/Kernel/Foundation/NKContaine ║
║ rs/pch/pch.h' referenced by AST file                                                         ║
║ 'C:\Users\FRANCK\Desktop\Nkentseu\Build\Obj\Debug-Windows\NKContainers\NKContainers.pch''    ║
║ 1 error generated.                                                                           ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

✗ ✗ Compilation failed: C:\Users\FRANCK\Desktop\Nkentseu\Kernel\Foundation\NKContainers\src\NKContainers\Views\NkSpan.cpp

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✗ Build Failed                                                                 Time: 4.32s  │
│ Errors: 86  | Failed files: 43                                                               │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                  BUILD FAILED                                  
════════════════════════════════════════════════════════════════════════════════
Projects Built:  4/22
Failed:         1
Not reached:    17  (arret au premier echec — voir --keep-going)
Errors:         86
Time:           1m7.9s
Status:         ✗ FAILURE
════════════════════════════════════════════════════════════════════════════════

Echecs (1) — a corriger :
  ✗ NKContainers

```

---

J'ai reçu un ensemble d'erreur !