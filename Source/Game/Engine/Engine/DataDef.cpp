#include "DataDef.h"
#include "Resource.h"
#include <stdint.h>
#include <bx/bx.h>
#include <bgfx.h>

const char*  g_textureNames[] =
{
    "u_texColor",
    "u_texNormal",
    "u_texSpecular",
    "u_texRelfection",
    "u_texEmissive",
    "u_texLightmap",
    "u_texBlendNormalMask",
    "u_texIBL",
    "u_shadowMap",
    "u_texReflectionMask",
    "u_texAndirMap",
    "u_texThickness",
    0
};

const char* g_humanBodyNames[] =
{
    "head",
    "neck",
    "left_shoulder",
    "left_arm",
    "left_fore_arm",
    "left_hand",
    "right_shoulder",
    "right_arm",
    "right_fore_arm",
    "right_hand",
    "hip",
    "left_up_leg",
    "left_leg",
    "left_foot",
    "right_up_leg",
    "right_leg",
    "right_foot",
    0
};

const char* g_lightTypeNames[] =
{
    "directional", "spot", "point", 0
};

const char* g_matFlagNames[] =
{
    "skinning", "alpha_mask", "rim_color", "translucency", "opacity", 0
};

const char* g_textureFlagNames[] =
{
    "u_mirror",
    "u_clamp",
    "v_mirror",
    "v_clamp",
    "w_mirror",
    "w_clamp",
    "min_point",
    "min_anisotropic",
    "mag_point",
    "mag_anisotropic",
    "min_point",
    0
};
uint32_t g_textureFlags[] =
{
    BGFX_TEXTURE_U_MIRROR, BGFX_TEXTURE_U_CLAMP,
    BGFX_TEXTURE_V_MIRROR, BGFX_TEXTURE_V_CLAMP,
    BGFX_TEXTURE_W_MIRROR, BGFX_TEXTURE_W_CLAMP,
    BGFX_TEXTURE_MIN_POINT,BGFX_TEXTURE_MIN_ANISOTROPIC,
    BGFX_TEXTURE_MAG_POINT,BGFX_TEXTURE_MAG_ANISOTROPIC,
    BGFX_TEXTURE_MIP_POINT,
};
uint32_t g_textureFlagNum = BX_COUNTOF(g_textureFlags);
 const char* g_uniformNames[] =
{
    "uniform_1i", "uniform_1f", "end", "uniform_1iv",
    "uniform_1fv", "uniform_2fv", "uniform_3fv", "uniform_4fv",
    "uniform_3x3fv", "uniform_4x4fv", 0,
};
uint8_t g_uniformNums[] =
{
    1, 1, 0, 1, 1, 2, 3, 4, 3*3, 4*4, 0
};


const char* g_actorClassNames[] =
{
    "level_geometry", "prop", "character", 0
};

const char* g_viewGroupNames[] =
{
    "shadow", "background", "scene", "debug", "bright", 0
};

const char* g_modelFlagNames[] =
{
    "invisible", "transform_dirty", "no_shadow", 0,
};

const char*   physics_type_names[] =
{
    "rigidbody", "ragdoll", "trigger", "complex", 0
};

const char* g_anim_ease_type_names[] =
{
  "smooth","linear", "fast", 0
};

const char* g_anim_motion_blending_type_names[] =
{
    "default",
    "ignore_src_rotation",
    "ignore_dst_rotation",
    "ignore_src_motion",
    "ignore_dst_motion",
    0
};

const char* g_anim_node_names[] =
{
    "value", "lerp", "additive", 0
};

EngineNames::ANIMATION = "animation";
EngineNames::ANIMATION_STATES = "states";
EngineNames::MESH = "mesh";
EngineNames::MATERIAL = "material";
EngineNames::TEXTURE = "texture";
EngineNames::TEXTURE_2D = "tex_2d";
EngineNames::TEXTURE_3D = "tex_3d";
EngineNames::ANIMATION_RIG = "rig";
EngineNames::SHADER = "shader";
EngineNames::PROGRAM = "program";
EngineNames::SHADING_ENV = "shading_env";
EngineNames::PHYSICS_CONFIG = "physics_config";
EngineNames::MODEL = "model";
EngineNames::LIGHT = "light";
EngineNames::ACTOR = "actor";
EngineNames::LEVEL = "level";

EngineTypes::ANIMATION = 0;
EngineTypes::ANIMATION_STATES = 0;
EngineTypes::MESH = 0;
EngineTypes::MATERIAL = 0;
EngineTypes::TEXTURE = 0;
EngineTypes::TEXTURE_2D = 0;
EngineTypes::TEXTURE_3D = 0;
EngineTypes::ANIMATION_RIG = 0;
EngineTypes::SHADER = 0;
EngineTypes::PROGRAM = 0;
EngineTypes::SHADING_ENV = 0;
EngineTypes::PHYSICS_CONFIG = 0;
EngineTypes::MODEL = 0;
EngineTypes::LIGHT = 0;
EngineTypes::ACTOR = 0;
EngineTypes::LEVEL = 0;

#define INIT_ENGINE_TYPE(_name) EngineTypes::##_name = stringid_caculate(EngineNames::##_name);

void init_engine_type_names()
{
    INIT_ENGINE_TYPE(ANIMATION);
    INIT_ENGINE_TYPE(ANIMATION_STATES);
    INIT_ENGINE_TYPE(MESH);
    INIT_ENGINE_TYPE(MATERIAL);
    INIT_ENGINE_TYPE(TEXTURE);
    INIT_ENGINE_TYPE(TEXTURE_2D);
    INIT_ENGINE_TYPE(TEXTURE_3D);
    INIT_ENGINE_TYPE(ANIMATION_RIG);
    INIT_ENGINE_TYPE(SHADER);
    INIT_ENGINE_TYPE(PROGRAM);
    INIT_ENGINE_TYPE(SHADING_ENV);
    INIT_ENGINE_TYPE(PHYSICS_CONFIG);
    INIT_ENGINE_TYPE(MODEL);
    INIT_ENGINE_TYPE(LIGHT);
    INIT_ENGINE_TYPE(ACTOR);
    INIT_ENGINE_TYPE(LEVEL);
}