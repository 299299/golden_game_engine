#pragma once

struct Variant
{
    enum Type
    {
        TYPE_INTEGER,
        TYPE_FLOAT,
        TYPE_BOOL,
        TYPE_STRING_ID,
        TYPE_COUNT // number of unique types
    };
    Type            m_type;
    union 
    {
        float       m_float;
        int         m_int;
        uint32_t    m_uint;
        bool        m_bool;
    };
};

struct NamedVariant
{
    StringId                m_name;
    Variant                 m_variant;
};
