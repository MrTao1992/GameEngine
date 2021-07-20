#include "BaseApplication.h"
#include <iostream>
namespace Phantom
{
    BaseApplication::BaseApplication(GfxConfiguration &cfg) : m_Config(cfg)
    {
    }

    int BaseApplication::Initialize()
    {
        int Result = 0;
        std::wcout << m_Config;
        return Result;
    }

    void BaseApplication::Finalize()
    {
    }
    void BaseApplication::Tick()
    {
    }
    bool BaseApplication::IsQuit()
    {
        return m_bQuit;
    }
}