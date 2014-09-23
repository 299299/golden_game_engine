#include "Utils.h"
#include "Log.h"
#include <Windows.h>
#include <io.h>
#include "Prerequisites.h"
//================================================================
#include <Common/Base/System/Io/Reader/hkStreamReader.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Serialize/Util/hkNativePackfileUtils.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Serialize/Util/hkStructureLayout.h>
#include <Common/Serialize/Util/hkSerializeUtil.h>
#include <Animation/Animation/hkaAnimationContainer.h>
#include <Physics2012/Utilities/Serialize/hkpPhysicsData.h>
//================================================================

int find_enum_index(const char* name, const char** enum_names)
{
    const char** enumPtr = enum_names;
    int tmpIndex = 0;
    int retValue = -1;
    while (*enumPtr)
    {
        if (strcmp(*enumPtr, name) == 0)
        {
            retValue = tmpIndex;
            break;
        }
        ++tmpIndex;
        ++enumPtr;
    }
    return retValue;
}

void* load_havok_inplace(void* data, uint32_t size)
{
    const char* loadError = 0;
    void* ret = hkNativePackfileUtils::loadInPlace(data, size, 0, &loadError);
    if(!ret) LOGE(loadError);
    return ret;
}

void unload_havok_inplace(void* data, uint32_t size)
{
    hkNativePackfileUtils::unloadInPlace(data, size);
}

IniReader::IniReader( const char* fileName )
{
    memset(this, 0x00 ,sizeof(IniReader));
    FILE* fp = fopen(fileName, "r");
    if(!fp) return;
    fseek(fp, 0L, SEEK_END);
    m_dataSize = ftell(fp);
    fseek(fp, 0L, SEEK_SET);
    m_data = new char[m_dataSize];
    fread((void*)m_data, m_dataSize, 1, fp);
    fclose(fp);
    const char* p = m_data;
    const char* end = m_data + m_dataSize;
    IniKeyValue data;
    data.m_key = m_data;
    while(p != end)
    {
        if(*p == '=')
        {
            data.m_keyLen = p - data.m_key;
            data.m_value = p + 1;
        }
        else if(*p == '\n')
        {
            data.m_valueLen = p - data.m_value;
            m_values[m_numKeys++] = data;
            data.m_key = p + 1;
        }
    }
}

IniReader::~IniReader()
{
    delete []m_data;
}

uint32_t IniReader::find_value( const char* key, char* bufOut ) const
{
    for (uint32_t i=0; i<m_numKeys;++i)
    {
        const IniKeyValue& data = m_values[i];
        if(!strncmp(data.m_key, key, data.m_keyLen))
        {
            strncpy(bufOut, data.m_value, data.m_valueLen);
            return data.m_valueLen;
        }
    }
    return 0;
}
