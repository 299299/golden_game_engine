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
static void insert_string_id(uint32_t key, const char* value, uint32_t len)
{
    if(value[0] == '\0') return;
    bx::LwMutexScope _l(g_stringLock);
    StringTable::iterator iter = g_stringTable.find(key);
    if(iter == g_stringTable.end())
    {
        char* mem = DEBUG_ALLOC(char, len+1);
        memcpy(mem, value, len);
        mem[len] = '\0';
        g_stringTable[key] = mem;
    }
    else {
        const char* second = iter->second;
        ENGINE_ASSERT_ARGS(!bx::stricmp(value, second), "hash collision [%s] != [%s]", value, second);
    }
}
const char* stringid_lookup(StringId id)
{
    if(!id) return "";
    bx::LwMutexScope _l(g_stringLock);
    StringTable::iterator iter = g_stringTable.find(id);
    if(iter == g_stringTable.end()) 
        return  0;
    return iter->second;
}
#define STRING_TABLE_FMT "%u,%d,%s\n"
void load_string_table(const char* fName)
{
    FILE* fp = fopen(fName, "r");
    if(!fp) {
        LOGW("%s can not open file %s", BX_FUNCTION, fName);
        return;
    }
    TIMELOG("load string table");
    char buf[256];
    uint32_t key1, key2 = 0;
    while(!feof(fp))
    {
        int argNum = fscanf(fp, STRING_TABLE_FMT, &key1, &key2, buf);
        if(argNum != 3) break;
        insert_string_id(key1, buf, key2);
    }
    fclose(fp);
}
void save_string_table(const char* fName)
{
    FILE* fp = fopen(fName, "w");
    if(!fp) {
        LOGE("%s can not open file %s", BX_FUNCTION, fName);
        return;
    }
    TIMELOG("save string table");
    StringTable::const_iterator iter = g_stringTable.begin();
    for(; iter != g_stringTable.end(); ++iter)
    {
        fprintf(fp, STRING_TABLE_FMT, iter->first, strlen(iter->second), iter->second);
    }
    fclose(fp);
    g_stringTable.clear();
}
#else
static char g_buffer[32];
const char* stringid_lookup(StringId id)
{
    if(!id) return "";
    bx::snprintf(g_buffer, sizeof(g_buffer), "%x", id);
    return g_buffer;
}
#endif

StringId stringid_caculate(const char* _str)
{
    return stringid_caculate(_str, strlen(_str));
}

StringId stringid_caculate(const char* _str, uint32_t _len)
{
    uint32_t hash = 0;
    if (!_str) return hash;
    hash = bx::hashMurmur2A(_str, _len);
#ifndef _RETAIL
    insert_string_id(hash, _str, _len);
#endif
    return hash;
}