#include "src/common/BaseApplication.h"
namespace Phantom
{
    GfxConfiguration config;
    IApplication *m_app = static_cast<IApplication *>(new BaseApplication(config));
}