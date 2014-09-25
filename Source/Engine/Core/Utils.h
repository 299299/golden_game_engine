#pragma once
#include "BaseTypes.h"
#include "StringId.h"

class hkRootLevelContainer;

int find_enum_index(const char* name, const char** enum_names);
void* load_havok_inplace(void* data, uint32_t size);
void unload_havok_inplace(void* data, uint32_t size);

#define INI_MAX_KEY_VALUE   (128)
struct IniReader
{
    struct IniKeyValue
    {
        const char* m_key;
        const char* m_value;
        uint32_t    m_keyLen;
        uint32_t    m_valueLen;
    };

    IniKeyValue     m_values[INI_MAX_KEY_VALUE];
    const char*     m_data;
    uint32_t        m_dataSize;
    uint32_t        m_numKeys;

    IniReader(const char* fileName);
    ~IniReader();
    uint32_t find_value(const char* key, char* bufOut) const;
};


struct ValueType
{
    enum Enum
    {
        INT,
        FLOAT,
        STRING,
        FLOAT4,
        UNKNOW,
    };
};

struct Key
{
    StringId    m_name;
    uint32_t    m_type;
    uint32_t    m_offset;
};

struct Fact
{
    Key*            m_keys;
    uint32_t        m_num_keys;
    char*           m_values; //--> default values
    uint32_t        m_value_size;

    uint32_t value_type(const StringId& k) const;
    bool has_key(const StringId& k) const;
    bool get_key(const StringId& k, Key& out_k) const;
    bool get_key(char* values, const StringId& k, int& v);
    bool get_key(char* values, const StringId& k, float& v) const;
    bool get_key(char* values, const StringId& k, StringId& v) const;
    bool get_key(char* values, const StringId& k, float* v) const;
    bool set_key(char* values, const StringId& k, int v) const;
    bool set_key(char* values, const StringId& k, float v) const;
    bool set_key(char* values, const StringId& k, const StringId& v) const;
    bool set_key(char* values, const StringId& k, const float* v) const;
};