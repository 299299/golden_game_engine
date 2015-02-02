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
#include "Actor.h"
#include "AnimationState.h"
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
//-----------------------------------------------------------------
extern void* load_resource_actor(const char*, uint32_t);
extern void  lookup_resource_actor(void*);
//-----------------------------------------------------------------
//-----------------------------------------------------------------
extern void* load_animation_state_layer(const char*, uint32_t);
extern void  lookup_animation_state_layer(void*);
//-----------------------------------------------------------------

ResourceFactory g_resourceFactories[] =
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
    {load_resource_actor, 0, lookup_resource_actor, 0, 0, ActorResource::get_name()},
    {load_animation_state_layer, 0, lookup_animation_state_layer, 0, 0, AnimationStateLayer::get_name()},
};
void regster_resource_factories()
{
    uint32_t num = BX_COUNTOF(g_resourceFactories);
    for (uint32_t i = 0; i < num; ++i)
    {
        g_resourceMgr.register_factory(g_resourceFactories[i]);
    }
}
int get_resource_order(const char* name)
{
    uint32_t num = BX_COUNTOF(g_resourceFactories);
    for (uint32_t i = 0; i < num; ++i)
    {
        if(!strcmp(g_resourceFactories[i].m_name, name))
            return i;
    }
    return -1;
}
//--------------------------------------------------------------------------
#define EXTERN_COMP_FUNCS_(comp_name)\
    extern Id       create_##comp_name(const void*, ActorId32);\
    extern void     destroy_##comp_name(Id);\
    extern void*    get_##comp_name(Id);\
    extern uint32_t num_all_##comp_name();\
    extern void*    get_all_##comp_name();

#define EXTERN_COMP_FUNCS_T(comp_name)\
    EXTERN_COMP_FUNCS_(comp_name)\
    extern void     transform_##comp_name(Id, const hkQsTransform&);

EXTERN_COMP_FUNCS_T(model);
EXTERN_COMP_FUNCS_T(light);
EXTERN_COMP_FUNCS_(anim_rig);
EXTERN_COMP_FUNCS_T(physics_object);
EXTERN_COMP_FUNCS_T(physics_proxy);
EXTERN_COMP_FUNCS_(anim_statelayer);

#define DECLARE_COMP_FUNCS_(comp_name, t_func)\
        {create_##comp_name, destroy_##comp_name, get_##comp_name, num_all_##comp_name, get_all_##comp_name, t_func, }

#define DECLARE_COMP_FUNCS_T(comp_name)\
        DECLARE_COMP_FUNCS_(comp_name, transform_##comp_name)

#define DECLARE_COMP_FUNCS(comp_name)\
        DECLARE_COMP_FUNCS_(comp_name, 0)

#include "Component.h"

void register_components()
{
    ComponentFactory g_compFactories[] =
    {
        DECLARE_COMP_FUNCS_T(model),
        DECLARE_COMP_FUNCS_T(light),
        DECLARE_COMP_FUNCS(anim_rig),
        DECLARE_COMP_FUNCS_T(physics_object),
        DECLARE_COMP_FUNCS_T(physics_proxy),
        DECLARE_COMP_FUNCS(anim_statelayer),
    };

    StringId g_compNames[] =
    {
        ModelResource::get_type(),
        LightResource::get_type(),
        AnimRig::get_type(),
        PhysicsResource::get_type(),
        ProxyResource::get_type(),
    };

    ENGINE_ASSERT(BX_COUNTOF(g_compFactories) == BX_COUNTOF(g_compNames), "COMPONENT REGISTER ERR");
    uint32_t num = BX_COUNTOF(g_compFactories);
    for (uint32_t i=0; i<num; ++i)
    {
        g_componentMgr.register_factory(g_compFactories[i], g_compNames[i]);
    }
}