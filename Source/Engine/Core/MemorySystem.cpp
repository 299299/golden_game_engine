#include "MemorySystem.h"
#include "memory.h"
#include "linear_allocator.h"
#include "Log.h"
//=================================================================
#include "Prerequisites.h"
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/System/Io/OStream/hkOStream.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
//=================================================================

static void errorReport(const char* msg, void* userArgGivenToInit)
{
    LOGHAVOK(msg);
}

MemorySystem    g_memoryMgr;
#ifndef _RETAIL
static  char                            g_debugBuf[1024*1024*2];
static  LinearAllocator                 g_debugAllocator(g_debugBuf, sizeof(g_debugBuf));
#endif

MemorySystem::MemorySystem()
{
    memset(m_allocators, 0x00, sizeof(m_allocators));
}

MemorySystem::~MemorySystem()
{

}

void MemorySystem::init(int havok_frame_size, int monitor_size, bool init_havok, bool havok_check_mem)
{
    if(init_havok)
    {
        if(havok_check_mem) m_memRouter = hkMemoryInitUtil::initChecking( hkMallocAllocator::m_defaultMallocAllocator, 
            hkMemorySystem::FrameInfo( havok_frame_size ) );
        else m_memRouter = hkMemoryInitUtil::initDefault( hkMallocAllocator::m_defaultMallocAllocator, 
            hkMemorySystem::FrameInfo( havok_frame_size ) );
        hkBaseSystem::init( m_memRouter, errorReport );
        hkMonitorStream::getInstance().resize(monitor_size); 
    }
    m_havokInited = init_havok;
    memory_globals::init();
    register_allocator(kMemoryCategoryCommon, &default_allocator());
#ifndef _RETAIL
    register_allocator(kMemoryCategoryDebug, &g_debugAllocator);
#endif

    extern void init_component_names();
    init_component_names();
}

void MemorySystem::quit()
{
    if(m_havokInited)
    {
        hkBaseSystem::quit();
        hkMemoryInitUtil::quit();
    }
    memory_globals::shutdown();
}

void* MemorySystem::allocate(uint32_t category, uint32_t size, uint32_t alignment)
{
    if(!size) return 0;
    return m_allocators[category]->allocate(size, alignment);
}

void MemorySystem::deallocate(uint32_t category, void* p)
{
    m_allocators[category]->deallocate(p);
}

uint32_t MemorySystem::allocated_size(uint32_t category)
{
    return m_allocators[category]->allocated_size();
}
    
void MemorySystem::clear(uint32_t category)
{
    ((LinearAllocator*)m_allocators[category])->clear();
}

void MemorySystem::register_allocator(uint32_t category, Allocator* allocator)
{
    m_allocators[category] = allocator;
}