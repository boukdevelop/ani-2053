> # L'histoire d'un fichier

***Énoncé :***
Choisissez un fichier du moteur et lisez son histoire complète. Reconstituez : sa création, les trois moments où il a le plus changé, et ce que les messages disent des raisons. Une page.
---

## L'historique complète de `Nkentseu.jenga` du moteur NKentseu

```bash
FRANCK@DESKTOP-9ABFSKK MINGW64 ~/Desktop/Nkentseu (main|SPARSE)
$ git log --oneline -- Nkentseu.jenga
addf709d NKCode beta.8 a beta.11 : la ligne publiee rejoint enfin main (#86)
cc41ca45 GemCrush : le jeu complet -- menu, aventure 30 niveaux, 3 modes, audio
synthetise (#84)
849a7e5e NK3DModeler : changer le type de materiau REINITIALISE tout (regle, pas
 liste) -- table de defauts par type, textures videes, plus banc console NKMatTy
peResetTest dont le controle de couverture rend rouge tout champ ajoute sans ent
ree
938fbd7e Merge branch 'feat/nkref'
6f1acdf4 NKEditorKit: theme et rendu de canvas, plus banc NKEditorKitTest
133da0b0 NkUIDesign : la tranche verticale — la declaration est LUE, pas seuleme
nt ecrite (21/21) (#83)
42d65c23 NKGui : completer la bibliotheque -- 4 primitives, 16 jetons, un theme
qui s'enumere, banc temoin 46/46 sans GPU (#81)
1a924a25 NK3DModeler : eclatement des imports, persistance de l origine, mode ob
jet, L (#67)
3bf761d7 NKRenderer : FBX operationnel (squelette, skinning, animations), journa
l introuvable/invalide (#70)
332ae4f8 NK3DModeler : refonte d'interface, import OBJ, selection liee et mode o
bjet (#62)
964b3779 NKAnimation : le substrat d animation quitte le renderer
d9e1f82d NKAnimPhysics : extraire la pose physiquement correcte hors du renderer
570ebf73 NKARDemo : la realite augmentee de bout en bout — camera, marqueur, obj
et ancre
68909d3e NkRef etape 0: canevas infini nu — pan (clic milieu / espace+glisser),
zoom molette CENTRE SOUS LE CURSEUR (NkRefView pur, ancre invariante), grille ad
aptative puissances de 2, axes origine, Home=reset + crochets agent NK_AGENT_SHO
T/EXIT/PAN/ZOOM (memes methodes que la souris) — verifie par captures: zoom ancr
e exact, pan exact, rendu deterministe (hashes identiques)
0702b028 NKXR etage 0 : runtime XR from scratch + simulateur desktop + demo ster
eo
232d0e88 NKAI : Re-Basin sur transformeur -- le flux residuel est le verrou, pas
 les tetes
d1be221c NKAI : bloc transformeur moderne (RMSNorm + RoPE + SwiGLU) -- il sur-ap
prend une sequence
4c4988fc NKAI : Ilyana -- corpus d'identite, tri en trois bacs, tokenizer pre-en
traine
3d62058e NKAI : un BPE qui tient l'echelle -- 16k fusions sur 25 Mo en 1,6 s
a763a97f NKAI : deux reseaux entraines separement, alignes par permutation
7624a19e NKAI : entrainement LoRA reprenable, et dialogue avec le modele affine
3c44a374 feat(nkcode): lecteur PDF + portage Linux (XLib/XCB) + restauration des
 fenetres (#55)
34f8decd NK3DModeler : squelette d'application -- la coquille tourne
89eb9cab Harnais de non-regression de NkEditMesh (prealable a la refonte BMesh)
ca0bca7d feat(editmode): bevel, inset, edge split, spin, dissolve + enregistreme
nt des apps NKAI manquantes
e562239a chore: consolidation des livraisons verifiees 23-25/07
7d33a3f7 feat(nkcode): Jenga in-process via CPython embarque (Phase 12, Windows)
 (#49)
e455ee91 fix: retire l'inclusion accidentelle de WIP d'autres agents dans 91a36e
e4 (Mou.jenga, Nkentseu.jenga, config/modules.jenga, NkTextRenderer.cpp/h, NkDia
logs.cpp) - ce n'etait pas mon travail, le stash 'WIP autres agents' les conserv
e intacts pour la reprise
91a36ee4 docs(nkmedia): ROADMAP a jour - PCM + MP3 embarque dans MP4 (commit 805
e0c93)
ebaf97ed feat(app): NkAudioPlayer - lecteur audio de REFERENCE (patron NKAudio p
ropre, liftable dans NKCode). AudioEngine::Initialize (device WASAPI/CoreAudio/A
LSA via backend AUTO, multi-plateforme) + AudioLoader::Load (WAV/MP3/OGG/FLAC/Op
us) + Play (bus Music) + suivi position/IsPlaying + Shutdown. Le moteur converti
t le taux du fichier vers le device (fix cdba6d5c) -> le lecteur n'a RIEN a fair
e cote resampling. --maxsec pour borner. link avrt (WASAPI).
3f0dad67 feat(nkmedia): NkVideoReader - LECTURE video (NKMedia savait seulement
encoder). Demuxeur AVI + decode MJPEG frame-par-frame via le decodeur JPEG NKIma
ge (+ RGB brut DIB bottom-up). API unifiee Open/Info/ReadFrame->RGBA8/SeekFrame.
 Valide: self-test (ecrit AVI MJPEG via NkVideoWriter -> relit -> verifie) + INT
EROP lit un AVI MJPEG ffmpeg (160x120, 10 frames). App NkVideoReadTest. MOV/MP4-
MJPEG + H264 = iterations suivantes.
fe840d51 feat(nktts): PISTE 2 etape 1 - chargeur LJSpeech operationnel (NKTTSTra
in). Lecteur WAV PCM16 maison + parse metadata.csv (texte<->WAV) + mel-spectrogr
amme 80 bandes via NkAudioFeatures (FFT radix-2). 13100 WAV valides, 5/5 charges
 bout-en-bout (9.66s -> 966 trames x 80). Fondation vers un modele TTS acoustiqu
e appris sur vraie voix.
e76c1f1f feat(nkimage): NkDeflate::Compress - VRAI deflate (LZ77 chaines de hash
 + Huffman FIXE, RFC 1951) au lieu de blocs STORED (aucune compression). PNG pas
se de 787 Ko a 6 Ko (129x) en restant BIT-EXACT (verifie ffmpeg). + NKImageCodec
Test : round-trip de tous les codecs verifie via ffmpeg (PNG/BMP/TGA/QOI/PPM/HDR
 bit-exacts ; GIF/WEBP encode = non implementes)
66e0f2c2 feat(nkai): ASR acoustique from-scratch (Option B.1) - NkASRModel BiGRU
+CTC (header-only NKSpeech) sur MFCC ; NKASRTest bout-en-bout (audio synthetique
 3 tons -> MFCC -> BiGRU -> CTC -> decodage glouton) : perte 51.7->0.01, 4/4 mot
s transcrits ; capitalise sur A.1 (scheduler LR) + A.2 (GRU/CTC)
beb4afb7 feat(nkai): cellules recurrentes GRU/LSTM (NKNN) + perte CTC (NKAutogra
d) - forward-backward log-space gradient-checke (5e-5), op Concat0 pour empiler
le temps ; NKRnnCtcTest entraine GRU+CTC (perte 5.46->0.0003, decodage glouton =
 cible) ; NKAutogradTest 32/32
e03896f0 feat(nknetwork): couche Replication livree (NkNetWorld agnostique ECS :
 snapshots delta+keyframe, spawn/despawn, inputs dedup, NkNetInterpolator) + HTT
PS reel (SendOverTLS mbedTLS opt-in NK_ENABLE_TLS, valide 200 sur example.com) +
 fix wire NkLobbyMessageHeader kSize 12->16 + SandboxNKNetwork (67 checks dont l
oopback 127.0.0.1) ; ROADMAP a jour
889ddda2 feat(nkmedia): creation video from-scratch (SANS ffmpeg) - NkVideoWrite
r + AVI (MJPEG/RAW)
17193a69 feat(nkmedia): harnais validation Opus NKOpusRef - decode clip (demux->
TOC->NkCeltDecoder) vs reference ffmpeg 48k, metriques RMS/correlation. Front-en
d VALIDE : 118080 echantillons = pile ffmpeg (alignement trames exact). Filet po
ur porter quant_all_bands
d6795b5a feat(nkmedia): nouveau module NKMedia - brique 1 NkMediaProbe (demux d'
en-tete ISOBMFF/MP4 + EBML/WebM from-scratch) ; identifie conteneur+codec+params
. Valide sur corpus reel (Bassa->MP4/AAC, ghomala->WebM/Opus). ROADMAP conteneur
s/codecs staged
018df48e feat(nkspeech): NKSpeechFeatureDemo - MFCC sur fichier audio reel (deco
de NKAudio -> features) ; valide la chaine parole->MFCC sur le corpus (Bassa/gho
mala). Note format corpus WebM/MP4 a transcoder
86231d8e feat(nkspeech): brique 1 Phase 8 - NkAudioFeatures MFCC/log-Mel from-sc
ratch (FFT radix-2 + filtres Mel + DCT + deltas), module NKSpeech + NKSpeechTest
 1/1 (sinus 1kHz -> bon canal Mel)
458eea7f feat(nkaudio): NkMicRecord - outil micro->WAV (test reel de NkAudioCapt
ure, WASAPI), enregistre N s en WAV 16-bit PCM
1c65f410 feat(nkanima M3.1): distribution de masse + centre de masse (COM) de po
se
824530f0 refactor(nkai): module NKGpt reutilisable — extraction des briques BPE
+ corpus + checkpoint de NKGptTrain vers Kernel/AI/NKGpt (lib statique, namespac
e nkentseu::ai::gpt) ; main.cpp 649->367 lignes ; utilisable par n'importe quell
e app. Etape 1/2 (NkGptTrainer class = etape 2). Build 25/25 OK, comportement id
entique
1184efbb feat(nkai): NKMeshAITest — etape 1 modelisation par IA (imitation) : Nk
EditMesh->features->MLP predit l'action ; 98.8% sur test (from-scratch, petite e
chelle)
f02ca2f0 chore(songoo): desactive du build (migration NKCanvas a finir) — source
 preservee dans main
b17a1f76 feat(nkai): app NKGptTrain (entrainement GPT) + workspace jenga
54b949da Consolidation travaux parallèles : NKAI (transformer/GPT + entraînement
 GPU-résident), rasterizer Software, NKCode, éditeur maillage (#23)
ba3b0507 feat(editor): editeur de maillage facon Blender + structure n-gon half-
edge (NkEditMesh) (#21)
d4fce7ee feat(render): grille infinie reutilisable + fix ombres GL (glClipContro
l/clipZ01) + fix freeze DX11 (ResizeBuffers/command list) + NkInput cross-platfo
rm + cap FPS/vsync + pool object-UBO dynamique + ombres instanciees ; consolidat
ion WIP multi-modules (NKCode, Noge, ...) (#19)
137eefc4 feat(nkphysics): M0 — integration semi-implicite + boucle Step (gravite
/damping, delegation detection NKCollision, sync shapes) ; NkPhysicsWorld Create
Body/Step + masse/inertie ; module enregistre ; self-test 4/4 (chute libre)
3240b1ae feat(moteur): reconciliation NKRenderer complete + NkAnima (supersede #
14) (#16)
eaaad92b feat(nkcode): IDE NKCode (launcher + outillage) porte sur main (#12)
8f7cde3c feat(integrations): backends ImGui (NKCanvas + NKRHI) + NKUI (NKRHI) de
couples + .jenga externes (#6)
15156667 chore(runtime): audit NKMemory complet + fix portabilite NkHash LP64 (#
5)
f19260db chore: snapshot etat complet — reorg sources NKSL + Nkoung (plateforme
de jeux 2D: toolkit responsive + Laser Puzzle + Labyrinthe) + Kernel/AI & Kernel
/Bare (scaffolds docs) + wiki Foundation + scripts git/.gitattributes
1f26ef96 ﻿Session 2026-05-29 — D-NkImage, Android APK restauré, Harmony compile
bcc7c99d update
d557314e update
52dbc593 update renderer system and pong game
f1e536a5 refactor 001
8737e282 Begin clearing and restructured file
7660304a Bug fixe
9c90ccc4 bug fix
9c49f79f bug fix vulkan opengl dx11 current bug software and dx12
5d90c862 bugfix
f909152c Align Wayland jenga links/tests (renderer/camera/sandbox)
6760d538 update architecture
a41122c3 Restructure workspace: per-project jenga files + NKMath/NKTime/NKStream
/NKMemory/NKRenderer
453f53a8 Rename NKWindow.jenga → Nkentseu.jenga, update workspace name
(END)
```

