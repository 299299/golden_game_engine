#include "Resource.h"
#include "Log.h"
#include "AnimationSystem.h"
#include "PhysicsWorld.h"
#include "PhysicsAutoLock.h"
#include "ShadingEnviroment.h"
#include "AnimRig.h"
#include "Animation.h"
#include "Graphics.h"
#include "Model.h"
#include "Shader.h"
#include "Material.h"
#include "Light.h"
#include "Mesh.h"
#include "IK.h"
#include "Texture.h"
#include "Ragdoll.h"
#include "PhysicsInstance.h"
#include "ProxyInstance.h"
#include "Level.h"
#include "RenderCamera.h"
#include "DebugDraw.h"
#include "Component.h"
#include "Actor.h"
#include "DataDef.h"

#ifdef HAVOK_COMPILE
#include <Animation/Animation/Animation/hkaAnimation.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredSkeleton.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredAnimation.h>
#endif

static void* g_tmpResourceArray[1024*10];
const uint32_t resourceMax = BX_COUNTOF(g_tmpResourceArray);
static ResourceInfo** result = (ResourceInfo**)g_tmpResourceArray;

//===================================================================================================
template <typename T, typename U> void reload_component_resource(void* oldResource, void* newResource)
{
    T* oldCompResource = (T*)oldResource;
    T* newCompResource = (T*)newResource;
    ComponentFactory* fac = g_componentMgr.find_factory(T::get_type());
    uint32_t componentNum = fac->num_components();
    U* components = (U*)fac->get_components();
    LOGI("component %s instance num = %d", T::get_name(), componentNum);
    for(size_t i=0; i<componentNum; ++i)
    {
        if(components[i].m_resource == oldCompResource)
            components[i].init(newCompResource); //---> no destroy?? may memleak
    }
}
template <typename T, typename U> void register_component_resource_reload_callback()
{
    g_resourceMgr.register_reload_callback(T::get_type(), reload_component_resource<T, U>);
}
//----------------------------------------------------------------------------------------------
template <typename T, typename U> void reload_component_resource_(void* oldResource, void* newResource)
{
    T* oldCompResource = (T*)oldResource;
    T* newCompResource = (T*)newResource;
    ComponentFactory* fac = g_componentMgr.find_factory(T::get_type());
    uint32_t componentNum = fac->num_components();
    U* components = (U*)fac->get_components();
    LOGI("component %s instance num = %d", T::get_name(), componentNum);
    for(size_t i=0; i<componentNum; ++i)
    {
        if(components[i].m_resource == oldCompResource)
        {
            components[i].destroy();
            components[i].init(newCompResource); //---> no destroy?? may memleak
        }
    }
}
template <typename T, typename U> void register_component_resource_reload_callback_()
{
    g_resourceMgr.register_reload_callback(T::get_type(), reload_component_resource_<T, U>);
}
//----------------------------------------------------------------------------------------------
void reload_light_resource(void* oldResource, void* newResource)
{
    LightResource* oldLight = (LightResource*)oldResource;
    LightResource* newLight = (LightResource*)newResource;
    ComponentFactory* fac = g_componentMgr.find_factory(LightResource::get_type());
    uint32_t num = fac->num_components();
    LightInstance* lights = (LightInstance*)fac->get_components();
    for (uint32_t i=0; i<num; ++i)
    {
        LightInstance& light = lights[i];
        if(light.m_resource == oldLight)
            light.m_resource = newLight;
    }
}
//===================================================================================================


//===============================================================================
void reload_anim_rig_resource(void* oldResource, void* newResource)
{
    AnimRig* oldCompResource = (AnimRig*)oldResource;
    AnimRig* newCompResource = (AnimRig*)newResource;
    ComponentFactory* fac = g_componentMgr.find_factory(AnimRig::get_type());
    uint32_t componentNum = fac->num_components();
    AnimRigInstance* components = (AnimRigInstance*)fac->get_components();
    LOGI("component %s instance num = %d", AnimRig::get_name(), componentNum);
    for(size_t i=0; i<componentNum; ++i)
    {
        if(components[i].m_resource == oldCompResource)
        {
            components[i].destroy();
            components[i].init(newCompResource, components[i].m_actor);
        }
    }
}

void reload_animation_resource(void* oldResource, void* newResource)
{
    Animation* oldAnimation = (Animation*)oldResource;
    Animation* newAnimation = (Animation*)newResource;

    uint32_t numOfAnimations = g_resourceMgr.find_resources_type_of(Animation::get_type(), result, resourceMax);
    LOGD("total num of animation resources = %d", numOfAnimations);
    for (uint32_t i = 0; i < numOfAnimations; ++i)
    {
        Animation* anim = (Animation*)result[i]->m_ptr;
        if(!anim->m_mirroredFrom) continue;

#ifdef HAVOK_COMPILE
        hkaMirroredAnimation* mirrorAnim = (hkaMirroredAnimation*)anim->m_animation;
        const hkaAnimationBinding* binding = mirrorAnim->getOriginalBinding();
        if(oldAnimation->m_binding == binding)
        {
            anim->destroy();
            anim->create_mirrored_animation(newAnimation);
        }
#endif
    }
}

