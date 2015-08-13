#include "Utils.h"
#include "Log.h"
#include "Prerequisites.h"
#include "MemorySystem.h"
#include "Profiler.h"
#include <stdio.h>
#include <stdlib.h>
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
    ENGINE_ASSERT(key->m_size == size, "%s key size %d != %d", __FUNCTION__, key->m_size, size);
    memcpy(value_out, (char*)value_buf + key->m_value_offset, size);
}

void Fact::set_value(StringId k, void* value_buf, const void* value_in, uint32_t size)
{
    int index = get_key_index(k);
    if(index < 0)
        return;

    Key* key = (Key*)((char*)this + m_key_offset) + index;
    ENGINE_ASSERT(key->m_size == size, "%s key size %d != %d", __FUNCTION__, key->m_size, size);
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

#ifdef  WIN32
#include <dbghelp.h>
#include <windows.h>
void stacktrace()
{
    SymInitialize(GetCurrentProcess(), NULL, TRUE);
    SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
    DWORD mtype;
    CONTEXT ctx;
    ZeroMemory(&ctx, sizeof(CONTEXT));
    ctx.ContextFlags = CONTEXT_CONTROL;
    RtlCaptureContext(&ctx);

    STACKFRAME64 stack;
    ZeroMemory(&stack, sizeof(STACKFRAME64));
#ifdef _M_IX86
    mtype = IMAGE_FILE_MACHINE_I386;
    stack.AddrPC.Offset = ctx.Eip;
    stack.AddrPC.Mode = AddrModeFlat;
    stack.AddrFrame.Offset = ctx.Ebp;
    stack.AddrFrame.Mode = AddrModeFlat;
    stack.AddrStack.Offset = ctx.Esp;
    stack.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
    mtype = IMAGE_FILE_MACHINE_AMD64;
    stack.AddrPC.Offset = ctx.Rip;
    stack.AddrPC.Mode = AddrModeFlat;
    stack.AddrFrame.Offset = ctx.Rsp;
    stack.AddrFrame.Mode = AddrModeFlat;
    stack.AddrStack.Offset = ctx.Rsp;
    stack.AddrStack.Mode = AddrModeFlat;
#endif

    DWORD ldsp = 0;
    IMAGEHLP_LINE64 line;
    ZeroMemory(&line, sizeof(IMAGEHLP_LINE64));
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

    char buf[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
    PSYMBOL_INFO sym = (PSYMBOL_INFO)buf;
    sym->SizeOfStruct = sizeof(SYMBOL_INFO);
    sym->MaxNameLen = MAX_SYM_NAME;

    UINT num = 0;
    while (StackWalk64(mtype,
        GetCurrentProcess(),
        GetCurrentThread(),
        &stack,
        &ctx,
        NULL,
        SymFunctionTableAccess64,
        SymGetModuleBase64,
        NULL))
    {

        if (stack.AddrPC.Offset == 0)
            break;

        ++num;
        BOOL res = SymGetLineFromAddr64(GetCurrentProcess(), stack.AddrPC.Offset, &ldsp, &line) &&
            SymFromAddr(GetCurrentProcess(), stack.AddrPC.Offset, 0, sym);

        if (res)
        {
            LOGE("\t[%i] %s (%s:%d)\n", num, sym->Name, line.FileName, line.LineNumber);
        }
        else
        {
            LOGE("\t[%i] 0x%p\n", num, stack.AddrPC.Offset);
        }
    }

    SymCleanup(GetCurrentProcess());
}
#else
#include <cxxabi.h>
#include <execinfo.h>
static void stacktrace()
{
    void* array[50];
    int size = backtrace(array, 50);

    char** messages = backtrace_symbols(array, size);

    // skip first stack frame (points here)
    for (int i = 1; i < size && messages != NULL; ++i)
    {
        char *mangled_name = 0, *offset_begin = 0, *offset_end = 0;

        // find parantheses and +address offset surrounding mangled name
        for (char *p = messages[i]; *p; ++p)
        {
            if (*p == '(')
            {
                mangled_name = p;
            }
            else if (*p == '+')
            {
                offset_begin = p;
            }
            else if (*p == ')')
            {
                offset_end = p;
                break;
            }
        }

        // if the line could be processed, attempt to demangle the symbol
        if (mangled_name && offset_begin && offset_end && mangled_name < offset_begin)
        {
            *mangled_name++ = '\0';
            *offset_begin++ = '\0';
            *offset_end++ = '\0';

            int status;
            char* real_name = abi::__cxa_demangle(mangled_name, 0, 0, &status);

            LOGE("\t[%d] %s: (%s)+%s %s\n", i, messages[i], (status == 0 ? real_name : mangled_name), offset_begin, offset_end);
            free(real_name);
        }
        // otherwise, print the whole line
        else
        {
            LOGE("\t[%d] %s\n", i, messages[i]);
        }
    }
    free(messages);
}
#endif


void error_abort(const char* file, int line, const char* message, ...)
{
    va_list ap;
    va_start(ap, message);
    vprintf(message, ap);
    va_end(ap);

    char buf[2048];
    bx::snprintf(buf, sizeof(buf), "\tIn: %s:%d\n", file, line);
    msg_box(buf);
    LOGE(buf);

    LOGE("Stacktrace:\n");
    stacktrace();
    exit(EXIT_FAILURE);
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