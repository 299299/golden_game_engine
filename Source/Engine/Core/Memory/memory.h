#pragma once
#include <new>
#include "BaseTypes.h"
#include "allocator.h"
#include "EngineAssert.h"

Allocator& default_allocator();

/// @defgroup Memory Memory
namespace memory
{
    /// Value used to fill unused memory
    const uint32_t PADDING_VALUE = 0xFFFFFFFFu;

    /// Returns the pointer @a p aligned to the desired @a align byte
    inline void* align_top(void* p, size_t align)
    {
        ENGINE_ASSERT(align >= 1, "Alignment must be > 1");
        ENGINE_ASSERT(align % 2 == 0 || align == 1, "Alignment must be a power of two");

        uintptr_t ptr = (uintptr_t)p;

        const size_t mod = ptr % align;

        if (mod)
        {
            ptr += align - mod;
        }

        return (void*) ptr;
    }

    /// Respects standard behaviour when calling on NULL @a ptr
    template <typename T>
    inline void call_destructor_and_deallocate(Allocator& a, T* ptr)
    {
        if (!ptr)
            return;

        ptr->~T();
        a.deallocate(ptr);
    }
} // namespace memory

namespace memory_globals
{
    /// Constructs the initial default allocators.
    /// @note
    /// Has to be called before anything else during the engine startup.
    void init();

    /// Destroys the allocators created with memory_globals::init().
    /// @note
    /// Should be the last call of the program.
    void shutdown();
} // namespace memory_globals

/// Allocates memory with @a allocator for the given @a T type
/// and calls constructor on it.
/// @note
/// @a allocator must be a reference to an existing allocator.
#define ENGINE_ALIGNOF(x) __alignof__(x)
#define ENGINE_NEW(allocator, T) new ((allocator).allocate(sizeof(T), ENGINE_ALIGNOF(T))) T

/// Calls destructor on @a ptr and deallocates memory using the
/// given @a allocator.
/// @note
/// @a allocator must be a reference to an existing allocator.
#define ENGINE_DELETE(allocator, ptr) memory::call_destructor_and_deallocate(allocator, ptr)
