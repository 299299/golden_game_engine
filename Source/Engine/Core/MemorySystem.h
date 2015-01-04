#pragma once
#include "BaseTypes.h"

#define NATIVE_MEMORY_ALIGN (16)

enum MemoryAllocCategory
{
    kMemoryCategoryCommon,
    kMemoryCategoryFrame,
#ifndef _RETAIL   
    kMemoryCategoryDebug,
#endif
    kMemoryCategoryMax
};

class hkMemoryRouter;
class Allocator;

struct MemorySystem
{
    MemorySystem();
    ~MemorySystem();

    void            init(int havok_frame_size, int monitor_size, bool init_havok, bool havok_check_mem);
    void            quit();
    void            frame_start();

    void*           allocate(uint32_t category, uint32_t size, uint32_t alignment = 16);
    void            deallocate(uint32_t category, void* p);
    uint32_t        allocated_size(uint32_t category);
    void            clear(uint32_t category);
    void            register_allocator(uint32_t category, Allocator* allocator);
    Allocator*      get_allocator(uint32_t category) { return m_allocators[category]; };

    hkMemoryRouter*                 m_memRouter;
    Allocator*                      m_allocators[kMemoryCategoryMax];
    bool                            m_havokInited;
};
extern MemorySystem g_memoryMgr;

#define COMMON_ALLOC(type, num)         (type*)g_memoryMgr.allocate(kMemoryCategoryCommon, sizeof(type)*num)
#define COMMON_DEALLOC(p)               g_memoryMgr.deallocate(kMemoryCategoryCommon, p)
#define FRAME_ALLOC(type, num)          (type*)g_memoryMgr.allocate(kMemoryCategoryFrame, sizeof(type)*num)
#define DEBUG_ALLOC(type, num)          (type*)g_memoryMgr.allocate(kMemoryCategoryDebug, sizeof(type)*num)
