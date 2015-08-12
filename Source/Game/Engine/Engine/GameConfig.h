#pragma once
#include "BaseTypes.h"

// max components
#define MAX_PHYSICS             1024
#define MAX_PROXY               32
#define MAX_LIGHTS              64
#define MAX_MODELS              1024

#define MAX_ANIM_FSM            32
#define MAX_ANIM_RIG            32

#define MAX_LOCOMOTION          32

// max actor
#define MAX_LEVEL_GEOMETRY      512
#define MAX_PROP                128
#define MAX_CHARACTER           32

#define MAX_MATERIAL_NUM        8 // per model


#define MAX_DEBUG_LINES         1024

#define MAX_RESOURCE_TYPES      64
#define MAX_RESOURCE_PACKAGES   64


#define MAX_BLOCK_NUM           32
#define TOTAL_BLOCK_NUM         512

#define RESOURCE_MAP_NUM        16384

#define MAX_ANIM_EVENTS         1024

#define DEBUG_MEMORY_SIZE       SIZE_MB(2)
#define HAVOK_FRAMEMEMORY_SIZE  SIZE_MB(4)
#define HAVOK_MONITOR_MEM_SIZE  SIZE_MB(2)
#define FRAME_MEMORY_SIZE       SIZE_MB(5)

#define MAX_COMPONENT_TYPES     64

#define MAX_COMPONET_PER_ACTOR  16

#define MAX_RAYCAST_PERFRAME    1024