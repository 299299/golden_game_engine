#pragma once
#include "BaseTypes.h"
#include "Assert.h"

/// Table of Ids.
///
/// @ingroup Containers
template <uint32_t MAX>
struct IdTable
{
    /// Creates the table for tracking exactly @a MAX - 1 unique Ids.
    IdTable();

    // The index of the first unused id.
    uint16_t m_freelist;

    // Next available unique id.
    uint16_t m_next_id;
    uint16_t m_size;

    // Table of ids.
    // The last valid id is reserved and cannot be used to
    // refer to Ids from the outside.
    Id m_ids[MAX];
};

/// Functions to manipulate IdTable.
///
/// @ingroup Containers
namespace id_table
{
    /// Creates a new Id in the table @a a and returns its value.
    template <uint32_t MAX> Id create(IdTable<MAX>& a);

    /// Destroys the @a id in the table @a a.
    template <uint32_t MAX> void destroy(IdTable<MAX>& a, Id id);

    /// Returns whether the table @a a has the given @a id.
    template <uint32_t MAX> bool has(const IdTable<MAX>& a, Id id);

    /// Returns the number of ids in the table @a a.
    template <uint32_t MAX> uint16_t size(const IdTable<MAX>& a);

    template <uint32_t MAX> const Id* begin(const IdTable<MAX>& a);
    template <uint32_t MAX> const Id* end(const IdTable<MAX>& a);
} // namespace id_table

namespace id_table
{
    //-----------------------------------------------------------------------------
    template <uint32_t MAX>
    inline Id create(IdTable<MAX>& a)
    {
        // Obtain a new id
        Id id;
        id.id = a.m_next_id++;

        // Recycle slot if there are any
        if (a.m_freelist != INVALID_ID)
        {
            id.index = a.m_freelist;
            a.m_freelist = a.m_ids[a.m_freelist].index;
        }
        else
        {
            id.index = a.m_size;
        }

        a.m_ids[id.index] = id;
        a.m_size++;

        return id;
    }

    //-----------------------------------------------------------------------------
    template <uint32_t MAX>
    inline void destroy(IdTable<MAX>& a, Id id)
    {
        ENGINE_ASSERT(has(a, id), "IdTable does not have ID: %d,%d", id.id, id.index);

        a.m_ids[id.index].id = INVALID_ID;
        a.m_ids[id.index].index = a.m_freelist;
        a.m_freelist = id.index;
        a.m_size--;
    }

    //-----------------------------------------------------------------------------
    template <uint32_t MAX>
    inline bool has(const IdTable<MAX>& a, Id id)
    {
        return id.index < MAX && a.m_ids[id.index].id == id.id;
    }

    //-----------------------------------------------------------------------------
    template <uint32_t MAX>
    inline uint16_t size(const IdTable<MAX>& a)
    {
        return a.m_size;
    }

    //-----------------------------------------------------------------------------
    template <uint32_t MAX>
    inline const Id* begin(const IdTable<MAX>& a)
    {
        return a.m_ids;
    }

    //-----------------------------------------------------------------------------
    template <uint32_t MAX>
    inline const Id* end(const IdTable<MAX>& a)
    {
        return a.m_ids + MAX;
    }
} // namespace id_table

//-----------------------------------------------------------------------------
template <uint32_t MAX>
inline IdTable<MAX>::IdTable()
    : m_freelist(INVALID_ID)
    , m_next_id(0)
    , m_size(0)
{
    for (uint32_t i = 0; i < MAX; i++)
    {
        m_ids[i].id = INVALID_ID;
    }
}