## La date de création de Nkentseu.jenga

```txt
$ git log 453f53a8
commit 453f53a88109ca3c465008e95f223af580924734
Author: Rihen <rihen.universe@gmail.com>
Date:   Sun Mar 1 14:24:20 2026 +0100

    Rename NKWindow.jenga → Nkentseu.jenga, update workspace name

commit ec594efa884c6288dfdd45336b5b69966a99909d
Author: Rihen <rihen.universe@gmail.com>
Date:   Sun Mar 1 14:21:25 2026 +0100

    Initial commit: Nkentseu framework (renamed from NKWindow workspace)

    - NKPlatform: OS/arch/compiler detection (C++20)
    - NKCore: types, macros, assertions, bits (C++20)
    - NKLogger: async multi-sink logging (C++17)
    - NKWindow: cross-platform windowing + event system (C++17)
    - Sandbox: demo application
```
Le fichier a été créé `Dimanche, le 1 mars 2026` par Rihen.

## Les trois moments où il a le plus changé

### #1

```txt
a41122c3 Restructure workspace: per-project jenga files + NKMath/NKTime/NKStream/NKMemory/NKRenderer
453f53a8 Rename NKWindow.jenga → Nkentseu.jenga, update workspace name
```
Le renommage de NKWindow.jenga pour Nkentseu.jenga au commit `453f53a8`. Et il a été déplacé de `NKMath/NKTime/NKStream/NKMemory/NKRenderer` à la racine même du projet.

