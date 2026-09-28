# L'inventaire des écrans

> ***Énoncé :***
Écrivez un programme qui affiche, pour chaque écran branché : sa taille, sa position, son facteur d'échelle, et lequel porte votre fenêtre. Déplacez la fenêtre d'un écran à l'autre et vérifiez que les valeurs suivent.

Le code source extrêment commentés pour fournir de meilleurs explications directement via le code :

```cpp
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKLogger/NkLog.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkSystemEvent.h"

using namespace nkentseu;

// Fonction qui affiche l'inventaire des écrans dans le journal.
static void AfficherInventaireEcrans(NkWindow &window)
{
    // Écran que NKWindow associe au moment où on lance la fenêtre.
    const NkDisplayInfo ecranCourant = window.GetCurrentMonitor();

    // Récupère la liste des écrans détectées par le système.
    const auto ecrans = window.EnumerateMonitors();

    // Affiche le nombre d'écrans trouvées.
    logger.Info("---- Ecrans detectes : {0} ----", ecrans.Size());

    // Parcourt chaque écran de la liste.
    for (usize i = 0; i < ecrans.Size(); ++i)
    {
        // Référence aux informations de l'écran courant de la boucle.
        const NkDisplayInfo &ecran = ecrans[i];

        // Ajoute une marque si cet écran porte la fenêtre.
        const char *marqueur =
            ecran.index == ecranCourant.index ? " [FENETRE ICI]" : "";

        // Affiche ses propriétés. La résolution logique tient compte du DPI ;
        // la résolution physique indique le nombre réel de pixels.
        logger.Info(
            "Ecran {0}{1} : {2} | logique {3}x{4} | physique {5}x{6} "
            "| position ({7}, {8}) | echelle x{9:.2f} | primaire={10}",
            ecran.index,
            marqueur,
            ecran.name,
            ecran.width,
            ecran.height,
            ecran.physWidth,
            ecran.physHeight,
            ecran.posX,
            ecran.posY,
            ecran.dpiScale,
            ecran.isPrimary ? "oui" : "non");
    }

    // Affiche le facteur DPI propre à la fenêtre.
    logger.Info("Facteur DPI de la fenetre : x{0:.2f}", window.GetDpiScale());
}

// Déclare les métadonnées de l'application.
NKENTSEU_DEFINE_APP_DATA(([]()
                          {
    NkAppData data{};
    data.appName = "Inventaire des ecrans";
    return data; })());

int nkmain(const NkEntryState &)
{
    NkWindowConfig config;
    config.title = "Inventaire des ecrans";
    config.width = 800;
    config.height = 600;
    config.centered = true;

    // Crée la fenêtre native.
    NkWindow window(config);

    // Arrête le programme avec une erreur si la fenêtre n'a pas été créée.
    if (!window.IsOpen())
    {
        logger.Error("[app] creation de la fenetre echouee");
        return -1;
    }

    // Affiche la liste des écrans dès le lancement.
    AfficherInventaireEcrans(window);

    // Mémorise l'écran et le DPI de départ pour repérer les changements.
    uint32 dernierEcran = window.GetCurrentMonitor().index;
    float32 dernierDpi = window.GetDpiScale();

    // Contrôle la boucle de vie de la fenêtre.
    bool running = true;

    // Continue tant que le programme tourne et que la fenêtre est ouverte.
    while (running && window.IsOpen())
    {
        while (NkEvent *event = NkEvents().PollEvent())
        {
            if (event->Is<NkWindowCloseEvent>())
            {
                running = false;
            }

            // Après un déplacement, vérifie si la fenêtre a changé d'écran ou de DPI.
            if (event->Is<NkWindowMoveEvent>())
            {
                const uint32 ecran = window.GetCurrentMonitor().index;
                const float32 dpi = window.GetDpiScale();

                // N'affiche à nouveau l'inventaire que si l'écran ou le DPI a changé.
                if (ecran != dernierEcran || dpi != dernierDpi)
                {
                    dernierEcran = ecran;
                    dernierDpi = dpi;
                    AfficherInventaireEcrans(window);
                }
            }

            // Réagit aussi aux changements d'échelle ou de configuration des écrans.
            if (event->Is<NkWindowDpiEvent>() ||
                event->Is<NkSystemDisplayEvent>())
            {
                dernierEcran = window.GetCurrentMonitor().index;
                dernierDpi = window.GetDpiScale();
                AfficherInventaireEcrans(window);
            }
        }
    }

    return 0;
}
```

Afin de simuler des écrans, je vais juste changer la résolution de mon écrans de travail afin de voir les différentes modifcations apportées.

```bash
PS C:\Users\FRANCK\Desktop\bouk\FirstWindow> jenga run

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

[2026-09-28 03:06:36.913] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:06:36.920] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1366x768 | physique 1366x768 | position (0, 0) | echelle x1.00 | primaire=oui
[2026-09-28 03:06:36.924] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.00
[2026-09-28 03:07:02.978] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:07:02.982] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1280x720 | physique 1280x720 | position (0, 0) | echelle x1.00 | primaire=oui
[2026-09-28 03:07:02.985] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.00
[2026-09-28 03:07:39.117] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:07:39.121] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1366x768 | physique 1366x768 | position (0, 0) | echelle x1.00 | primaire=oui
[2026-09-28 03:07:39.121] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.00
[2026-09-28 03:07:53.430] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:07:53.432] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1366x768 | physique 1366x768 | position (0, 0) | echelle x1.25 | primaire=oui
[2026-09-28 03:07:53.444] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.25
[2026-09-28 03:07:53.449] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:07:53.464] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1366x768 | physique 1366x768 | position (0, 0) | echelle x1.25 | primaire=oui
[2026-09-28 03:07:53.464] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.25
[2026-09-28 03:08:22.488] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:08:22.760] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1366x768 | physique 1366x768 | position (0, 0) | echelle x1.00 | primaire=oui
[2026-09-28 03:08:22.773] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.00
[2026-09-28 03:08:23.010] [INF] [default] [main.cpp:19 in AfficherInventaireEcrans] -> ---- Ecrans detectes : 1 ----
[2026-09-28 03:08:23.011] [INF] [default] [main.cpp:33 in AfficherInventaireEcrans] -> Ecran 0 [FENETRE ICI] : \\.\DISPLAY1 | logique 1366x768 | physique 1366x768 | position (0, 0) | echelle x1.00 | primaire=oui
[2026-09-28 03:08:23.011] [INF] [default] [main.cpp:50 in AfficherInventaireEcrans] -> Facteur DPI de la fenetre : x1.00

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (118.57s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\Users\FRANCK\Desktop\bouk\FirstWindow> 
```

---

On voit très clairement tous les changements qui ont été apportés rien qu'en changeant la résolution et le DPI de l'ordinateur.