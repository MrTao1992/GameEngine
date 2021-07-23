#pragma once
#include <windows.h>
#include <windowsx.h>
#include "BaseApplication.h"
#include "GraphicsManager.h"

namespace Phantom
{
    class WindowsApplication : public BaseApplication
    {
    public:
        WindowsApplication(GfxConfiguration &config)
            : BaseApplication(config){};

        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick();

        inline HWND GetMainWindow() const { return m_hWnd; };

    private:
        // 　　hwnd：指向窗口的句柄。
        // 　　uMsg：指定消息类型。
        // 　　wParam：指定其余的、消息特定的信息。该参数的内容与UMsg参数值有关。
        // 　　IParam：指定其余的、消息特定的信息。该参数的内容与uMsg参数值有关。
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM IParam);

    private:
        HWND m_hWnd;
    };

}
