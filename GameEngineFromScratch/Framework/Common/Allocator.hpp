#include <cstddef>
#include <stdint.h>

namespace My
{
    struct BlockHeader
    {
        BlockHeader *pNext;
    };

    struct PageHeader
    {
        PageHeader *pNext;
        //返回内存块
        BlockHeader *Blocks()
        {
            return reinterpret_cast<BlockHeader *>(this + 1);
        }
    };

    class Allocator
    {
    public:
        static const uint8_t PATTERN_ALIGN = 0xFC;
        static const uint8_t PATTERN_ALLOC = 0xFD;
        static const uint8_t PATTERN_FREE = 0xFE;

        Allocator();
        Allocator(size_t data_size, size_t page_size, size_t alignment);
        ~Allocator();

        //重置内存配置
        void Reset(size_t data_size, size_t page_size, size_t alignment);

        //创建和释放块内存
        void *Allocate();
        void Free(void *p);
        void FreeAll();

    private:
#if defined(_DEBUG)
        void FillFreePage(PageHeader *pPage);
        void FillFreeBlock(BlockHeader *pBlock);
        void FillAllocatedBlock(BlockHeader *pBlock);
#endif
        BlockHeader *NextBlock(BlockHeader *pBlock);
        PageHeader *m_pPageList;
        BlockHeader *m_pFreeList;
        size_t m_szDataSize;
        size_t m_szPageSize;
        size_t m_szAlignmentSize;
        size_t m_szBlockSize;
        uint32_t m_nBlocksPerPage;

        //统计数据
        uint32_t m_nPages;
        uint32_t m_nBlocks;
        uint32_t m_nFreeBlocks;
		 // disable copy & assignment
		 Allocator(const Allocator& clone);
		 Allocator &operator=(const Allocator &rhs);
    };
}