//用XCB来创建和管理基本的X窗口，而用Xlib + GLX来创建OpenGL相关的图形资源
#pragma once
#include "glad/glad_glx.h"
#include "XcbApplication.hpp"

namespace My
{
    class OpenGLApplication : public XcbApplication
    {
    public:
        OpenGLApplication(GfxConfiguration &config)
            : XcbApplication(config){};

        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();

    protected:
        virtual void OnDraw();

    private:
        Display *m_pDisplay;
        GLXContext m_Context;
        GLXDrawable m_Drawable;
    };
}
