#pragma once
#include "allocator.h"


/// Allocates memory linearly from a predefined chunk
/// and frees all the allocations with a single call to clear()
///
/// @ingroup Memory
class LinearAllocator : public Allocator
{
public:

    LinearAllocator(Allocator& backing, size_t size);
    LinearAllocator(void* start, size_t size);
    ~LinearAllocator();

    /// @copydoc Allocator::allocate()
    void* allocate(size_t size, size_t align = Allocator::DEFAULT_ALIGN);

    /// @copydoc Allocator::deallocate()
    /// @note
    /// The linear allocator does not support deallocating
    /// individual allocations, rather you have to call
    /// clear() to free all memory at once.
    void deallocate(void* data);

    /// Frees all the allocations made by allocate()
    void clear();

    /// @copydoc Allocator::allocated_size()
    size_t allocated_size();

private:

    Allocator* m_backing;
    void* m_physical_start;
    size_t m_total_size;
    size_t m_offset;
};