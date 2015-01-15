#pragma once
#include "BaseTypes.h"
#include "allocator.h"
#include "Prerequisites.h"

/// Packed array of objects with lookup table.
template <typename T>
struct IdArray
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
        uint32_t num = m_capacity;
        Id* head = m_sparse;
        for (uint32_t i = 0; i < num; i++)
        {
            head[i].id = INVALID_ID;
        }
    }

    void init(uint32_t capacity, Allocator* allocator)
    {
        m_alloactor = allocator;
        uint32_t memSize = sizeof(Id) + sizeof(uint16_t) * 2 + sizeof(T);
        memSize *= capacity;
        char* p = (char*)allocator->allocate(memSize, 16);
        memset(p, 0x00, memSize);
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
        m_alloactor->deallocate(m_objects);
    }

    bool has(Id id)
    {
        return id.index < m_capacity && m_sparse[id.index].id == id.id;
    }

    Id create(T** object)
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
        *object = &m_objects[m_size];
        m_size++;

        return id;
    }

    void destroy(Id id)
    {
        ENGINE_ASSERT_ARGS(has(id), "IdArray does not have ID: %d,%d", id.id, id.index);

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

    T* get(Id id)
    {
        ENGINE_ASSERT_ARGS(has(id), "IdArray does not have ID: %d,%d", id.id, id.index);
        return &m_objects[m_sparse_to_dense[id.index]];
    }

    uint32_t size() const { return m_size; };

    const T* begin() const { return m_objects; };
    T* begin() { return m_objects; };

    Id*                 m_sparse;
    uint16_t*           m_sparse_to_dense;
    uint16_t*           m_dense_to_sparse;
    T*                  m_objects;
    uint32_t            m_capacity;
    Allocator*          m_alloactor;

    uint16_t            m_freelist;
    uint16_t            m_next_id;
    uint16_t            m_size;
};

struct CIdArray
{
    void clear()
    {
        m_freelist = INVALID_ID;
        m_next_id  = 0;
        m_size = 0;
        uint32_t num = m_capacity;
        Id* head = m_sparse;
        for (uint32_t i = 0; i < num; i++)
        {
            head[i].id = INVALID_ID;
        }
    }

    void init(uint32_t capacity, uint16_t object_size, Allocator* allocator)
    {
        m_alloactor = allocator;
        m_object_size = object_size;
        uint32_t memSize = sizeof(Id) + sizeof(uint16_t) * 2 + m_object_size;
        memSize *= capacity;
        char* p = (char*)allocator->allocate(memSize, 16);
        memset(p, 0x00, memSize);
        m_objects = p;
        p += m_object_size * capacity;
        m_sparse = (Id*)p;
        p += sizeof(Id) * capacity;
        m_sparse_to_dense = (uint16_t*)p;
        p += sizeof(uint16_t) * capacity;
        m_dense_to_sparse = (uint16_t*)p;
        m_capacity = capacity;
        clear();
    }

    void destroy()
    {
        m_alloactor->deallocate(m_objects);
    }

    bool has(Id id)
    {
        return id.index < m_capacity && m_sparse[id.index].id == id.id;
    }

    Id create(char** ptr)
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
        else id.index = m_size;

        m_sparse[id.index] = id;
        m_sparse_to_dense[id.index] = m_size;
        m_dense_to_sparse[m_size] = id.index;
        *ptr = get_by_index(m_size);
        m_size++;

        return id;
    }

    void destroy(Id id)
    {
        ENGINE_ASSERT_ARGS(has(id), "IdArray does not have ID: %d,%d", id.id, id.index);

        m_sparse[id.index].id = INVALID_ID;
        m_sparse[id.index].index = m_freelist;
        m_freelist = id.index;

        // Swap with last element
        const uint32_t last = m_size - 1;
        ENGINE_ASSERT(last >= m_sparse_to_dense[id.index], "Swapping with previous item");

        char* dst = get_by_index(m_sparse_to_dense[id.index]);
        char* src = get_by_index(m_objects[last]);
        memcpy(dst, src, m_object_size);

        // Update tables
        uint16_t std = m_sparse_to_dense[id.index];
        uint16_t dts = m_dense_to_sparse[last];
        m_sparse_to_dense[dts] = std;
        m_dense_to_sparse[std] = dts;
        m_size--;
    }

    char* get(Id id)
    {
        ENGINE_ASSERT_ARGS(has(id), "IdArray does not have ID: %d,%d", id.id, id.index);
        return get_by_index(m_sparse_to_dense[id.index]);
    }
    char* get_by_index(uint32_t index)
    {
        return m_objects + index * m_object_size;
    }
    uint32_t size() const { return m_size; };
    const char* begin() const { return m_objects; };
    char* begin() { return m_objects; };

    Id*                 m_sparse;
    uint16_t*           m_sparse_to_dense;
    uint16_t*           m_dense_to_sparse;
    char*               m_objects;
    uint32_t            m_capacity;
    Allocator*          m_alloactor;

    uint16_t            m_freelist;
    uint16_t            m_next_id;
    uint16_t            m_size;
    uint16_t            m_object_size;
};