#pragma once
#include "BaseTypes.h"

struct StringId
{
    StringId();
    explicit StringId(uint32_t value);
    explicit StringId(const char* stringValue);

    inline uint32_t value() const { return m_value; };
    inline bool isZero() const { return (m_value == 0); };
    inline bool operator == (const StringId& rhs) const { return m_value == rhs.m_value; }
    inline bool operator != (const StringId& rhs) const { return m_value != rhs.m_value; }
    inline bool operator < (const StringId& rhs) const { return m_value < rhs.m_value; }
    inline bool operator > (const StringId& rhs) const { return m_value > rhs.m_value; }

    uint32_t           m_value;

    static StringId ZERO;
    static uint32_t calculate(const char* str);
};


#ifdef _DEBUG
    uint32_t static_hash(const char* s, uint32_t value);
#else
    #define  static_hash(s, v) (v)
#endif

const char* stringid_lookup(const StringId& id);
#ifndef _RETAIL
void load_string_table(const char* fName);
void save_string_table(const char* fName);
#endif
