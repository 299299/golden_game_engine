#include "AnimationSystem.h"
#include "Thread.h"
#include "MemorySystem.h"
#include "DataDef.h"
#include "Component.h"
#include "Profiler.h"
#include "Log.h"
#include "IdArray.h"
#include "GameConfig.h"
#include "Event.h"
#include "Resource.h"
#include "Model.h"
#include "Mesh.h"
#include "Animation.h"
#include "IK.h"
#include "Ragdoll.h"
#include "AnimRig.h"
#include "Actor.h"
#include "AnimationState.h"
#include "AnimControl.h"
#ifdef HAVOK_COMPILE
#include <Common/Base/Container/Array/hkArray.h>
#include <Common/Base/Container/LocalArray/hkLocalArray.h>
#include <Animation/Animation/Playback/SampleAndBlend/hkaSampleBlendJobQueueUtils.h>
#include <Animation/Animation/Playback/SampleAndBlend/hkaSampleBlendJob.h>
#include <Animation/Animation/Playback/hkaAnimatedSkeleton.h>
#include <Animation/Animation/Rig/hkaPose.h>
#include <Animation/Animation/hkaAnimationContainer.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredSkeleton.h>
#include <Animation/Animation/Animation/Mirrored/hkaMirroredAnimation.h>
#include <Animation/Animation/Animation/hkaAnimationBinding.h>
#include <Common/Serialize/Util/hkLoader.h>
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Common/Visualize/hkDebugDisplay.h>
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Animation/Animation/Rig/hkaSkeletonUtils.h>
#endif

AnimationSystem g_animMgr;
static IdArray<AnimRigInstance>                    m_rigs;
static IdArray<AnimationStatesInstance>            m_stateLayers;
static int                                         m_status = 0;
static hkaSampleBlendJob                           m_jobs[MAX_ANIM_RIG];

static void check_status()
{
    ENGINE_ASSERT((m_status != kTickProcessing),  "AnimSystem Status is Processing!!!");
}
static void set_status(int newStatus)
{
    m_status = newStatus;
}

void AnimationSystem::init(const AnimationConfig& cfg)
{
    m_status = 0;
    m_events = COMMON_ALLOC(AnimationEvent, cfg.max_anim_events);
    ENGINE_ASSERT(MAX_ANIM_RIG >= cfg.max_rigs, "max animation rig overflow %d > %d", MAX_ANIM_RIG, cfg.max_rigs);
    m_rigs.init(cfg.max_rigs, g_memoryMgr.get_allocator(kMemoryCategoryCommon));
    m_stateLayers.init(cfg.max_state_layers, g_memoryMgr.get_allocator(kMemoryCategoryCommon));
#ifdef HAVOK_COMPILE
    hkaSampleBlendJobQueueUtils::registerWithJobQueue(g_threadMgr.get_jobqueue());
#endif
}

void AnimationSystem::shutdown()
{
    for (int i=0; i<m_stateLayers.size(); ++i)
    {
        m_stateLayers[i].destroy();
    }
    m_stateLayers.destroy();
    m_rigs.destroy();
    COMMON_DEALLOC(m_events);
}

void AnimationSystem::frame_start()
{
    set_status(kTickFrameStart);
    m_numAnimEvts = 0;
}

void AnimationSystem::kickin_jobs()
{
    int num = m_rigs.size();
    if(num == 0)
        return;
    AnimRigInstance* rigs = m_rigs.begin();
#ifdef HAVOK_COMPILE
#ifdef MT_ANIMATION
    PROFILE(Animation_KickInJobs);
    set_status(kTickProcessing);
    for (int i=0; i<num;++i)
    {
        AnimRigInstance& instance = rigs[i];
        m_jobs[i].build(instance.m_skeleton, instance.m_pose);
    }
    hkLocalArray<hkJob*> jobPointers( num );
    jobPointers.setSize( num );
    for ( int i = 0; i < num; ++i )
    {
        jobPointers[i] = &m_jobs[i];
    }
    g_threadMgr.get_jobqueue()->addJobBatch( jobPointers, hkJobQueue::JOB_HIGH_PRIORITY );
#else
    for (uint32_t i=0; i<num;++i)
    {
        AnimRigInstance& instance = rigs[i];
        hkaAnimatedSkeleton* skel = instance.m_skeleton;
        hkaPose* pose = instance.m_pose;
        skel->sampleAndCombineAnimations(
            pose->accessUnsyncedPoseLocalSpace().begin(),
            pose->getFloatSlotValues().begin() );
    }
#endif
#endif
}

