#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKTime/NkClock.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Shapes/NkRectangleShape.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

int nkmain(const NkEntryState&)
{
    NkWindowConfig config;
    config.title = "Square Movement";
    config.width = 800;
    config.height = 600;
    config.bgColor = 0x1E1E28FF;
    config.vsync = true;

    NkWindow window(config);
    if (!window.IsValid())
        return -1;

    NkContextDesc context;
    context.api = NkGraphicsApi::NK_GFX_API_DX11;
    NkRenderWindow target(window, context);
    if (!target.IsValid())
    {
        window.Close();
        return -2;
    }

    NkClock clock;
    auto& events = NkEvents();
    bool running = true;
    float32 squareX = 0.0f;
    NkRectangleShape square{{50.0f, 50.0f}};
    square.SetFillColor({255, 0, 0, 255});

    while (running && window.IsOpen())
    {
        float32 dt = clock.Tick().delta;
        if (dt > 0.1f)
            dt = 1.0f / 60.0f;

        while (NkEvent* event = events.PollEvent())
        {
            if (event->As<NkWindowCloseEvent>())
                running = false;
        }
        if (!running)
            break;

        squareX += 100.0f * dt;
        if (squareX > 800.0f)
            squareX = -50.0f;

        target.Clear({30, 30, 40, 255});
        square.SetPosition({squareX, 275.0f});
        target.Draw(square);
        target.Display();
    }

    window.Close();
    return 0;
}
