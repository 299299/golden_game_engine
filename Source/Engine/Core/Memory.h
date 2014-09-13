#pragma once
#include "BaseTypes.h"

#define NATIVE_MEMORY_ALIGN (16)

enum MemoryAllocCategory
{
    kMemoryCategoryCommon,
    kMemoryCategoryFrame,
    kMemoryCategoryStatic,
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

    void            init(bool bCheckMem);
    void            quit();
    void            dump();

    //=====================================================
    //          LINEAR ALLOCATION
    void*           alloc(uint32_t category, uint32_t size, uint32_t alignment = 16);
    void            free(uint32_t category, void* p);
    void            free(uint32_t category, void* p, uint32_t numOfBytes);
    uint32_t        allocedSize(uint32_t category);
    void            clear(uint32_t category);
    void            registerAllocator(uint32_t category, Allocator* allocator);
    //=====================================================

    hkMemoryRouter*                 m_memRouter;
    Allocator*                      m_allocators[kMemoryCategoryMax];
};
extern MemorySystem g_memoryMgr;

#define STATIC_ALLOC(type, num)         (type*)g_memoryMgr.alloc(kMemoryCategoryStatic, sizeof(type)*num)
#define FRAME_ALLOC(type, num)          (type*)g_memoryMgr.alloc(kMemoryCategoryFrame, sizeof(type)*num)
#define DEBUG_ALLOC(type, num)          (type*)g_memoryMgr.alloc(kMemoryCategoryDebug, sizeof(type)*num)
