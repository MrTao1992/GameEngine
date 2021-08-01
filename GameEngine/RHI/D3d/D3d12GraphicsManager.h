#pragma once
#include <stdint.h>
#include <d3d12.h>
#include <DXGI1_4.h>
#include "GraphicsManager.h"
#include "buffer.h"
#include "Image.h"

namespace Phantom
{

    class D3d12GraphicsManager : public GraphicsManager
    {
    public:
        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();

    private:
        HRESULT CreateDescriptorHeaps();
        HRESULT CreateRenderTarget();
        HRESULT CreateDepthStencil();
        HRESULT CreateGraphicsResources();
        HRESULT CreateSamplerBuffer();
        HRESULT CreateConstantBuffer(const Buffer &buffer);
        HRESULT CreateIndexBuffer(const Buffer &buffer);
        HRESULT CreateVertexBuffer(const Buffer &buffer);
        HRESULT CreateTextureBuffer(const Image &image);

    private:
        static const uint32_t kFrameCount = 2;
        ID3D12Device *m_pDev = nullptr;                        // 指向Direct3D设备接口的指针
        D3D12_VIEWPORT m_ViewPort;                             // 视窗结构
        D3D12_RECT m_ScissorRect;                              // 剪裁矩形结构
        IDXGISwapChain3 *m_pSwapChain = nullptr;               // 交换链接口的指针
        ID3D12Resource *m_pRenderTargets[kFrameCount];         // 指向呈现缓冲区的指针。(描述符)
        ID3D12Resource *m_pDepthStencilBuffer;                 // 指向深度模板缓冲区的指针
        ID3D12CommandAllocator *m_pCommandAllocator = nullptr; // 命令缓冲区分配器的指针
        ID3D12CommandQueue *m_pCommandQueue = nullptr;         // 命令队列的指针
        ID3D12RootSignature *m_pRootSignature = nullptr;       // 图形根签名定义了哪些资源绑定到管道上
        ID3D12DescriptorHeap *m_pRtvHeap = nullptr;            // GPU对象描述符数组
        ID3D12DescriptorHeap *m_pDsvHeap = nullptr;            // GPU对象描述符数组
        ID3D12DescriptorHeap *m_pCbvSrvUavHeap;                // GPU对象描述符数组
        ID3D12DescriptorHeap *m_pSamplerHeap;                  // GPU对象描述符数组
        ID3D12PipelineState *m_pPipelineState = nullptr;       // 一个对象维护所有当前设置的着色器的状态
                                                               // 和某些固定的函数状态对象
                                                               // such as the input assembler, tesselator, rasterizer and output manager
        ID3D12GraphicsCommandList *m_pCommandList = nullptr;   // 一个存储GPU命令的列表，当完成时将提交给GPU执行

        uint32_t m_nRtvDescriptorSize;
        uint32_t m_nCbvSrvDescriptorSize;

        ID3D12Resource *m_pVertexBuffer = nullptr;         // 指向顶点缓冲区的指针
        D3D12_VERTEX_BUFFER_VIEW m_VertexBufferView;       // 顶点缓冲区的视图
        ID3D12Resource *m_pIndexBuffer = nullptr;          // 指向顶点缓冲区的指针
        D3D12_INDEX_BUFFER_VIEW m_IndexBufferView;         // 顶点缓冲区的视图
        ID3D12Resource *m_pTextureBuffer = nullptr;        // 指向纹理缓冲区的指针
        ID3D12Resource *m_pConstantUploadBuffer = nullptr; // 指向深度模板缓冲区的指针

        // Synchronization objects
        uint32_t m_nFrameIndex;
        HANDLE m_hFenceEvent;
        ID3D12Fence *m_pFence = nullptr;
        uint32_t m_nFenceValue;
    };
}