void AnimationSystem::tick_finished_jobs()
{
    set_status(kTickFinishedJobs);
    int num = m_rigs.size();
    if(!num)
        return;
    PROFILE(AnimationFinishJobs);
#ifdef HAVOK_COMPILE
#ifdef MT_ANIMATION
    for(int i=0; i<num; ++i)
    {
        m_jobs[i].destroy();
    }
#endif
#endif
}

void AnimationSystem::skin_actors( Actor* actors, int num )
{
    PROFILE(Animation_SkinActors);

    StringId anim_type = EngineTypes::ANIMATION_RIG;
    StringId model_type = EngineTypes::MODEL;
    for (int i=0; i<num; ++i)
    {
        Actor& actor = actors[i];
        AnimRigInstance* rig = (AnimRigInstance*)actor.get_first_component_of(anim_type);
        Model* model = (Model*)actor.get_first_component_of(model_type);

        if(!model) continue;
        bool bVisibleThisFrame = model->m_visibleThisFrame;
        if(!bVisibleThisFrame) continue;

        hkaPose* pose = rig->m_pose;
        const Mesh* mesh = model->m_mesh;
        if(!mesh->m_num_joints) continue;

        const hkQsTransform& t = actor.m_transform;
        const Matrix* invMats = (const Matrix*)((char*)mesh + mesh->m_joint_offset);

#ifdef HAVOK_COMPILE
        const hkQsTransform* poseMS = pose->getSyncedPoseModelSpace().begin();
        int num_of_pose = pose->getSyncedPoseModelSpace().getSize();

        {
            PROFILE(Animation_SkinMatrix);
            float* matrix = model->alloc_skinning_mat();
            hkQsTransform tempT1, tempT2;
            for (int i=0; i < num_of_pose; ++i)
            {
                tempT2.set4x4ColumnMajor(invMats[i].m_x);
                tempT1.setMul(poseMS[i], tempT2);
                tempT2.setMul(t, tempT1);
                tempT2.get4x4ColumnMajor(matrix);
                matrix += 16;
            }
        }

#if 1
        {
            PROFILE(Animation_UpdateAABB);
            hkAabb aabb;
            hkaSkeletonUtils::calcAabb(num_of_pose, pose->getSyncedPoseLocalSpace().begin(),
                pose->getSkeleton()->m_parentIndices.begin(), t, aabb);
            Aabb& bbox = model->m_aabb;
            transform_vec3(bbox.m_min, aabb.m_min);
            transform_vec3(bbox.m_max, aabb.m_max);
            t.get4x4ColumnMajor(model->m_transform);
            REMOVE_BITS(model->m_flag, kNodeTransformDirty);
        }
#endif
#endif
    }
}

void AnimationSystem::update_animations(float dt)
{
    int num = m_rigs.size();
    PROFILE(Animation_Update);
    AnimRigInstance* rigs = m_rigs.begin();
    AnimationEvent* events = m_events;
    int evt_num = m_numAnimEvts;
    for(int i=0; i<num;++i)
    {
        int num = rigs[i].collect_event(events, dt);
        events += num;
        evt_num += num;
        rigs[i].update(dt);
    }
    m_numAnimEvts = evt_num;
    num = m_stateLayers.size();
    AnimationStatesInstance* l = m_stateLayers.begin();
    for(int i=0; i<num;++i)
    {
        l[i].update(dt);
    }
}

