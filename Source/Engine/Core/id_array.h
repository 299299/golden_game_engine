#pragma once
#include "BaseTypes.h"
#include "EngineAssert.h"
#include "allocator.h"

/// Packed array of objects with lookup table.
///
/// @ingroup Containers
template <uint32_t MAX, typename T>
struct IdArray
{
    /// Creates the table for tracking exactly @a MAX - 1 unique Ids.
    IdArray();

    /// Random access by index.
    T& operator[](uint32_t i);
    /// Random access by index.
    const T& operator[](uint32_t i) const;

    void clear();

    // The index of the first unused id
    uint16_t m_freelist;

    // Next available unique id
    uint16_t m_next_id;
    uint16_t m_size;

    // The last valid id is reserved and cannot be used to
    // refer to Ids from the outside
    Id m_sparse[MAX];
    uint16_t m_sparse_to_dense[MAX];
    uint16_t m_dense_to_sparse[MAX];
    T m_objects[MAX];
};

/// Functions to manipulate IdArray.
///
/// @ingroup Containers
namespace id_array
{
    /// Creates a new @a object in the array @a a and returns its id.
    template <uint32_t MAX, typename T> Id create(IdArray<MAX, T>& a, const T& object);

    /// Destroys the object with the given @a id.
    template <uint32_t MAX, typename T> void destroy(IdArray<MAX, T>& a, Id id);

    /// Returns whether the table has the object with the given @a id.
    template <uint32_t MAX, typename T> bool has(const IdArray<MAX, T>& a, Id id);

    /// Returns the number of objects in the array.
    template <uint32_t MAX, typename T> uint32_t size(const IdArray<MAX, T>& a);

    /// Returns the object with the given @a id.
    template <uint32_t MAX, typename T> T& get(const Id& id);

    template <uint32_t MAX, typename T> T* begin(IdArray<MAX, T>& a);
    template <uint32_t MAX, typename T> const T* begin(const IdArray<MAX, T>& a);
    template <uint32_t MAX, typename T> T* end(IdArray<MAX, T>& a);
    template <uint32_t MAX, typename T> const T* end(const IdArray<MAX, T>& a);
} // namespace id_array

namespace id_array
{
    //-----------------------------------------------------------------------------
    template <uint32_t MAX, typename T>
    inline Id create(IdArray<MAX, T>& a, const T& object)
    {
        ENGINE_ASSERT(a.m_size < MAX, "Object list full");

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
    template <uint32_t MAX, typename T>
    inline void destroy(IdArray<MAX, T>& a, Id id)
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
    template <uint32_t MAX, typename T>
    inline T& get(IdArray<MAX, T>& a, const Id& id)
    {
        ENGINE_ASSERT(has(a, id), "IdArray does not have ID: %d,%d", id.id, id.index);

        return a.m_objects[a.m_sparse_to_dense[id.index]];
    }

    //-----------------------------------------------------------------------------
    template <uint32_t MAX, typename T>
    inline bool has(const IdArray<MAX, T>& a, Id id)
    {
        return id.index < MAX && a.m_sparse[id.index].id == id.id;
    }

    //-----------------------------------------------------------------------------
    template <uint32_t MAX, typename T>
    inline uint32_t size(const IdArray<MAX, T>& a)
    {
        return a.m_size;
    }

    //-----------------------------------------------------------------------------
    template <uint32_t MAX, typename T>
    inline T* begin(IdArray<MAX, T>& a)
    {
        return a.m_objects;
    }

    //-----------------------------------------------------------------------------
    template <uint32_t MAX, typename T>
    inline const T* begin(const IdArray<MAX, T>& a)
    {
        return a.m_objects;
    }

    //-----------------------------------------------------------------------------
    template <uint32_t MAX, typename T>
    inline T* end(IdArray<MAX, T>& a)
    {
        return a.m_objects + a.m_size;
    }

    //-----------------------------------------------------------------------------
    template <uint32_t MAX, typename T>
    inline const T* end(const IdArray<MAX, T>& a)
    {
        return a.m_objects + a.m_size;
    }
} // namespace id_array

//-----------------------------------------------------------------------------
template <uint32_t MAX, typename T>
inline IdArray<MAX, T>::IdArray()
{
    clear();
}

//-----------------------------------------------------------------------------
template <uint32_t MAX, typename T>
inline T& IdArray<MAX, T>::operator[](uint32_t i)
{
    ENGINE_ASSERT(i < m_size, "Index out of bounds");
    return m_objects[i];
}

//-----------------------------------------------------------------------------
template <uint32_t MAX, typename T>
inline const T& IdArray<MAX, T>::operator[](uint32_t i) const
{
    ENGINE_ASSERT(i < m_size, "Index out of bounds");
    return m_objects[i];
}

template <uint32_t MAX, typename T>
inline void IdArray<MAX, T>::clear()
{
    m_freelist = INVALID_ID;
    m_next_id  = 0;
    m_size = 0;

    for (uint32_t i = 0; i < MAX; i++)
    {
        m_sparse[i].id = INVALID_ID;
    }
}


template <typename T>
struct DynamicIdArray
{
    /// Random access by index.
    T& operator[](uint32_t i)
    {
        return m_objects[i];
    }

