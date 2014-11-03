#include "Utils.h"
#include "Engine.h"
#include "Actor.h"
#include "Level.h"
#include "Resource.h"
#include "PhysicsWorld.h"
#include "AnimationSystem.h"
#include "AnimRig.h"
#include "AnimControl.h"
#include "MathDefs.h"
//=======================================================================================
#include <Animation/Animation/Playback/hkaAnimatedSkeleton.h>
#include <Animation/Animation/hkaAnimationContainer.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredSkeleton.h>
#include <Animation/Animation/Rig/hkaSkeleton.h>
#include <Animation/Animation/Rig/hkaPose.h>
#include <Animation/Animation/Playback/Control/Default/hkaDefaultAnimationControl.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Animation/Animation/Animation/ReferencePose/hkaReferencePoseAnimation.h>
#include <Animation/Animation/Rig/hkaSkeletonUtils.h>
//=======================================================================================

enum EngineCommandId
{
    kEngineCmdLoadLevel,
    kEngineCmdUnLoadLevel,
    kEngineCmdCreateActor,
    kEngineCmdDestroyActor,
    kEngineCmdEaseIn,
    kEngineCmdEaseOut,
    kEngineCmdSetTime,
    kEngineCmdSetSpeed,
    kEngineCmdSetWeight,
    kEngineCmdEaseOutLayers,
    kEngineCmdMax
};
struct AnimCmdParams
{
    ActorId32   m_actor;
    float       m_float;
    uint8_t     m_int[4];
};
extern void* get_anim_rig(Id id);

#define GET_RIG_FROM_CMD()\
    AnimCmdParams* params = (AnimCmdParams*)cmd.m_params;\
    Actor* actor = g_actorWorld.get_actor(params->m_actor);\
    if(!actor) return;\
    AnimRigInstance* inst = (AnimRigInstance*)get_anim_rig(actor->m_components[kComponentAnimRig]);
#define GET_CONTROL_FROM_CMD()\
    GET_RIG_FROM_CMD();\
    hk_anim_ctrl* control = inst->get_control(params->m_int[0]);\
    if(!control) return;

static void on_command_load_level(const Command& cmd)
{
    StringId level_name = *((StringId*)cmd.m_params);
    Level* level = FIND_RESOURCE_NAMED(Level, level_name);
    if(level) level->load();
}
static void on_command_unload_level(const Command& cmd)
{
    StringId level_name = *((StringId*)cmd.m_params);
    Level* level = FIND_RESOURCE_NAMED(Level, level_name);
    if(level) level->unload();
}
static void on_command_create_actor(const Command& cmd)
{
    StringId actor_name = *((StringId*)cmd.m_params);
    float* transforms = (float*)(cmd.m_params + sizeof(StringId));
    hkQsTransform t;
    t.setIdentity();
    t.m_translation.set(transforms[0], transforms[1], transforms[2]);
    t.m_rotation.setFromEulerAngles(transforms[3], transforms[4], transforms[5]);
	t.m_scale.set(transforms[6], transforms[7], transforms[8]);
    g_actorWorld.create_actor(actor_name, t);
}
static void on_command_destroy_actor(const Command& cmd)
{
    g_actorWorld.destroy_actor(*(ActorId32*)(cmd.m_params));
}

static void on_command_easein_animation(const Command& cmd)
{
    GET_CONTROL_FROM_CMD();
    if(!control->m_enabled) 
    {
        inst->m_skeleton->addAnimationControl(control);
        control->m_enabled = true;
    }
    control->m_layer = params->m_int[1];
    control->set_loop(params->m_int[2]);
    control->ease_in(params->m_float, params->m_int[3]);
}
static void on_command_easeout_animation(const Command& cmd)
{
    GET_CONTROL_FROM_CMD();
    control->m_layer = params->m_int[1];
    control->ease_out(params->m_float, params->m_int[2]);
}
static void on_command_settime_animation(const Command& cmd)
{
    GET_CONTROL_FROM_CMD();
    control->setLocalTime(params->m_float);
}
static void on_command_setspeed_animation(const Command& cmd)
{
    GET_CONTROL_FROM_CMD();
    control->setPlaybackSpeed(params->m_float);
}
static void on_command_setweight_animation(const Command& cmd)
{
    GET_CONTROL_FROM_CMD();
    control->setMasterWeight(params->m_float);
}
static void on_command_easeout_layers_animation(const Command& cmd)
{
    GET_RIG_FROM_CMD();
    hkaAnimatedSkeleton* skeleton = inst->m_skeleton;
    int num = skeleton->getNumAnimationControls();
    int layer = params->m_int[0];
    int type = params->m_int[1];
    for (int i=0; i<num; ++i)
    {
        hk_anim_ctrl* ac = (hk_anim_ctrl*)skeleton->getAnimationControl(i);
        int ctrl_layer = (int)ac->m_layer;
        if(ctrl_layer != layer) continue;
        ac->ease_out(params->m_float, type);
    }
}


