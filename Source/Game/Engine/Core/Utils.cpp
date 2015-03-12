#include "Utils.h"
#include "Log.h"
#include "Prerequisites.h"
#include "MemorySystem.h"
#include "Profiler.h"
#include <bx/timer.h>
#include <bx/fpumath.h>
#include <bx/string.h>
#ifdef HAVOK_COMPILE
#include <Common/Base/System/Io/Reader/hkStreamReader.h>
#include <Common/Base/System/Io/IStream/hkIStream.h>
#include <Common/Serialize/Util/hkNativePackfileUtils.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Serialize/Util/hkStructureLayout.h>
#include <Common/Serialize/Util/hkSerializeUtil.h>
#include <Animation/Animation/hkaAnimationContainer.h>
#include <Physics2012/Utilities/Serialize/hkpPhysicsData.h>
#include <Windows.h>
#endif

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
#ifdef HAVOK_COMPILE
    const char* loadError = 0;
    void* ret = hkNativePackfileUtils::loadInPlace(data, size, 0, &loadError);
    if(!ret) LOGE(loadError);
    return ret;
#else
    return 0;
#endif
}

void unload_havok_inplace(void* data, uint32_t size)
{
#ifdef HAVOK_COMPILE
    hkNativePackfileUtils::unloadInPlace(data, size);
#endif
}

void msg_box( const char* fmt, ... )
{
    char buf[256];
    va_list argp;
    va_start(argp, fmt);
    vsnprintf(buf, sizeof(buf), fmt, argp);
    va_end(argp);
#ifdef HAVOK_COMPILE
    ::MessageBoxA(NULL, buf, "NagaGAME", MB_TOPMOST);
#else
    printf("console msg-box [%s][%s]\n", buf, "NagaGAME");
    printf("msg_box --> press any key:");
    getchar();
#endif
}

bool check_unique_process()
{
#ifdef HAVOK_COMPILE
    #define MUTEX_NAME     ("Global//NAGA_ENGINE_GAME_SINGLE_MUTEX")
    HANDLE hMutex = CreateMutexA(NULL, FALSE, MUTEX_NAME);
    if (GetLastError() == ERROR_ALREADY_EXISTS)
    {
        ::CloseHandle(hMutex);
        return false;
    }
#endif
    return true;
}

int Fact::get_key_index(StringId k) const
{
    uint32_t num = m_num_keys;
    StringId* head = (StringId*)((char*)this + m_name_offset);
    FIND_IN_ARRAY_RET(head, num, k);
}

void Fact::get_value(StringId k, void* value_buf, void* value_out, uint32_t size) const
{
    int index = get_key_index(k);
    if(index < 0)
        return;

    Key* key = (Key*)((char*)this + m_key_offset) + index;
    ENGINE_ASSERT_ARGS(key->m_size == size, "%s key size %d != %d", __FUNCTION__, key->m_size, size);
    memcpy(value_out, (char*)value_buf + key->m_value_offset, size);
}

void Fact::set_value(StringId k, void* value_buf, const void* value_in, uint32_t size)
{
    int index = get_key_index(k);
    if(index < 0)
        return;

    Key* key = (Key*)((char*)this + m_key_offset) + index;
    ENGINE_ASSERT_ARGS(key->m_size == size, "%s key size %d != %d", __FUNCTION__, key->m_size, size);
    memcpy((char*)value_buf + key->m_value_offset, value_in, size);
}

void Fact::fill_default_values(void* value_buf) const
{
    memcpy(value_buf, (const char*)this + m_value_offset, m_value_size);
}

uint32_t Fact::get_memory_size() const
{ 
    return sizeof(Fact) + sizeof(StringId) * m_num_keys + sizeof(Key) * m_num_keys + m_value_size;
}

void CommandMachine::init(int max_commands, int max_callbacks)
{
    char* p_this = (char*)this;
    m_callbacks = (_command_callback_*)(p_this + sizeof(CommandMachine));
    m_commands = (Command*)(p_this + + sizeof(CommandMachine) + sizeof(_command_callback_) * max_callbacks);
    m_maxCommands = max_commands;
}

uint32_t CommandMachine::caculate_memory(int max_commands, int max_callbacks)
{
    return sizeof(CommandMachine) + sizeof(_command_callback_) * max_callbacks + max_commands * sizeof(Command);
}

void CommandMachine::addCommand( const Command& command )
{
    ENGINE_ASSERT(m_numCommands < m_maxCommands - 1, "Command Machine overflow.");

    // Set the global time for the command
    Command gCmd = command;
    gCmd.m_time += m_currentTime;

    int idx = 0;
    int num = m_numCommands;
    while( (idx < num) && (gCmd.m_time >= m_commands[idx].m_time) )
    {
        idx++;
    }

    if (idx == m_numCommands)
    {
        m_commands[m_numCommands++] = gCmd;
    }
    else
    {
        for (int i = m_numCommands; i > idx; --i)
        {
           m_commands[i] = m_commands[i-1];
        }
        m_commands[idx] = gCmd;
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
    int num = m_numCommands;
    Command* head = m_commands;
    for (int i=0; i< num; ++i)
    {
        head[i].m_time += diffTime;
    }
    m_currentTime = newTime;
}

void CommandMachine::update( float timestep )
{
    PROFILE(CommandMachine_Update);
    const float endTime = m_currentTime + timestep;
    int idx = 0;
    int num = m_numCommands;
    Command* head = m_commands;
    for (; idx < num; ++idx)
    {
        const Command& cmd = head[idx];
        float cmdTime = cmd.m_time;
        if(cmdTime > endTime) break;
        _command_callback_ func = m_callbacks[cmd.m_command];
        func(cmd);
        m_currentTime = bx::fmax(m_currentTime, cmd.m_time);
    }
    m_currentTime = endTime;
    if(idx == 0) return;

    int num_cmd_left = num - idx;
    for (int i = 0; i < num_cmd_left; ++i)
    {
        head[i] = head[idx+i];
    }
    m_numCommands = num_cmd_left;
}

void engine_assertion( const char *file, int line, const char *expression, bool result )
{

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