    /// Random access by index.
    const T& operator[](uint32_t i) const
    {
        return m_objects[i];
    }

    void clear()
    {
        m_freelist = INVALID_ID;
        m_next_id  = 0;
        m_size = 0;
        for (uint32_t i = 0; i < m_capacity; i++)
        {
            m_sparse[i].id = INVALID_ID;
        }
    }

    void init(uint32_t capacity, Allocator& allocator)
    {
        uint32_t memSize = sizeof(Id) + sizeof(uint16_t) * 2 + sizeof(T);
        memSize *= capacity;
        char* p = allocator.allocate(memSize, 16);
        m_objects = (T*)p;
        p += sizeof(T) * capacity;
        m_sparse = (Id*) p;
        p += sizeof(Id) * capacity;
        m_sparse_to_dense = (uint16_t*)p;
        p += sizeof(uint16_t) * capacity;
        m_dense_to_sparse = (uint16_t*)p;
        m_capacity = capacity;
        clear();
    }

    void destroy()
    {
        allocator.deallocate(m_objects);
    }

    bool has(Id id)
    {
        return id.index < m_capacity && m_sparse[id.index].id == id.id;
    }

    Id create(const T& object)
    {
        ENGINE_ASSERT(m_size < m_capacity, "Object list full");

        // Obtain a new id
        Id id;
        id.id = m_next_id++;

        // Recycle slot if there are any
        if (m_freelist != INVALID_ID)
        {
            id.index = m_freelist;
            m_freelist = m_sparse[m_freelist].index;
        }
        else
        {
            id.index = m_size;
        }

        m_sparse[id.index] = id;
        m_sparse_to_dense[id.index] = m_size;
        m_dense_to_sparse[m_size] = id.index;
        m_objects[m_size] = object;
        m_size++;

        return id;
    }

    void destroy(Id id)
    {
        ENGINE_ASSERT(has(id), "IdArray does not have ID: %d,%d", id.id, id.index);

        m_sparse[id.index].id = INVALID_ID;
        m_sparse[id.index].index = m_freelist;
        m_freelist = id.index;

        // Swap with last element
        const uint32_t last = m_size - 1;
        ENGINE_ASSERT(last >= m_sparse_to_dense[id.index], "Swapping with previous item");
        m_objects[m_sparse_to_dense[id.index]] = m_objects[last];

        // Update tables
        uint16_t std = m_sparse_to_dense[id.index];
        uint16_t dts = m_dense_to_sparse[last];
        m_sparse_to_dense[dts] = std;
        m_dense_to_sparse[std] = dts;
        m_size--;
    }

    T& get(Id id)
    {
        ENGINE_ASSERT(has(id), "IdArray does not have ID: %d,%d", id.id, id.index);
        return m_objects[m_sparse_to_dense[id.index]];
    }

    uint32_t size() const { return m_size; };

    const T* begin() const { return m_objects; };
    T* begin() { return m_objects; };

    uint16_t    m_freelist;
    uint16_t    m_next_id;
    uint16_t    m_size;

    Id*         m_sparse;
    uint16_t*   m_sparse_to_dense;
    uint16_t*   m_dense_to_sparse;
    T*          m_objects;
    uint32_t    m_capacity;
};