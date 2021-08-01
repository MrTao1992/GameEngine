#pragma once

namespace Phantom
{

    struct Members;

    class Timer
    {
    private:
        Members *m_Members;

    public:
        // 创建时钟
        Timer();
        // 重置时钟
        virtual void Reset();
        // 返回秒钟
        virtual float Elapsed();
        // 返回毫秒钟
        virtual float ElapsedMillis();
    };

}