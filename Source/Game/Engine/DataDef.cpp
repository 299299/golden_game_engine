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


const char* g_defaultTextureNames[] =
{
    "core/common/default_diffuse",
    "core/common/default_normal",
    "core/common/default_specular",
    "",
    "",
    "",
    0
};


const char* g_lightTypeNames[] =
{
    "directional",
    "spot",
    "point",
    0
};


const char* g_beatTypeNames[] =
{
    "left_foot_down",
    "right_foot_down",
    0,
};

const char* g_matFlagNames[] =
{
    "skinning",
    "alpha_mask",
    "rim_color",
    "translucency",
    "opacity",
    0
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
    "mag-point",
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
    "uniform-1i", "uniform-1f", "end", "uniform-1iv",
    "uniform-1fv", "uniform-2fv", "uniform-3fv", "uniform-4fv",
    "uniform-3x3fv", "uniform-4x4fv", 0,
};
uint8_t g_uniformNums[] =
{
    1, 1, 0, 1, 1, 2, 3, 4, 3*3, 4*4, 0
};


const char* g_actorClassNames[] =
{
    "level_geometry",
    "prop",
    "character",
    0
};

const char* g_viewGroupNames[] =
{
    "shadow",
    "background",
    "scene",
    "debug",
    "bright",
    0
};

const char* g_modelFlagNames[] =
{
    "invisible",
    "transform_dirty",
    "no_shadow",
    0,
};

const char*   physics_type_names[] =
{
    "rigidbody",
    "ragdoll",
    "trigger",
    "complex",
    0
};

const char* movement_names[] =
{
    "move_by_velociy",
    "move_by_animation",
    "move_by_velociy_and_animation",
    0
};

//======================================================
// RESOURCES
#include "Texture.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "Light.h"
#include "Animation.h"
#include "AnimRig.h"
#include "PhysicsInstance.h"
#include "ProxyInstance.h"
#include "PhysicsWorld.h"
#include "Material.h"
#include "IK.h"
#include "Ragdoll.h"
#include "ShadingEnviroment.h"
#include "Level.h"
//-----------------------------------------------------------------
extern void* load_resource_texture(const char*, uint32_t);
extern void  bringout_resource_texture(void*);
//-----------------------------------------------------------------
extern void* load_resource_texture2d(const char*, uint32_t);
extern void  bringin_resource_texture2d(void*);
extern void  bringout_resource_texture2d(void*);
//-----------------------------------------------------------------
extern void* load_resource_texture3d(const char*, uint32_t);
extern void  bringin_resource_texture3d(void*);
extern void  bringout_resource_texture3d(void*);
//-----------------------------------------------------------------
extern void* load_resource_mesh(const char*, uint32_t);
extern void  bringin_resource_mesh(void*);
extern void  bringout_resource_mesh(void*);
//-----------------------------------------------------------------
extern void* load_resource_shader(const char*, uint32_t);
extern void bringin_resource_shader(void*);
extern void bringout_resource_shader(void*);
//-----------------------------------------------------------------
extern void lookup_resource_shader_program(void*);
extern void bringin_resource_shader_program(void*);
extern void bringout_resource_shader_program(void*);
//-----------------------------------------------------------------
extern void* load_resource_animation(const char*, uint32_t);
extern void  destroy_resource_animation(void *);
extern void  lookup_resource_animation(void *);
//-----------------------------------------------------------------
extern void* load_resource_anim_rig(const char*, uint32_t);
extern void  lookup_resource_anim_rig(void*);
extern void  destroy_resource_anim_rig(void *);
//-----------------------------------------------------------------
extern void* load_resource_material(const char*, uint32_t);
extern void  lookup_resource_material(void*);
extern void  bringin_resource_material(void*);
//-----------------------------------------------------------------
extern void  lookup_resource_model( void* );
//-----------------------------------------------------------------
extern void* load_resource_physics( const char*, uint32_t );
extern void  destroy_resource_physics( void* );
//-----------------------------------------------------------------
extern void* load_resource_proxy( const char*, uint32_t);
extern void  destroy_resource_proxy( void * );
//-----------------------------------------------------------------
extern void* load_resource_ragdoll( const char*, uint32_t );
extern void  destroy_resource_ragdoll(void*);
//-----------------------------------------------------------------
extern void  lookup_resource_lookat_ik(void*);
extern void  lookup_resource_reach_ik(void*);
extern void  lookup_resource_foot_ik(void*);
//-----------------------------------------------------------------
extern void  lookup_resource_shading_enviroment( void* );
//-----------------------------------------------------------------
extern void* load_resource_level(const char*, uint32_t);
extern void  lookup_resource_level(void*);
//-----------------------------------------------------------------

static ResourceFactory g_resourceFactories[] =
{
    {load_resource_texture, 0, 0, 0, bringout_resource_texture, Texture::get_name()},
    {load_resource_texture2d, 0, 0, bringin_resource_texture2d, bringout_resource_texture2d, Raw2DTexture::get_name()},
    {load_resource_texture3d, 0, 0, bringin_resource_texture3d, bringout_resource_texture3d, Raw3DTexture::get_name()},
    {load_resource_mesh, 0, 0, bringin_resource_mesh, bringout_resource_mesh, Mesh::get_name()},
    {load_resource_shader, 0, 0, bringin_resource_shader, bringout_resource_shader, Shader::get_name()},
    {0, 0, lookup_resource_shader_program, bringin_resource_shader_program, bringout_resource_shader_program, ShaderProgram::get_name()},
    {load_resource_animation, destroy_resource_animation, lookup_resource_animation, 0, 0, Animation::get_name()},
    {load_resource_anim_rig, destroy_resource_anim_rig, lookup_resource_anim_rig, 0, 0, AnimRig::get_name()},
    {load_resource_material, 0, lookup_resource_material, bringin_resource_material, 0, Material::get_name()},
    {0, 0, 0, 0, 0, LightResource::get_name()},
    {0, 0, lookup_resource_model, 0, 0, ModelResource::get_name()},
    {0, 0, 0, 0, 0, PhysicsConfig::get_name()},
    {load_resource_physics, destroy_resource_physics, 0, 0, 0, PhysicsResource::get_name()},
    {load_resource_proxy, destroy_resource_proxy, 0, 0, 0, ProxyResource::get_name()},
    {load_resource_ragdoll, destroy_resource_ragdoll, 0, 0, 0, RagdollResource::get_name()},
    {0, 0, lookup_resource_lookat_ik, 0, 0, LookAtResource::get_name()},
    {0, 0, lookup_resource_reach_ik, 0, 0, ReachResource::get_name()},
    {0, 0, lookup_resource_foot_ik, 0, 0, FootResource::get_name()},
    {0, 0, lookup_resource_shading_enviroment, 0, 0, ShadingEnviroment::get_name()},
    {load_resource_level, 0, lookup_resource_level, 0, 0, Level::get_name()},
};
void regster_resource_factories()
{
    uint32_t num = BX_COUNTOF(g_resourceFactories);
    for (uint32_t i = 0; i < num; ++i)
    {
        g_resourceMgr.register_factory(g_resourceFactories[i]);
    }
}
int get_resource_order(const StringId& type)
{
    uint32_t num = BX_COUNTOF(g_resourceFactories);
    for (uint32_t i = 0; i < num; ++i)
    {
        if(type == StringId(g_resourceFactories[i].m_name))
            return i;
    }
    return -1;
}