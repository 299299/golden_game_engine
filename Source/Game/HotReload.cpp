#include "Resource.h"
#include "Log.h"
//===========================================
#include "AnimationSystem.h"
#include "PhysicsWorld.h"
#include "PhysicsAutoLock.h"
//===========================================
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
#include "AnimFSM.h"
#include "Level.h"
#include "Actor.h"
#include <bx/bx.h>
//==========================================================================================
#include <Animation/Animation/Animation/hkaAnimation.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredSkeleton.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredAnimation.h>
//==========================================================================================

static void* g_tmpResourceArray[1024*10];
const uint32_t resourceMax = BX_COUNTOF(g_tmpResourceArray);
static ResourceInfo** result = (ResourceInfo**)g_tmpResourceArray;

extern int find_component_type(const StringId& typeName);
extern uint32_t num_components(uint32_t type);
extern void* get_components(uint32_t type);

//===================================================================================================
template <typename T, typename U> void reload_component_resource(void* oldResource, void* newResource)
{
    T* oldCompResource = (T*)oldResource;
    T* newCompResource = (T*)newResource;
    int type = find_component_type(T::getType());
    uint32_t componentNum = num_components(type);
    U* components = (U*)get_components(type);
    LOGI("component %s instance num = %d", T::getName(), componentNum);
    for(size_t i=0; i<componentNum; ++i)
    {
        if(components[i].m_resource == oldCompResource)
            components[i].init(newCompResource); //---> no destroy?? may memleak
    }
}
template <typename T, typename U> void register_component_resource_reload_callback()
{
    g_resourceMgr.registerReloadCallback(T::getType(), reload_component_resource<T, U>);
}
void reload_light_resource(void* oldResource, void* newResource)
{
    LightResource* oldLight = (LightResource*)oldResource;
    LightResource* newLight = (LightResource*)newResource;
    uint32_t num = num_components(kComponentLight);
    LightInstance* lights = (LightInstance*)get_components(kComponentLight);
    for (uint32_t i=0; i<num; ++i)
    {
        LightInstance& light = lights[i];
        if(light.m_resource == oldLight)
            light.m_resource = newLight;
    }
}
//===================================================================================================


//===============================================================================
void reload_animation_resource(void* oldResource, void* newResource)
{
    Animation* oldAnimation = (Animation*)oldResource;
    Animation* newAnimation = (Animation*)newResource;

    uint32_t numOfFSM = g_resourceMgr.findResourcesTypeOf(AnimFSM::getType(), result, resourceMax);
    LOGD("total num of anim fsm resources = %d", numOfFSM);
    //holy shit, deep loop!
    for (uint32_t i=0; i<numOfFSM; ++i)
    {
        AnimFSM* fsm = (AnimFSM*)result[i]->m_ptr;
        for (uint32_t j=0; j<fsm->m_numLayers; ++j)
        {
            AnimFSMLayer& layer = fsm->m_layers[j];
            for(uint32_t k=0; k<layer.m_numStates; ++k)
            {
                State& state = layer.m_states[k];
                for (uint32_t m=0; m<state.m_numAnimations; ++m)
                {
                    if(state.m_animations[m] == oldAnimation)
                        state.m_animations[m] = newAnimation;
                }
            }
        }
        //just tell anim fsm to reload.
        reload_component_resource<AnimFSM, AnimFSMInstance>(fsm, fsm);
    }

    uint32_t numOfAnimations = g_resourceMgr.findResourcesTypeOf(Animation::getType(), result, resourceMax);
    LOGD("total num of animation resources = %d", numOfAnimations);
    for (uint32_t i = 0; i < numOfAnimations; ++i)
    {
        Animation* anim = (Animation*)result[i]->m_ptr;
        if(anim->m_mirroredFrom.isZero()) continue;
        hkaMirroredAnimation* mirrorAnim = (hkaMirroredAnimation*)anim->m_animation;
        const hkaAnimationBinding* binding = mirrorAnim->getOriginalBinding();
        if(oldAnimation->m_binding == binding)
        {
            anim->destroy();
            anim->createMirrorAnimation(newAnimation);
        }
    }
}

void reload_anim_rig_resource(void* oldResource, void* newResource)
{

}

//===============================================================================

void reload_level_resource(void* oldResource, void* newResource)
{
    Level* oldLevel = (Level*)oldResource;
    Level* newLevel = (Level*)newResource;
    oldLevel->unload();
    newLevel->load(-1);
    newLevel->flush();
}