//===============================================================================

void reload_level_resource(void* oldResource, void* newResource)
{
    Level* oldLevel = (Level*)oldResource;
    Level* newLevel = (Level*)newResource;
    oldLevel->unload();
    newLevel->load();
}

void reload_shading_enviroment(void* oldResource, void* newResource)
{
    ShadingEnviroment* oldShading = (ShadingEnviroment*)oldResource;
    ShadingEnviroment* newShading = (ShadingEnviroment*)newResource;
    if(g_actorWorld.m_shading_env == oldShading) g_actorWorld.m_shading_env = newShading;
}
void reload_material_resource(void* oldResource, void* newResource)
{
    Material* oldMat = (Material*)oldResource;
    Material* newMat = (Material*)newResource;

    uint32_t numOfModels = g_resourceMgr.find_resources_type_of(ModelResource::get_type(), result, resourceMax);
    LOGD("total num of model resources = %d", numOfModels);
    for(uint32_t i=0; i<numOfModels; ++i)
    {
        ModelResource* model = (ModelResource*)result[i]->m_ptr;
        for(uint32_t j=0; j<model->m_numMaterials; ++j)
        {
            if(model->m_materials[j] == oldMat)
            {
                model->m_materials[j] = newMat;
            }
        }
    }

    numOfModels = g_modelWorld.m_numModels;

    ComponentFactory* fac = g_componentMgr.find_factory(ModelResource::get_type());
    ModelInstance* models = (ModelInstance*)fac->get_components();
    LOGD("total num of model instances = %d", numOfModels);
    for(uint32_t i=0; i<numOfModels; ++i)
    {
        ModelInstance& model = models[i];
        for(uint32_t j=0; j<model.m_numMaterials; ++j)
        {
            if(model.m_materials[j] == oldMat)
            {
                model.m_materials[j] = newMat;
            }
        }
    }

}
void reload_texture_resource(void* oldResource, void* newResource)
{
    Texture* oldTex = (Texture*)oldResource;
    Texture* newTex = (Texture*)newResource;

    uint32_t numOfMaterials = g_resourceMgr.find_resources_type_of(Material::get_type(), result, resourceMax);
    LOGD("total num of materials = %d", numOfMaterials);
    for(uint32_t i=0; i<numOfMaterials; ++i)
    {
        Material* mat = (Material*)result[i]->m_ptr;
        for(uint32_t j=0; j<mat->m_numSamplers; ++j)
        {
            MatSampler& sampler = mat->m_samplers[j];
            if(sampler.m_texture == oldTex)
            {
                sampler.m_texture = newTex;
            }
        }
        mat->bringin();
    }
}
void reload_texture_3d_resource(void* oldResource, void* newResource)
{
    Raw3DTexture* oldTex = (Raw3DTexture*)oldResource;
    Raw3DTexture* newTex = (Raw3DTexture*)newResource;

    uint32_t numOfEnv = g_resourceMgr.find_resources_type_of(ShadingEnviroment::get_type(), result, resourceMax);
    LOGD("total num of shading enviroment = %d", numOfEnv);
    for(uint32_t i=0; i<numOfEnv; ++i)
    {
        ShadingEnviroment* env = (ShadingEnviroment*)result[i]->m_ptr;
        for (uint32_t j = 0; j < env->m_numColorgradingTextures; ++j)
        {
            if(env->m_colorGradingTextures[j] == oldTex) env->m_colorGradingTextures[j] = newTex;
        }
    }
}
void reload_mesh_resource(void* oldResource, void* newResource)
{
    Mesh* oldMesh = (Mesh*)oldResource;
    Mesh* newMesh = (Mesh*)newResource;

    uint32_t numOfModels = g_resourceMgr.find_resources_type_of(ModelResource::get_type(), result, resourceMax);
    LOGD("total num of model resources = %d", numOfModels);
    for(uint32_t i=0; i<numOfModels; ++i)
    {
        ModelResource* model = (ModelResource*)result[i]->m_ptr;
        if(model->m_mesh == oldMesh)
            model->m_mesh = newMesh;
    }
}
void reload_program_resource(void* oldResource, void* newResource)
{
#define CHECK_SHADER_HANDLE(shader)  if(shader.idx == oldHandle.idx) shader.idx = newHandle.idx;

    ShaderProgram* oldProgram = (ShaderProgram*)oldResource;
    ShaderProgram* newProgram = (ShaderProgram*)newResource;

    bgfx::ProgramHandle oldHandle = oldProgram->m_handle;
    bgfx::ProgramHandle newHandle = newProgram->m_handle;

    extern PostProcess          g_postProcess;
    CHECK_SHADER_HANDLE(g_postProcess.m_brightShader);
    CHECK_SHADER_HANDLE(g_postProcess.m_blurShader);
    CHECK_SHADER_HANDLE(g_postProcess.m_combineShader);

    uint32_t numOfMaterials = g_resourceMgr.find_resources_type_of(Material::get_type(), result, resourceMax);
    LOGD("total num of materials = %d", numOfMaterials);
    for(uint32_t i=0; i<numOfMaterials; ++i)
    {
        Material* mat = (Material*)result[i]->m_ptr;
        if(mat->m_shader == oldProgram)
            mat->m_shader = newProgram;
        if(mat->m_shadowShader == oldProgram)
            mat->m_shadowShader = newProgram;
    }
}

