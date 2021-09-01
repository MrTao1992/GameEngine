#include <windows.h>
#include <windowsx.h>
#include <tchar.h>

//使用d2d创建窗口绘制2d图形
#include <d2d1.h>
//d2d工厂模式公放接口
ID2D1Factory *pFactory = nullptr;
//渲染对象
ID2D1HwndRenderTarget *pRenderTarget = nullptr;
//画笔接口对象
ID2D1SolidColorBrush *pLightSlateGrayBrush = nullptr;
ID2D1SolidColorBrush *pCornflowerBlueBrush = nullptr;

//泛型模板
template <class T>
inline void SafeRelease(T **ppInterFaceToRelease)
{
    if (*ppInterFaceToRelease != nullptr)
    {
        (*ppInterFaceToRelease)->Release();
        (*ppInterFaceToRelease) = nullptr;
    }
}

//创建画布，创建画笔
HRESULT CreateGraphicsResources(HWND hWnd)
{
    HRESULT hr = S_OK;
    if (pRenderTarget == nullptr)
    {
        RECT rc;
        GetClientRect(hWnd, &rc);

        D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

        hr = pFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, size), &pRenderTarget);
        if (SUCCEEDED(hr))
        {
            hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::LightSlateGray), &pLightSlateGrayBrush);
        }

        if (SUCCEEDED(hr))
        {
            hr = pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(D2D1::ColorF::CornflowerBlue), &pCornflowerBlueBrush);
        }
    }
    return hr;
}

//释放画布，画笔
void DiscardGraphicsResources()
{
    SafeRelease(&pRenderTarget);
    SafeRelease(&pLightSlateGrayBrush);
    SafeRelease(&pCornflowerBlueBrush);
}

// WindowProc函数原型
LRESULT CALLBACK WindowProc(HWND hWnd,
                            UINT message,
                            WPARAM wParam,
                            LPARAM lParam);

//Windows程序的入口点
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR lpCmdLine,
                   int nCmdShow)
{
    HWND hWnd;
    // 用于存储windows的结构信息
    WNDCLASSEX wc;

    // initialize COM
    if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE)))
        return -1;
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // 填充结构信息
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("WindowClass1");

    // 注册结构
    RegisterClassEx(&wc);

    // 创建窗口,并使用结果的处理
    hWnd = CreateWindowEx(0,
                          _T("WindowClass1"),              // name of the window class
                          _T("Hello, Engine![Direct 2D]"), // title of the window
                          WS_OVERLAPPEDWINDOW,             // window style
                          100,                             // x-position of the window
                          100,                             // y-position of the window
                          960,                             // width of the window
                          540,                             // height of the window
                          NULL,                            // we have no parent window, NULL
                          NULL,                            // we aren't using menus, NULL
                          hInstance,                       // application handle
                          NULL);                           // used with multiple windows, NULL

    // 在屏幕上显示的窗口
    ShowWindow(hWnd, nCmdShow);

    // 这个结构包含Windows事件消息
    MSG msg;

    // 等待消息，处理队列消息
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);

        DispatchMessage(&msg);
    }

    // uninitialize COM
    CoUninitialize();

    return msg.wParam;
}

// 主消息回调函数
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    bool wasHandled = false;
    switch (message)
    {
    case WM_CREATE:
        if (FAILED(D2D1CreateFactory(
                D2D1_FACTORY_TYPE_SINGLE_THREADED, &pFactory)))
        {
            result = -1; // Fail CreateWindowEx.
            return result;
        }
        wasHandled = true;
        result = 0;
        break;

    case WM_PAINT:
    {
        HRESULT hr = CreateGraphicsResources(hWnd);
        if (SUCCEEDED(hr))
        {
            PAINTSTRUCT ps;
            BeginPaint(hWnd, &ps);

            // start build GPU draw command
            pRenderTarget->BeginDraw();

            // clear the background with white color
            pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::White));

            // retrieve the size of drawing area
            D2D1_SIZE_F rtSize = pRenderTarget->GetSize();

            // draw a grid background.
            int width = static_cast<int>(rtSize.width);
            int height = static_cast<int>(rtSize.height);

            for (int x = 0; x < width; x += 10)
            {
                pRenderTarget->DrawLine(
                    D2D1::Point2F(static_cast<FLOAT>(x), 0.0f),
                    D2D1::Point2F(static_cast<FLOAT>(x), rtSize.height),
                    pLightSlateGrayBrush,
                    0.5f);
            }

            for (int y = 0; y < height; y += 10)
            {
                pRenderTarget->DrawLine(
                    D2D1::Point2F(0.0f, static_cast<FLOAT>(y)),
                    D2D1::Point2F(rtSize.width, static_cast<FLOAT>(y)),
                    pLightSlateGrayBrush,
                    0.5f);
            }

            // draw two rectangles
            D2D1_RECT_F rectangle1 = D2D1::RectF(
                rtSize.width / 2 - 50.0f,
                rtSize.height / 2 - 50.0f,
                rtSize.width / 2 + 50.0f,
                rtSize.height / 2 + 50.0f);

            D2D1_RECT_F rectangle2 = D2D1::RectF(
                rtSize.width / 2 - 100.0f,
                rtSize.height / 2 - 100.0f,
                rtSize.width / 2 + 100.0f,
                rtSize.height / 2 + 100.0f);

            // draw a filled rectangle
            pRenderTarget->FillRectangle(&rectangle1, pLightSlateGrayBrush);

            // draw a outline only rectangle
            pRenderTarget->DrawRectangle(&rectangle2, pCornflowerBlueBrush);

            // end GPU draw command building
            hr = pRenderTarget->EndDraw();
            if (FAILED(hr) || hr == D2DERR_RECREATE_TARGET)
            {
                DiscardGraphicsResources();
            }

            EndPaint(hWnd, &ps);
        }
    }
        wasHandled = true;
        break;

    case WM_SIZE:
        if (pRenderTarget != nullptr)
        {
            RECT rc;
            GetClientRect(hWnd, &rc);

            D2D1_SIZE_U size = D2D1::SizeU(rc.right - rc.left, rc.bottom - rc.top);

            pRenderTarget->Resize(size);
        }
        wasHandled = true;
        break;

    case WM_DESTROY:
        DiscardGraphicsResources();
        if (pFactory)
        {
            pFactory->Release();
            pFactory = nullptr;
        }
        PostQuitMessage(0);
        result = 0;
        wasHandled = true;
        break;

    case WM_DISPLAYCHANGE:
        InvalidateRect(hWnd, nullptr, false);
        wasHandled = true;
        break;
    }

    // Handle any messages the switch statement didn't
    if (!wasHandled)
    {
        result = DefWindowProc(hWnd, message, wParam, lParam);
    }
    return result;
}
