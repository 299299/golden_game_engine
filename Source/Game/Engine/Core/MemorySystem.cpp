#include "MemorySystem.h"
#include "memory.h"
#include "linear_allocator.h"
#include "Log.h"
#include "StringId.h"
#include "GameConfig.h"
#include "Prerequisites.h"
//=================================================================
#include <string.h>
#ifdef HAVOK_COMPILE
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/System/Io/OStream/hkOStream.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#endif
//=================================================================

#define STRING_TABLE_FILE                           ("string_table.txt")

#ifdef HAVOK_COMPILE
static void errorReport(const char* msg, void* userArgGivenToInit)
{
    LOGHAVOK(msg);
}
#endif

MemorySystem    g_memoryMgr;

MemorySystem::MemorySystem()
{
    memset(m_allocators, 0x00, sizeof(m_allocators));
}

MemorySystem::~MemorySystem()
{

}

void MemorySystem::init(bool havok_check_mem)
{
#ifdef HAVOK_COMPILE
    if(havok_check_mem) m_memRouter = hkMemoryInitUtil::initChecking( hkMallocAllocator::m_defaultMallocAllocator,
        hkMemorySystem::FrameInfo( HAVOK_FRAMEMEMORY_SIZE ) );
    else m_memRouter = hkMemoryInitUtil::initDefault( hkMallocAllocator::m_defaultMallocAllocator,
        hkMemorySystem::FrameInfo( HAVOK_FRAMEMEMORY_SIZE ) );
    hkBaseSystem::init( m_memRouter, errorReport );
    hkMonitorStream::getInstance().resize(HAVOK_MONITOR_MEM_SIZE);
#endif
    m_havokInited = true;
    memory_globals::init();
    register_allocator(kMemoryCategoryCommon, &default_allocator());
    LinearAllocator* allocator = new LinearAllocator(default_allocator().allocate(FRAME_MEMORY_SIZE), FRAME_MEMORY_SIZE);
    register_allocator(kMemoryCategoryFrame, allocator);
#ifndef _RETAIL
    allocator = new LinearAllocator(default_allocator().allocate(DEBUG_MEMORY_SIZE), DEBUG_MEMORY_SIZE);
    register_allocator(kMemoryCategoryDebug, allocator);
    load_string_table(STRING_TABLE_FILE);
#endif
}

void MemorySystem::shutdown()
{
    LinearAllocator* allocator = (LinearAllocator*)m_allocators[kMemoryCategoryFrame];
    default_allocator().deallocate(allocator->get_start());
    delete allocator;
#ifndef _RETAIL
    save_string_table(STRING_TABLE_FILE);
    allocator = (LinearAllocator*)m_allocators[kMemoryCategoryDebug];
    default_allocator().deallocate(allocator->get_start());
    delete allocator;
#endif
#ifdef HAVOK_COMPILE
    if(m_havokInited)
    {
        hkBaseSystem::quit();
        hkMemoryInitUtil::quit();
    }
#endif
    memory_globals::shutdown();
}

void MemorySystem::frame_start()
{
    clear(kMemoryCategoryFrame);
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