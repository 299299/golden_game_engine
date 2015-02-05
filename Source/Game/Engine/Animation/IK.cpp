#include "IK.h"
#include "AnimRaycast.h"
#include "AnimRig.h"
#include "Resource.h"
#include "DataDef.h"
#include "Log.h"
#include "PhysicsWorld.h"
#ifdef HAVOK_COMPILE
#include <Animation/Animation/Rig/hkaSkeleton.h>
#include <Animation/Animation/Rig/hkaSkeletonUtils.h>
#include <Animation/Animation/Rig/hkaPose.h>
#include <Animation/Animation/Ik/LookAt/hkaLookAtIkSolver.h>
#include <Animation/Animation/Ik/TwoJoints/hkaTwoJointsIkSolver.h>
#include <Animation/Animation/Ik/FootPlacement/hkaFootPlacementIkSolver.h>
#include <Animation/Animation/Ik/Ccd/hkaCcdIkSolver.h>
#include <Common/Visualize/hkDebugDisplay.h>
#include <Physics2012/Collide/Filter/Group/hkpGroupFilter.h>
#endif


//============================================================
//                  LOOK AT INSTANCE
//============================================================
void LookAtInstance::init(const void* resource)
{
    m_resource = (const LookAtResource*)resource;
    m_lookAtWeight = 0.0f;
#ifdef HAVOK_COMPILE
    m_lookAtLastTargetWS.setZero4();
#endif
}

void LookAtInstance::do_lookat(const hkVector4& targetPosWS,
                              const hkQsTransform& worldFromModel,
                              hkaPose& thePose)
{
#ifdef HAVOK_COMPILE
    bool lookAtOn = m_enabled;
    const LookAtResource* res = m_resource;
    const int* jointIndices = res->m_rig->m_humanJointIndices;

    // Current transforms (MS) of the head and neck
    int headIdx = jointIndices[kBodyHead];
    int neckIdx = jointIndices[kBodyNeck];
    const hkQsTransform& headMS = thePose.getBoneModelSpace(headIdx);
    const hkQsTransform& neckMS = thePose.getBoneModelSpace(neckIdx);

    // Position of the head (MS)
    const hkVector4& headPosMS = headMS.getTranslation();

    // Forward-looking direction (MS)
    hkVector4 forwardDirMS; forwardDirMS.setRotatedDir(headMS.getRotation(), hkVector4(0,0,1));

#ifndef _RETAIL
    {
        hkVector4 headPosWS; headPosWS.setTransformedPos(worldFromModel, headPosMS);
        HK_DISPLAY_LINE(headPosWS, targetPosWS, 0xffff0000);
    }
#endif

    // We want to look at something; but we shouldn't try to look at something behind the character
    if (lookAtOn)
    {
        hkVector4 targetPosMS; targetPosMS.setTransformedInversePos(worldFromModel, targetPosWS);

        hkVector4 headToTargetDirMS; headToTargetDirMS.setSub4(targetPosMS, headPosMS);
        if (headToTargetDirMS.dot3(forwardDirMS)<0.0f)
        {
            // Target is behind us, ignore it
            lookAtOn = false;
        }
    }

    // Still we want to look at something
    if (lookAtOn)
    {
        // If we were doing look at before, blend the new position
        if (m_lookAtWeight>0.0f)
        {
            m_lookAtLastTargetWS.setInterpolate4(m_lookAtLastTargetWS, targetPosWS, res->m_targetGain);
        }
        else
        {
            // Otherwise use this new position straight away
            m_lookAtLastTargetWS = targetPosWS;
        }
    }

    // Ease in/out the weight depending on whether there is something we want to look at
    const hkReal desiredWeight = lookAtOn ? 1.0f : 0.0f;
    m_lookAtWeight += (desiredWeight - m_lookAtWeight) * res->m_gain;

    // If weight gets under threshold, do nothing
    if (m_lookAtWeight < 0.01f)
    {
        m_lookAtWeight = 0.0f;
    }
    else
    {
        // Use the LookAt Ik solver to modify the orientation of the head
        // Use the weight the gain, so we move smoothly over time
        hkaLookAtIkSolver::Setup setup;
        const float* fwdLS = res->m_fwdLS;
        setup.m_fwdLS.set(fwdLS[0], fwdLS[1], fwdLS[2]);
        setup.m_limitAxisMS.setRotatedDir(neckMS.getRotation(), hkVector4(0, 0.34f ,1.0f));
        setup.m_limitAxisMS.normalize3();
        setup.m_limitAngle = res->m_lookAtLimit;

        hkVector4 targetMS; targetMS.setTransformedInversePos(worldFromModel, m_lookAtLastTargetWS);

        // By using hkaPose and the PROPAGATE flag we automatically update the descendant bones of the head
        hkaLookAtIkSolver::solve(setup, targetMS, m_lookAtWeight, thePose.accessBoneModelSpace(headIdx, hkaPose::PROPAGATE));
    }
#endif
}

