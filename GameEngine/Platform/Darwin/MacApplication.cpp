#include "BaseApplication.h"
#include "GraphicsManager.h"
namespace Phantom
{
    GfxConfiguration config;
    IApplication *m_app = static_cast<IApplication *>(new BaseApplication(config));
    GraphicsManager *m_graphicsManager = static_cast<GraphicsManager *>(new GraphicsManager());
}