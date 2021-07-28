#include <stdio.h>
#include "GraphicsManager.h"
#include "IApplication.h"
using namespace Phantom;
namespace Phantom
{
    extern IApplication *m_app;
    extern GraphicsManager *m_graphicsManager;
}

int main(int argc, char **argv)
{
    int ret;
    if (ret = m_app->Initialize() != 0)
    {
        printf("App Initialize failed, will exit now.");
        return ret;
    }
    m_app->CreateMainWindow();
    if (ret = m_graphicsManager->Initialize() != 0)
    {
        printf("GraphicsManager Initialize failed, will exit now.");
        return ret;
    }

    while (!m_app->IsQuit())
    {
        m_app->Tick();
        m_graphicsManager->Tick();
    }

    m_app->Finalize();
    m_graphicsManager->Finalize();

    return 0;
}