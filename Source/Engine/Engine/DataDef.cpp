#include "DataDef.h"
#include "Resource.h"
#include <stdint.h>
#include <bx/bx.h>
#include <bgfx/bgfx.h>

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
    "rigidbody_only", 
    "ragdoll", 
    "trigger", 
    "complex", 
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
#include "AnimFSM.h"
#include "PhysicsInstance.h"
#include "ProxyInstance.h"
#include "PhysicsWorld.h"
#include "Material.h"
#include "IK.h"
#include "Ragdoll.h"
#include "ShadingEnviroment.h"
#include "Level.h"
#include "Actor.h"
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
extern void  destroy_resource_anim_rig(void *);
//-----------------------------------------------------------------
extern void* load_resource_anim_fsm(const char*, uint32_t);
extern void  lookup_resource_anim_fsm(void*);
//-----------------------------------------------------------------
extern void* load_resource_material(const char*, uint32_t);
extern void  lookup_resource_material(void*);
extern void  bringin_resource_material(void*);
//-----------------------------------------------------------------
extern void* load_resource_model(const char*, uint32_t);
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
extern void* load_resource_actor(const char*, uint32_t);
extern void  lookup_resource_actor(void*);
//-----------------------------------------------------------------
extern void* load_resource_level(const char*, uint32_t);
extern void  lookup_resource_level(void*);
//-----------------------------------------------------------------
static ResourceFactory g_resourceFactories[] = 
{
    {load_resource_texture, 0, 0, 0, bringout_resource_texture, Texture::getName()},
    {load_resource_texture2d, 0, 0, bringin_resource_texture2d, bringout_resource_texture2d, Raw2DTexture::getName()},
    {load_resource_texture3d, 0, 0, bringin_resource_texture3d, bringout_resource_texture3d, Raw3DTexture::getName()},
    {load_resource_mesh, 0, 0, bringin_resource_mesh, bringout_resource_mesh, Mesh::getName()},
    {load_resource_shader, 0, 0, bringin_resource_shader, bringout_resource_shader, Shader::getName()},
    {0, 0, lookup_resource_shader_program, bringin_resource_shader_program, bringout_resource_shader_program, ShaderProgram::getName()},
    {load_resource_animation, destroy_resource_animation, lookup_resource_animation, 0, 0, Animation::getName()},
    {load_resource_anim_rig, destroy_resource_anim_rig, 0, 0, 0, AnimRig::getName()},
    {load_resource_anim_fsm, 0, lookup_resource_anim_fsm, 0, 0, AnimFSM::getName()},
    {load_resource_material, 0, lookup_resource_material, bringin_resource_material, 0, Material::getName()},
    {0, 0, 0, 0, 0, LightResource::getName()},
    {load_resource_model, 0, lookup_resource_model, 0, 0, ModelResource::getName()},
    {0, 0, 0, 0, 0, PhysicsConfig::getName()},
    {load_resource_physics, destroy_resource_physics, 0, 0, 0, PhysicsResource::getName()},
    {load_resource_proxy, destroy_resource_proxy, 0, 0, 0, ProxyResource::getName()},
    {load_resource_ragdoll, destroy_resource_ragdoll, 0, 0, 0, RagdollResource::getName()},
    {0, 0, lookup_resource_lookat_ik, 0, 0, LookAtResource::getName()},
    {0, 0, lookup_resource_reach_ik, 0, 0, ReachResource::getName()},
    {0, 0, lookup_resource_foot_ik, 0, 0, FootResource::getName()},
    {0, 0, lookup_resource_shading_enviroment, 0, 0, ShadingEnviroment::getName()},
    {load_resource_actor, 0, lookup_resource_actor, 0, 0, ActorResource::getName()},
    {load_resource_level, 0, lookup_resource_level, 0, 0, Level::getName()},
};
void regster_resource_factories()
{
    for (uint32_t i = 0; i < BX_COUNTOF(g_resourceFactories); ++i)
    {
        g_resourceMgr.registerFactory(g_resourceFactories[i]);
    }
}
int get_resource_order(const StringId& type)
{
    for (uint32_t i = 0; i < BX_COUNTOF(g_resourceFactories); ++i)
    {
        if(type == StringId(g_resourceFactories[i].m_name))
            return i;
    }
    return -1;
}
//-----------------------------------------------------------------
extern Id       create_render_model(const void*);
extern void     destroy_render_model(Id);
extern void*    get_render_model(Id);
extern uint32_t num_render_models();
extern void*    get_render_models();
//-----------------------------------------------------------------
extern Id       create_render_light(const void*);
extern void     destroy_render_light(Id);
extern void*    get_render_light(Id);
extern uint32_t num_render_lights();
extern void*    get_render_lights();
//-----------------------------------------------------------------
extern Id       create_anim_rig(const void*);
extern void     destroy_anim_rig(Id);
extern void*    get_anim_rig(Id);
extern uint32_t num_anim_rigs();
extern void*    get_anim_rigs();
//-----------------------------------------------------------------
extern Id       create_anim_fsm(const void*);
extern void     destroy_anim_fsm(Id);
extern void*    get_anim_fsm(Id);
extern uint32_t num_anim_fsms();
extern void*    get_anim_fsms();
//-----------------------------------------------------------------
extern Id       create_physics_object(const void*);
extern void     destroy_physics_object(Id);
extern void*    get_physics_object(Id);
extern uint32_t num_physics_objects();
extern void*    get_physics_objects();
//-----------------------------------------------------------------
extern Id       create_physics_proxy(const void*);
extern void     destroy_physics_proxy(Id);
extern void*    get_physics_proxy(Id);
extern uint32_t num_physics_proxies();
extern void*    get_physics_proxies();
//-----------------------------------------------------------------
struct ComponentFactory
{
    Id          (*create)(const void*);
    void        (*destroy)(Id);
    void*       (*get)(Id);
    uint32_t    (*get_num)();
    void*       (*get_total)();
};
static ComponentFactory g_componentFactories[] =
{
    create_render_model, destroy_render_model, get_render_model, num_render_models, get_render_models,
    create_render_light, destroy_render_light, get_render_light, num_render_lights, get_render_lights,
    create_anim_rig, destroy_anim_rig, get_anim_rig, num_anim_rigs, get_anim_rigs,
    create_anim_fsm, destroy_anim_fsm, get_anim_fsm, num_anim_fsms, get_anim_fsms,
    create_physics_object, destroy_physics_object, get_physics_object, num_physics_objects, get_physics_objects,
    create_physics_proxy, destroy_physics_proxy, get_physics_proxy, num_physics_proxies, get_physics_proxies,
};
StringId g_componentTypes[kComponentTypeNum];
const char* g_componentTypeNames[kComponentTypeNum];

