#include "Utils.h"
#include "Log.h"
#include <Windows.h>
#include <io.h>
#include "Prerequisites.h"
#include "EngineAssert.h"
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

const char* g_fact_keynames[] = 
{
    "int", "float", "string", "float4", 0
};
uint32_t g_fact_valuesizes[] =
{
    sizeof(int), sizeof(float), sizeof(StringId), sizeof(float)*4, 0
};

void msg_box( const char* text, const char* title )
{
    ::MessageBoxA(NULL, text, title, MB_TOPMOST);
}

uint32_t Fact::value_type(const StringId& k) const
{
    Key key;
    if(!get_key(k, key)) return ValueType::UNKNOW;
    return key.m_type;
}

bool Fact::has_key(const StringId& k) const
{
    for(uint32_t i=0; i<m_num_keys; ++i)
    {
        if(m_keys[i].m_name == k) return true;
    }
    return false;
}

bool Fact::get_key(const StringId& k, Key& out_k) const
{
    for(uint32_t i=0; i<m_num_keys; ++i)
    {
        if(m_keys[i].m_name == k)
        {
            out_k = m_keys[i]; return true;
        }
    }
    return false;
}

bool Fact::get_key(char* values, const StringId& k, int& v) const
{
    Key key;
    bool has = get_key(k, key);
    if(!has) return false;
    v = *(int*)(values + key.m_offset);
    return has;
}

bool Fact::get_key(char* values, const StringId& k, float& v) const
{
    Key key;
    bool has = get_key(k, key);
    if(!has) return false;
    v = *(float*)(values + key.m_offset);
    return has;
}

bool Fact::get_key(char* values, const StringId& k, StringId& v) const
{
    Key key;
    bool has = get_key(k, key);
    if(!has) return false;
    v = *(StringId*)(values + key.m_offset);
    return has;
}

bool Fact::get_key(char* values, const StringId& k, float* v) const
{
    Key key;
    bool has = get_key(k, key);
    if(!has) return false;
    memcpy(v, values + key.m_offset, sizeof(float)*4);
    return has;
}

bool Fact::set_key(char* values, const StringId& k, int v) const
{
    Key key;
    if(!get_key(k, key)) return false;
    *(int*)(values + key.m_offset) = v;
    return false;
}

bool Fact::set_key(char* values, const StringId& k, float v) const
{
    Key key;
    if(!get_key(k, key)) return false;
    *(float*)(values + key.m_offset) = v;
    return true;
}

bool Fact::set_key(char* values, const StringId& k, const StringId& v) const
{
    Key key;
    if(!get_key(k, key)) return false;
    *(StringId*)(values + key.m_offset) = v;
    return true;
}

bool Fact::set_key(char* values, const StringId& k, const float* v) const
{
    Key key;
    if(!get_key(k, key)) return false;
    memcpy(values + key.m_offset, v, sizeof(float) * 4);
    return true;
}


void CommandMachine::addCommand( const Command& command )
{
    ENGINE_ASSERT(m_numCommands < MAX_COMMAND_NUM - 1, "Command Machine overflow.");

    // Set the global time for the command
    Command gCmd = command;
    gCmd.m_time += getCurrentTime();

    int idx = 0;
    while( (idx < m_numCommands) && (gCmd.m_time >= m_eventQueue[idx].m_time) )
    {
        idx++;
    }

    if (idx == m_numCommands)
    {
        m_eventQueue[m_numCommands++] = gCmd;
    }
    else
    {
        m_eventQueue.insertAt(idx, gCmd);
        for (int i = m_numCommands; i > idx; --i)
        {
           m_eventQueue[i] = m_eventQueue[i-1];
        }
        m_eventQueue[idx] = gCmd;
        ++m_numCommands;
    }
}

void CommandMachine::flushQueue()
{
    m_numCommands = 0;
}

float CommandMachine::getCurrentTime() const
{
    return m_currentTime;
}

void CommandMachine::resetTime(float newTime)
{
    float diffTime = newTime - m_currentTime;
    for (int i=0; i< m_numCommands; ++i)
    {
        m_eventQueue[i].m_time += diffTime;
    }
    m_currentTime = newTime;
}

void CommandMachine::update( float timestep )
{
    const float endTime = m_currentTime + timestep;
    int idx = 0;
    for (; idx < m_numCommands; ++idx)
    {
        Command cmd = m_eventQueue[idx];
        float cmdTime = cmd.m_time;
        if(cmdTime > endTime) break;
        _command_callback_ cb = m_commandCallbacks[cmd.m_command];
        cb(cmd, m_context);
        m_currentTime = hkMath::max2(m_currentTime, cmd.m_time);
    }
    m_currentTime = endTime;

    int num_cmd_left = m_numCommands - idx;
    for (int i = 0; i < num_cmd_left; ++i)
    {
        m_eventQueue[i] = m_eventQueue[idx+i];
    }
}


void CommandMachine::addCommandCallback(_command_callback_ cb)
{
    m_commandCallbacks[m_numCommandCallbacks++] = cb;
}

// Walk to jump with Sync.

// hkReal timeLeft = m_walkControl->getPeriod() - m_walkControl->getLocalTime();
// HK_ANIM_EVENT( NOW,              EASE_OUT,               WALK_CONTROL, timeLeft );
// HK_ANIM_EVENT( NOW,              SET_LOCAL_TIME,         JUMP_CONTROL, 0.0f );
// HK_ANIM_EVENT( NOW,              SET_PLAYBACK_SPEED,     JUMP_CONTROL, 0.0f );
// HK_ANIM_EVENT( NOW,              EASE_IN,                JUMP_CONTROL, timeLeft );
// HK_ANIM_EVENT( NOW,              CHANGE_STATE,           WALK_TO_JUMP );
// HK_ANIM_EVENT( NOW + timeLeft,   SET_PLAYBACK_SPEED,     JUMP_CONTROL, 1.0f );
// HK_ANIM_EVENT( NOW + timeLeft,   CHANGE_STATE,           JUMP );

// Straight transition

// HK_ANIM_EVENT( NOW,      EASE_OUT,     WALK_CONTROL, 0.1f )
// HK_ANIM_EVENT( NOW,      EASE_IN,      FALL_CONTROL, 0.1f )
// HK_ANIM_EVENT( NOW+0.1f, CHANGE_STATE, FALLING )

// Flushing command pipe

// HK_ANIM_EVENT( NOW, FLUSH );

// Wait for annotation event before going to idle

// hkReal eventTime = m_walkControl->getAnimation->getAnnotations()[0].m_time - m_walkControl->getLocalTime();
// hkReal loopedEventTime = (eventTime < 0.0f) ? eventTime + m_walkControl->getPeriod() : eventTime;
// HK_ANIM_EVENT(NOW, CHANGE_STATE, WAITING);
// HK_ANIM_EVENT(NOW + loopedEventTime, CHANGE_STATE, IDLE);

// Overlay a wave anim for 2 secs
// HK_ANIM_EVENT(NOW, EASE_IN, WAVE_CONTROL, 0.1f);
// HK_ANIM_EVENT(NOW+2, EASE_OUT, WAVE_CONTROL, 0.1f);