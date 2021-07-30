#pragma once
#include "IInterface.h"
namespace Phantom
{
    IInterface IRuntimeModule
    {
    public:
        virtual ~IRuntimeModule(){};
        //初始化函数
        virtual int Initialize() = 0;
        //完成结束函数
        virtual void Finalize() = 0;
        //跳动帧函数
        virtual void Tick() = 0;
    };
}