#ifndef _RETAIL
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
#include "FileWatcher.h"
#include "ToolUtils.h"

#ifdef HAVOK_COMPILE
#include <Animation/Animation/Animation/hkaAnimation.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredSkeleton.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredAnimation.h>
#endif

#define MAX_RESOURCES_NUM 1024*10
struct HotReloadData
{
    FileWatcher         m_watcher;
    ResourceInfo**      m_results;

    void init()
    {
        m_results = (ResourceInfo**)malloc(sizeof(ResourceInfo*) * MAX_RESOURCES_NUM);
        m_watcher.start_watching("intermediate", true);
    }
    void shutdown()
    {
        free(m_results);
    }
};

HotReloadData* g_hotReload = 0;

#define FIND_RESOURCES(_type)   g_resourceMgr.find_resources_type_of(_type::get_type(), g_hotReload->m_results, MAX_RESOURCES_NUM);
#define GET_RESOURCE(_type)     (_type*)g_hotReload->m_results[i]->m_ptr;

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
void reload_physics_resource(void* oldResource, void* newResource)
{
    PhysicsResource* oldBody = (PhysicsResource*)oldResource;
    PhysicsResource* newBody = (PhysicsResource*)newResource;
    ComponentFactory* fac = g_componentMgr.find_factory(PhysicsResource::get_type());
    uint32_t num = fac->num_components();
    PhysicsInstance* bodies = (PhysicsInstance*)fac->get_components();
    for (uint32_t i=0; i<num; ++i)
    {
        PhysicsInstance& body = bodies[i];
        if(body.m_resource == oldBody)
        {
            body.destroy();
            body.init(newBody, body.m_actor);
        }
    }
}

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

    uint32_t numOfAnimations = FIND_RESOURCES(Animation);
    LOGD("total num of animation resources = %d", numOfAnimations);
    for (uint32_t i = 0; i < numOfAnimations; ++i)
    {
        Animation* anim = GET_RESOURCE(Animation);
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

    uint32_t numOfModels = FIND_RESOURCES(ModelResource);
    LOGD("total num of model resources = %d", numOfModels);
    for(uint32_t i=0; i<numOfModels; ++i)
    {
        ModelResource* model = GET_RESOURCE(ModelResource);
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

    uint32_t numOfMaterials = FIND_RESOURCES(Material);
    LOGD("total num of materials = %d", numOfMaterials);
    for(uint32_t i=0; i<numOfMaterials; ++i)
    {
        Material* mat = GET_RESOURCE(Material);
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

    uint32_t numOfEnv = FIND_RESOURCES(ShadingEnviroment);
    LOGD("total num of shading enviroment = %d", numOfEnv);
    for(uint32_t i=0; i<numOfEnv; ++i)
    {
        ShadingEnviroment* env = GET_RESOURCE(ShadingEnviroment);
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

    uint32_t numOfModels = FIND_RESOURCES(ModelResource);
    LOGD("total num of model resources = %d", numOfModels);
    for(uint32_t i=0; i<numOfModels; ++i)
    {
        ModelResource* model = GET_RESOURCE(ModelResource);
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

    uint32_t numOfMaterials = FIND_RESOURCES(Material);
    LOGD("total num of materials = %d", numOfMaterials);
    for(uint32_t i=0; i<numOfMaterials; ++i)
    {
        Material* mat = GET_RESOURCE(Material);
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

    uint32_t numOfPrograms = FIND_RESOURCES(ShaderProgram);
    LOGD("total num of programs = %d", numOfPrograms);
    for(uint32_t i=0; i<numOfPrograms; ++i)
    {
        ShaderProgram* program = GET_RESOURCE(ShaderProgram);
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
    g_resourceMgr.register_reload_callback(PhysicsResource::get_type(), reload_physics_resource);

    register_component_resource_reload_callback<ModelResource, ModelInstance>();
    register_component_resource_reload_callback<LookAtResource, LookAtInstance>();
    register_component_resource_reload_callback<ReachResource, ReachInstance>();

    register_component_resource_reload_callback_<RagdollResource,RagdollInstance>();
    register_component_resource_reload_callback_<FootResource, FootInstance>();
    register_component_resource_reload_callback_<ProxyResource, ProxyInstance>();

    g_hotReload = new HotReloadData;
    g_hotReload->init();
}

void resource_hot_reload_shutdown()
{
    g_hotReload->shutdown();
    SAFE_DELETE(g_hotReload);
}

void run_data_compile()
{
#ifdef _DEBUG
    const char* exeName = "gameDebug.exe";
#else
    const char* exeName = "gameRelease.exe";
#endif
    StringArray args;
    args.push_back("--action");
    args.push_back("DataCompile");
    args.push_back("-i");
    args.push_back("intermediate");
    args.push_back("-o");
    args.push_back("-data");
    shell_exec(exeName, args);
}

void resource_hot_reload_update(float dt)
{
    if(!g_hotReload)
        return;

    char _buf[256];
    bool _changed = g_hotReload->m_watcher.get_next_change(_buf, sizeof _buf);
    if(!_changed)
        return;

    int _dot = -1;
    int _len = strlen(_buf);
    FIND_IN_ARRAY(_buf, _len, '.', _dot);

    const char* _ext = _buf + _dot + 1;
    StringId _type = StringId(_ext);

    ResourceFactory* fac = g_resourceMgr.find_factory(_type);
    if(!fac)
    {
        LOGE("can not find any reload ext for %s type", _ext);
        return;
    }

#if 0
    char _name[256];
    memset(_name, 0, sizeof _name);
    strncpy(_name, _buf, _dot);
    g_resourceMgr.reload_resource(_type, StringId(_name), _buf);
#endif

    run_data_compile();

    std::ifstream ifs(DC_RESULT);
    if(!ifs.good())
        return;
    std::string line;
    while(std::getline(ifs, line))
    {
        std::string ext = getFileExt(line);
        std::string resourceName = get_resource_name(line);
        g_resourceMgr.reload_resource(StringId(ext.c_str()), StringId(resourceName.c_str()), line.c_str());
    }
}

#endif