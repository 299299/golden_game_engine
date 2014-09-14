#pragma once
#include "Prerequisites.h"
#include "Log.h"

template<typename T>
struct DynamicObjectArray
{
    T*                                  m_objects;
    Index*                              m_indices;
    unsigned                            m_num_objects;
    unsigned                            m_capacity;
    uint16_t                            m_freelist_enqueue;
    uint16_t                            m_freelist_dequeue;

    inline void setCapacity(uint16_t cap)
    {
        m_capacity = cap;
    }

    inline unsigned getRequireMem() const
    {
        return (sizeof(Index) + sizeof(T))* m_capacity;
    }

    inline void init(char* p)
    {
        m_indices = (Index*)p;
        m_num_objects = m_freelist_enqueue = m_freelist_dequeue = 0;

        for (unsigned i=0; i<m_capacity; ++i) {
            m_indices[i].m_id = i;
            m_indices[i].m_next = i+1;
        }
        p += m_capacity * sizeof(Index);
        m_objects = (T*)p;
        //check boundary
        HK_ASSERT(0, (((char*)m_objects + sizeof(T)*m_capacity) == ((char*)m_indices + getRequireMem())));
    }

    inline bool has(ID id) const {
        Index &in = m_indices[id & INDEX_MASK];
        return in.m_id == id && in.m_index != INVALID_U16;
    }
    
    inline T& lookup(ID id) {
        return m_objects[m_indices[id & INDEX_MASK].m_index];
    }
    
    inline ID add() {
        Index &in = m_indices[m_freelist_dequeue];
        m_freelist_dequeue = in.m_next;
        in.m_id += NEW_OBJECT_ID_ADD;
        in.m_index = m_num_objects++;
        HK_ASSERT(0, m_num_objects < m_capacity);
        T &o = m_objects[in.m_index];
        o.m_id = in.m_id;
        return o.m_id;
    }

    inline T& addObject() {
        Index &in = m_indices[m_freelist_dequeue];
        m_freelist_dequeue = in.m_next;
        in.m_id += NEW_OBJECT_ID_ADD;
        in.m_index = m_num_objects++;
        HK_ASSERT(0, m_num_objects < m_capacity);
        T &o = m_objects[in.m_index];
        o.m_id = in.m_id;
        return o; 
    }

    inline void remove(ID id) {
        Index &in = m_indices[id & INDEX_MASK];
        T &o = m_objects[in.m_index];
        o = m_objects[--m_num_objects];
        m_indices[o.m_id & INDEX_MASK].m_index = in.m_index;
        in.m_index = INVALID_U16;
        m_indices[m_freelist_enqueue].m_next = id & INDEX_MASK;
        m_freelist_enqueue = id & INDEX_MASK;
    }

    inline unsigned getSize() const { return m_num_objects; }
    inline T&       operator[] (unsigned i)  { return m_objects[i]; };
    inline T*       begin()   { return m_objects;};
    inline void     clear()   
    {
        m_num_objects = 0;
        m_freelist_dequeue = 0;
        m_freelist_enqueue = m_capacity-1;
    };
};

#define INIT_STATIC_POOL(array, num)\
        { array.setCapacity(num); char* p = STATIC_ALLOC(char, array.getRequireMem()); array.init(p);}


struct MemoryBuffer
{
    char*                   m_buffer;
    size_t                  m_size;
    bool                    m_used;
    char                    m_padding[3];

    char* allocBuffer(size_t size)
    {
        HK_ASSERT2(0, !m_used, "memory buffer used!!!");
        m_used = true;
        if(m_size >= size)
            return m_buffer;
        _aligned_free(m_buffer);
        m_buffer = (char*)_aligned_malloc(size, 16);
        m_size = size;
        return m_buffer;
    }

    bool  freeBuffer(char* p)
    {
        if(p != m_buffer)
            return false;
        m_used = false;
        return true;
    }

    void  destroy()
    {
        _aligned_free(m_buffer);
        m_buffer = 0;
    }
};



struct RingMemBuffer
{
    char*           m_ringMemHead;
    char*           m_ringMemTail;
    char*           m_ringMemCur;
    
    void init(char* head, uint32_t size)
    {
        m_ringMemHead = head;
        m_ringMemCur = m_ringMemHead;
        m_ringMemTail = m_ringMemHead + size;
    }
    
    char* alloc(int size)
    {
        HK_ASSERT(0, size < (m_ringMemTail - m_ringMemHead));
        int memLeft = m_ringMemCur - m_ringMemHead;
        //if not enough space left, I dont have another idea for handle this.
        //just start from 0.
        if(memLeft < size)
        {
            m_ringMemCur = m_ringMemHead + size;
            return m_ringMemHead;
        }
        else {
            char* p = m_ringMemCur;
            m_ringMemCur += size;
            return p;
        }
    }
};


