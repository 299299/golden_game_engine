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
    "value", "lerp", "additive", "select", 0
};

namespace EngineNames
{
    const char* ANIMATION = "animation";
    const char* ANIMATION_STATES = "states";
    const char* MESH = "mesh";
    const char* MATERIAL = "material";
    const char* TEXTURE = "texture";
    const char* TEXTURE_3D = "tex_3d";
    const char* ANIMATION_RIG = "rig";
    const char* SHADER = "shader";
    const char* PROGRAM = "program";
    const char* SHADING_ENV = "shading_env";
    const char* PHYSICS_CONFIG = "physics_config";
    const char* MODEL = "model";
    const char* LIGHT = "light";
    const char* ACTOR = "actor";
    const char* LEVEL = "level";
};

namespace EngineTypes
{
    StringId ANIMATION = 0;
    StringId ANIMATION_STATES = 0;
    StringId MESH = 0;
    StringId MATERIAL = 0;
    StringId TEXTURE = 0;
    StringId TEXTURE_2D = 0;
    StringId TEXTURE_3D = 0;
    StringId ANIMATION_RIG = 0;
    StringId SHADER = 0;
    StringId PROGRAM = 0;
    StringId SHADING_ENV = 0;
    StringId PHYSICS_CONFIG = 0;
    StringId MODEL = 0;
    StringId LIGHT = 0;
    StringId ACTOR = 0;
    StringId LEVEL = 0;
};


#define INIT_ENGINE_TYPE(NAME) EngineTypes::NAME = stringid_caculate(EngineNames::NAME);

void init_engine_type_names()
{
    INIT_ENGINE_TYPE(ANIMATION);
    INIT_ENGINE_TYPE(ANIMATION_STATES);
    INIT_ENGINE_TYPE(MESH);
    INIT_ENGINE_TYPE(MATERIAL);
    INIT_ENGINE_TYPE(TEXTURE);
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