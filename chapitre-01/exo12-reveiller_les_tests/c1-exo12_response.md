# Réveiller les tests

***Énoncé :***
Le workspace désactive la compilation des tests. Trouvez la ligne qui le fait, lancez malgré tout une suite de tests d'un module, et rendez : combien de suites existent, combien s'exécutent, combien passent.

---

Dans l'optique de mener à bien cette exercice, j'ai eu à rechercher où est ce que l'on peut activer et désactiver les tests dans le fichiers ``Nkentseu.jenga`` aux lignes 451 et 453.

En faisant les test malgré la situation, je rescence `60 tests` dont :

```txt
Gamepad_Tests, NKAgent_Tests, NKAudio_Tests, NKAutograd_Tests, NKCamera_Tests, NKCanvas_Tests, NKCivilization_Tests, NKCollision_Tests, NKContainers_Tests, NKCore_Tests, N
KData_Tests, NKECS_Tests, NKEmbodied_Tests, NKEvent_Tests, NKEvolve_Tests, NKFileSystem_Tests, NKFont_Tests, NKGen_Tests, NKImage_Tests, NKInfer_Tests, NKLogger_Tests, NKMath_Tests, NKMemory_T
ests, NKNN_Tests, NKNavigation_Tests, NKNetwork_Tests, NKOptim_Tests, NKPhysics_Tests, NKPlatform_Tests, NKRHIDemo_Tests, NKRHI_Tests, NKRL_Tests, NKReflection_Tests, NKRenderer_Tests, NKSeria
lization_Tests, NKStream_Tests, NKTensor_Tests, NKThreading_Tests, NKTime_Tests, NKTrain_Tests, NKUI_Tests, NKWindow_Tests, NKXR_Tests, NewGeneration_Tests, NkCanvasDemo_Tests, NkDrawableDemo_
Tests, NkFDV2_Tests, NkFontDemo_Tests, NkRHIDemoFullImage_Tests, NkRHIDemoFull_Tests, NkRHIInterpTest_Tests, NkSWRasterPrimitives_Tests, NkSpriteDemo_Tests, Noge_Tests, RendererRHI_Tests, cr2d
_Tests, firsttriangle_Tests, gltftest_Tests, r2d01_Tests, renderdemo_Tests


```