// given a 4 byte aligned pointer (as typically returned by new)
// round it up to align and store the offset just before the
// returned pointer.
inline void* memoryRoundUp(void* pvoid, int align, int size)
{
    HK_ASSERT2(0x60cf3558,  (reinterpret_cast<int>(pvoid) & 0x3) == 0, "Pointer was not 4 byte aligned");
    int* p = reinterpret_cast<int*>(pvoid);
    char* aligned = reinterpret_cast<char*>(HK_NEXT_MULTIPLE_OF( align, reinterpret_cast<int>(p+1)) );
    int offset = (int)( aligned - reinterpret_cast<char*>(p) );
    reinterpret_cast<int*>(aligned)[-1] = offset;
    return aligned;
}
// given a pointer from hkMemoryRoundUp, recover the original pointer.
inline void* memoryRoundDown(void* p)
{
    int offset = reinterpret_cast<int*>(p)[-1];
    return static_cast<char*>(p) - offset;
}
inline uint32_t memAlignedSize(uint32_t size, uint32_t alignment)
{
    size = HK_NEXT_MULTIPLE_OF(4, size);
    size += alignment;
    return size;
}

class Allocator
{
public:
    Allocator(const char* name) : m_name(name) {};
    ~Allocator() {};
    virtual void* alloc(uint32_t size, uint32_t alignment = 16) = 0;
    virtual void  free(void* p) = 0;
    virtual void  free(void* p, uint32_t numBytes) {};
    virtual void  clear() {};
    virtual void  dump() const {};
    virtual void  check() const {};

    virtual uint32_t allocedSize() const  = 0;
    const char* getName() const { return m_name; };
protected:
    const char*         m_name;
};

class MallocAllocator : public Allocator
{
public:
    MallocAllocator(const char* name) : Allocator(name),m_allocCount(0),m_freeCount(0) {};

    virtual void* alloc(uint32_t size, uint32_t alignment = 16)
    {
        size += alignment;
        void* p = ::malloc(size);
        m_alreadyAlloced += size;
        ++m_allocCount;
        return (char*)memoryRoundUp(p, alignment, size);
    }
    
    virtual uint32_t allocedSize() const  { return m_alreadyAlloced; }

    virtual void free(void* p) 
    {
        ++m_freeCount;
        ::free(memoryRoundDown(p));
    }

    virtual void  free(void* p, uint32_t numBytes)
    {
        ++m_freeCount;
        uint32_t nAllocated = numBytes + reinterpret_cast<uint32_t*>(p)[-1];
        m_alreadyAlloced -= nAllocated;
        ::free(memoryRoundDown(p));
    }

    virtual void dump() const
    {
        LOGI("%s allocated = %u[B],%u[KB] alloc-num=%u, free-num=%u", 
            m_name, m_alreadyAlloced, m_alreadyAlloced/1024, m_allocCount, m_freeCount);
    }

    virtual void  check() const
    {
        if(m_freeCount < m_allocCount)
        {
            LOGE("%s mem leaked !!! alloc-num=%d, free-num=%d", getName(), m_allocCount, m_freeCount);
        }
    }

    uint32_t            m_alreadyAlloced;
    uint32_t            m_allocCount;
    uint32_t            m_freeCount;
};

class LinearAllocator : public Allocator
{
    char*               m_pBase;
    char*               m_pOffset;
    uint32_t            m_capacity;
    uint32_t            m_alreadyAlloced;
    uint32_t            m_lastAlloced;
    uint32_t            m_allocCount;

public:
    LinearAllocator(const char* name, char* mem, uint32_t capacity)
    :Allocator(name)
    ,m_pBase(mem)
    ,m_pOffset(mem)
    ,m_capacity(capacity)
    ,m_alreadyAlloced(0)
    ,m_lastAlloced(0)
    ,m_allocCount(0)
    {

    }


    virtual void* alloc(uint32_t size, uint32_t alignment = 16)
    {
        char* p = m_pOffset;
        size = memAlignedSize(size, alignment);
        m_pOffset += size;
        m_alreadyAlloced += size;
        m_lastAlloced = m_alreadyAlloced;
        HK_ASSERT(0, m_alreadyAlloced < m_capacity);
        //LOGD("%s ALLOC SIZE=%d, ALLOCED=%d, LEFT=%d", getName(), size, m_alreadyAlloced, m_capacity - m_alreadyAlloced);
        return memoryRoundUp(p, alignment, size);
    }
    
    virtual void clear()
    {
        m_pOffset = m_pBase;
        m_lastAlloced = m_alreadyAlloced;
        m_alreadyAlloced = 0;
    }

    virtual uint32_t allocedSize() const { return m_lastAlloced; }
    virtual void free(void*) {};

    virtual void dump() const
    {
        LOGI("%s allocated = %u[B],%u[KB] alloc-num=%d", m_name, m_lastAlloced, m_lastAlloced/1024, m_allocCount);
    }
};