### #2

```txt
54b949da Consolidation travaux parallèles : NKAI (transformer/GPT + entraînement GPU-résident), rasterizer Software, NKCode, éditeur maillage (#23)
ba3b0507 feat(editor): editeur de maillage facon Blender + structure n-gon half-edge (NkEditMesh) (#21)
d4fce7ee feat(render): grille infinie reutilisable + fix ombres GL (glClipControl/clipZ01) + fix freeze DX11 (ResizeBuffers/command list) + NkInput cross-platform + cap FPS/vsync + pool object
-UBO dynamique + ombres instanciees ; consolidation WIP multi-modules (NKCode, Noge, ...) (#19)
137eefc4 feat(nkphysics): M0 — integration semi-implicite + boucle Step (gravite/damping, delegation detection NKCollision, sync shapes) ; NkPhysicsWorld CreateBody/Step + masse/inertie ; modu
le enregistre ; self-test 4/4 (chute libre)
3240b1ae feat(moteur): reconciliation NKRenderer complete + NkAnima (supersede #14) (#16)
eaaad92b feat(nkcode): IDE NKCode (launcher + outillage) porte sur main (#12)

```

Ce qui s'est passé : C'est la période d'explosion fonctionnelle du projet. Nkentseu.jenga passe d'un simple chef d'orchestre du moteur graphique à un système massif intégrant :

