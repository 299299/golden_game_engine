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

#define FIND_RESOURCES(_type)   g_resourceMgr.find_resources_type_of(_type, g_hotReload->m_results, MAX_RESOURCES_NUM);
#define GET_RESOURCE(_type)     (_type*)g_hotReload->m_results[i]->m_ptr;

//===================================================================================================
void reload_physics_resource(void* oldResource, void* newResource)
{
#if 0
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
#endif
}

//===============================================================================
void reload_anim_rig_resource(void* oldResource, void* newResource)
{
    AnimRig* oldCompResource = (AnimRig*)oldResource;
    AnimRig* newCompResource = (AnimRig*)newResource;
    ComponentFactory* fac = g_componentMgr.find_factory(EngineTypes::ANIMATION_RIG);
    uint32_t componentNum = fac->num_components();

    AnimRigInstance* components = (AnimRigInstance*)fac->get_components();
    LOGI("component %s instance num = %d", EngineNames::ANIMATION_RIG, componentNum);
    for(size_t i=0; i<componentNum; ++i)
    {
        AnimRigInstance* rig = components + i;
        if(rig->m_resource == oldCompResource)
        {
            rig->destroy();
            rig->init(newCompResource, components[i].m_actor);
        }
    }

}

void reload_animation_resource(void* oldResource, void* newResource)
{
    Animation* oldAnimation = (Animation*)oldResource;
    Animation* newAnimation = (Animation*)newResource;

    uint32_t numOfAnimations = FIND_RESOURCES(EngineTypes::ANIMATION);
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

    uint32_t model_num = num_all_model();
    Model* models = (Model*)get_all_model();

    for(size_t i=0; i<model_num; ++i)
    {
        Model* model = models + i;
        uint32_t mat_num = model->m_numMaterials;

        for(uint32_t j=0; j<mat_num; ++j)
        {
            if(model->m_materials[j] == oldMat)
            {
                model->m_materials[j] = newMat;
            }
        }
    }
}
void reload_texture_resource(void* oldResource, void* newResource)
{
    Texture* oldTex = (Texture*)oldResource;
    Texture* newTex = (Texture*)newResource;

    uint32_t numOfMaterials = FIND_RESOURCES(EngineTypes::MATERIAL);
    LOGD("total num of materials = %d", numOfMaterials);
    for(uint32_t i=0; i<numOfMaterials; ++i)
    {
        Material* mat = GET_RESOURCE(Material);
        MatSampler* samplers = (MatSampler*)((char*)mat + mat->m_sampler_offset);
        uint32_t numOfSamplers = mat->m_num_samplers;

        for(uint32_t j=0; j<numOfSamplers; ++j)
        {
            if(samplers[j].m_texture == oldTex)
            {
                samplers[j].m_texture = newTex;
            }
        }
        bringin_resource_material(mat);
    }
}
void reload_texture_3d_resource(void* oldResource, void* newResource)
{
    Raw3DTexture* oldTex = (Raw3DTexture*)oldResource;
    Raw3DTexture* newTex = (Raw3DTexture*)newResource;

    uint32_t numOfEnv = FIND_RESOURCES(EngineTypes::SHADING_ENV);
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

    uint32_t model_num = num_all_model();
    Model* models = (Model*)get_all_model();

    for(size_t i=0; i<model_num; ++i)
    {
        Model* model = models + i;
        if(model->m_mesh == oldMesh)
        {
            model->m_mesh = newMesh;
        }
    }
}

void reload_program_resource(void* oldResource, void* newResource)
{
    ShaderProgram* oldProgram = (ShaderProgram*)oldResource;
    ShaderProgram* newProgram = (ShaderProgram*)newResource;

    if(g_debugDrawMgr.m_shader == oldProgram)
        g_debugDrawMgr.m_shader = newProgram;

    uint32_t numOfMaterials = FIND_RESOURCES(EngineTypes::MATERIAL);
    LOGD("total num of materials = %d", numOfMaterials);
    for(uint32_t i=0; i<numOfMaterials; ++i)
    {
        Material* mat = GET_RESOURCE(Material);
        if(mat->m_shader == oldProgram)
            mat->m_shader = newProgram;
        if(mat->m_shadow_shader == oldProgram)
            mat->m_shadow_shader = newProgram;
    }
}

void reload_shader_resource(void* oldResource, void* newResource)
{
    Shader* oldShader = (Shader*)oldResource;
    Shader* newShader = (Shader*)newResource;

    uint32_t numOfPrograms = FIND_RESOURCES(EngineTypes::PROGRAM);
    LOGD("total num of programs = %d", numOfPrograms);
    for(uint32_t i=0; i<numOfPrograms; ++i)
    {
        ShaderProgram* program = GET_RESOURCE(ShaderProgram);
        if(program->m_vs == oldShader || program->m_ps == oldShader)
        {
            bringout_resource_shader_program(program);
            if(program->m_vs == oldShader)
                program->m_vs = newShader;
            if(program->m_ps == oldShader)
                program->m_ps = newShader;
            bringin_resource_shader_program(program);
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
    g_resourceMgr.register_reload_callback(EngineTypes::SHADING_ENV, reload_shading_enviroment);
    g_resourceMgr.register_reload_callback(EngineTypes::TEXTURE, reload_texture_resource);
    g_resourceMgr.register_reload_callback(EngineTypes::TEXTURE_3D, reload_texture_3d_resource);
    g_resourceMgr.register_reload_callback(EngineTypes::MESH, reload_mesh_resource);
    g_resourceMgr.register_reload_callback(EngineTypes::ACTOR, reload_actor_resource);
    g_resourceMgr.register_reload_callback(EngineTypes::MATERIAL, reload_material_resource);
    g_resourceMgr.register_reload_callback(EngineTypes::SHADER, reload_shader_resource);
    g_resourceMgr.register_reload_callback(EngineTypes::PROGRAM, reload_program_resource);
    g_resourceMgr.register_reload_callback(EngineTypes::LEVEL, reload_level_resource);
    g_resourceMgr.register_reload_callback(EngineTypes::ANIMATION, reload_animation_resource);
    g_resourceMgr.register_reload_callback(EngineTypes::ANIMATION_RIG, reload_anim_rig_resource);
    //g_resourceMgr.register_reload_callback(PhysicsResource::get_type(), reload_physics_resource);

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
    StringId _type = stringid_caculate(_ext);

    ResourceFactory* fac = g_resourceMgr.find_factory(_type);
    if(!fac)
    {
        LOGE("can not find any reload ext for %s type", _ext);
        return;
    }

    run_data_compile();

    std::ifstream ifs(DC_RESULT);
    if(!ifs.good())
        return;
    std::string line;
    while(std::getline(ifs, line))
    {
        std::string ext = getFileExt(line);
        std::string resourceName = get_resource_name(line);
        g_resourceMgr.reload_resource(
            stringid_caculate(ext.c_str()),
            stringid_caculate(resourceName.c_str()),
            line.c_str());
    }
}

#endif