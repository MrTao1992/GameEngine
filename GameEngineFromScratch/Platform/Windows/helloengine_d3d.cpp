#include <windows.h>
#include <windowsx.h>
#include <tchar.h>
#include <stdint.h>

#include <d3d11.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXColors.h>

using namespace DirectX;
using namespace DirectX::PackedVector;

const uint32_t SCREEN_WIDTH = 960;
const uint32_t SCREEN_HEIGHT = 480;

IDXGISwapChain *g_pSwapchain = nullptr;   // 交换链接口的指针
ID3D11Device *g_pDev = nullptr;           // Direct3D设备接口的指针
ID3D11DeviceContext *g_pDevcon = nullptr; // Direct3D设备上下文的指针

ID3D11RenderTargetView *g_pRTView = nullptr;

ID3D11InputLayout *g_pLayout = nullptr; // 指针指向输入布局
ID3D11VertexShader *g_pVS = nullptr;    // vertex shader
ID3D11PixelShader *g_pPS = nullptr;     // pixel shader

ID3D11Buffer *g_pVBuffer = nullptr; // 顶点数据buffer

// 顶点数据格式结构体
struct VERTEX
{
    XMFLOAT3 Position;
    XMFLOAT4 Color;
};

template <class T>
inline void SafeRelease(T **ppInterfaceToRelease)
{
    if (*ppInterfaceToRelease != nullptr)
    {
        (*ppInterfaceToRelease)->Release();

        (*ppInterfaceToRelease) = nullptr;
    }
}

void CreateRenderTarget()
{
    HRESULT hr;
    ID3D11Texture2D *pBackBuffer;

    // Get a pointer to the back buffer
    g_pSwapchain->GetBuffer(0, __uuidof(ID3D11Texture2D),
                            (LPVOID *)&pBackBuffer);

    // Create a render-target view
    g_pDev->CreateRenderTargetView(pBackBuffer, NULL,
                                   &g_pRTView);
    pBackBuffer->Release();

    // Bind the view
    g_pDevcon->OMSetRenderTargets(1, &g_pRTView, NULL);
}

//设置视图尺寸
void SetViewPort()
{
    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    //左上角坐标位
    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = SCREEN_WIDTH;
    viewport.Height = SCREEN_HEIGHT;

    g_pDevcon->RSSetViewports(1, &viewport);
}

void InitGraphics()
{
    //准备顶点数据
    VERTEX OurVertices[] =
        {
            {XMFLOAT3(0.0f, 0.5f, 0.0f), XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f)},
            {XMFLOAT3(0.45f, -0.5, 0.0f), XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f)},
            {XMFLOAT3(-0.45f, -0.5f, 0.0f), XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f)}};

    //创建顶点缓存buffer描述
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));

    bd.Usage = D3D11_USAGE_DYNAMIC;             // 写访问访问CPU和GPU
    bd.ByteWidth = sizeof(VERTEX) * 3;          // 读取时顶点宽度
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;    // 使用顶点数据flag
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE; // 允许顶点数据写buffer

    //创建顶点缓存区buffer
    g_pDev->CreateBuffer(&bd, NULL, &g_pVBuffer);

    //拷贝顶点数据到缓存区中
    D3D11_MAPPED_SUBRESOURCE ms;
    g_pDevcon->Map(g_pVBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms); // 初始化缓存区
    memcpy(ms.pData, OurVertices, sizeof(VERTEX) * 3);                    // 拷贝数据到缓存区中
    g_pDevcon->Unmap(g_pVBuffer, NULL);                                   // 清空顶点buffer
}

// 处理shader渲染流程
void InitPipeline()
{
    ID3DBlob *VS, *PS;

    D3DReadFileToBlob(L"copy.vso", &VS);
    D3DReadFileToBlob(L"copy.pso", &PS);

    g_pDev->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &g_pVS);
    g_pDev->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &g_pPS);

    g_pDevcon->VSSetShader(g_pVS, 0, 0);
    g_pDevcon->PSSetShader(g_pPS, 0, 0);

    D3D11_INPUT_ELEMENT_DESC ied[] =
        {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };

    g_pDev->CreateInputLayout(ied, 2, VS->GetBufferPointer(), VS->GetBufferSize(), &g_pLayout);
    g_pDevcon->IASetInputLayout(g_pLayout);

    VS->Release();
    PS->Release();
}

