#pragma once
#include "BaseTypes.h"
#include "StringId.h"

class hkRootLevelContainer;

int find_enum_index(const char* name, const char** enum_names);
void* load_havok_inplace(void* data, uint32_t size);
void unload_havok_inplace(void* data, uint32_t size);
void msg_box(const char* fmt, ...);
void accurate_sleep(uint32_t milliSeconds);
bool check_unique_process();

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
    uint32_t    m_size;
    uint32_t    m_value_offset;
};

struct Fact
{
    uint32_t        m_name_offset;
    uint32_t        m_key_offset;
    uint32_t        m_num_keys;
    uint32_t        m_value_offset; // default values
    uint32_t        m_value_size;

    int  get_key_index(StringId k) const;
    void get_value(StringId k, void* value_buf, void* value_out, uint32_t size) const;
    void set_value(StringId k, void* value_buf, const void* value_in, uint32_t size);
    void fill_default_values(void* value_buf);
};


struct Command
{
    float           m_time;
    uint8_t         m_command;
    char            m_params[59];
}; //-->64 byte. ---> a more elegant way ?


typedef void (*_command_callback_)(const Command& cmd);

struct CommandMachine
{
    void init(int max_commands, int max_callbacks);
    static uint32_t caculate_memory(int max_commands, int max_callbacks);

    /// Adds a command to the queue
    void addCommand( const Command& command );
    /// Advance machine to the given time.
    void update( float timestep );
    /// Flush all commands from the queue
    void flushQueue();
    /// Access the internal clock
    float getCurrentTime() const;
    /// Reset the internal clock
    void resetTime(float newTime = 0.0f);

    _command_callback_*     m_callbacks;
    Command*                m_commands;
    float                   m_currentTime;
    int                     m_numCommands;
    int                     m_maxCommands;
};


