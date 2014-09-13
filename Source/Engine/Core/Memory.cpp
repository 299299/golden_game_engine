#include "Memory.h"
#include "Log.h"
#include "MemoryPool.h"
//=================================================================
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/System/Error/hkDefaultError.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/System/Io/OStream/hkOStream.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
//=================================================================

#define HAVOK_FRAME_MEM_SIZE                   (1024*1024*5)  //(5M)
#define MONITOR_FRAME_SIZE                     (1024*1024*3)  //(3M)

static void errorReport(const char* msg, void* userArgGivenToInit)
{
    LOGHAVOK(msg);
}

MemorySystem    g_memoryMgr;
static MallocAllocator g_commonAllocator("common_memory");

MemorySystem::MemorySystem()
{
    memset(m_allocators, 0x00, sizeof(m_allocators));
}

MemorySystem::~MemorySystem()
{

}

void MemorySystem::init(bool bCheckMem)
{
    if(bCheckMem) m_memRouter = hkMemoryInitUtil::initChecking( hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo( HAVOK_FRAME_MEM_SIZE ) );
    else m_memRouter = hkMemoryInitUtil::initDefault( hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo( HAVOK_FRAME_MEM_SIZE ) );
    hkBaseSystem::init( m_memRouter, errorReport );
    hkMonitorStream::getInstance().resize( MONITOR_FRAME_SIZE  );
    registerAllocator(kMemoryCategoryCommon, &g_commonAllocator);
}

void MemorySystem::quit()
{
    hkBaseSystem::quit();
    hkMemoryInitUtil::quit();
    for (uint32_t i=0; i<kMemoryCategoryMax; ++i)
    {
        Allocator* allocator = m_allocators[i];
        if(!allocator) continue;
        allocator->dump();
        allocator->check();
    }
}

void MemorySystem::dump()
{
    for (uint32_t i=0; i<kMemoryCategoryMax; ++i)
    {
        Allocator* allocator = m_allocators[i];
        if(!allocator) continue;
        allocator->dump();
    }
}

void* MemorySystem::alloc(uint32_t category, uint32_t size, uint32_t alignment)
{
    if(!size) return 0;
    return m_allocators[category]->alloc(size, alignment);
}

void MemorySystem::free(uint32_t category, void* p)
{
    m_allocators[category]->free(p);
}

void MemorySystem::free( uint32_t category, void* p, uint32_t numOfBytes )
{
    m_allocators[category]->free(p, numOfBytes);
}

uint32_t MemorySystem::allocedSize(uint32_t category)
{
    return m_allocators[category]->allocedSize();
}
    
void MemorySystem::clear(uint32_t category)
{
    m_allocators[category]->clear();
}

void MemorySystem::registerAllocator(uint32_t category, Allocator* allocator)
{
    m_allocators[category] = allocator;
}