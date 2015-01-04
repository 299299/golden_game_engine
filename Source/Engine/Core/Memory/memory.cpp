#include "memory.h"
#include "allocator.h"

namespace memory
{
    /// Allocator based on C malloc().
    class HeapAllocator : public Allocator
    {
    public:

        HeapAllocator()
            : m_allocated_size(0)
            , m_allocation_count(0)
        {
        }

        ~HeapAllocator()
        {
            ENGINE_ASSERT(m_allocation_count == 0 && allocated_size() == 0,
                "Missing %d deallocations causing a leak of %ld bytes", m_allocation_count, allocated_size());
        }

        /// @copydoc Allocator::allocate()
        void* allocate(size_t size, size_t align = Allocator::DEFAULT_ALIGN)
        {
            size_t actual_size = actual_allocation_size(size, align);

            Header* h = (Header*)malloc(actual_size);
            h->size = actual_size;

            void* data = memory::align_top(h + 1, align);

            pad(h, data);

            m_allocated_size += actual_size;
            m_allocation_count++;

            return data;
        }

        /// @copydoc Allocator::deallocate()
        void deallocate(void* data)
        {
            if (!data)
                return;

            Header* h = header(data);

            m_allocated_size -= h->size;
            m_allocation_count--;

            free(h);
        }

        /// @copydoc Allocator::allocated_size()
        size_t allocated_size()
        {
            return m_allocated_size;
        }

        /// Returns the size in bytes of the block of memory pointed by @a data
        size_t get_size(void* data)
        {
            Header* h = header(data);
            return h->size;
        }

    private:

        // Holds the number of bytes of an allocation
        struct Header
        {
            uint32_t    size;
        };

        //-----------------------------------------------------------------------------
        size_t actual_allocation_size(size_t size, size_t align)
        {
            return size + align + sizeof(Header);
        }

        //-----------------------------------------------------------------------------
        Header* header(void* data)
        {
            uint32_t* ptr = (uint32_t*)data;
            ptr--;

            while (*ptr == memory::PADDING_VALUE)
            {
                ptr--;
            }

            return (Header*)ptr;
        }

        //-----------------------------------------------------------------------------
        void* data(Header* header, size_t align)
        {
            return memory::align_top(header + 1, align);
        }

        //-----------------------------------------------------------------------------
        void pad(Header* header, void* data)
        {
            uint32_t* p = (uint32_t*)(header + 1);

            while (p != data)
            {
                *p = memory::PADDING_VALUE;
                p++;
            }
        }

    private:
        size_t      m_allocated_size;
        uint32_t    m_allocation_count;
    };
} // namespace memory

namespace memory_globals
{
    using namespace memory;
    // Create default allocators
    char _buffer[1024];
    HeapAllocator* _default_allocator = NULL;

    void init()
    {
        _default_allocator = new (_buffer) HeapAllocator();
    }

    void shutdown()
    {
        _default_allocator->~HeapAllocator();
    }
} // namespace memory_globals

Allocator& default_allocator()
{
    return *memory_globals::_default_allocator;
}

