# Le module seul

# NKMath — Build Dependency Tree

Représentation de la séquence de compilation du workspace **NKMath** via Jenga v2.8.0 (Configuration: Debug | Target: Windows x86_64 | Toolchain: clang-mingw). 

L'arbre se lit de **bas en haut** : la couche initiale `NKPlatform` est construite en premier à la base, et le projet final `NKMath` se situe au sommet.

```text
[5] NKMath [STATIC_LIB] (Cible finale)
│   ├── NkAngle.cpp
│   ├── NkEulerAngle.cpp
│   ├── NkColor.cpp
│   ├── NkFunctions.cpp
│   ├── NkMat.cpp
│   ├── NkQuat.cpp
│   ├── NkRandom.cpp
│   ├── NkRange.cpp
│   ├── NkRectangle.cpp
│   ├── NkSIMD.cpp
│   ├── NkSegment.cpp
│   └── NkVec.cpp
│
├── [4] NKContainers [STATIC_LIB]
│   ├── NkBinaryTree.cpp
│   ├── NkHashMap.cpp
│   ├── NkBTree.cpp
│   ├── NkPriorityQueue.cpp
│   ├── NkMap.cpp
│   ├── NkSet.cpp
│   ├── NkUnorderedSet.cpp
│   ├── NkUnorderedMap.cpp
│   ├── NkTrie.cpp
│   ├── NkArray.cpp
│   ├── NkPool.cpp
│   ├── NkRingBuffer.cpp
│   ├── NkFunction.cpp
│   ├── NkBind.cpp
│   ├── NkFunctional.cpp
│   ├── NkPair.cpp
│   ├── NkTuple.cpp
│   ├── NkInitializerList.cpp
│   ├── NkIterator.cpp
│   ├── NkContainers.cpp
│   ├── NkDeque.cpp
│   ├── NkDoubleList.cpp
│   ├── NkList.cpp
│   ├── NkQuadTree.cpp
│   ├── NkVector.cpp
│   ├── NkGraph.cpp
│   ├── NkASCII.cpp
│   ├── NkEncoding.cpp
│   ├── NkBase64.cpp
│   ├── NkUTF16.cpp
│   ├── NkUTF32.cpp
│   ├── NkUTF8.cpp
│   ├── NkBasicString.cpp
│   ├── NkFormat.cpp
│   ├── NkString.cpp
│   ├── NkStringBuilder.cpp
│   ├── NkStringHash.cpp
│   ├── NkOptional.cpp
│   ├── NkResult.cpp
│   ├── NkStringUtils.cpp
│   ├── NkStringView.cpp
│   ├── NkVariant.cpp
│   └── NkSpan.cpp
│
├── [3] NKMemory [STATIC_LIB]
│   ├── NkFunction.cpp
│   ├── NkContainerAllocator.cpp
│   ├── NkGc.cpp
│   ├── NkFunctionSIMD.cpp
│   ├── NkGlobalOperators.cpp
│   ├── NkHash.cpp
│   ├── NkMemory.cpp
│   ├── NkPoolAllocator.cpp
│   ├── NkMultiLevelAllocator.cpp
│   ├── NkProfiler.cpp
│   ├── NkTag.cpp
│   ├── NkTracker.cpp
│   ├── NkUtils.cpp
│   └── NkAllocator.cpp
│
├── [2] NKCore [STATIC_LIB]
│   ├── NkLimits.cpp
│   ├── NkAssert.cpp
│   ├── NkTraits.cpp
│   ├── NkBits.cpp
│   └── NkPlatform.cpp
│
└── [1] NKPlatform [STATIC_LIB] (Base du projet)
    ├── NkArchDetect.cpp
    ├── NkCompilerDetect.cpp
    ├── NkCGXDetect.cpp
    ├── NkEndianness.cpp
    ├── NkEnv.cpp
    ├── NkPlatformConfig.cpp
    └── NkCPUFeatures.cpp