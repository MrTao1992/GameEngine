#pragma once
#include <d2d1.h>
#include "GraphicsManager.h"
#include "Image.h"

namespace Phantom
{
    class D2dGraphicsManager : public GraphicsManager
    {
    public:
        virtual int Initialize();
        virtual void Finalize();

        virtual void Tick();

        void DrawBitmap(const Image image[], int32_t index);

    protected:
        HRESULT CreateGraphicsResources();
        ID2D1Bitmap *m_pBitmap = nullptr;

    protected:
        ID2D1Factory *m_pFactory = nullptr;
        ID2D1HwndRenderTarget *m_pRenderTarget = nullptr;
    };
}