void init_engine_commands(CommandMachine* cmd_machine)
{
    _command_callback_ command_funcs[] =
    {
        on_command_load_level,
        on_command_unload_level,
        on_command_create_actor,
        on_command_destroy_actor,
        on_command_easein_animation,
        on_command_easeout_animation,
        on_command_settime_animation,
        on_command_setspeed_animation,
        on_command_setweight_animation,
        on_command_easeout_layers_animation,
    };
    memcpy(cmd_machine->m_callbacks, command_funcs, sizeof(command_funcs));
}


void command_load_level(const StringId& level_name, float when)
{
    Command cmd;
    *(StringId*)(cmd.m_params) = level_name;
    cmd.m_time = when;
    cmd.m_command = kEngineCmdLoadLevel;
    g_engine.m_cmd_machine->addCommand(cmd);
}

void command_unload_level(const StringId& level_name, float when)
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kEngineCmdUnLoadLevel;
    *(StringId*)(cmd.m_params) = level_name;
    g_engine.m_cmd_machine->addCommand(cmd);
}

void command_easein_animation( ActorId32 actor, int index, float blend_time, int layer, bool bloop, int type, float when)
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kEngineCmdEaseIn;
    AnimCmdParams* params = (AnimCmdParams*)cmd.m_params;
    params->m_actor = actor;
    params->m_float = blend_time;
    params->m_int[0] = index;
    params->m_int[1] = layer;
    params->m_int[2] = bloop;
    params->m_int[3] = type;
    g_engine.m_cmd_machine->addCommand(cmd);
}

void command_easeout_animation( ActorId32 actor, int index, float blend_time, int type, float when)
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kEngineCmdEaseOut;
    AnimCmdParams* params = (AnimCmdParams*)cmd.m_params;
    params->m_actor = actor;
    params->m_float = blend_time;
    params->m_int[0] = index;
    params->m_int[1] = type;
    g_engine.m_cmd_machine->addCommand(cmd);
}

void command_easeout_layers( ActorId32 actor, int layer, float blend_time, int type, float when)
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kEngineCmdEaseOutLayers;
    AnimCmdParams* params = (AnimCmdParams*)cmd.m_params;
    params->m_actor = actor;
    params->m_float = blend_time;
    params->m_int[0] = layer;
    params->m_int[1] = type;
    g_engine.m_cmd_machine->addCommand(cmd);
}

void command_set_animation_weight( ActorId32 actor, int index, float weight, float when)
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kEngineCmdSetWeight;
    AnimCmdParams* params = (AnimCmdParams*)cmd.m_params;
    params->m_actor = actor;
    params->m_float = weight;
    params->m_int[0] = index;
    g_engine.m_cmd_machine->addCommand(cmd);
}

void command_set_animation_speed( ActorId32 actor, int index, float speed, float when)
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kEngineCmdSetSpeed;
    AnimCmdParams* params = (AnimCmdParams*)cmd.m_params;
    params->m_actor = actor;
    params->m_float = speed;
    params->m_int[0] = index;
    g_engine.m_cmd_machine->addCommand(cmd);
}

void command_set_animation_time( ActorId32 actor, int index, float local_time, float when)
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kEngineCmdSetSpeed;
    AnimCmdParams* params = (AnimCmdParams*)cmd.m_params;
    params->m_actor = actor;
    params->m_float = local_time;
    params->m_int[0] = index;
    g_engine.m_cmd_machine->addCommand(cmd);
}

void command_create_actor(const StringId& type, const float* transform, float when)
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kEngineCmdCreateActor;
    char* params = cmd.m_params;
    *(StringId*)(params) = type;
    memcpy(params + sizeof(StringId), transform, sizeof(float)*9);
    g_engine.m_cmd_machine->addCommand(cmd);
}

void command_destroy_actor(ActorId32 actor, float when)
{
    Command cmd;
    cmd.m_time = when;
    cmd.m_command = kEngineCmdDestroyActor;
    char* params = cmd.m_params;
    *(ActorId32*)(params) = actor;
    g_engine.m_cmd_machine->addCommand(cmd);
}