void AnimationSystem::update_attachment( Actor* actors, int num )
{
    PROFILE(Animation_UpdateAttachment);
    StringId anim_type = EngineTypes::ANIMATION_RIG;
    for (int i=0; i<num; ++i)
    {
        Actor& actor = actors[i];
        int index = actor.get_first_component_index_of(anim_type);
        Id rigId = actor.m_components[index];
        AnimRigInstance* rig = (AnimRigInstance*)get_anim_rig(rigId);
        if(!rig)
            continue;
        rig->update_attachment(actor.m_transform);
    }
}

void AnimationSystem::register_factories()
{
    ResourceFactory _rig = { load_resource_anim_rig, destroy_resource_anim_rig, 0, 0, 0, EngineNames::ANIMATION_RIG, 1};
    g_resourceMgr.register_factory(_rig);

    ResourceFactory _animation = {load_resource_animation, destroy_resource_animation, lookup_resource_animation, 0, 0, EngineNames::ANIMATION, 2};
    g_resourceMgr.register_factory(_animation);

    ResourceFactory _states = { 0, 0, lookup_animation_states, 0, 0, EngineNames::ANIMATION_STATES, 3};
    g_resourceMgr.register_factory(_states);

    ComponentFactory _comp_rig = { create_anim_rig, destroy_anim_rig, get_anim_rig, num_all_anim_rig, get_all_anim_rig, 0, lookup_anim_rig_instance_data, 0};
    g_componentMgr.register_factory(_comp_rig, EngineTypes::ANIMATION_RIG);

    ComponentFactory _comp_states = { create_anim_state, destroy_anim_state, get_anim_state, num_all_anim_state, get_all_anim_state, 0, lookup_anim_state_instance_data, 1};
    g_componentMgr.register_factory(_comp_states, EngineTypes::ANIMATION_STATES);
}


//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
Id create_anim_rig( const void* resource, ActorId32 id)
{
    check_status();
    AnimRigInstance* inst;
    Id animId = m_rigs.create(&inst);
    inst->init(resource, id);
    return animId;
}

void destroy_anim_rig( Id id )
{
    check_status();
    if(!m_rigs.has(id))
        return;
    m_rigs.get(id)->destroy();
    m_rigs.destroy(id);
}

void* get_anim_rig( Id id )
{
    if(!m_rigs.has(id))
        return 0;
    return m_rigs.get(id);
}

int num_all_anim_rig()
{
    return m_rigs.size();
}

void* get_all_anim_rig()
{
    return m_rigs.begin();
}

void lookup_anim_rig_instance_data( void* resource )
{
    ComponentInstanceData* data = (ComponentInstanceData*)resource;
    data->m_resource = g_resourceMgr.find_resource(EngineTypes::ANIMATION_RIG, data->m_name);
}

Id create_anim_state( const void* resource, ActorId32 id)
{
    check_status();
    AnimationStatesInstance* inst;
    Id animId = m_stateLayers.create(&inst);
    inst->init(resource, id);
    return animId;
}

void destroy_anim_state( Id id )
{
    check_status();
    if(!m_stateLayers.has(id))
        return;
    m_stateLayers.get(id)->destroy();
    m_stateLayers.destroy(id);
}

void* get_anim_state( Id id )
{
    if(!m_stateLayers.has(id))
        return 0;
    return m_stateLayers.get(id);
}

int num_all_anim_state()
{
    return m_stateLayers.size();
}

void* get_all_anim_state()
{
    return m_stateLayers.begin();
}

void lookup_anim_state_instance_data( void* resource )
{
    ComponentInstanceData* data = (ComponentInstanceData*)resource;
    data->m_resource = FIND_RESOURCE(AnimationStates, EngineTypes::ANIMATION_STATES, data->m_name);
}


//-----------------------------------------------------------------
//
//-----------------------------------------------------------------

#ifndef _RETAIL
struct DebugEvtText
{
    float           m_time;
    const char*     m_message;
};

