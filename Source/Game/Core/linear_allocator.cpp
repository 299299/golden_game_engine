#include "linear_allocator.h"
#include "memory.h"

//-----------------------------------------------------------------------------
LinearAllocator::LinearAllocator(Allocator& backing, size_t size)
    : m_backing(&backing)
    , m_physical_start(NULL)
    , m_total_size(size)
    , m_offset(0)
{
    m_physical_start = backing.allocate(size);
}

//-----------------------------------------------------------------------------
LinearAllocator::LinearAllocator(void* start, size_t size)
    : m_backing(NULL), m_physical_start(start), m_total_size(size), m_offset(0)
{
}

//-----------------------------------------------------------------------------
LinearAllocator::~LinearAllocator()
{
    if (m_backing)
    {
        m_backing->deallocate(m_physical_start);
        ENGINE_ASSERT(m_offset == 0, "Memory leak of %ld bytes, maybe you forgot to call clear()?", m_offset);
    }
}

//-----------------------------------------------------------------------------
void* LinearAllocator::allocate(size_t size, size_t align)
{
    const size_t actual_size = size + align;

    // Memory exhausted
    if (m_offset + actual_size > m_total_size)
    {
        return NULL;
    }

    void* user_ptr = memory::align_top((char*) m_physical_start + m_offset, align);

    m_offset += actual_size;

    return user_ptr;
}

//-----------------------------------------------------------------------------
void LinearAllocator::deallocate(void* /*data*/)
{
    // Single deallocations not supported. Use clear().
}

//-----------------------------------------------------------------------------
void LinearAllocator::clear()
{
    m_offset = 0;
}

//-----------------------------------------------------------------------------
size_t LinearAllocator::allocated_size()
{
    return m_offset;
}
