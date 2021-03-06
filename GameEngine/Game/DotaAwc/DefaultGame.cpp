#include "DefaultApplication.h"
#include "GraphicsManager.h"
#include "IApplication.h"
#if defined(OS_MACOS)
#include "CocoaApplication.h"
#else
#include "WindowsApplication.h"
#endif
namespace Phantom
{
    GfxConfiguration config(8, 8, 8, 8, 32, 0, 0, 960, 540, ("Game Engine From Scratch (Windows)"));
#if defined(OS_MACOS)
    IApplication *m_app = static_cast<IApplication *>(new CocoaApplication(config));
#else
    IApplication *m_app = static_cast<IApplication *>(new WindowsApplication(config));
#endif
    GraphicsManager *m_graphicsManager = static_cast<GraphicsManager *>(new GraphicsManager());
}