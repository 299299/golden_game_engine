#pragma once
#include "BaseTypes.h"
#include "Assert.h"
#include "Allocator.h"

/// Packed array of objects with lookup table.
///
/// @ingroup Containers
template <typename T>
struct IdArray
{
    /// Creates the table for tracking exactly @a MAX - 1 unique Ids.
    IdArray(Allocator* alloactor, uint32_t capacity);
    ~IdArray();

    /// Random access by index.
    T& operator[](uint32_t i);
    /// Random access by index.
    const T& operator[](uint32_t i) const;

    uint32_t m_capacity;

    // The index of the first unused id
    uint16_t m_freelist;

    // Next available unique id
    uint16_t m_next_id;
    uint16_t m_size;

    // The last valid id is reserved and cannot be used to
    // refer to Ids from the outside
    Id*         m_sparse;
    uint16_t*   m_sparse_to_dense;
    uint16_t*   m_dense_to_sparse;
    T*          m_objects;
    Allocator*  m_allocator;
};

/// Functions to manipulate IdArray.
///
/// @ingroup Containers
namespace id_array
{
    /// Creates a new @a object in the array @a a and returns its id.
    template <typename T> Id create(IdArray<T>& a, const T& object);

    /// Destroys the object with the given @a id.
    template <typename T> void destroy(IdArray<T>& a, Id id);

    /// Returns whether the table has the object with the given @a id.
    template <typename T> bool has(const IdArray<T>& a, Id id);

    /// Returns the number of objects in the array.
    template <typename T> uint32_t size(const IdArray<T>& a);

    /// Returns the object with the given @a id.
    template <typename T> T& get(const Id& id);

    template <typename T> T* begin(IdArray<T>& a);
    template <typename T> const T* begin(const IdArray<T>& a);
    template <typename T> T* end(IdArray<T>& a);
    template <typename T> const T* end(const IdArray<T>& a);
} // namespace id_array

namespace id_array
{
    //-----------------------------------------------------------------------------
    template <typename T>
    inline Id create(IdArray<T>& a, const T& object)
    {
        ENGINE_ASSERT(a.m_size < a.m_capacity, "Object list full");

        // Obtain a new id
        Id id;
        id.id = a.m_next_id++;

        // Recycle slot if there are any
        if (a.m_freelist != INVALID_ID)
        {
            id.index = a.m_freelist;
            a.m_freelist = a.m_sparse[a.m_freelist].index;
        }
        else
        {
            id.index = a.m_size;
        }

        a.m_sparse[id.index] = id;
        a.m_sparse_to_dense[id.index] = a.m_size;
        a.m_dense_to_sparse[a.m_size] = id.index;
        a.m_objects[a.m_size] = object;
        a.m_size++;

        return id;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    inline void destroy(IdArray<T>& a, Id id)
    {
        ENGINE_ASSERT(has(a, id), "IdArray does not have ID: %d,%d", id.id, id.index);

        a.m_sparse[id.index].id = INVALID_ID;
        a.m_sparse[id.index].index = a.m_freelist;
        a.m_freelist = id.index;

        // Swap with last element
        const uint32_t last = a.m_size - 1;
        ENGINE_ASSERT(last >= a.m_sparse_to_dense[id.index], "Swapping with previous item");
        a.m_objects[a.m_sparse_to_dense[id.index]] = a.m_objects[last];

        // Update tables
        uint16_t std = a.m_sparse_to_dense[id.index];
        uint16_t dts = a.m_dense_to_sparse[last];
        a.m_sparse_to_dense[dts] = std;
        a.m_dense_to_sparse[std] = dts;
        a.m_size--;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    inline T& get(IdArray<T>& a, const Id& id)
    {
        ENGINE_ASSERT(has(a, id), "IdArray does not have ID: %d,%d", id.id, id.index);

        return a.m_objects[a.m_sparse_to_dense[id.index]];
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    inline bool has(const IdArray<T>& a, Id id)
    {
        return id.index < a.m_capacity && a.m_sparse[id.index].id == id.id;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    inline uint32_t size(const IdArray<T>& a)
    {
        return a.m_size;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    inline T* begin(IdArray<T>& a)
    {
        return a.m_objects;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    inline const T* begin(const IdArray<T>& a)
    {
        return a.m_objects;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    inline T* end(IdArray<T>& a)
    {
        return a.m_objects + a.m_size;
    }

    //-----------------------------------------------------------------------------
    template <typename T>
    inline const T* end(const IdArray<T>& a)
    {
        return a.m_objects + a.m_size;
    }
} // namespace id_array

//-----------------------------------------------------------------------------
template <typename T>
inline IdArray<T>::IdArray(Allocator* alloactor, uint32_t capacity)
    : m_freelist(INVALID_ID)
    , m_next_id(0)
    , m_size(0)
    , m_capacity(capacity)
    , m_allocator(allocator)
{
    uint32_t memSize = (sizeof(Id) + sizeof(uint16_t) + sizeof(T)) * capacity;
    char* p = allocator->allocate(memSize);
    m_objects = (T*)p;
    p += (sizeof(T) * capacity);
    m_sparse = (Id*)p;
    p += (sizeof(Id) * capacity);
    m_sparse_to_dense = (uint16_t*)p;
    p += (sizeof(uint16_t) * capacity);
    m_dense_to_sparse = (uint16_t*)p;
    for(uint32_t i=0; i<capacity; ++i)
    {
        m_sparse[i].id = INVALID_ID;
    }
}

template <typename T>
inline IdArray<T>::~IdArray()
{
    m_allocator->deallocate(m_objects);
}

//-----------------------------------------------------------------------------
template <typename T>
inline T& IdArray<T>::operator[](uint32_t i)
{
    ENGINE_ASSERT(i < m_size, "Index out of bounds");
    return m_objects[i];
}

//-----------------------------------------------------------------------------
template <typename T>
inline const T& IdArray<T>::operator[](uint32_t i) const
{
    ENGINE_ASSERT(i < m_size, "Index out of bounds");
    return m_objects[i];
}

