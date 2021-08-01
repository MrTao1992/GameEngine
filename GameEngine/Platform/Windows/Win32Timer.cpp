#include <Windows.h>
#include "Timer.h"
typedef unsigned long long int uint64;
namespace Phantom
{
    //供WIN9X使用的高精度定时器：QueryPerformanceFrequency()和QueryPerformanceCounter()。
    //要求计算机从硬件上支持高精度定时器。需包括windows.h头文件。
    struct Members
    {
        LARGE_INTEGER m_Start;
        double m_Frequency;
    };

    Timer::Timer()
        : m_Members(new Members())
    {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        m_Members->m_Frequency = 1.0 / frequency.QuadPart;

        Reset();
    }

    void Timer::Reset()
    {
        QueryPerformanceCounter(&m_Members->m_Start);
    }

    float Timer::Elapsed()
    {
        LARGE_INTEGER current;
        QueryPerformanceCounter(&current);
        uint64 cycles = current.QuadPart - m_Members->m_Start.QuadPart;
        return (float)(cycles * m_Members->m_Frequency);
    }

    float Timer::ElapsedMillis()
    {
        return Elapsed() * 1000.0f; //����
    }

}