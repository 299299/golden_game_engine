#pragma once
#include "allocator.h"

/// Allocates memory linearly in a stack-like fashion from a
/// predefined chunk. All deallocations must occur in LIFO
/// order.
///
/// @ingroup Memory
class StackAllocator : public Allocator
{
public:

    StackAllocator(void* start, size_t size);
    ~StackAllocator();

    /// @copydoc Allocator::allocate()
    void* allocate(size_t size, size_t align = Allocator::DEFAULT_ALIGN);

    /// @copydoc Allocator::deallocate()
    /// @note
    /// Deallocations must occur in LIFO order i.e. the
    /// last allocation must be freed for first.
    void deallocate(void* data);

    /// @copydoc Allocator::allocated_size()
    size_t allocated_size();

private:

    struct Header
    {
        uint32_t offset;
        uint32_t alloc_id;
    };

    void* m_physical_start;
    size_t m_total_size;

    void* m_top;

    uint32_t m_allocation_count;
};