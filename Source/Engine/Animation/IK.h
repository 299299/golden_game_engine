#pragma once
#include "StringId.h"
#include "Prerequisites.h"

class hkaSkeleton;
class hkaPose;
class hkaFootPlacementIkSolver;
struct AnimRigInstance;
struct AnimRig;
class  AnimRaycastInterface;

ENGINE_NATIVE_ALIGN struct LookAtResource
{
    DECLARE_RESOURCE(lookat);

    float                                   m_fwdLS[3];
    float                                   m_lookAtLimit;
    float                                   m_gain;
    float                                   m_targetGain;
    
    const AnimRig*                          m_rig;
    StringId                                m_rigName;
};


ENGINE_NATIVE_ALIGN struct ReachResource
{
    DECLARE_RESOURCE(reach);

    float                                   m_elbowAxis[3];
    float                                   m_hingeLimitAngle[2];    
    float                                   m_targetGain;
    float                                   m_reachGain;
    float                                   m_leaveGain;
    float                                   m_moveGain;
    int                                     m_index;
    
    const AnimRig*                          m_rig;
    StringId                                m_rigName;
};
    
ENGINE_NATIVE_ALIGN struct  FootResource
{
    DECLARE_RESOURCE(foot);

    float                                   m_leftKneeAxisLS[3];
    float                                   m_rightKneeAxisLS[3];
    float                                   m_footEndLS[3];

    float                                   m_orignalGroundHeightMS;
    float                                   m_minAnkleHeightMS;
    float                                   m_maxAnkleHeightMS;
    float                                   m_footPlantedAnkleHeightMS;
    float                                   m_footRaisedAnkleHeightMS;
    float                                   m_cosineMaxKneeAngle;
    float                                   m_cosineMinKneeAngle;
    float                                   m_raycastDistanceUp;
    float                                   m_raycastDistanceDown;
    float                                   m_groundAscendingGain;
    float                                   m_groundDescendingGain;
    float                                   m_standAscendingGain;
    float                                   m_footPlantedGain;
    float                                   m_footRaisedGain;
    float                                   m_footOnOffGain;
    float                                   m_footUnLockGain;
    float                                   m_pelvisFeedback;
    float                                   m_heightError;
    float                                   m_pelvisUpDownBias;
    int                                     m_raycastType;
    StringId                                m_raycastCollisionLayer;
    
    const AnimRig*                          m_rig;
    StringId                                m_rigName;
};

//===================================================================================================

ENGINE_NATIVE_ALIGN struct LookAtInstance
{
    hkVector4                   m_lookAtLastTargetWS;
    const LookAtResource*       m_resource;
    float                       m_lookAtWeight;
    bool                        m_enabled;

    void init(const void* resource);
    void destroy() {};
    void setTransform(const hkQsTransform& t) {};
    void setEnabled(bool bEnable) { m_enabled = bEnable; };
    
    void  doLookAt(const hkVector4& targetPosWS,
                   const hkQsTransform& worldFromModel, 
                   hkaPose& thePose);
};

ENGINE_NATIVE_ALIGN struct ReachInstance
{
    hkVector4                   m_reachLastTargetWS;
    const ReachResource*        m_resource;
    float                       m_reachWeight;
    bool                        m_enabled;

    void init(const void* resource);
    void destroy() {}; 
    void setTransform(const hkQsTransform& t) {};
    void setEnabled(bool bEnable) { m_enabled = bEnable; };

    
    void  doReach(const hkVector4& targetPosWS,
                  const hkQsTransform& worldFromModel, 
                  hkaPose& thePose);
};

ENGINE_NATIVE_ALIGN struct FootInstance
{
    hkaFootPlacementIkSolver*   m_solver[2];
    AnimRaycastInterface*       m_raycast;
    const FootResource*         m_resource;
    float                       m_weight;
    bool                        m_footOnAir[2];
    bool                        m_enabled;

    void init(const void* resource);
    void destroy();
    void setTransform(const hkQsTransform& t) {};
    void setEnabled(bool bEnable) { m_enabled = bEnable; };

    void  createSolver(hkaSkeleton* skel);
    void  doFootIK( bool isStanding,
                    const hkQsTransform& worldFromModel,
                    hkaPose& poseInOut, 
                    hkReal& verticalDisplacementInOut);
};
