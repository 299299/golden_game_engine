#pragma once
#include "Prerequisites.h"
#include "StringId.h"

class hkaRagdollInstance;
class hkaSkeletonMapper;
class hkaRagdollRigidBodyController;
class hkLoader;
class hkaAnimatedSkeleton;
class hkaSkeleton;
class hkaPose;
class hkRootLevelContainer;

enum RagdollState
{
    kRagdollKeyframed,
    kRagdollDynamic,
    kRagdollNone
};
#define MAX_LOWER_BODY_BONE       (16)

ENGINE_NATIVE_ALIGN struct RagdollResource
{
    DECLARE_RESOURCE(ragdoll);

    void load(hkRootLevelContainer* container);

    hkInt16                                 m_lowerBodyBones[MAX_LOWER_BODY_BONE];
    hkaRagdollInstance*                     m_ragdoll;
    hkaSkeletonMapper*                      m_ragdollToHighResMapper;
    hkaSkeletonMapper*                      m_highResToRagdollMapper;
    float                                   m_velocityGain;
    float                                   m_positionGain;
    float                                   m_positionMaxLinearVelocity;
    float                                   m_positionMaxAngularVelocity;
    float                                   m_snapGain;
    float                                   m_snapMaxLinearVelocity;
    float                                   m_snapMaxAngularVelocity;
    float                                   m_snapMaxLinearDistance;
    float                                   m_snapMaxAngularDistance;
    float                                   m_ragdollFeedback;
    float                                   m_hierarchyGain;
    float                                   m_dampVelocity;
    float                                   m_accelerationGain;
    StringId                                m_leftLeg;
    StringId                                m_rightLeg;

    uint32_t                                m_havokDataOffset;
    uint32_t                                m_havokDataSize;

    bool                                    m_fixLegs;
    bool                                    m_hasFeedBack;
    uint8_t                                 m_numLowerBodyBones;
    char                                    m_padding[1];
};


ENGINE_NATIVE_ALIGN struct RagdollInstance
{
    void init(const void* resource);
    void destroy();
    void setTransform(const hkQsTransform& t);
    void setEnabled(bool bEnable);

    void addToSimulation();
    void removeFromSimulation();

    //=====================================================================================
    hkVector4 doRagdoll(const hkQsTransform& worldFromModel, hkaPose& thePose,  float timeStep);
    void doRagdollFeedback(const hkQsTransform& worldFromModel, hkaPose &thePose, float timeStep);
    void stopRagdollFeedback();
    void setMotors(float force, float tau, float propRecoveryVel, float conRecoveryVel);
    //=====================================================================================

    ID                                          m_id;
    const RagdollResource*                      m_resource;
    hkaAnimatedSkeleton*                        m_animSkeleton;
    hkaRagdollInstance*                         m_ragdoll;
    hkaRagdollRigidBodyController*              m_rigidBodyController;
    float                                       m_dynamicTime;
    uint8_t                                     m_state;
    bool                                        m_initFeedback;
    char                                        m_padding[2];
};

void* load_resource_ragdoll(const char* data, uint32_t size);
void  destroy_resource_ragdoll(void* resource);