void reload_shader_resource(void* oldResource, void* newResource)
{
#define CHECK_PROGRAM_HANDLE(shader)  if(shader.idx == oldHandle.idx) shader.idx = newHandle.idx;

    extern PostProcess          g_postProcess;
    Shader* oldShader = (Shader*)oldResource;
    Shader* newShader = (Shader*)newResource;

    uint32_t numOfPrograms = g_resourceMgr.find_resources_type_of(ShaderProgram::get_type(), result, resourceMax);
    LOGD("total num of programs = %d", numOfPrograms);
    for(uint32_t i=0; i<numOfPrograms; ++i)
    {
        ShaderProgram* program = (ShaderProgram*)result[i]->m_ptr;
        if(program->m_vs == oldShader || program->m_ps == oldShader)
        {
            bgfx::ProgramHandle oldHandle = program->m_handle;
            program->bringout();
            if(program->m_vs == oldShader) program->m_vs = newShader;
            if(program->m_ps == oldShader) program->m_ps = newShader;
            program->bringin();
            bgfx::ProgramHandle newHandle = program->m_handle;

            CHECK_PROGRAM_HANDLE(g_postProcess.m_brightShader);
            CHECK_PROGRAM_HANDLE(g_postProcess.m_blurShader);
            CHECK_PROGRAM_HANDLE(g_postProcess.m_combineShader);
            CHECK_PROGRAM_HANDLE(g_debugDrawMgr.m_shader);
        }
    }
}

void reload_actor_resource(void* oldResource, void* newResource)
{
    ActorResource* oldActor = (ActorResource*)oldResource;
    ActorResource* newActor = (ActorResource*)newResource;

    for(uint32_t i=0; i<kActorClassNum; ++i)
    {
        Actor* actors = g_actorWorld.get_actors(i);
        uint32_t num = g_actorWorld.num_actors(i);
        for(uint32_t j=0; j<num; ++j)
        {
            Actor& actor = actors[j];
            if(actor.m_resource == oldActor)
            {
                hkQsTransform t = actor.m_transform;
                actor.destroy();
                actor.init(newActor, t, actor.m_id);
            }
        }
    }
}

//===================================================================================================


void resource_hot_reload_init()
{
    g_resourceMgr.register_reload_callback(ShadingEnviroment::get_type(), reload_shading_enviroment);
    g_resourceMgr.register_reload_callback(Texture::get_type(), reload_texture_resource);
    g_resourceMgr.register_reload_callback(Raw3DTexture::get_type(), reload_texture_3d_resource);
    g_resourceMgr.register_reload_callback(Mesh::get_type(), reload_mesh_resource);
    g_resourceMgr.register_reload_callback(ActorResource::get_type(), reload_actor_resource);
    g_resourceMgr.register_reload_callback(Material::get_type(), reload_material_resource);
    g_resourceMgr.register_reload_callback(Shader::get_type(), reload_shader_resource);
    g_resourceMgr.register_reload_callback(ShaderProgram::get_type(), reload_program_resource);
    g_resourceMgr.register_reload_callback(Level::get_type(), reload_level_resource);
    g_resourceMgr.register_reload_callback(Animation::get_type(), reload_animation_resource);
    g_resourceMgr.register_reload_callback(LightResource::get_type(), reload_light_resource);
    g_resourceMgr.register_reload_callback(AnimRig::get_type(), reload_anim_rig_resource);

    register_component_resource_reload_callback<ModelResource, ModelInstance>();
    register_component_resource_reload_callback<LookAtResource, LookAtInstance>();
    register_component_resource_reload_callback<ReachResource, ReachInstance>();

    register_component_resource_reload_callback_<RagdollResource,RagdollInstance>();
    register_component_resource_reload_callback_<FootResource, FootInstance>();
    register_component_resource_reload_callback_<PhysicsResource, PhysicsInstance>();
    register_component_resource_reload_callback_<ProxyResource, ProxyInstance>();
}


