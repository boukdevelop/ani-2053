#include "NKWindow/NKMain.h"
#include "NKCanvas/App/NkCanvasApp.h"

class FenetreNue : public nkentseu::renderer::NkCanvasApp
{
public:
    FenetreNue()
    {
        Config().title = "Fentre Nue";
        Config().width = 800;
        Config().height = 600;
        Config().clearColor = {18, 18, 24, 255};
    }
};

int nkmain(const nkentseu::NkEntryState &state)
{
    return nkentseu::renderer::NkCanvasApp::Run<FenetreNue>(state);
}