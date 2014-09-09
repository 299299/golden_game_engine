#include "Character.h"
#include "Profiler.h"
#include "Memory.h"
#include "DataDef.h"
//==============graphics==================//
#include "Scene.h"
#include "Model.h"
#include "Mesh.h"
#include "MathDefs.h"
#include "DebugDraw.h"
#include "Graphics.h"
//==============physics==================//
#include "PhysicsInstance.h"
#include "ProxyInstance.h"
#include "PhysicsWorld.h"
#include "PhysicsAutoLock.h"
//==============Animation==================//
#include "AnimationSystem.h"
#include "IK.h"
#include "Ragdoll.h"
#include "Animation.h"
#include "AnimRig.h"
#include "AnimFSM.h"
//=======================================================================================
#include <Common/Base/Types/Geometry/Aabb/hkAabb.h>
#include <Animation/Animation/Playback/hkaAnimatedSkeleton.h>
#include <Animation/Animation/Rig/hkaPose.h>
#include <Common/Visualize/hkDebugDisplay.h>
//=======================================================================================

void Character::start(const hkQsTransform& t)
{
    m_transform = t;
    m_lookAtWS.setZero4();
    m_reachWS[0].setZero4();
    m_reachWS[1].setZero4();
    m_locomotion.init();
    m_modelIndex = getFirstCompIndexTypeOf(ModelResource::getType());
    m_animRigIndex  = getFirstCompIndexTypeOf(AnimRig::getType());
    m_animFSMIndex = getFirstCompIndexTypeOf(AnimFSM::getType());
    m_proxyIndex = getFirstCompIndexTypeOf(ProxyResource::getType());
}

void Character::stop()
{
    
}

void Character::applyAnimations(float dt)
{
    /*
    AnimRigInstance* anim = (AnimRigInstance*)lookup_component_anim(m_animation);
    if(!anim)
        return;
    //@TODO other event ?
    for(uint32_t i=0; i<anim->m_numLayers; ++i)
    {
        int triggerNum = anim->getTriggers(0, dt, s_triggers);
        for(int j=0; j<triggerNum; ++j)
        {
            AnimationTrigger& t = s_triggers[j];
            if(t.m_type == kAnimTriggerEvent)
                anim->fireTransition(t.m_name, i);
        }
    }

    anim->updateLocalClock(dt);
    */
}

void Character::preStep(float dt)
{
    m_model = (ModelInstance*)getComponent(m_modelIndex);
    m_proxy = (ProxyInstance*)getComponent(m_proxyIndex);
    m_rig = (AnimRigInstance*)getComponent(m_animRigIndex);
    m_animFSM = (AnimFSMInstance*)getComponent(m_animFSMIndex);
    m_locomotion.m_proxy = m_proxy;
    m_locomotion.m_fsm = m_animFSM;

    applyAnimations(dt);
    m_locomotion.update(dt, m_transform);
    updateFSM(dt);
}

void Character::postStep(float dt)
{
    doRagdoll(dt);
    doIK(dt);
    doSkinning();
}

void Character::updateFSM(float dt)
{
    if(m_animFSM) m_animFSM->update(dt);
}

void Character::doSkinning()
{
    AnimRigInstance* rig = m_rig;
    ModelInstance* model = m_model;

    if(!rig || !model) return;
    
    bool bVisibleThisFrame = model->m_visibleThisFrame;
    if(!bVisibleThisFrame) return;

    hkaPose* pose = rig->m_pose;
    const Mesh* mesh = model->m_resource->m_mesh;
    if(!mesh->m_numJoints) return;

    const Matrix* invMats = model->m_resource->m_mesh->m_jointMatrix;
    const hkArray<hkQsTransform>& poseMS = pose->getSyncedPoseModelSpace();
    model->allocSkinningMat();

    float* matrix = model->m_skinMatrix;
    hkQsTransform tempT1, tempT2;
    for (int i=0; i < poseMS.getSize(); ++i)
    {
        transform_matrix(tempT2, invMats[i].m_x);
        tempT1.setMul(poseMS[i], tempT2);
        tempT2.setMul(m_transform, tempT1);
        transform_matrix(matrix, tempT2);
        matrix += 16;
    }

    hkAabb aabb;
    pose->getModelSpaceAabb(aabb);
    float minTmp[3], maxTmp[3];
    Aabb bbox;
    transform_vec3(minTmp, aabb.m_min);
    transform_vec3(maxTmp, aabb.m_max);
    const float adFSize = 0.25f;
    const float adVSize[3] = {adFSize, adFSize, adFSize};
    bx::vec3Add(bbox.m_max, maxTmp, adVSize);
    bx::vec3Sub(bbox.m_min, minTmp, adVSize);
    transform_matrix(model->m_transform, m_transform);
    transformAabb(model->m_aabb.m_min, 
                  model->m_aabb.m_max, 
                  model->m_transform,
                  bbox.m_min, 
                  bbox.m_max);
    //ProxyInstance* proxy = (ProxyInstance*)lookup_component_proxy(m_locomotion.m_physics);
    //model->m_transform.t_y() += proxy->m_resource->m_offset;
    model->removeFlag(kNodeTransformDirty);

#ifndef _RETIAL
    drawPose(*pose, m_transform, RGBA(125,125,255,255));
#endif
}

void Character::doIK(float dt)
{
    /*
    AnimRigInstance* anim = (AnimRigInstance*)lookup_component_anim(m_animation);
    IKInstance* ik = (IKInstance*)lookup_component_ik(m_ik);
    if(!anim || !ik) return;
    hkQsTransform& worldFromModel = m_locomotion.m_transform;
    hkaPose& thePose = anim->getPose();

    if(ik->hasIK(kIKLookAt))
        ik->m_lookAt.doLookAt(m_ikMask & kIKLookAt, m_lookAtWS, worldFromModel, thePose);
    if(ik->hasIK(kIKReachLeft))
        ik->m_reach[0].doReach(m_ikMask & kIKReachLeft, m_reachWS[0], worldFromModel, thePose);
    if(ik->hasIK(kIKReachRight))
        ik->m_reach[1].doReach(m_ikMask & kIKReachRight, m_reachWS[1], worldFromModel, thePose);
    if(ik->hasIK(kIKFoot))
        ik->m_foot.doFootIK( m_ikMask & kIKFoot, m_locomotion.isStanding(), worldFromModel, thePose, m_locomotion.m_verticalDisplacement);
    */
}

void Character::doRagdoll(float dt)
{

}