#include "MemoryManager.hpp"
#include <malloc.h>
using namespace My;
namespace My
{
    static const uint32_t kBlockSizes[] = {
        //4字节增量
        4,
        8,
        12,
        16,
        20,
        24,
        28,
        32,
        36,
        40,
        44,
        48,
        52,
        56,
        60,
        64,
        68,
        72,
        76,
        80,
        84,
        88,
        92,
        96,

        //32字节增量
        128,
        160,
        192,
        224,
        256,
        288,
        320,
        352,
        384,
        416,
        448,
        480,
        512,
        544,
        576,
        608,
        640,
        //64字节增量
        704, 768, 832, 896, 960, 1024};

}