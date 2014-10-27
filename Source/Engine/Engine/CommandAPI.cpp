#include "Utils.h"
#include "Actor.h"
#include "Level.h"
#include "PhysicsWorld.h"
#include "AnimationSystem.h"

enum EngineCommandId
{
    kEngineCmdLoadLevel,
    kEngineCmdUnLoadLevel,
};

static void on_command_load_level(const Command& cmd, void* context)
{
    StringId level_name = *((StringId*)cmd.m_params);
    Level* level = FIND_RESOURCE(Level, StringId(level_name));
    if(level) level->load();
}
static void on_command_unload_level(const Command& cmd, void* context)
{
    StringId level_name = *((StringId*)cmd.m_params);
    Level* level = FIND_RESOURCE(Level, StringId(level_name));
    if(level) level->unload();
}

void init_engine_commands(CommandMachine* cmd_machine)
{

}


void command_load_level(const StringId& level_name, float when)
{
    
}

void command_unload_level(const StringId& level_name, float when)
{
    
}
