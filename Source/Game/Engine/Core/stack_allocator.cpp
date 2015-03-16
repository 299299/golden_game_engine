#include "stack_allocator.h"
#include "memory.h"

//-----------------------------------------------------------------------------
StackAllocator::StackAllocator(void* start, size_t size)
    : m_physical_start(start)
    , m_total_size(size)
    , m_top(start)
    , m_allocation_count(0)
{
}

//-----------------------------------------------------------------------------
StackAllocator::~StackAllocator()
{
    ENGINE_ASSERT(m_allocation_count == 0 && allocated_size() == 0, "Missing %d deallocations causing a leak of %ld bytes", m_allocation_count, allocated_size());
}

//-----------------------------------------------------------------------------
void* StackAllocator::allocate(size_t size, size_t align)
{
    const size_t actual_size = sizeof(Header) + size + align;

    // Memory exhausted
    if ((char*) m_top + actual_size > (char*) m_physical_start + m_total_size)
    {
        return NULL;
    }

    // The offset from TOS to the start of the buffer
    uint32_t offset = (char*) m_top - (char*) m_physical_start;

    // Align user data only, ignore header alignment
    m_top = (char*) memory::align_top((char*) m_top + sizeof(Header), align) - sizeof(Header);

    Header* header = (Header*) m_top;
    header->offset = offset;
    header->alloc_id = m_allocation_count;

    void* user_ptr = (char*) m_top + sizeof(Header);
    m_top = (char*) m_top + actual_size;

    m_allocation_count++;

    return user_ptr;
}

//-----------------------------------------------------------------------------
void StackAllocator::deallocate(void* data)
{
    if (!data)
        return;

    Header* data_header = (Header*) ((char*)data - sizeof(Header));

    ENGINE_ASSERT(data_header->alloc_id == m_allocation_count - 1, "Deallocations must occur in LIFO order");

    m_top = (char*) m_physical_start + data_header->offset;

    m_allocation_count--;
}

//-----------------------------------------------------------------------------
size_t StackAllocator::allocated_size()
{
    return (char*) m_top - (char*) m_physical_start;
}
