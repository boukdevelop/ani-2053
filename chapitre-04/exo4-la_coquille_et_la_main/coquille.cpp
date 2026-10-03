#include "NKWindow/NKMain.h"
#include "NKCanvas/App/NkCanvasApp.h"
#include "NKCanvas/Renderer/Shapes/NkRectangleShape.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

class SquareApp : public NkCanvasApp
{
private:
    float32 mSquareX = 0.0f;
    NkRectangleShape mSquare{{50.0f, 50.0f}};

public:
    SquareApp()
    {
        Config().title = "Square Movement";
        Config().width = 800;
        Config().height = 600;
        Config().clearColor = {30, 30, 40, 255};

        mSquare.SetFillColor({255, 0, 0, 255});
    }

protected:
    void OnUpdate(float32 deltaTime) override
    {
        mSquareX += 100.0f * deltaTime;

        if (mSquareX > 800.0f)
            mSquareX = -50.0f;
    }

    void OnRender(NkRenderWindow& window) override
    {
        mSquare.SetPosition({mSquareX, 275.0f});
        window.Draw(mSquare);
    }
};

int nkmain(const NkEntryState& state)
{
    return NkCanvasApp::Run<SquareApp>(state);
}