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
    "left-shoulder", 
    "left-arm", 
    "left-fore-arm",
    "left-hand",
    "right-shoulder", 
    "right-arm", 
    "right-fore-arm",
    "right-hand",
    "hip",
    "left-up-leg", 
    "left-leg", 
    "left-foot",
    "right-up-leg", 
    "right-leg", 
    "right-foot", 
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
    "directional", "spot", "point", 0
};


const char* g_beatTypeNames[] =
{
    "left-foot-down", "right-foot-down", 0,
};

const char* g_matFlagNames[] = 
{
    "skinning", "alpha-mask", "rim-color", "translucency", "opacity", 0
};

const char* g_textureFlagNames[] = 
{
    "u-mirror","u-clamp","v-mirror","v-clamp","w-mirror","w-clamp",
    "min-point","min-anisotropic","mag-point","mag-anisotropic", "min-point", 0
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


const char* g_entityClassNames[] =
{
    "level-geometry",
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
    "transform-dirty",
    "no-shadow",
    0,
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
#include "Entity.h"
#include "ShadingEnviroment.h"
#include "Level.h"
//======================================================
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
    {load_resource_physics_config, 0, 0, 0, 0, PhysicsConfig::getName()},
    {load_resource_physics, destroy_resource_physics, 0, 0, 0, PhysicsResource::getName()},
    {load_resource_proxy, destroy_resource_proxy, 0, 0, 0, ProxyResource::getName()},
    {load_resource_ragdoll, destroy_resource_ragdoll, 0, 0, 0, RagdollResource::getName()},
    {0, 0, lookup_resource_lookat_ik, 0, 0, LookAtResource::getName()},
    {0, 0, lookup_resource_reach_ik, 0, 0, ReachResource::getName()},
    {0, 0, lookup_resource_foot_ik, 0, 0, FootResource::getName()},
    {load_resource_entity, 0, lookup_resource_entity, 0, 0, EntityResource::getName()},
    {0, 0, lookup_resource_shading_enviroment, 0, 0, ShadingEnviroment::getName()},
    {load_resource_level, 0, lookup_resource_level, 0, 0, Level::getName()},
};
void registerResourceFactories()
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