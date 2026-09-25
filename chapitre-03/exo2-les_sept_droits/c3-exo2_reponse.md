> # Les septs droits

***Énoncé :***
Ouvrez sept fenêtres successives, chacune avec un seul des sept droits désactivé. Notez ce que l'utilisateur ne peut plus faire dans chaque cas.
--

Les **7 droits** de Nkentseu sont :

- resizable;
- movable;
- closable;
- minimizable;
- maximizable;
- canFullscreen;
- modal;

---

La structure qui sera adopté tout au long de cette exercice, et c'est dans cette structure que sera soustrait à chaque fois des droits :

```cpp
#include <iostream>
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKLogger/NkLog.h"
#include "NKTime/NkTime.h"
#include "NKTime/NkChrono.h"

#include "NKEvent/NkWindowEvent.h"

NKENTSEU_DEFINE_APP_DATA(([]()
                          {
    nkentseu::NkAppData d{};
    d.appName = "Boukala";
    d.appVersion = "1.0.0";
    return d; })());

int nkmain(const nkentseu::NkEntryState &state)
{
    nkentseu::NkWindowConfig cfg;
    cfg.title = "Ma fenetre";
    cfg.width = 1280;
    cfg.height = 720;
    cfg.resizable = true;           // A partir d'ici
    cfg.movable = true;
    cfg.closable = true;
    cfg.minimizable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;
    cfg.modal = true;               // Jusqu'ici

    nkentseu::NkWindow window(cfg);
    if (!window.IsOpen())
    {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    bool running = true;

    while (running)
    {
        nkentseu::NkEvent *event = nullptr;
        while ((event = nkentseu::NkEvents().PollEvent()) != nullptr)
        {
            // Process events
            if (event->Is<nkentseu::NkWindowCloseEvent>())
            {
                running = false;
            }
        }
    }
    return 0;
}
```

## A. `resizable`

Lorsque j'enlève le droit au redimensionnement, normalement l'utilisateur ne devrait plus avoi rla possibilité de redimensionner la fenêtre. Mais à ma grande surprise il n'y a aucune différence entre `cfg.resizable = true` et `cfg.resizable = false`.

## B. `movable`

## C. ``closable``

## D. `minimizable`

## E. `maximizable`

## F. `canFullscreen`

## G. `modal`

Je ne sais pas pourquoi, mais aucun de toutes ces interdictions ne fionctionnent, car si j'enlève `movable` ou `modal` ou encore `canFullscreen`, rien de différent ne se passe. C'était comme si je n'avais ajouté ces configurations.

***NB :*** Le code ci-dessous est le code utilisé pour tous les test de cette exercice.