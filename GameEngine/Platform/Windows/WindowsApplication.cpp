#include "WindowsApplication.h"
#include <tchar.h>
namespace Phantom
{
    int WindowsApplication::Initialize()
    {
        int result;

        // first call base class initialization
        result = BaseApplication::Initialize();

        if (result != 0)
            exit(result);
        // 获取控制台程序的句柄
        HINSTANCE hInstance = GetModuleHandle(NULL);
        //窗口的句柄，由函数填充
        HWND hWnd;
        //该结构体保存窗口类的信息
        WNDCLASSEX wc;
        //清除要使用的窗口类
        ZeroMemory(&wc, sizeof(WNDCLASSEX));
        //用所需的信息填充结构
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = WindowProc;
        wc.hInstance = hInstance;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.lpszClassName = _T("GameEngineFromScratch");
        //注册窗口类
        RegisterClassEx(&wc);
        //创建窗口并使用结果作为句柄
        hWnd = CreateWindowEx(0,
                              _T("GameEngineFromScratch"), // name of the window class
                              LPCWSTR(m_Config.appName),   // title of the window
                              WS_OVERLAPPEDWINDOW,         // window style
                              CW_USEDEFAULT,               // x-position of the window
                              CW_USEDEFAULT,               // y-position of the window
                              m_Config.screenWidth,        // width of the window
                              m_Config.screenHeight,       // height of the window
                              NULL,                        // we have no parent window, NULL
                              NULL,                        // we aren't using menus, NULL
                              hInstance,                   // application handle
                              this);                       // pass pointer to current object

        //展示窗口
        ShowWindow(hWnd, SW_SHOW);
        m_hWnd = hWnd;
        return result;
    }

    void WindowsApplication::Finalize()
    {
    }
    void WindowsApplication::Tick()
    {
        // 这个结构体保存Windows事件消息
        MSG msg;
        //我们使用PeekMessage代替GetMessage
        //因为我们不应该阻塞线程在任何地方
        //引擎执行驱动模块
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            //将击键消息转换为正确的格式
            TranslateMessage(&msg);

            //发送消息到WindowProc函数
            DispatchMessage(&msg);
        }
    }
    // 这是程序的主要消息处理程序
    LRESULT CALLBACK Phantom::WindowsApplication::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        WindowsApplication *pThis;
        if (message == WM_NCCREATE)
        {
            pThis = static_cast<WindowsApplication *>(reinterpret_cast<CREATESTRUCT *>(lParam)->lpCreateParams);

            SetLastError(0);
            if (!SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pThis)))
            {
                if (GetLastError() != 0)
                    return FALSE;
            }
        }
        else
        {
            pThis = reinterpret_cast<WindowsApplication *>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
        }

        // 对给定的消息进行排序并找到要运行的代码
        switch (message)
        {
        case WM_PAINT:
        {
            pThis->OnDraw();
        }
        break;

        case WM_KEYDOWN:
        {
            // 将用输入管理器替换它
            m_bQuit = true;
        }
        break;

            // 当窗口关闭时读取此消息
        case WM_DESTROY:
        {
            // 完全关闭应用程序
            PostQuitMessage(0);
            m_bQuit = true;
            return 0;
        }
        }

        // 处理switch语句没有处理的消息
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

}