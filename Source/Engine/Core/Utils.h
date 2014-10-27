#pragma once
#include "BaseTypes.h"
#include "StringId.h"

class hkRootLevelContainer;

int find_enum_index(const char* name, const char** enum_names);
void* load_havok_inplace(void* data, uint32_t size);
void unload_havok_inplace(void* data, uint32_t size);
void msg_box(const char* text, const char* title);
void accurate_sleep(uint32_t milliSeconds);

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
    bool get_key(char* values, const StringId& k, int& v) const;
    bool get_key(char* values, const StringId& k, float& v) const;
    bool get_key(char* values, const StringId& k, StringId& v) const;
    bool get_key(char* values, const StringId& k, float* v) const;
    bool set_key(char* values, const StringId& k, int v) const;
    bool set_key(char* values, const StringId& k, float v) const;
    bool set_key(char* values, const StringId& k, const StringId& v) const;
    bool set_key(char* values, const StringId& k, const float* v) const;
};


struct Command
{
    float           m_time;
    uint8_t         m_command;
    char            m_params[27];
}; //-->32 byte.

#define MAX_CMD_CALLBACK	(32)
typedef void (*_command_callback_)(const Command& cmd);

struct CommandMachine
{
    void init(int max_commands);
    static uint32_t caculate_memory(int max_commands);
    
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
    
	_command_callback_		m_callbacks[MAX_CMD_CALLBACK];
    Command*                m_commands;
    float                   m_currentTime;
    int                     m_numCommands;
    int                     m_maxCommands;
};