void reload_shading_enviroment(void* oldResource, void* newResource)
{
    ShadingEnviroment* oldShading = (ShadingEnviroment*)oldResource;
    ShadingEnviroment* newShading = (ShadingEnviroment*)newResource;
    
}
void reload_material_resource(void* oldResource, void* newResource)
{
    Material* oldMat = (Material*)oldResource;
    Material* newMat = (Material*)newResource;

    uint32_t numOfModels = g_resourceMgr.findResourcesTypeOf(ModelResource::getType(), result, resourceMax);
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

    numOfModels = num_components(kComponentModel);
    ModelInstance* models = (ModelInstance*)get_components(kComponentModel);
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

    uint32_t numOfMaterials = g_resourceMgr.findResourcesTypeOf(Material::getType(), result, resourceMax);
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
        mat->bringIn();
    }
}
void reload_texture_3d_resource(void* oldResource, void* newResource)
{
    Raw3DTexture* oldTex = (Raw3DTexture*)oldResource;
    Raw3DTexture* newTex = (Raw3DTexture*)newResource;

    uint32_t numOfEnv = g_resourceMgr.findResourcesTypeOf(ShadingEnviroment::getType(), result, resourceMax);
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

    uint32_t numOfModels = g_resourceMgr.findResourcesTypeOf(ModelResource::getType(), result, resourceMax);
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
    
     uint32_t numOfMaterials = g_resourceMgr.findResourcesTypeOf(Material::getType(), result, resourceMax);
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
    
    uint32_t numOfPrograms = g_resourceMgr.findResourcesTypeOf(ShaderProgram::getType(), result, resourceMax);
    LOGD("total num of programs = %d", numOfPrograms);
    for(uint32_t i=0; i<numOfPrograms; ++i)
    {
        ShaderProgram* program = (ShaderProgram*)result[i]->m_ptr;
        if(program->m_vs == oldShader || 
           program->m_ps == oldShader)
        {
            bgfx::ProgramHandle oldHandle = program->m_handle;
            program->bringOut();
            if(program->m_vs == oldShader) program->m_vs = newShader;
            if(program->m_ps == oldShader) program->m_ps = newShader;
            program->bringIn();
            bgfx::ProgramHandle newHandle = program->m_handle;
            
            CHECK_PROGRAM_HANDLE(g_postProcess.m_brightShader);
            CHECK_PROGRAM_HANDLE(g_postProcess.m_blurShader);
            CHECK_PROGRAM_HANDLE(g_postProcess.m_combineShader);
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
                actor.init(newActor, t);
            }
        }
    }
}
//===================================================================================================


void resource_hot_reload_init()
{
    g_resourceMgr.registerReloadCallback(ShadingEnviroment::getType(), reload_shading_enviroment);
    g_resourceMgr.registerReloadCallback(Texture::getType(), reload_texture_resource);
    g_resourceMgr.registerReloadCallback(Raw3DTexture::getType(), reload_texture_3d_resource);
    g_resourceMgr.registerReloadCallback(Mesh::getType(), reload_mesh_resource);
    g_resourceMgr.registerReloadCallback(ActorResource::getType(), reload_actor_resource);
    g_resourceMgr.registerReloadCallback(Material::getType(), reload_material_resource);
    g_resourceMgr.registerReloadCallback(Shader::getType(), reload_shader_resource);
    g_resourceMgr.registerReloadCallback(ShaderProgram::getType(), reload_program_resource);
    g_resourceMgr.registerReloadCallback(Level::getType(), reload_level_resource);
    g_resourceMgr.registerReloadCallback(Animation::getType(), reload_animation_resource);
    g_resourceMgr.registerReloadCallback(AnimRig::getType(), reload_anim_rig_resource);
    g_resourceMgr.registerReloadCallback(LightResource::getType(), reload_light_resource);

    register_component_resource_reload_callback<ModelResource, ModelInstance>();
    register_component_resource_reload_callback<RagdollResource,RagdollInstance>();
    register_component_resource_reload_callback<AnimRig, AnimRigInstance>();
    register_component_resource_reload_callback<LookAtResource, LookAtInstance>();
    register_component_resource_reload_callback<ReachResource, ReachInstance>();
    register_component_resource_reload_callback<FootResource, FootInstance>();
    register_component_resource_reload_callback<PhysicsResource, PhysicsInstance>();
    register_component_resource_reload_callback<ProxyResource, ProxyInstance>();
    register_component_resource_reload_callback<AnimFSM, AnimFSMInstance>();
}


