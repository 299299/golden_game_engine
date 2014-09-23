#pragma once
#include "BaseTypes.h"

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
