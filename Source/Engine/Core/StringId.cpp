#include "StringId.h"
#include "MathDefs.h"
#include "Prerequisites.h"
#include "Log.h"
#include <ctype.h>

#ifndef _RETAIL
#include "MemorySystem.h"
#include <bx/tinystl/allocator.h>
#include <bx/tinystl/unordered_map.h>
#include <stdio.h>
#include <fstream>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
typedef tinystl::unordered_map<uint32_t, const char*> StringTable;
static StringTable              g_stringTable;
static hkCriticalSection        g_stringTableCS;
void insert_string_id(uint32_t key, const char* value)
{
    if(value[0] == '\0') return;
    hkCriticalSectionLock _l(&g_stringTableCS);
    StringTable::iterator iter = g_stringTable.find(key);
    if(iter == g_stringTable.end())
    {
        uint32_t strLen = strlen(value);
        char* mem = DEBUG_ALLOC(char, strLen+1);
        memcpy(mem, value, strLen);
        mem[strLen+1] = '\0';
        g_stringTable[key] = mem;
    }
    else {
        if(strcmp(value, iter->second))
        {
            LOGE("hash string collision %s --- %s", value, iter->second);
            HK_ASSERT(0, 0);
        }
    }
}
#endif

uint32_t StringId::calculate(const char* str)
{
    uint32_t hash = 0;
    if (!str)
        return hash;

#ifndef _RETAIL
    const char* p = str;
#endif

    while (*str)
    {
        // Perform the actual hashing as case-insensitive
        char c = *str;
        hash = SDBMHash(hash, tolower(c));
        ++str;
    }

#ifndef _RETAIL
    insert_string_id(hash, p);
#endif   
    
    return hash;
}


StringId StringId::ZERO;
StringId::StringId()
    :m_value(0)
{

}

StringId::StringId(uint32_t value)
    :m_value(value)
{

}

StringId::StringId(const char* stringValue)
    :m_value(calculate(stringValue))
{

}

#ifdef _DEBUG
uint32_t static_hash(const char* s, uint32_t value)
{
    HK_ASSERT(0, StringId::calculate(s) == value);
    return value;
}
#endif

#ifndef _RETAIL
const char* stringid_lookup(const StringId& id)
{
    if(id.isZero()) return "";
    hkCriticalSectionLock _l(&g_stringTableCS);
    StringTable::iterator iter = g_stringTable.find(id.value());
    if(iter == g_stringTable.end()) return  0;
    return iter->second;
}
#define STRING_TABLE_FMT "%u,%x,%s\n"
void load_string_table(const char* fName)
{
    FILE* fp = fopen(fName, "r");
    if(!fp) {
        LOGW(__FUNCTION__ "can not open file %s", fName);
        return;
    }
    TIMELOG("load string table");
    char buf[256];
    uint32_t key1, key2 = 0;
    while(!feof(fp))
    {    
        int argNum = fscanf(fp, STRING_TABLE_FMT, &key1, &key2, buf);
        if(argNum != 3) break;
        if(key1 != key2) break;
        insert_string_id(key1, buf);
    }
    fclose(fp);
}
void save_string_table(const char* fName)
{
    FILE* fp = fopen(fName, "w");
    if(!fp) {
        LOGE(__FUNCTION__ "can not open file %s", fName);
        return;
    }
    
    StringTable::const_iterator iter = g_stringTable.begin();
    for(; iter != g_stringTable.end(); ++iter)
    {
        uint32_t key = iter->first;
        const std::string& value = iter->second;
        fprintf(fp, STRING_TABLE_FMT, key, key, value.c_str());
    }
    
    fclose(fp);
}
#else
static char g_buffer[32];
const char* stringid_lookup(const StringId& id)
{
    if(id.isZero()) return "";
    sprintf_s(g_buffer, "%x", id.value());
    return g_buffer;
}
#endif

