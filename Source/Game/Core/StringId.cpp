#include "StringId.h"
#include "MathDefs.h"
#include "Log.h"
#include <ctype.h>
#include "Prerequisites.h"
#include <bx/hash.h>

#ifndef _RETAIL
#include "MemorySystem.h"
#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>
#include <stdio.h>
#include <fstream>
#include <bx/mutex.h>
#include <bx/string.h>
typedef tinystl::unordered_map<uint32_t, const char*> StringTable;
static StringTable              g_stringTable;
static bx::LwMutex              g_stringLock;
void insert_string_id(uint32_t key, const char* value)
{
    if(value[0] == '\0') return;
    bx::LwMutexScope _l(g_stringLock);
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
        ENGINE_ASSERT_ARGS(!bx::stricmp(value, iter->second), "hash collision [%s] != [%s]", value, iter->second);
    }
}
const char* stringid_lookup(const StringId& id)
{
    if(!id) return "";
    bx::LwMutexScope _l(g_stringLock);
    StringTable::iterator iter = g_stringTable.find(id.value());
    if(iter == g_stringTable.end()) return  0;
    return iter->second;
}
#define STRING_TABLE_FMT "%u,%x,%s\n"
void load_string_table(const char* fName)
{
    FILE* fp = fopen(fName, "r");
    if(!fp) {
        LOGW(__FUNCTION__ " can not open file %s", fName);
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
        LOGE(__FUNCTION__ " can not open file %s", fName);
        return;
    }
    TIMELOG("save string table");
    StringTable::const_iterator iter = g_stringTable.begin();
    for(; iter != g_stringTable.end(); ++iter)
    {
        fprintf(fp, STRING_TABLE_FMT, iter->first, iter->first, iter->second);
    }
    fclose(fp);
    g_stringTable.clear();
}
#else
static char g_buffer[32];
const char* stringid_lookup(const StringId& id)
{
    if(!id) return "";
    bx::snprintf(g_buffer, sizeof(g_buffer), "%x", id.value());
    return g_buffer;
}
#endif

uint32_t StringId::calculate(const char* str)
{
    uint32_t hash = 0;
    if (!str) return hash;
    hash = bx::hashMurmur2A(str, strlen(str));
#ifndef _RETAIL
    insert_string_id(hash, str);
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
    ENGINE_ASSERT(StringId::calculate(s) == value, "static_hash failed.");
    return value;
}
#endif