HRESULT CreateGraphicsResources(HWND hWnd)
{
    HRESULT hr = S_OK;
    if (g_pSwapchain == nullptr)
    {
        // 创建交换链信息
        DXGI_SWAP_CHAIN_DESC scd;

        // 清空结构后使用
        ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

        // 填充交换链信息
        scd.BufferCount = 1;                                //交换链中的后台缓冲区数量；我们一般只用一个后台缓冲区来实现双缓存。当然，你也可以使用两个后台缓冲区来实现三缓存。
        scd.BufferDesc.Width = SCREEN_WIDTH;                //后台缓冲区宽度
        scd.BufferDesc.Height = SCREEN_HEIGHT;              //后台缓冲区高度
        scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM; //后台缓冲区像素格式
        scd.BufferDesc.RefreshRate.Numerator = 60;          //刷新帧率
        scd.BufferDesc.RefreshRate.Denominator = 1;
        scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;  // 将它用作渲染目标
        scd.OutputWindow = hWnd;                            // 将要渲染到的窗口的句柄
        scd.SampleDesc.Count = 4;                           // 多重采样数量和质量级别
        scd.Windowed = TRUE;                                // 当设为true时，程序以窗口模式运行；当设为false时，程序以全屏（full-screen）模式运行
        scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; // 全屏时渲染显示方式

        const D3D_FEATURE_LEVEL FeatureLevels[] = {D3D_FEATURE_LEVEL_11_1,
                                                   D3D_FEATURE_LEVEL_11_0,
                                                   D3D_FEATURE_LEVEL_10_1,
                                                   D3D_FEATURE_LEVEL_10_0,
                                                   D3D_FEATURE_LEVEL_9_3,
                                                   D3D_FEATURE_LEVEL_9_2,
                                                   D3D_FEATURE_LEVEL_9_1};
        D3D_FEATURE_LEVEL FeatureLevelSupported;

      	HRESULT hr = S_OK;
        // 创建一个设备,设备上下文和交换链使用结构中的信息
        hr = D3D11CreateDeviceAndSwapChain(NULL,
                                           D3D_DRIVER_TYPE_HARDWARE,
                                           NULL,
                                           0,
                                           FeatureLevels,
                                           _countof(FeatureLevels),
                                           D3D11_SDK_VERSION,
                                           &scd,
                                           &g_pSwapchain,
                                           &g_pDev,
                                           &FeatureLevelSupported,
                                           &g_pDevcon);

        if (hr == E_INVALIDARG)
        {
            hr = D3D11CreateDeviceAndSwapChain(NULL,
                                               D3D_DRIVER_TYPE_HARDWARE,
                                               NULL,
                                               0,
                                               &FeatureLevelSupported,
                                               1,
                                               D3D11_SDK_VERSION,
                                               &scd,
                                               &g_pSwapchain,
                                               &g_pDev,
                                               NULL,
                                               &g_pDevcon);
        }

        if (hr == S_OK)
        {
            CreateRenderTarget();
            SetViewPort();
            InitPipeline();
            InitGraphics();
        }
    }
    return hr;
}

//释放绘图资源
void DiscardGraphicsResources()
{
    SafeRelease(&g_pLayout);
    SafeRelease(&g_pVS);
    SafeRelease(&g_pPS);
    SafeRelease(&g_pVBuffer);
    SafeRelease(&g_pSwapchain);
    SafeRelease(&g_pRTView);
    SafeRelease(&g_pDev);
    SafeRelease(&g_pDevcon);
}

//单帧渲染函数
void RenderFrame()
{
    // 使用深蓝清理缓冲区
    const FLOAT clearColor[] = {0.0f, 0.2f, 0.4f, 1.0f};
    g_pDevcon->ClearRenderTargetView(g_pRTView, clearColor);

    {
        UINT stride = sizeof(VERTEX);
        UINT offset = 0;
        g_pDevcon->IASetVertexBuffers(0, 1, &g_pVBuffer, &stride, &offset);

        g_pDevcon->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        g_pDevcon->Draw(3, 0);
    }

    g_pSwapchain->Present(0, 0);
}
// the WindowProc function prototype
LRESULT CALLBACK WindowProc(HWND hWnd,
                            UINT message,
                            WPARAM wParam,
                            LPARAM lParam);

// 创建windows窗口
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPTSTR lpCmdLine,
                   int nCmdShow)
{
    // the handle for the window, filled by a function
    HWND hWnd;
    // this struct holds information for the window class
    WNDCLASSEX wc;

    // clear out the window class for use
    ZeroMemory(&wc, sizeof(WNDCLASSEX));

    // fill in the struct with the needed information
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = _T("WindowClass1");

    // register the window class
    RegisterClassEx(&wc);

    // create the window and use the result as the handle
    hWnd = CreateWindowEx(0,
                          _T("WindowClass1"),              // name of the window class
                          _T("Hello, Engine![Direct 3D]"), // title of the window
                          WS_OVERLAPPEDWINDOW,             // window style
                          100,                             // x-position of the window
                          100,                             // y-position of the window
                          SCREEN_WIDTH,                    // width of the window
                          SCREEN_HEIGHT,                   // height of the window
                          NULL,                            // we have no parent window, NULL
                          NULL,                            // we aren't using menus, NULL
                          hInstance,                       // application handle
                          NULL);                           // used with multiple windows, NULL

    // display the window on the screen
    ShowWindow(hWnd, nCmdShow);

    // enter the main loop:

    // this struct holds Windows event messages
    MSG msg;

    // wait for the next message in the queue, store the result in 'msg'
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        // translate keystroke messages into the right format
        TranslateMessage(&msg);

        // send the message to the WindowProc function
        DispatchMessage(&msg);
    }

    // return this part of the WM_QUIT message to Windows
    return msg.wParam;
}

// this is the main message handler for the program
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    LRESULT result = 0;
    bool wasHandled = false;

    // sort through and find what code to run for the message given
    switch (message)
    {
    case WM_CREATE:
        wasHandled = true;
        break;

    case WM_PAINT:
        result = CreateGraphicsResources(hWnd);
        RenderFrame();
        wasHandled = true;
        break;

	case WM_SIZE:
		if (g_pSwapchain != nullptr)
		{
		    DiscardGraphicsResources();
			g_pSwapchain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH);
		}
		wasHandled = true;
        break;

    case WM_DESTROY:
        DiscardGraphicsResources();
        PostQuitMessage(0);
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
