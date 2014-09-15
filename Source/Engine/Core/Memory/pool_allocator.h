#pragma once
#include "allocator.h"

/// Allocates fixed-size memory blocks from a fixed memory pool.
/// The backing allocator is used to allocate the memory pool.
///
/// @ingroup Memory
class PoolAllocator : public Allocator
{
public:

    /// Uses @a backing to allocate the memory pool for containing exactly
    /// @a num_blocks blocks of @a block_size size each aligned to @a block_align.
    PoolAllocator(Allocator& backing, size_t num_blocks, size_t block_size, size_t block_align = Allocator::DEFAULT_ALIGN);
    ~PoolAllocator();

    /// Allocates a block of memory from the memory pool.
    /// @note
    /// The @a size and @a align must match those passed to PoolAllocator::PoolAllocator()
    void* allocate(size_t size, size_t align = Allocator::DEFAULT_ALIGN);

    /// @copydoc Allocator::deallocate()
    void deallocate(void* data);

    /// @copydoc Allocator::allocated_size()
    size_t allocated_size();

private:

    Allocator&  m_backing;

    void* m_start;
    void* m_freelist;
    size_t m_block_size;
    size_t m_block_align;

    uint32_t m_num_allocations;
    size_t m_allocated_size;
};
