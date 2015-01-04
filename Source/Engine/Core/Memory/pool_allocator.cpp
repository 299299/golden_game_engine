#include "pool_allocator.h"
#include "EngineAssert.h"

//-----------------------------------------------------------------------------
PoolAllocator::PoolAllocator(Allocator& backing, size_t num_blocks, size_t block_size, size_t block_align)
    : m_backing(backing)
    , m_start(NULL)
    , m_freelist(NULL)
    , m_block_size(block_size)
    , m_block_align(block_align)
    , m_num_allocations(0)
    , m_allocated_size(0)
{
    ENGINE_ASSERT(num_blocks > 0, "Unsupported number of blocks");
    ENGINE_ASSERT(block_size > 0, "Unsupported block size");
    ENGINE_ASSERT(block_align > 0, "Unsupported block alignment");

    size_t actual_block_size = block_size + block_align;
    size_t pool_size = num_blocks * actual_block_size;

    char* mem = (char*) backing.allocate(pool_size, block_align);

    // Initialize intrusive freelist
    char* cur = mem;
    for (size_t bb = 0; bb < num_blocks - 1; bb++)
    {
        uintptr_t* next = (uintptr_t*) cur;
        *next = (uintptr_t) cur + actual_block_size;
        cur += actual_block_size;
    }

    uintptr_t* end = (uintptr_t*) cur;
    *end = (uintptr_t) NULL;

    m_start = mem;
    m_freelist = mem;
}

//-----------------------------------------------------------------------------
PoolAllocator::~PoolAllocator()
{
    m_backing.deallocate(m_start);
}

//-----------------------------------------------------------------------------
void* PoolAllocator::allocate(size_t size, size_t align)
{
    ENGINE_ASSERT(size == m_block_size, "Size must match block size");
    ENGINE_ASSERT(align == m_block_align, "Align must match block align");
    ENGINE_ASSERT(m_freelist != NULL, "Out of memory");

    uintptr_t next_free = *((uintptr_t*) m_freelist);
    void* user_ptr = m_freelist;
    m_freelist = (void*) next_free;

    m_num_allocations++;
    m_allocated_size += m_block_size;

    return user_ptr;
}

//-----------------------------------------------------------------------------
void PoolAllocator::deallocate(void* data)
{
    if (!data)
        return;

    ENGINE_ASSERT(m_num_allocations > 0, "Did not allocate");

    uintptr_t* next = (uintptr_t*) data;
    *next = (uintptr_t) m_freelist;

    m_freelist = data;

    m_num_allocations--;
    m_allocated_size -= m_block_size;
}

//-----------------------------------------------------------------------------
size_t PoolAllocator::allocated_size()
{
    return m_allocated_size;
}