#include "DebugDraw.h"
void debug_draw_animation(float dt)
{
    PROFILE(debug_draw_animation);

    int num = m_rigs.size();
    AnimRigInstance* rigs = m_rigs.begin();
    for (int i=0; i<num; ++i)
    {
        AnimRigInstance& rig = rigs[i];
        const AnimRig* res = rig.m_resource;
        hkaPose* pose = rig.m_pose;
        Actor* actor = g_actorWorld.get_actor(rig.m_actor);
        const hkQsTransform& t = actor->m_transform;

        //draw debug pose
        extern int g_engineMode;
        if(g_engineMode == 0)
            draw_pose(*pose, t, RGBCOLOR(125,125,255), false);
        else
            draw_pose_vdb(*pose, t);

#ifdef HAVOK_COMPILE
        {
            //draw debug attachment
            uint32_t num_attach = res->m_num_joints;
            const BoneAttachment* attachments = (const BoneAttachment*)((char*)res + res->m_attachment_offset);
            const float* world_poses = rig.m_attachment_transforms;
            if(world_poses)
            {
                for (uint32_t i=0; i<num_attach; ++i)
                {
                    const BoneAttachment& attchment = attachments[i];
                    const float* world_pose = world_poses + 16 * i;
                    hkQsTransform t1;
                    t1.set4x4ColumnMajor(world_pose);
                    g_debugDrawMgr.add_axis(t1);
                    g_debugDrawMgr.add_text_3d(t1.m_translation, RGBCOLOR(255,0,0), stringid_lookup(attchment.m_name));
                }
            }
        }

        {
            // draw animation control
            hkaAnimatedSkeleton* s = rig.m_skeleton;
            int num = s->getNumAnimationControls();
            g_debugDrawMgr.add_text(RGBCOLOR(255,0,0), stringid_lookup(actor->m_name));
            for (int i=0; i<num; ++i)
            {
                hk_anim_ctrl* ac = (hk_anim_ctrl*)s->getAnimationControl(i);
                g_debugDrawMgr.add_text(RGBCOLOR(0,0,255), "%s weight = %f, time = %f", get_anim_debug_name(ac->m_animation), ac->getMasterWeight(), ac->getLocalTime());
            }
        }
#endif
    }

    typedef tinystl::unordered_map<ActorId32, DebugEvtText> DebugEvtMap;
    static DebugEvtMap g_evtMap;
    const float evt_time = 0.5f;

    for (DebugEvtMap::iterator iter = g_evtMap.begin(); iter != g_evtMap.end(); ++iter)
    {
        DebugEvtText& dbg_evt = iter->second;
        dbg_evt.m_time -= dt;
        if(dbg_evt.m_time <= 0)
        {
            dbg_evt.m_time = 0;
            continue;
        }

        Actor* actor = g_actorWorld.get_actor(iter->first);
        if(!actor)
            continue;
        g_debugDrawMgr.add_text_3d(actor->m_transform.m_translation, RGBCOLOR(255,0,255), dbg_evt.m_message);
    }

    num = g_animMgr.m_numAnimEvts;
    AnimationEvent* evts = g_animMgr.m_events;
    for (int i=0; i<num; ++i)
    {
        ActorId32 id = evts[i].m_who;
        DebugEvtMap::iterator iter = g_evtMap.find(id);
        if(iter != g_evtMap.end())
        {
            iter->second.m_message = stringid_lookup(evts[i].m_name);
            iter->second.m_time = evt_time;
        }
        else
        {
            DebugEvtText dbg_evt;
            dbg_evt.m_message = stringid_lookup(evts[i].m_name);
            dbg_evt.m_time = evt_time;
            g_evtMap[id] = dbg_evt;
        }
    }
}

typedef tinystl::unordered_map<void*, const char*> anim_debug_map;
static anim_debug_map  m_anim_debug_names;
void add_anim_debug_name(void* p, StringId name)
{
    anim_debug_map::iterator i = m_anim_debug_names.find(p);
    if(i != m_anim_debug_names.end())
        return;
    m_anim_debug_names[p] = stringid_lookup(name);
}

const char* get_anim_debug_name(void* p)
{
    anim_debug_map::iterator it = m_anim_debug_names.find(p);
    const char* anim_name = 0;
    if(it != m_anim_debug_names.end())
        anim_name = it->second;
    return anim_name;
}

#endif


//-----------------------------------------------------------------
//
//-----------------------------------------------------------------