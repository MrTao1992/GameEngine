#pragma once
#include "../common/GfxConfiguration.h"
#include "IRuntimeModule.h"
namespace Phantom
{
    IInterface IApplication : implements IRuntimeModule
    {
    public:
        //初始化函数
        virtual int Initialize() = 0;
        //完成结束函数
        virtual void Finalize() = 0;
        //主回路的一个循环
        virtual void Tick() = 0;
        //是否退出
        virtual bool IsQuit() = 0;
        //初始化应用配置
        virtual GfxConfiguration &GfxCfg() = 0;
        //获取窗口事件消息处理程序
        virtual void *GetMainWindowHandler() = 0;
        //创建程序窗口
        virtual void CreateMainWindow() = 0;
    };
}