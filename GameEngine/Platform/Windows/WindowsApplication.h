#pragma once
#include <windows.h>
#include <windowsx.h>
#include "BaseApplication.h"

namespace Phantom
{
    class WindowsApplication : public BaseApplication
    {
    public:
        using BaseApplication::BaseApplication;
        void Finalize() override;
        void Tick() override;

        void *GetMainWindowHandler() override { return m_hWnd; };
        void CreateMainWindow() override;

    private:
        // 　　hwnd：指向窗口的句柄。
        // 　　uMsg：指定消息类型。
        // 　　wParam：指定其余的、消息特定的信息。该参数的内容与UMsg参数值有关。
        // 　　IParam：指定其余的、消息特定的信息。该参数的内容与uMsg参数值有关。
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM IParam);

    private:
        HWND m_hWnd;
        HDC m_hDc;
        bool m_bInDrag = false;
        int m_iPreviousX = 0;
        int m_iPreviousY = 0;
    };

}
