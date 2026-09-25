# Les bornes

>**Énoncé :**
Fixez une taille minimale, puis essayez de réduire la fenêtre en dessous. Retirez-la, recommencez, et notez la plus petite taille que le système accepte.

Le code source :

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
    cfg.width = 800;
    cfg.height = 400;          // <-- TAILLE MIN
    cfg.resizable = true;
    cfg.movable = true;
    cfg.closable = true;
    cfg.minimizable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;
    cfg.modal = true;

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

la taille minimale de la fenêtre de sortie ici est de `400px`, de ce fait lorsque j'essaye de diminuer moins que cela il m'est impossible de le faire à moins de 50px.

De même, lorsque j'enlève la taille minimale il m'est impossible de réduire sa hauteur à moins de 50px.

**CONCLUSION :** Le système supporte minimum `50px`, je le sais car j'ai eu à essayer plusieur dimensions et j'ai peu trouver que cette dimensions est la plus petite acceptable.