* L'IDE embarqué (NKCode).
* Les modules d'IA (NKAI, modèles Transformer/GPT).
* L'éditeur de maillage 3D (NKEditMesh).
* Le moteur physique (NKPhysics) et les wrappers de rendu/UI (NKRHI, NKCanvas, ImGui).

### #3

```txt
cc41ca45 GemCrush : le jeu complet -- menu, aventure 30 niveaux, 3 modes, audio synthetise (#84)
849a7e5e NK3DModeler : changer le type de materiau REINITIALISE tout (regle, pas liste) -- table de defauts par type, textures videes, plus banc console NKMatTypeResetTest dont le controle de
couverture rend rouge tout champ ajoute sans entree
```

Ce qui s'est passé : c'est la période du changement du type de matériau et de la configuration de `GemCrush` le jeu complet avec menu, aventure 30 niveaux, 3 modes, audio synthétisé.

## Les raisons de tous ces changements

Les raisons invoquées : Le projet a dépassé le stade du simple moteur de jeu pour devenir une plateforme applicative complète (outils créatifs, IA, suite multimédia). Le fichier Nkentseu.jenga s'est stabilisé à la suite d'un processus rigoureux de Merge Requests/PRs (#49, #55, #83, #86) pour synchroniser le travail distribué des différents agents et modules vers la branche main.