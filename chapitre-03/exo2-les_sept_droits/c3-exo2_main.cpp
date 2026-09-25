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
