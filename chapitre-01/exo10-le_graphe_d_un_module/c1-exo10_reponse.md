# Le graphe d'un module

**Énoncé :**
Prenez NKCanvas. Ouvrez son .jenga, relevez ses dépendances directes, puis celles de ses dépendances. Arrêtez-vous à deux niveaux et dessinez le graphe. Combien de projets faut-il construire avant lui ?

### Les dépeandances directes de **NKCanvas** sont contenu dans `_canvasDeps`, à savoir :

* NKWindow;
* NKFont;
* NKImage;
* NKStream;
* NKTime;
* NKGlad;
* NKThreading;

Il faut construire `7 projets` à construire avant *NKCanvas*.

### Les dépenadances de **NKWindow** :
* NKPlatform;
* NKCore;
* NKLogger;
* NKMath;
* NKTime;
* NKContainers;
* NKMemory;
* NKThreading;
* NKEvent;
* NKFileSystem;

### Les dépendances de **NKFont** :
* NKPlatform;
* NKCore;
* NKMemory;
* NKMath;
* NKContainers;
* NKThreading;
* NKLogger;

## Arborescence

```txt
NKCanvas
├── NKWindow
│   ├── NKPlatform
│   ├── NKCore
│   ├── NKLogger
│   ├── NKMath
│   ├── NKTime
│   ├── NKContainers
│   ├── NKMemory
│   ├── NKThreading
│   ├── NKEvent
│   └── NKFileSystem
└── NKFont
    ├── NKPlatform
    ├── NKCore
    ├── NKMemory
    ├── NKMath
    ├── NKContainers
    ├── NKThreading
    └── NKLoggers
```