//============================================================
//                  REACH INSTANCE
//============================================================
void ReachInstance::init(const void* resource)
{
    m_reachWeight = 0;
    m_resource = (const ReachResource*)resource;
#ifdef HAVOK_COMPILE
    m_reachLastTargetWS.setZero4();
#endif
}

void ReachInstance::do_reach(  const hkVector4& targetPosWS,
                              const hkQsTransform& worldFromModel,
                              hkaPose& thePose)
{
#ifdef HAVOK_COMPILE
    bool reachOn = m_enabled;
    const ReachResource* res = m_resource;
    const int* jointIndices = res->m_rig->m_humanJointIndices;
    if (reachOn)
    {
        if (m_reachWeight > 0.0f)
        {
            m_reachLastTargetWS.setInterpolate( m_reachLastTargetWS,
                                                targetPosWS,
                                                res->m_targetGain);
        }
        else
        {
            m_reachLastTargetWS = targetPosWS;
        }
    }

    // Do gain on the weight for the reaching
    const hkReal desiredWeight = (reachOn) ? 1.0f : 0.0f;
    const hkReal diffWeight = desiredWeight - m_reachWeight;
    m_reachWeight += diffWeight * res->m_reachGain;

    // If weight 0 or very small, switch off completely and do nothing
    if (m_reachWeight < 0.01f)
    {
        m_reachWeight = 0.0f;
    }
    else
    {
        // Fix the position, use the Two Joints IK solver
        hkVector4 pointMS;
        pointMS.setTransformedInversePos(worldFromModel, m_reachLastTargetWS);

        hkaTwoJointsIkSolver::Setup setup;
        int idx1, idx2, idx3;
        idx1 = res->m_index == 0 ? kBodyShoulder_L : kBodyShoulder_R;
        idx2 = res->m_index == 0 ? kBodyArm_L : kBodyArm_R;
        idx3 = res->m_index == 0 ? kBodyForeArm_L : kBodyForeArm_R;
        setup.m_firstJointIdx = jointIndices[idx1];
        setup.m_secondJointIdx = jointIndices[idx2];
        setup.m_endBoneIdx = jointIndices[idx3];
        const float* elbowAxis = res->m_elbowAxis;
        setup.m_hingeAxisLS.set(elbowAxis[0], elbowAxis[1], elbowAxis[2]);
        setup.m_firstJointIkGain = m_reachWeight;
        setup.m_secondJointIkGain = m_reachWeight;
        setup.m_endJointIkGain = m_reachWeight;
        setup.m_endTargetMS = pointMS;
        setup.m_cosineMinHingeAngle = cosf(res->m_hingeLimitAngle[0]*HK_REAL_DEG_TO_RAD);
        setup.m_cosineMaxHingeAngle = cosf(res->m_hingeLimitAngle[1]*HK_REAL_DEG_TO_RAD);
        hkaTwoJointsIkSolver::solve(setup, thePose);
    }
#endif
}
//============================================================
//                  FOOT INSTANCE
//============================================================
void FootInstance::init(const void* resource)
{
    m_resource = (const FootResource*)resource;
    m_raycast = new AnimRaycastInterface();
    m_raycast->m_type = m_resource->m_raycastType;

#ifdef HAVOK_COMPILE
    const FootResource* res = m_resource;
    const int* jointIndices = res->m_rig->m_humanJointIndices;

    hkaFootPlacementIkSolver::Setup setupData;
    hkaSkeleton* skel = m_resource->m_rig->m_skeleton;
    // COMMON
    {
        setupData.m_skeleton = skel;
        const float* endLS = res->m_footEndLS;
        setupData.m_footEndLS.set(endLS[0], endLS[1], endLS[2]);
        setupData.m_worldUpDirectionWS.set(0,1,0);
        setupData.m_originalGroundHeightMS = res->m_orignalGroundHeightMS;
        setupData.m_minAnkleHeightMS = res->m_minAnkleHeightMS;
        setupData.m_maxAnkleHeightMS = res->m_maxAnkleHeightMS;
        setupData.m_footPlantedAnkleHeightMS = res->m_footPlantedAnkleHeightMS;
        setupData.m_footRaisedAnkleHeightMS = res->m_footRaisedAnkleHeightMS;
        setupData.m_cosineMaxKneeAngle = cosf((float)HK_DOUBLE_DEG_TO_RAD*res->m_cosineMaxKneeAngle);
        setupData.m_cosineMinKneeAngle = cosf((float)HK_DOUBLE_DEG_TO_RAD*res->m_cosineMinKneeAngle);
        setupData.m_raycastDistanceUp = res->m_raycastDistanceUp;
        setupData.m_raycastDistanceDown = res->m_raycastDistanceDown;
    }

    // LEFT LEG
    {
        const float* leftAxisLS = res->m_leftKneeAxisLS;
        setupData.m_kneeAxisLS.set(leftAxisLS[0], leftAxisLS[1], leftAxisLS[2]);
        setupData.m_hipIndex =  jointIndices[kBodyUpLeg_L];
        setupData.m_kneeIndex = jointIndices[kBodyLeg_L];
        setupData.m_ankleIndex = jointIndices[kBodyFoot_L];
        m_solver[0] = new hkaFootPlacementIkSolver(setupData);
    }

    // RIGHT LEG
    {
        const float* rightAxisLS = res->m_rightKneeAxisLS;
        setupData.m_kneeAxisLS.set(rightAxisLS[0], rightAxisLS[1], rightAxisLS[2]);
        setupData.m_hipIndex =  jointIndices[kBodyUpLeg_R];
        setupData.m_kneeIndex = jointIndices[kBodyLeg_R];
        setupData.m_ankleIndex = jointIndices[kBodyFoot_R];
        m_solver[1] = new hkaFootPlacementIkSolver(setupData);
    }
#endif
}

