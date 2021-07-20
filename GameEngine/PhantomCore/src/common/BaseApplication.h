#pragma once
#include "../interface/IApplication.h"
namespace Phantom
{
    class BaseApplication : implements IApplication
    {
    public:
        BaseApplication(GfxConfiguration &cfg);
        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();
        virtual bool IsQuit();
        inline GfxConfiguration &GfxCfg() { return m_Config; };

    protected:
        virtual void OnDraw(){};
        static bool m_bQuit;
        GfxConfiguration m_Config;

    private:
        BaseApplication(){};
    };

}