Id create_componet(uint32_t type, const void* resource)
{
    return g_componentFactories[type].create(resource);
}
void destroy_component(uint32_t type, Id id)
{
    g_componentFactories[type].destroy(id);
}
void* get_component(uint32_t type, Id id)
{
    return g_componentFactories[type].get(id);
}
uint32_t num_components(uint32_t type)
{
    return g_componentFactories[type].get_num();
}
void* get_components(uint32_t type)
{
    return g_componentFactories[type].get_total();
}
void init_component_names()
{
    g_componentTypeNames[kComponentModel] = ModelResource::getName();
    g_componentTypes[kComponentModel] = ModelResource::getType();

    g_componentTypeNames[kComponentLight] = LightResource::getName();
    g_componentTypes[kComponentLight] = LightResource::getType();

    g_componentTypeNames[kComponentPhysics] = PhysicsResource::getName();
    g_componentTypes[kComponentPhysics] = PhysicsResource::getType();

    g_componentTypeNames[kComponentProxy] = ProxyResource::getName();
    g_componentTypes[kComponentProxy] = ProxyResource::getType();

    g_componentTypeNames[kComponentAnimRig] = AnimRig::getName();
    g_componentTypes[kComponentAnimRig] = AnimRig::getType();

    g_componentTypeNames[kComponentAnimFSM] = AnimFSM::getName();
    g_componentTypes[kComponentAnimFSM] = AnimFSM::getType();
};
int find_component_type(const StringId& typeName)
{
    for (int i=0; i<kComponentTypeNum; ++i)
    {
        if(g_componentTypes[i] == typeName)
            return i;
    }
    return -1;
}
//-----------------------------------------------------------------