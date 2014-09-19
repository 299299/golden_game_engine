#include "AnimationSystem.h"
#include "Thread.h"
#include "MemorySystem.h"
#include "DataDef.h"
#include "Profiler.h"
#include "Log.h"
#include "DebugDraw.h"
#include "id_array.h"
#include "config.h"
//===================================
// RESOURCES
#include "Resource.h"
#include "Actor.h"
#include "Model.h"
#include "Mesh.h"
#include "Animation.h"
#include "IK.h"
#include "Ragdoll.h"
#include "AnimRig.h"
#include "AnimFSM.h"
//===================================
//=======================================================================================
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
//=======================================================================================

AnimationSystem g_animMgr;
static IdArray<MAX_ANIM_FSM, AnimFSMInstance>      m_fsms;
static IdArray<MAX_ANIM_RIG, AnimRigInstance>      m_rigs;
static hkaSampleBlendJob                           m_animJobs[MAX_ANIM_RIG];
static int                                         m_status = 0;

static void check_status()
{
    ENGINE_ASSERT((m_status != kTickProcessing),  "AnimSystem Status is Processing!!!");
}
static void set_status(int newStatus)
{
    m_status = newStatus;
}

void AnimationSystem::init()
{
    m_status = 0;
    hkaSampleBlendJobQueueUtils::registerWithJobQueue( g_threadMgr.getJobQueue());
}

void AnimationSystem::quit()
{
    
}

void AnimationSystem::frameStart()
{
    set_status(kTickFrameStart);
}

void AnimationSystem::kickInJobs()
{
    uint32_t numSkeletons = id_array::size(m_rigs);
    if(numSkeletons == 0) return;
    PROFILE(Animation_KickInJobs);
    set_status(kTickProcessing);
    AnimRigInstance* rigs = id_array::begin(m_rigs);
    for (uint32_t i=0; i<numSkeletons;++i)
    {
        AnimRigInstance& instance = rigs[i];
        m_animJobs[i].build(instance.m_skeleton, instance.m_pose, true);
    }
    hkLocalArray<hkJob*> jobPointers( numSkeletons );
    jobPointers.reserve( numSkeletons );
    for ( uint32_t i = 0; i < numSkeletons; ++i )
    {
        m_animJobs[i].pushBack(&( m_animJobs[i]));
    }
    g_threadMgr.getJobQueue()->addJobBatch( jobPointers, hkJobQueue::JOB_HIGH_PRIORITY );
}

void AnimationSystem::tickFinishJobs()
{
    uint32_t numSkeletons = id_array::size(m_rigs);
    if(!numSkeletons) return;
    PROFILE(AnimationFinishJobs);
    for(int i=0; i<numSkeletons;++i)
    {
        m_animJobs[i].destroy();
    }
    set_status(kTickFinishedJobs);
}

void AnimationSystem::skin_actors( Actor* actors, uint32_t num )
{
    extern void* get_anim_rig(Id);
    extern void* get_render_model(Id);
    for (uint32_t i=0; i<num; ++i)
    {
        Actor& actor = actors[i];
        Id rigId = actor.m_components[kComponentAnimRig];
        Id modelId = actor.m_components[kComponentModel];
        AnimRigInstance* rig = (AnimRigInstance*)get_anim_rig(rigId);
        ModelInstance* model = (ModelInstance*)get_render_model(modelId);

        bool bVisibleThisFrame = model->m_visibleThisFrame;
        if(!bVisibleThisFrame) continue;

        hkaPose* pose = rig->m_pose;
        const Mesh* mesh = model->m_resource->m_mesh;
        if(!mesh->m_numJoints) continue;

        const Matrix* invMats = model->m_resource->m_mesh->m_jointMatrix;
        const hkArray<hkQsTransform>& poseMS = pose->getSyncedPoseModelSpace();
        model->allocSkinningMat();

        float* matrix = model->m_skinMatrix;
        hkQsTransform tempT1, tempT2;
        for (int i=0; i < poseMS.getSize(); ++i)
        {
            transform_matrix(tempT2, invMats[i].m_x);
            tempT1.setMul(poseMS[i], tempT2);
            tempT2.setMul(actor.m_transform, tempT1);
            transform_matrix(matrix, tempT2);
            matrix += 16;
        }

        hkAabb aabb;
        hkQsTransform& t = actor.m_transform;
        pose->getModelSpaceAabb(aabb);
        float minTmp[3], maxTmp[3];
        Aabb bbox;
        transform_vec3(minTmp, aabb.m_min);
        transform_vec3(maxTmp, aabb.m_max);
        const float adFSize = 0.25f;
        const float adVSize[3] = {adFSize, adFSize, adFSize};
        bx::vec3Add(bbox.m_max, maxTmp, adVSize);
        bx::vec3Sub(bbox.m_min, minTmp, adVSize);
        transform_matrix(model->m_transform, t);
        transformAabb(model->m_aabb.m_min, 
            model->m_aabb.m_max, 
            model->m_transform,
            bbox.m_min, 
            bbox.m_max);
        //ProxyInstance* proxy = (ProxyInstance*)lookup_component_proxy(m_locomotion.m_physics);
        //model->m_transform.t_y() += proxy->m_resource->m_offset;
        REMOVE_BITS(model->m_flag, kNodeTransformDirty);

#ifndef _RETIAL
        drawPose(*pose, t, RGBA(125,125,255,255));
#endif
    }
    
}

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
Id create_anim_fsm( const void* resource )
{
    AnimFSMInstance inst;
    inst.init(resource);
    return id_array::create(m_fsms, inst);
}

void destroy_anim_fsm( Id id )
{
    if(!id_array::has(m_fsms, id)) return;
    AnimFSMInstance& inst = id_array::get(m_fsms, id);
    inst.destroy();
    id_array::destroy(m_fsms, id);
}

void* get_anim_fsm( Id id )
{
    if(!id_array::has(m_fsms, id)) return 0;
    return &id_array::get(m_fsms, id);
}

uint32_t num_anim_fsms()
{
    return id_array::size(m_fsms);
}

void* get_anim_fsms()
{
    return id_array::begin(m_fsms);
}

Id create_anim_rig( const void* resource )
{
    check_status();
    AnimRigInstance inst;
    inst.init(resource);
    return id_array::create(m_rigs, inst);
}

void destroy_anim_rig( Id id )
{
    check_status();
    if(!id_array::has(m_rigs, id)) return;
    AnimRigInstance& inst = id_array::get(m_rigs, id);
    inst.destroy();
    id_array::destroy(m_rigs, id);
}

void* get_anim_rig( Id id )
{
    if(!id_array::has(m_rigs, id)) return 0;
    return &id_array::get(m_rigs, id);
}

uint32_t num_anim_rigs()
{
    return id_array::size(m_rigs);
}

void* get_anim_rigs()
{
    return id_array::begin(m_rigs);
}
//-----------------------------------------------------------------
//
//-----------------------------------------------------------------