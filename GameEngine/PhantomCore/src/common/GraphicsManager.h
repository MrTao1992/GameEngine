#pragma once

#include "IRuntimeModule.h"

namespace Phantom
{
    class GraphicsManager : implements IRuntimeModule
    {
    public:
        virtual ~GraphicsManager(){};
        //初始化函数
        virtual int Initialize();
        //完成结束函数
        virtual void Finalize();
        //跳动帧函数
        virtual void Tick();
        //绘制单一网格
        virtual void DrawSingleMesh();
    };

}