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
class hkpRigidBody;

enum RagdollState
{
    kRagdollKeyframed,
    kRagdollDynamic,
    kRagdollNone
};
#define MAX_LOWER_BODY_BONE       (16)

ENGINE_NATIVE_ALIGN(struct) RagdollResource
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

    StringId                                m_keyframeLayer;
    StringId                                m_dynamicLayer;

    uint32_t                                m_havokDataOffset;
    uint32_t                                m_havokDataSize;

    bool                                    m_fixLegs;
    bool                                    m_hasFeedBack;
    uint8_t                                 m_numLowerBodyBones;
    char                                    m_padding[1];
};


ENGINE_NATIVE_ALIGN(struct) RagdollInstance
{
    void init(const void* resource);
    void destroy();
    void set_transform(const hkQsTransform& t);

    void add_to_simulation();
    void remove_from_simulation();

    //=====================================================================================
    hkVector4 do_ragdoll(const hkQsTransform& worldFromModel, hkaPose& thePose,  float timeStep);
    void do_ragdoll_feedback(const hkQsTransform& worldFromModel, hkaPose &thePose, float timeStep);
    void stop_ragdoll_feedback();
    void set_motors(float force, float tau, float propRecoveryVel, float conRecoveryVel);
    //=====================================================================================

    const RagdollResource*                      m_resource;
    hkaAnimatedSkeleton*                        m_animSkeleton;
    hkaRagdollInstance*                         m_ragdoll;
    hkaRagdollRigidBodyController*              m_rigidBodyController;
    float                                       m_dynamicTime;
    uint8_t                                     m_state;
    bool                                        m_initFeedback;
    char                                        m_padding[2];
};
