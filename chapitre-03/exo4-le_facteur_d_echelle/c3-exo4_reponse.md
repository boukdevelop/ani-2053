# Le facteur d'echelle

> ***Énoncé :***
Affichez côte à côte la taille rendue par la fenêtre, celle rendue par la cible de rendu, et le facteur d'échelle. Si votre écran donne 1, trouvez un écran qui donne autre chose, ou changez le réglage d'échelle du système.

Le code source utilisé :

```cpp
#include <iostream>
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKLogger/NkLog.h"
#include "NKTime/NkTime.h"
#include "NKTime/NkChrono.h"

#include "NKEvent/NkWindowEvent.h"

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]()
                          {
    NkAppData d{};
    d.appName = "MaFenetre";
    return d; })());

int nkmain(const NkEntryState &)
{
    NkWindowConfig cfg;
    cfg.title = "Ma première fenêtre";
    cfg.width = 800;
    cfg.height = 600;

    // les droits de Nkentseu
    cfg.resizable = true;
    cfg.movable = true;
    cfg.closable = true;
    cfg.minimizable = true;
    cfg.maximizable = true;
    cfg.canFullscreen = true;
    cfg.modal = true;

    NkWindow window(cfg);
    if (!window.IsOpen())
    {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    bool running = true;

    float tailleX = 0;
    float tailleY = 0;

    while (running)
    {
        NkEvent *event = nullptr;
        while ((event = NkEvents().PollEvent()) != nullptr)
        {
            // process events
            if (event->Is<NkWindowCloseEvent>())
            {
                running = false;
            }
        }

        if (window.GetSize().x != tailleX || window.GetSize().y != tailleY)
        {
            logger.Info("[mesures] Taille rendue par la fenêtre {0} | DPI {1}", window.GetSize(), window.GetDpiScale());
            logger.Info("[mesures] Taille rendue par la fenêtre {0}x{1} | DPI {2}", window.GetSize().x, window.GetSize().y, window.GetDpiScale());

            tailleX = window.GetSize().x;
            tailleY = window.GetSize().y;
        }
    }

    return 0;
}
```

## Pour une mise à échelle de 100%

Le `DPI = 1` reste identique à lui même quelque soit la modification apportée aux dimensions de la fenêtre. Comme le montre cette sortie :

```bash
PS C:\Users\FRANCK\Desktop\bouk\FirstWindow> jenga r

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

[2026-09-26 06:36:56.733] [INF] [default] [main.cpp:60 in nkmain] -> [mesures] Taille rendue par la fenetre (800, 600) | DPI 1
[2026-09-26 06:36:56.748] [INF] [default] [main.cpp:61 in nkmain] -> [mesures] Taille rendue par la fenetre 800x600 | DPI 1
[2026-09-26 06:37:07.599] [INF] [default] [main.cpp:60 in nkmain] -> [mesures] Taille rendue par la fenetre (811, 600) | DPI 1
[2026-09-26 06:37:07.600] [INF] [default] [main.cpp:61 in nkmain] -> [mesures] Taille rendue par la fenetre 811x600 | DPI 1
[2026-09-26 06:37:10.926] [INF] [default] [main.cpp:60 in nkmain] -> [mesures] Taille rendue par la fenetre (833, 643) | DPI 1
[2026-09-26 06:37:10.927] [INF] [default] [main.cpp:61 in nkmain] -> [mesures] Taille rendue par la fenetre 833x643 | DPI 1

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (25.93s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```

## Pour une mise à l'échelle de 125%

Le DPI ici change pour monter à 1.25, mais le comportement reste le mmême. Il ne change pas et reste à `DPI = 1.25` sauf vers la fin où j'ai encore remis les paramètre d'affichage à 100% pendant que l'application était en cours et il revient à `DPI = 1` comme cela l'est visible ci-dessous :

```bash
PS C:\Users\FRANCK\Desktop\bouk\FirstWindow> jenga r

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

[2026-09-26 06:41:29.699] [INF] [default] [main.cpp:60 in nkmain] -> [mesures] Taille rendue par la fenetre(798, 592) | DPI 1.25
[2026-09-26 06:41:29.706] [INF] [default] [main.cpp:61 in nkmain] -> [mesures] Taille rendue par la fenetre798x592 | DPI 1.25
[2026-09-26 06:41:43.642] [INF] [default] [main.cpp:60 in nkmain] -> [mesures] Taille rendue par la fenetre(805, 592) | DPI 1.25
[2026-09-26 06:41:43.643] [INF] [default] [main.cpp:61 in nkmain] -> [mesures] Taille rendue par la fenetre805x592 | DPI 1.25
[2026-09-26 06:41:45.883] [INF] [default] [main.cpp:60 in nkmain] -> [mesures] Taille rendue par la fenetre(882, 646) | DPI 1.25
[2026-09-26 06:41:45.885] [INF] [default] [main.cpp:61 in nkmain] -> [mesures] Taille rendue par la fenetre882x646 | DPI 1.25
[2026-09-26 06:42:08.727] [INF] [default] [main.cpp:60 in nkmain] -> [mesures] Taille rendue par la fenetre(704, 515) | DPI 1
[2026-09-26 06:42:08.740] [INF] [default] [main.cpp:61 in nkmain] -> [mesures] Taille rendue par la fenetre704x515 | DPI 1

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (86.61s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
```
