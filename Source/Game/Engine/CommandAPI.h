#pragma once
#include "Prerequisites.h"

void command_chang_gamestate(const char* name, float when = 0.0f);
//-------------------------------------------------------
// LEVEL API
void command_load_level(const StringId& level_name, float when = 0.0f);
void command_unload_level(const StringId& level_name, float when = 0.0f);
//-------------------------------------------------------

//-------------------------------------------------------
// ANIMATION API
void command_easein_animation(ActorId32 actor, int index, float blend_time, int layer, bool bloop, int type = kEaseCurveSmooth, float when = 0.0f);
void command_easeout_animation(ActorId32 actor, int index, float blend_time, int type = kEaseCurveSmooth, float when = 0.0f);
void command_easeout_layers(ActorId32 actor, int layer, float blend_time, int type = kEaseCurveSmooth, float when = 0.0f);
void command_set_animation_weight(ActorId32 actor, int index, float weight, float when = 0.0f);
void command_set_animation_speed(ActorId32 actor, int index, float speed, float when = 0.0f);
void command_set_animation_time(ActorId32 actor, int index, float local_time, float when = 0.0f);

//-------------------------------------------------------
// ACTOR API
void command_create_actor(const StringId& type, const float* transform, float when = 0.0f);
void command_destroy_actor(ActorId32 actor, float when = 0.0f);