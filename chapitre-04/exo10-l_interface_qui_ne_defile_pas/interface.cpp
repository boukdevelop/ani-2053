#include "NKWindow/NKMain.h"
#include "NKWindow/NKWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkEventSystem.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKTime/NkClock.h"
#include "NKLogger/NkLog.h"
#include "NKCanvas/Core/NkContextDesc.h"
#include "NKCanvas/Core/NkGraphicsApi.h"
#include "NKCanvas/Renderer/Targets/NkRenderWindow.h"
#include "NKCanvas/Renderer/Shapes/NkRectangleShape.h"
#include "NKCanvas/Renderer/Resources/NkSprite.h"
#include "NKFont/Embedded/NkFontEmbedded.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

int nkmain(const NkEntryState &state)
{
    constexpr uint32 kWidth = 800;
    constexpr uint32 kHeight = 600;
    constexpr float32 kScrollSpeed = 100.0f;
    constexpr float32 kCaptureSeconds = 5.0f;

    bool resetView = true;
    for (usize i = 0; i < state.args.Size(); ++i)
    {
        if (state.args[i] == "--sans-reset")
            resetView = false;
    }

    NkWindowConfig config;
    config.title = "NkCanvas - interface fixe";
    config.width = kWidth;
    config.height = kHeight;
    config.resizable = false;
    config.vsync = true;

    NkWindow window(config);
    if (!window.IsValid())
        return -1;

    NkContextDesc context;
    context.api = NkGraphicsApi::NK_GFX_API_DX11;
    context.dx11.vsync = true;
    NkRenderWindow target(window, context);
    if (!target.IsValid())
    {
        window.Close();
        return -2;
    }

    nkentseu::renderer::NkFont font;
    if (!font.LoadEmbedded(*target.GetRenderer(), NkEmbeddedFontId::DroidSans))
    {
        logger.Error("[interface] impossible de charger la police integree");
        window.Close();
        return -3;
    }

    NkText label(font, "INTERFACE FIXE  |  Monde defilant", 22);
    label.SetPosition({24.0f, 46.0f});
    label.SetFillColor({245, 247, 255, 255});

    NkClock clock;
    auto &events = NkEvents();
    bool running = true;
    bool captured = false;
    float32 centerX = kWidth / 2.0f;

    NkView2D worldView;
    worldView.center = {centerX, kHeight / 2.0f};
    worldView.size = {static_cast<float32>(kWidth), static_cast<float32>(kHeight)};

    NkRectangleShape tile{{84.0f, 84.0f}};
    tile.SetFillColor({52, 111, 173, 255});
    NkRectangleShape bar{{static_cast<float32>(kWidth), 72.0f}};
    bar.SetFillColor({24, 31, 47, 255});
    NkRectangleShape underline{{static_cast<float32>(kWidth), 3.0f}};
    underline.SetFillColor({71, 204, 190, 255});

    const char *capturePath = resetView ? "avec.png" : "sans.png";
    logger.Infof("[interface] mode=%s, capture dans %.0f secondes: %s",
                 resetView ? "avec ResetView" : "sans ResetView",
                 kCaptureSeconds, capturePath);

    while (running && window.IsOpen())
    {
        float32 dt = clock.Tick().delta;
        if (dt > 0.1f)
            dt = 1.0f / 60.0f;

        while (NkEvent *event = events.PollEvent())
        {
            if (event->As<NkWindowCloseEvent>())
                running = false;
        }
        if (!running)
            break;

        centerX += kScrollSpeed * dt;
        worldView.center.x = centerX;

        target.Clear({18, 22, 32, 255});
        target.SetView(worldView);

        for (int32 i = -2; i <= 16; ++i)
        {
            tile.SetPosition({static_cast<float32>(i) * 180.0f, 258.0f});
            target.Draw(tile);
        }

        if (resetView)
        {
            target.ResetView();
        }

        bar.SetPosition({0.0f, 0.0f});
        underline.SetPosition({0.0f, 72.0f});
        target.Draw(bar);
        target.Draw(underline);
        target.Draw(label);
        target.Display();

        if (!captured && clock.GetTime().total >= kCaptureSeconds)
        {
            if (!target.Capture(capturePath))
            {
                logger.Error("[interface] echec de capture: %s", capturePath);
                window.Close();
                return -4;
            }
            captured = true;
            logger.Infof("[interface] capture reussie: %s", capturePath);
        }
    }

    window.Close();
    return 0;
}
