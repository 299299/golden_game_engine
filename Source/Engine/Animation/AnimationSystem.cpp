#include "AnimationSystem.h"
#include "Thread.h"
#include "MemorySystem.h"
#include "DataDef.h"
#include "Profiler.h"
#include "Log.h"
#include "DebugDraw.h"
#include "id_array.h"
#include "config.h"
#include "Event.h"
//=======================================================================================
// RESOURCES
#include "Resource.h"
#include "Actor.h"
#include "Model.h"
#include "Mesh.h"
#include "Animation.h"
#include "IK.h"
#include "Ragdoll.h"
#include "AnimRig.h"
#include "ProxyInstance.h"
//=======================================================================================
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
#include <Animation/Animation/Rig/hkaSkeletonUtils.h>
//=======================================================================================

AnimationSystem g_animMgr;
static IdArray<MAX_ANIM_RIG, AnimRigInstance>      m_rigs;
static hkaSampleBlendJob                           m_animJobs[MAX_ANIM_RIG];
static int                                         m_status = 0;

#define MT_ANIMATION

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
    m_events = COMMON_ALLOC(AnimationEvent, MAX_ANIM_EVENTS);
    hkaSampleBlendJobQueueUtils::registerWithJobQueue(g_threadMgr.get_jobqueue());
}

void AnimationSystem::quit()
{
    COMMON_DEALLOC(m_events);
}

void AnimationSystem::frame_start()
{
    set_status(kTickFrameStart);
}

void AnimationSystem::kick_in_jobs()
{
    uint32_t num = id_array::size(m_rigs);
    if(num == 0) return;
    AnimRigInstance* rigs = id_array::begin(m_rigs);
#ifdef MT_ANIMATION
    PROFILE(Animation_KickInJobs);
    set_status(kTickProcessing);
    for (uint32_t i=0; i<num;++i)
    {
        AnimRigInstance& instance = rigs[i];
        m_animJobs[i].build(instance.m_skeleton, instance.m_pose);
    }
    hkLocalArray<hkJob*> jobPointers( num );
    jobPointers.resize( num );
    for ( uint32_t i = 0; i < num; ++i )
    {
        jobPointers[i] = &m_animJobs[i];
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
}

void AnimationSystem::tick_finished_jobs()
{
#ifdef MT_ANIMATION
    uint32_t num = id_array::size(m_rigs);
    if(!num) return;
    PROFILE(AnimationFinishJobs);
    for(uint32_t i=0; i<num; ++i)
    {
        m_animJobs[i].destroy();
    }
    set_status(kTickFinishedJobs);
#endif
}

void AnimationSystem::skin_actors( Actor* actors, uint32_t num )
{
    PROFILE(Animation_SkinActors);
    extern void* get_anim_rig(Id);
    extern void* get_render_model(Id);
    for (uint32_t i=0; i<num; ++i)
    {
        Actor& actor = actors[i];
        Id rigId = actor.m_components[kComponentAnimRig];
        Id modelId = actor.m_components[kComponentModel];
        AnimRigInstance* rig = (AnimRigInstance*)get_anim_rig(rigId);
        ModelInstance* model = (ModelInstance*)get_render_model(modelId);

        if(!model) continue;
        bool bVisibleThisFrame = model->m_visibleThisFrame;
        if(!bVisibleThisFrame) continue;

        hkaPose* pose = rig->m_pose;
        const Mesh* mesh = model->m_resource->m_mesh;
        if(!mesh->m_numJoints) continue;

        const hkQsTransform& t = actor.m_transform;
        const Matrix* invMats = model->m_resource->m_mesh->m_jointMatrix;
        const hkQsTransform* poseMS = pose->getSyncedPoseModelSpace().begin();

        int num_of_pose = poseMS.getSize();
        rig->update_attachments(t);

        {
            PROFILE(Animation_SkinMatrix);
            float* matrix = model->alloc_skinning_mat();
            hkQsTransform tempT1, tempT2;
            for (int i=0; i < num_of_pose; ++i)
            {
                transform_matrix(tempT2, invMats[i].m_x);
                tempT1.setMul(poseMS[i], tempT2);
                tempT2.setMul(actor.m_transform, tempT1);
                transform_matrix(matrix, tempT2);
                matrix += 16;
            }
        }
        
#if 1
        {
            PROFILE(Animation_UpdateAABB);
            hkAabb aabb;
            const hkQsTransform* poseLS = pose->getSyncedPoseLocalSpace().begin();
            hkaSkeletonUtils::calcAabb(num_of_pose, poseLS.begin(), 
                                      pose->getSkeleton()->m_parentIndices.begin(), t, aabb);
            Aabb& bbox = model->m_aabb;
            transform_vec3(bbox.m_min, aabb.m_min);
            transform_vec3(bbox.m_max, aabb.m_max);
            transform_matrix(model->m_transform, t);
            REMOVE_BITS(model->m_flag, kNodeTransformDirty);
        }
#endif
        

#ifndef _RETIAL
        draw_pose(*pose, t, RGBCOLOR(125,125,255), false);
        uint32_t num_attach = rig->m_resource->m_attachNum;
        const BoneAttachment* attachments = rig->m_resource->m_attachments;
        const float* world_poses = rig->m_attachmentTransforms;
        for (uint32_t i=0; i<num_attach; ++i)
        {
            const BoneAttachment& attchment = attachments[i];
            const float* world_pose = world_poses + 16 * i;
            hkQsTransform t;
            transform_matrix(t, world_pose);
            g_debugDrawMgr.add_axis(t);
            float world_pos[] = {world_pose[12], world_pose[13], world_pose[14]};
            g_debugDrawMgr.add_text_3d(world_pos, stringid_lookup(attchment.m_name), RGBCOLOR(255,0,0));
        }
#endif
    }
}

void AnimationSystem::update_animations(float dt)
{
    uint32_t num = id_array::size(m_rigs);
    if(!num) return;
    PROFILE(Animation_UpdateLocalClock);
    AnimRigInstance* rigs = id_array::begin(m_rigs);
    for(uint32_t i=0; i<num;++i)
    {
        rigs[i].update(dt);
    }
}

void AnimationSystem::apply_animation_rootmotion( Actor* actors, uint32_t num, float dt )
{
	PROFILE(Animation_ApplyRootmotion);
	extern void* get_anim_rig(Id);
	extern void* get_physics_proxy(Id);
	hkQsTransform t;
	for (uint32_t i=0; i<num; ++i)
	{
		Actor& actor = actors[i];
		Id rigId = actor.m_components[kComponentAnimRig];
		Id proxyId = actor.m_components[kComponentProxy];
		AnimRigInstance* rig = (AnimRigInstance*)get_anim_rig(rigId);
		ProxyInstance* proxy = (ProxyInstance*)get_physics_proxy(proxyId);
		if(!proxy||!rig) continue;
		if(!rig->m_applyRootmotion) continue;
		rig->get_rootmotion(dt, t);

		hkQsTransform& transform = proxy->m_transform;
		transform.m_rotation.mul(t.m_rotation);

		hkVector4 desiredMotionWorld;
		hkQuaternion currentOrient;
		desiredMotionWorld.setRotatedDir( transform.m_rotation, t.m_translation );
		// Divide motion by time
		proxy->m_targetVelocity.setMul4 (1.0f / dt, desiredMotionWorld );
	}
}


//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
Id create_anim_rig( const void* resource, ActorId32 )
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