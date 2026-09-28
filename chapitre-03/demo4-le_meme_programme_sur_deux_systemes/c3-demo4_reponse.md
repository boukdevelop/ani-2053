# Le même programme sur deux systèmes

> ***Énoncé :***
Faites tourner le même binaire, ou la même source recompilée, sur deux systèmes différents. Relevez tout ce qui change sans que vous ayez rien écrit pour cela.

Afind de mener à bien cette exercice, j'utiliserai le code qui a servie à l'exercice 8 [le presse-papier](exo8-le_presse_papiers_dans_les_deux_sens/c3-exo8_reponse.md). Ce projet sera lancer respectivement sur `Windows` et sur `Zorin OS` un système de la **suite Debian**.

## Sur Windows

```bash
PS C:\Users\FRANCK\Desktop\bouk\FirstWindow> jenga c

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

Removed C:\Users\FRANCK\Desktop\bouk\FirstWindow\Build\Obj\Debug-Windows\Window\src_main.obj
Removed C:\Users\FRANCK\Desktop\bouk\FirstWindow\Build\Bin\Debug-Windows\Window\Window.exe
PS C:\Users\FRANCK\Desktop\bouk\FirstWindow> jenga b

╔══════════════════════════════════════════════════════════════════╗
║                                                                  ║
║                ██╗███████╗███╗   ██╗ ██████╗  █████╗             ║
║                ██║██╔════╝████╗  ██║██╔════╝ ██╔══██╗            ║
║                ██║█████╗  ██╔██╗ ██║██║  ███╗███████║            ║
║           ██   ██║██╔══╝  ██║╚██╗██║██║   ██║██╔══██║            ║
║           ╚█████╔╝███████╗██║ ╚████║╚██████╔╝██║  ██║            ║
║            ╚════╝ ╚══════╝╚═╝  ╚═══╝ ╚═════╝ ╚═╝  ╚═╝            ║
║                                                                  ║
║                                                                  ║
╚══════════════════════════════════════════════════════════════════╝

Loading workspace...

Configuration: Debug
Target:        Windows x86_64
Toolchain:     clang-mingw

Build Order (1 projects):
  1. Window [CONSOLE_APP]


╔══════════════════════════════════════════════════════════════════════════════════════════════╗
║  Project: Window                                                          Kind: CONSOLE_APP  ║
╚══════════════════════════════════════════════════════════════════════════════════════════════╝

ℹ Found 1 source file(s)
✓   [1/1] Compiled: main.cpp
ℹ Linking...
✓ Built: Build\Bin\Debug-Windows\Window\Window.exe

┌──────────────────────────────────────────────────────────────────────────────────────────────┐
│  ✓ Build Successful                                                            Time: 2m7.7s  │
└──────────────────────────────────────────────────────────────────────────────────────────────┘

════════════════════════════════════════════════════════════════════════════════
                                BUILD COMPLETED                                 
════════════════════════════════════════════════════════════════════════════════
Projects Built:  1/1
Time:           2m7.7s
Status:         ✓ SUCCESS
════════════════════════════════════════════════════════════════════════════════

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

[2026-09-28 02:28:42.264] [INF] [default] [main.cpp:37 in nkmain] -> [texte avant]
#include "NKWindow/NKWindow.h"
#include "NKWindow/NKMain.h"
#include "NKLogger/NkLog.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkMouseEvent.h"

using namespace nkentseu;

NKENTSEU_DEFINE_APP_DATA(([]()
                          {
    NkAppData data{};
    data.appName = "KDs Presse-Papper";
    data.appVersion = "1.0.0";
    return data; })());

int nkmain(const NkEntryState &)
{
    NkWindowConfig cfg;
    cfg.title = "KDs Presse-Papper";
    cfg.width = 800;
    cfg.height = 600;

    NkWindow window(cfg);
    if (!window.IsOpen())
    {
        logger.Error("[app] creation fenetre echouee");
        return -1;
    }

    // Lire et garder les deux contenus avant de modifier le presse-papiers.
    NkString texteAvant = window.GetClipboardText();

    NkClipboardImage image;
    const bool imageLue = window.GetClipboardImage(image);
    bool running = true;

    logger.Info("[texte avant]\n{0}", texteAvant.CStr());

    if (imageLue && image.IsValid())
    {
        logger.Info("[image avant] {0}x{1}",
                    image.width, image.height);
    }
    else
    {
        logger.Info("[image avant] aucune image lisible");
    }

    // Transformer le texte puis verifier immediatement ce que NkWindow relit.
    NkString texteMajuscule = texteAvant;
    texteMajuscule.ToUpper(); // Conversion ASCII.
    window.SetClipboardText(texteMajuscule);

    const NkString texteApres = window.GetClipboardText();
    logger.Info("[texte apres ecriture]\n{0}", texteApres.CStr());

    if (imageLue && image.IsValid())
    {
        // RGBA8 : inverser R, G et B, sans modifier A (l'alpha).
        for (usize i = 0; i < image.pixels.Size(); i += 4)
        {
            image.pixels[i] = static_cast<uint8>(255u - image.pixels[i]);
            image.pixels[i + 1] = static_cast<uint8>(255u - image.pixels[i + 1]);
            image.pixels[i + 2] = static_cast<uint8>(255u - image.pixels[i + 2]);
        }

        if (window.SetClipboardImage(image))
        {
            NkClipboardImage imageApres;

            if (window.GetClipboardImage(imageApres) && imageApres.IsValid())
            {
                logger.Info("[image apres ecriture] {0}x{1}",
                            imageApres.width, imageApres.height);
            }
            else
            {
                logger.Error("[image apres ecriture] impossible de relire l'image");
            }
        }
        else
        {
            logger.Error("[image] echec de l'ecriture dans le presse-papiers");
        }
    }

    // Verifier si le texte est encore present apres l'ecriture de l'image
    const NkString texteFinal = window.GetClipboardText();
    logger.Info("[texte final apres ecriture image]\n{0}", texteFinal.CStr());

    while (running)
    {
        NkEvent *event = nullptr;
        while ((event = NkEvents().PollEvent()) != nullptr)
        {
            if (event->Is<NkWindowCloseEvent>())
            {
                running = false;
            }
        }
    }

    return 0;
}
[2026-09-28 02:28:42.265] [INF] [default] [main.cpp:46 in nkmain] -> [image avant] aucune image lisible
[2026-09-28 02:28:42.268] [INF] [default] [main.cpp:55 in nkmain] -> [texte apres ecriture]
#INCLUDE "NKWINDOW/NKWINDOW.H"
#INCLUDE "NKWINDOW/NKMAIN.H"
#INCLUDE "NKLOGGER/NKLOG.H"
#INCLUDE "NKEVENT/NKWINDOWEVENT.H"
#INCLUDE "NKEVENT/NKMOUSEEVENT.H"

USING NAMESPACE NKENTSEU;

NKENTSEU_DEFINE_APP_DATA(([]()
                          {
    NKAPPDATA DATA{};
    DATA.APPNAME = "KDS PRESSE-PAPPER";
    DATA.APPVERSION = "1.0.0";
    RETURN DATA; })());

INT NKMAIN(CONST NKENTRYSTATE &)
{
    NKWINDOWCONFIG CFG;
    CFG.TITLE = "KDS PRESSE-PAPPER";
    CFG.WIDTH = 800;
    CFG.HEIGHT = 600;

    NKWINDOW WINDOW(CFG);
    IF (!WINDOW.ISOPEN())
    {
        LOGGER.ERROR("[APP] CREATION FENETRE ECHOUEE");
        RETURN -1;
    }

    // LIRE ET GARDER LES DEUX CONTENUS AVANT DE MODIFIER LE PRESSE-PAPIERS.
    NKSTRING TEXTEAVANT = WINDOW.GETCLIPBOARDTEXT();

    NKCLIPBOARDIMAGE IMAGE;
    CONST BOOL IMAGELUE = WINDOW.GETCLIPBOARDIMAGE(IMAGE);
    BOOL RUNNING = TRUE;

    LOGGER.INFO("[TEXTE AVANT]\N{0}", TEXTEAVANT.CSTR());

    IF (IMAGELUE && IMAGE.ISVALID())
    {
        LOGGER.INFO("[IMAGE AVANT] {0}X{1}",
                    IMAGE.WIDTH, IMAGE.HEIGHT);
    }
    ELSE
    {
        LOGGER.INFO("[IMAGE AVANT] AUCUNE IMAGE LISIBLE");
    }

    // TRANSFORMER LE TEXTE PUIS VeRIFIER IMMeDIATEMENT CE QUE NKWINDOW RELIT.
    NKSTRING TEXTEMAJUSCULE = TEXTEAVANT;
    TEXTEMAJUSCULE.TOUPPER(); // CONVERSION ASCII.
    WINDOW.SETCLIPBOARDTEXT(TEXTEMAJUSCULE);

    CONST NKSTRING TEXTEAPRES = WINDOW.GETCLIPBOARDTEXT();
    LOGGER.INFO("[TEXTE APRES ECRITURE]\N{0}", TEXTEAPRES.CSTR());

    IF (IMAGELUE && IMAGE.ISVALID())
    {
        // RGBA8 : INVERSER R, G ET B, SANS MODIFIER A (L'ALPHA).
        FOR (USIZE I = 0; I < IMAGE.PIXELS.SIZE(); I += 4)
        {
            IMAGE.PIXELS[I] = STATIC_CAST<UINT8>(255U - IMAGE.PIXELS[I]);
            IMAGE.PIXELS[I + 1] = STATIC_CAST<UINT8>(255U - IMAGE.PIXELS[I + 1]);
            IMAGE.PIXELS[I + 2] = STATIC_CAST<UINT8>(255U - IMAGE.PIXELS[I + 2]);
        }

        IF (WINDOW.SETCLIPBOARDIMAGE(IMAGE))
        {
            NKCLIPBOARDIMAGE IMAGEAPRES;

            IF (WINDOW.GETCLIPBOARDIMAGE(IMAGEAPRES) && IMAGEAPRES.ISVALID())
            {
                LOGGER.INFO("[IMAGE APRES ECRITURE] {0}X{1}",
                            IMAGEAPRES.WIDTH, IMAGEAPRES.HEIGHT);
            }
            ELSE
            {
                LOGGER.ERROR("[IMAGE APRES ECRITURE] IMPOSSIBLE DE RELIRE L'IMAGE");
            }
        }
        ELSE
        {
            LOGGER.ERROR("[IMAGE] ECHEC DE L'ECRITURE DANS LE PRESSE-PAPIERS");
        }
    }

    // VeRIFIER SI LE TEXTE EST ENCORE PReSENT APReS L'eCRITURE DE L'IMAGE
    CONST NKSTRING TEXTEFINAL = WINDOW.GETCLIPBOARDTEXT();
    LOGGER.INFO("[TEXTE FINAL APRES ECRITURE IMAGE]\N{0}", TEXTEFINAL.CSTR());

    WHILE (RUNNING)
    {
        NKEVENT *EVENT = NULLPTR;
        WHILE ((EVENT = NKEVENTS().POLLEVENT()) != NULLPTR)
        {
            IF (EVENT->IS<NKWINDOWCLOSEEVENT>())
            {
                RUNNING = FALSE;
            }
        }
    }

    RETURN 0;
}
[2026-09-28 02:28:42.269] [INF] [default] [main.cpp:89 in nkmain] -> [texte final apres ecriture image]
#INCLUDE "NKWINDOW/NKWINDOW.H"
#INCLUDE "NKWINDOW/NKMAIN.H"
#INCLUDE "NKLOGGER/NKLOG.H"
#INCLUDE "NKEVENT/NKWINDOWEVENT.H"
#INCLUDE "NKEVENT/NKMOUSEEVENT.H"

USING NAMESPACE NKENTSEU;

NKENTSEU_DEFINE_APP_DATA(([]()
                          {
    NKAPPDATA DATA{};
    DATA.APPNAME = "KDS PRESSE-PAPPER";
    DATA.APPVERSION = "1.0.0";
    RETURN DATA; })());

INT NKMAIN(CONST NKENTRYSTATE &)
{
    NKWINDOWCONFIG CFG;
    CFG.TITLE = "KDS PRESSE-PAPPER";
    CFG.WIDTH = 800;
    CFG.HEIGHT = 600;

    NKWINDOW WINDOW(CFG);
    IF (!WINDOW.ISOPEN())
    {
        LOGGER.ERROR("[APP] CREATION FENETRE ECHOUEE");
        RETURN -1;
    }

    // LIRE ET GARDER LES DEUX CONTENUS AVANT DE MODIFIER LE PRESSE-PAPIERS.
    NKSTRING TEXTEAVANT = WINDOW.GETCLIPBOARDTEXT();

    NKCLIPBOARDIMAGE IMAGE;
    CONST BOOL IMAGELUE = WINDOW.GETCLIPBOARDIMAGE(IMAGE);
    BOOL RUNNING = TRUE;

    LOGGER.INFO("[TEXTE AVANT]\N{0}", TEXTEAVANT.CSTR());

    IF (IMAGELUE && IMAGE.ISVALID())
    {
        LOGGER.INFO("[IMAGE AVANT] {0}X{1}",
                    IMAGE.WIDTH, IMAGE.HEIGHT);
    }
    ELSE
    {
        LOGGER.INFO("[IMAGE AVANT] AUCUNE IMAGE LISIBLE");
    }

    // TRANSFORMER LE TEXTE PUIS VeRIFIER IMMeDIATEMENT CE QUE NKWINDOW RELIT.
    NKSTRING TEXTEMAJUSCULE = TEXTEAVANT;
    TEXTEMAJUSCULE.TOUPPER(); // CONVERSION ASCII.
    WINDOW.SETCLIPBOARDTEXT(TEXTEMAJUSCULE);

    CONST NKSTRING TEXTEAPRES = WINDOW.GETCLIPBOARDTEXT();
    LOGGER.INFO("[TEXTE APRES ECRITURE]\N{0}", TEXTEAPRES.CSTR());

    IF (IMAGELUE && IMAGE.ISVALID())
    {
        // RGBA8 : INVERSER R, G ET B, SANS MODIFIER A (L'ALPHA).
        FOR (USIZE I = 0; I < IMAGE.PIXELS.SIZE(); I += 4)
        {
            IMAGE.PIXELS[I] = STATIC_CAST<UINT8>(255U - IMAGE.PIXELS[I]);
            IMAGE.PIXELS[I + 1] = STATIC_CAST<UINT8>(255U - IMAGE.PIXELS[I + 1]);
            IMAGE.PIXELS[I + 2] = STATIC_CAST<UINT8>(255U - IMAGE.PIXELS[I + 2]);
        }

        IF (WINDOW.SETCLIPBOARDIMAGE(IMAGE))
        {
            NKCLIPBOARDIMAGE IMAGEAPRES;

            IF (WINDOW.GETCLIPBOARDIMAGE(IMAGEAPRES) && IMAGEAPRES.ISVALID())
            {
                LOGGER.INFO("[IMAGE APRES ECRITURE] {0}X{1}",
                            IMAGEAPRES.WIDTH, IMAGEAPRES.HEIGHT);
            }
            ELSE
            {
                LOGGER.ERROR("[IMAGE APRES ECRITURE] IMPOSSIBLE DE RELIRE L'IMAGE");
            }
        }
        ELSE
        {
            LOGGER.ERROR("[IMAGE] ECHEC DE L'ECRITURE DANS LE PRESSE-PAPIERS");
        }
    }

    // VeRIFIER SI LE TEXTE EST ENCORE PReSENT APReS L'eCRITURE DE L'IMAGE
    CONST NKSTRING TEXTEFINAL = WINDOW.GETCLIPBOARDTEXT();
    LOGGER.INFO("[TEXTE FINAL APRES ECRITURE IMAGE]\N{0}", TEXTEFINAL.CSTR());

    WHILE (RUNNING)
    {
        NKEVENT *EVENT = NULLPTR;
        WHILE ((EVENT = NKEVENTS().POLLEVENT()) != NULLPTR)
        {
            IF (EVENT->IS<NKWINDOWCLOSEEVENT>())
            {
                RUNNING = FALSE;
            }
        }
    }

    RETURN 0;
}

━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
  ◀  FIN D'EXECUTION  —  termine normalement  (12.03s)
━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
PS C:\Users\FRANCK\Desktop\bouk\FirstWindow> 
```