void FootInstance::destroy()
{
    SAFE_DELETE(m_raycast);
#ifdef HAVOK_COMPILE
    SAFE_DELETE(m_solver[0]);
    SAFE_DELETE(m_solver[1]);
#endif
}


void  FootInstance::do_foot(bool isStanding,
                            const hkQsTransform& worldFromModel,
                            hkaPose& poseInOut,
                            hkReal& verticalDisplacementInOut)
{
#ifdef HAVOK_COMPILE
    bool footIkOn = m_enabled;
    const FootResource* res = m_resource;
    const int* jointIndices = res->m_rig->m_humanJointIndices;

    hkReal rightError;
    hkReal leftError;

    const hkQsTransform& originalLeftFootMS = poseInOut.getBoneModelSpace(jointIndices[kBodyFoot_L]);
    const hkQsTransform& originalRightFootMS = poseInOut.getBoneModelSpace(jointIndices[kBodyFoot_R]);
#if 0
    // Update some tweakable setup parameters
    m_solver[kRightLeg]->m_setup.m_maxAnkleHeightMS = res->m_maxAnkleHeightMS;;
    m_solver[kLeftLeg]->m_setup.m_maxAnkleHeightMS = res->m_maxAnkleHeightMS;;
    m_solver[kRightLeg]->m_setup.m_minAnkleHeightMS = res->m_minAnkleHeightMS;;
    m_solver[kLeftLeg]->m_setup.m_minAnkleHeightMS = res->m_minAnkleHeightMS;;
#endif

    hkaFootPlacementIkSolver::Input footPlacementInput;
    footPlacementInput.m_raycastInterface = m_raycast;
    footPlacementInput.m_worldFromModel = worldFromModel;
    footPlacementInput.m_groundAscendingGain = (isStanding) ? res->m_standAscendingGain : res->m_groundAscendingGain;
    footPlacementInput.m_groundDescendingGain = res->m_groundDescendingGain;
    footPlacementInput.m_footPlantedGain = res->m_footPlantedGain;
    footPlacementInput.m_footRaisedGain = res->m_footRaisedGain;
    footPlacementInput.m_onOffGain = res->m_footOnOffGain;
    footPlacementInput.m_footPlacementOn = footIkOn;

    int index = g_physicsWorld.get_layer(res->m_raycastCollisionLayer);
    if(index)
    {
        footPlacementInput.m_collisionFilterInfo  = hkpGroupFilter::calcFilterInfo(index);
        footPlacementInput.m_useCollisionFilterInfo = true;
    }

    // LEFT LEG
    {
        footPlacementInput.m_originalAnkleTransformMS = originalLeftFootMS;

        hkaFootPlacementIkSolver::Output footPlacementOutput;
        m_solver[0]->doFootPlacement(footPlacementInput, footPlacementOutput, poseInOut);

        leftError = footPlacementOutput.m_verticalError;
        m_footOnAir[0] = ! footPlacementOutput.m_hitSomething;
    }

    // RIGHT LEG
    {
        footPlacementInput.m_originalAnkleTransformMS = originalRightFootMS;

        hkaFootPlacementIkSolver::Output footPlacementOutput;
        m_solver[1]->doFootPlacement(footPlacementInput, footPlacementOutput, poseInOut);

        rightError = footPlacementOutput.m_verticalError;
        m_footOnAir[1] = ! footPlacementOutput.m_hitSomething;
    }

    // If standing, we always bias going down
    const hkReal w = isStanding ? 1.0f : res->m_pelvisUpDownBias;
    const hkReal weightedError = w * hkMath::min2(leftError, rightError) + (1.0f - w) * hkMath::max2(leftError, rightError);
    hkReal pelvisDelta = weightedError * res->m_pelvisFeedback; // damp it

    verticalDisplacementInOut += pelvisDelta;

    // Clamp
    if (verticalDisplacementInOut > 0.5f)
    {
        verticalDisplacementInOut = 0.5f;
    }
    if (verticalDisplacementInOut < -0.5f)
    {
        verticalDisplacementInOut = -0.5f;
    }
#endif
}