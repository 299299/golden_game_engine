#include "Ragdoll.h"
#include "PhysicsWorld.h"
#include "PhysicsAutoLock.h"
#include "DataDef.h"
#include "Log.h"
#include "Resource.h"
#include "Utils.h"
#include "EngineAssert.h"
//==================================================================
#include <Common/Serialize/Util/hkRootLevelContainer.h>
#include <Animation/Physics2012Bridge/Instance/hkaRagdollInstance.h>
#include <Animation/Physics2012Bridge/Controller/PoweredConstraint/hkaRagdollPoweredConstraintController.h>
#include <Animation/Physics2012Bridge/Controller/RigidBody/hkaRagdollRigidBodyController.h>
#include <Animation/Physics2012Bridge/Utils/hkaRagdollUtils.h>
#include <Common/Visualize/hkDebugDisplay.h>
#include <Common/Base/Container/LocalArray/hkLocalBuffer.h>
#include <Animation/Animation/Rig/hkaSkeleton.h>
#include <Animation/Animation/Playback/hkaAnimatedSkeleton.h>
#include <Animation/Animation/Rig/hkaSkeletonUtils.h>
#include <Animation/Animation/Rig/hkaPose.h>
#include <Animation/Animation/Mapper/hkaSkeletonMapper.h>
#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>
#include <Physics/Constraint/Data/Ragdoll/hkpRagdollConstraintData.h>
#include <Common/Base/Container/Array/hkFixedInplaceArray.h>
#include <Physics/Constraint/Motor/Position/hkpPositionConstraintMotor.h>
#include <Physics/Constraint/Data/LimitedHinge/hkpLimitedHingeConstraintData.h>
#include <Physics2012/Utilities/Constraint/Bilateral/hkpConstraintUtils.h>
#include <Physics2012/Collide/Filter/Group/hkpGroupFilter.h>
//==================================================================

static int   findBoneIndex(const hkaSkeleton* skeleton, const StringId& boneName)
{
    for(int i=0;i<skeleton->m_bones.getSize();++i)
    {
        const hkaBone& bone = skeleton->m_bones[i];
        if(boneName == StringId(bone.m_name.cString()))
            return i;
    }
    return -1;
}
bool boneInArray(hkInt16 boneId, const hkInt16* bones, uint8_t num)
{
    for(uint8_t i=0; i<num; ++i)
    {
        if(bones[i] == boneId)
            return true;
    }
    return false;
}
//=====================================================================
//                   RESOURCE
//=====================================================================
void RagdollResource::load(hkRootLevelContainer* container)
{
    m_ragdoll = LOAD_OBJECT(container, hkaRagdollInstance);
    ENGINE_ASSERT(m_ragdoll, "can not load hkaRagdollInstance");
    const hkaSkeleton* ragdollSkeleton = m_ragdoll->getSkeleton();
    void *objectFound = LOAD_OBJECT(container, hkaSkeletonMapper);
    while (objectFound)
    {
        hkaSkeletonMapper* mapperFound = reinterpret_cast<hkaSkeletonMapper*> (objectFound);
        // Use the skeleton to dtermine which mapper is which
        if (mapperFound->m_mapping.m_skeletonA == ragdollSkeleton)
        {
            m_ragdollToHighResMapper = mapperFound;
        }
        else
        {
            ENGINE_ASSERT(mapperFound->m_mapping.m_skeletonB == ragdollSkeleton, 
                         "mapperFound->m_mapping.m_skeletonB == ragdollSkeleton");
            m_highResToRagdollMapper = mapperFound;
        }
        objectFound = container->findObjectByType(hkaSkeletonMapperClass.getName(), objectFound);
    }
    ENGINE_ASSERT(m_highResToRagdollMapper, "Couldn't load high-to-ragdoll mapping");
    ENGINE_ASSERT(m_ragdollToHighResMapper, "Couldn't load ragdoll-to-high mapping");

    // Create a list of bones in the lower body
    // We use this array to set the leg bones / lower body to keyframed and upper body to dynamic later.
    {
        const hkaSkeleton* skeleton = m_ragdoll->getSkeleton();
        m_numLowerBodyBones = 0;

        // Pelvis
        m_lowerBodyBones[m_numLowerBodyBones++] = 0;

        // Right Leg
        const hkInt16 startRight = findBoneIndex(skeleton, m_rightLeg);
        m_lowerBodyBones[m_numLowerBodyBones++] = startRight;
        hkLocalArray<hkInt16> bones(100);
        hkaSkeletonUtils::getDescendants(*skeleton, startRight, bones);
        for(int i=0; i<bones.getSize(); ++i)
            m_lowerBodyBones[m_numLowerBodyBones++] = bones[i];

        // Left leg
        const hkInt16 startLeft = findBoneIndex(skeleton, m_leftLeg);
        m_lowerBodyBones[m_numLowerBodyBones++] = startLeft;
        bones.clear();
        hkaSkeletonUtils::getDescendants(*skeleton, startRight, bones);
        for(int i=0; i<bones.getSize(); ++i)
            m_lowerBodyBones[m_numLowerBodyBones++] = bones[i];

        LOGD("num of lower body bones = %d.", m_numLowerBodyBones);
        ENGINE_ASSERT(m_numLowerBodyBones <= MAX_LOWER_BODY_BONE, "lower body bone num overflow.");
    }
}

//=====================================================================
//                   INSTANCE
//=====================================================================
// Set quality and filter info for a ragdoll body part
static void setDynamicWithCollisions(hkpRigidBody* rb, int,int,int);
static void setDynamicWithoutCollisions(hkpRigidBody* rb,int);
static void setKeyframedWithoutCollisions(hkpRigidBody* rb,int);

void RagdollInstance::init(const void* resource)
{
    m_dynamicTime = 0.0f;
    m_initFeedback = false;
    m_resource = (const RagdollResource*)resource;
    m_ragdoll = m_resource->m_ragdoll->clone(hkpConstraintInstance::CLONE_DATAS_WITH_MOTORS);
    
    int dynamicLayer = g_physicsWorld.getFilterLayer(m_resource->m_dynamicLayer);

    // Initialize collision/motion settings for the rigidbody ragdoll parts
    for ( int b =0; b < m_ragdoll->getNumBones(); b++)
    {
        hkpRigidBody* rb = m_ragdoll->getRigidBodyOfBone(b);
        // Initialize with quality type and collision filter
        setDynamicWithCollisions( rb, b, m_ragdoll->getParentOfBone( b ), dynamicLayer );
    }

    // We turn off friction for all constraints - this helps the controllers match the animation pose better
    for ( int c =1; c < m_ragdoll->getNumBones(); c++)
    {
        hkpConstraintData* constraintData = m_ragdoll->getConstraintOfBone(c)->getDataRw();
        switch (constraintData->getType())
        {
            case hkpConstraintData::CONSTRAINT_TYPE_LIMITEDHINGE:
            {
                hkpLimitedHingeConstraintData* hinge = static_cast<hkpLimitedHingeConstraintData*> (constraintData);
                hinge->setMaxFrictionTorque( 0.0f );
                break;
            }
            case hkpConstraintData::CONSTRAINT_TYPE_RAGDOLL:
            {
                hkpRagdollConstraintData* ragdoll = static_cast<hkpRagdollConstraintData*> (constraintData);
                ragdoll->setMaxFrictionTorque( 0.0f );
                break;
            }
        }
    }


    // This routine iterates through the bodies pointed to by the constraints and stabilizes their inertias.
    // This makes both ragdoll controllers lees sensitive to angular effects and hence more effective
    const hkArray<hkpConstraintInstance*>& constraints = m_ragdoll->getConstraintArray();
    hkpInertiaTensorComputer::optimizeInertiasOfConstraintTree( constraints.begin(), 
                                                                constraints.getSize(), 
                                                                m_ragdoll->getRigidBodyOfBone(0) );

    // Construct the ragdoll rigidbody controller
    // This controller handles the hit reaction
    m_rigidBodyController = new hkaRagdollRigidBodyController( m_ragdoll );
}

void RagdollInstance::destroy()
{
    removeFromSimulation();
    SAFE_DELETE(m_rigidBodyController);
    SAFE_REMOVEREF(m_ragdoll);
}

void RagdollInstance::addToSimulation()
{
    if(m_ragdoll->getWorld())
        return;
    hkpWorld* hkWorld = g_physicsWorld.getWorld();
    PHYSICS_LOCKWRITE(hkWorld);
    m_ragdoll->addToWorld(hkWorld, true);
}

void RagdollInstance::removeFromSimulation()
{
    if(!m_ragdoll)
        return;
    hkpWorld* world = m_ragdoll->getWorld();
    if(!world)
        return;
    PHYSICS_LOCKWRITE(world);
    m_ragdoll->removeFromWorld();
}

// doRagdoll() : drives the ragdoll to the incoming pose and modifies that pose to reflect the ragdoll
hkVector4 RagdollInstance::doRagdoll( const hkQsTransform& worldFromModel, 
                                      hkaPose& thePose,  
                                      float timeStep )
{
    // Get the ragdoll's reference pose in model space
    // We use this pose as the in+out pose to the mapper below
    const hkaSkeleton* rSkel = m_ragdoll->getSkeleton();
    hkLocalBuffer<hkQsTransform> ragdollModelSpace( rSkel->m_bones.getSize() );
    hkaSkeletonUtils::transformLocalPoseToModelPose( rSkel->m_bones.getSize(), 
                                                     rSkel->m_parentIndices.begin(), 
                                                     rSkel->m_referencePose.begin(), 
                                                     ragdollModelSpace.begin() );

    // Map the pose from the animation (highres) to ragdoll (lowres)
    m_resource->m_highResToRagdollMapper->mapPose( thePose.getSyncedPoseModelSpace().begin(), 
                                       rSkel->m_referencePose.begin(), 
                                       ragdollModelSpace.begin(), 
                                       hkaSkeletonMapper::CURRENT_POSE );

    // Drive the powered constraints to this ragdoll pose using a controller
    {
        hkLocalBuffer<hkQsTransform> ragdollLocalSpace( rSkel->m_bones.getSize() );
        hkaSkeletonUtils::transformModelPoseToLocalPose( rSkel->m_bones.getSize(), 
                                                         rSkel->m_parentIndices.begin(), 
                                                         ragdollModelSpace.begin(), 
                                                         ragdollLocalSpace.begin() );

        hkaRagdollPoweredConstraintController::startMotors(m_ragdoll);
        hkaRagdollPoweredConstraintController::driveToPose( m_ragdoll,  ragdollLocalSpace.begin() ) ;
    }

    // Get the current pose from the ragdoll, map it back to the character
    {
        m_ragdoll->getPoseModelSpace(ragdollModelSpace.begin(), worldFromModel);

        const hkQsTransform* localBIn  = thePose.getSyncedPoseLocalSpace().begin();
        hkQsTransform*       modelBOut = thePose.accessSyncedPoseModelSpace().begin();
        m_resource->m_ragdollToHighResMapper->mapPose( ragdollModelSpace.begin(), localBIn, modelBOut, hkaSkeletonMapper::CURRENT_POSE );
    }

    // During the first half second, we check that no constraints are violated: this may happen if the ragdoll
    // started in a position where some bones where penetrating the landscape. We use the checkAndFixConstraint() utility method
    // to push the bones out.
    if (m_dynamicTime < 0.5f)
    {
        const hkArray<hkpConstraintInstance*>& constraints = m_ragdoll->getConstraintArray();
        for (int c=constraints.getSize()-1; c>=0; --c)
        {
            // Do only one at a time
            if (hkpConstraintUtils::checkAndFixConstraint(constraints[c], 0.1f))
                break;
        }
    }

    m_dynamicTime += timeStep;
    // For this demo, we force the proxy to follow the root - 
    // we just do this to simplify shadow calcs which are relative to the proxy
    // In general, you don't need to do this
    //m_characterProxy->setPosition( ragdollInstance_->getRigidBodyOfBone(0)->getPosition() );
    //@TODO
    return m_ragdoll->getRigidBodyOfBone(0)->getPosition();
}

// doRagdollFeedback() drives the rigid bodies that make up the ragdoll during non-death states. This is used for get hit effects, and
// for bone collisions.
// By default, the lower body is keyframed - it doesn't react, while the upper body is dynamic - it reacts.
void RagdollInstance::doRagdollFeedback(const hkQsTransform& worldFromModel, 
                                        hkaPose &thePose, 
                                        float timeStep)
{
    const RagdollResource* res = m_resource;
    // We start by mapping the animation pose to the low-res space
    // Start with the reference pose (in+out parameter to mapper)
    const hkaSkeleton* rSkel = m_ragdoll->getSkeleton();
    hkLocalBuffer<hkQsTransform> lowResModelSpace( rSkel->m_bones.getSize() );
    hkaSkeletonUtils::transformLocalPoseToModelPose( rSkel->m_bones.getSize(), 
                                                     rSkel->m_parentIndices.begin(), 
                                                     rSkel->m_referencePose.begin(), 
                                                     lowResModelSpace.begin() );

    // Map from animation to ragdoll
    res->m_highResToRagdollMapper->mapPose( thePose.getSyncedPoseModelSpace().begin(), 
                                       rSkel->m_referencePose.begin(), 
                                       lowResModelSpace.begin(), 
                                       hkaSkeletonMapper::CURRENT_POSE );

    // Convert the output to local space (required by the controller
    hkLocalBuffer<hkQsTransform> lowResLocalSpace( rSkel->m_bones.getSize() );
    hkaSkeletonUtils::transformModelPoseToLocalPose( rSkel->m_bones.getSize(), 
                                                     rSkel->m_parentIndices.begin(), 
                                                     lowResModelSpace.begin(), 
                                                     lowResLocalSpace.begin() );

    // If we weren't doing this before...
    if (!m_initFeedback)
    {
        // Switch off any motors that we may have on (if we were doing ragdolls in death state)
        hkaRagdollPoweredConstraintController::stopMotors( m_ragdoll );
        m_ragdoll->setPoseModelSpace(lowResModelSpace.begin(), worldFromModel);
        const hkInt16* lowerBodyBones = res->m_lowerBodyBones;
        uint8_t numOfBones = res->m_numLowerBodyBones;

        int keyframeLayer = g_physicsWorld.getFilterLayer(res->m_keyframeLayer);
        int dynamicLayer = g_physicsWorld.getFilterLayer(res->m_dynamicLayer);

        // Set the properties (motion type and collision filter) of the rigid bodies representing the bones
        for (int i=0; i < m_ragdoll->getNumBones(); i++)
        {
            hkpRigidBody* rb = m_ragdoll->getRigidBodyOfBone(i);

            // Bones in the legs are usually keyframed (unless the user has told us otherwise)
            // Rest of bones (upper body) are dynamic (for get-hit effects).
            // We put all of them in the same system to ignore collisions between bones
            bool isLowerBodyBone = boneInArray(i, lowerBodyBones, numOfBones);
            if (res->m_fixLegs && isLowerBodyBone)
                setKeyframedWithoutCollisions( rb, keyframeLayer);
            else
                setDynamicWithoutCollisions( rb, dynamicLayer);
            rb->setLinearVelocity( hkVector4::getZero() );
            rb->setAngularVelocity( hkVector4::getZero() );
        }

        // Let the ragdoll rigid body controller know that we are starting to drive rigid bodies again
        m_rigidBodyController->reinitialize();
        m_initFeedback = true;
    }

    const int numBodies = m_ragdoll->getRigidBodyArray().getSize();
    HK_TIMER_BEGIN("KFHUtil", HK_NULL);

    // We now drive the rigid bodies so they follow the animation, using a ragdoll rigid body controller
    hkaKeyFrameHierarchyUtility::ControlData& controlData = m_rigidBodyController->m_controlDataPalette[0];

    controlData.m_hierarchyGain =   res->m_hierarchyGain;
    controlData.m_velocityDamping = res->m_dampVelocity;
    controlData.m_accelerationGain = res->m_accelerationGain;
    controlData.m_velocityGain = res->m_velocityGain;
    controlData.m_positionGain = res->m_positionGain;
    controlData.m_positionMaxLinearVelocity = res->m_positionMaxLinearVelocity;
    controlData.m_positionMaxAngularVelocity = res->m_positionMaxAngularVelocity;
    controlData.m_snapGain = res->m_snapGain;
    controlData.m_snapMaxLinearVelocity = res->m_snapMaxLinearVelocity;
    controlData.m_snapMaxAngularVelocity = res->m_snapMaxAngularVelocity;
    controlData.m_snapMaxLinearDistance =  res->m_snapMaxLinearDistance;
    controlData.m_snapMaxAngularDistance = res->m_snapMaxAngularDistance;
    hkLocalBuffer<hkaKeyFrameHierarchyUtility::Output> output(numBodies);
    m_rigidBodyController->driveToPose( timeStep, lowResLocalSpace.begin(), 
                                        worldFromModel, output.begin());

    HK_TIMER_END();

    // Get the current pose, and blend based on stress
    {
        hkLocalBuffer<hkQsTransform> ragdollModelSpace( rSkel->m_bones.getSize() );
        m_ragdoll->getPoseModelSpace(ragdollModelSpace.begin(), worldFromModel);

        hkLocalBuffer<hkQsTransform> ragdollLocalSpace( rSkel->m_bones.getSize() );
        hkaSkeletonUtils::transformModelPoseToLocalPose( rSkel->m_bones.getSize(), 
                                                         rSkel->m_parentIndices.begin(), 
                                                         ragdollModelSpace.begin(), 
                                                         ragdollLocalSpace.begin() );

        float ragdollFeedBack = m_resource->m_ragdollFeedback;
        for (int i =0; i < numBodies; i++ )
        {
            // Show stress : we set the color of rigid bodies based on 
            //the output of the controller (the stress)
    #ifndef _RETAIL
            {
                hkReal stress = hkMath::sqrt( output[i].m_stressSquared );
                stress *= 0.05f; // scale the value for display
                stress = hkMath::max2( stress, 0.0f );
                stress = hkMath::min2( stress, 1.0f );

                HK_TIMER_BEGIN("DisplayObject", HK_NULL);
                int color = 0xff808080;
                int colorOffset = int( stress * 127 );
                color -= colorOffset << 16;
                color += colorOffset << 8;
                color -= colorOffset << 0;
                HK_SET_OBJECT_COLOR( hkUlong( m_ragdoll->getRigidBodyArray()[i]->getCollidable()), color );
                HK_TIMER_END();
            }
    #endif

            // Here we do the interpolation  between the animation-based pose and 
            // the ragdoll-based pose, based on the stress
            lowResLocalSpace[i].setInterpolate4( lowResLocalSpace[i], 
                                                 ragdollLocalSpace[i], 
                                                 ragdollFeedBack);
        }
    }

    // We now map the blended pose to the high res skeleton
    {
        // Need to recalculate the model space version of the blended pose
        hkaSkeletonUtils::transformLocalPoseToModelPose( rSkel->m_bones.getSize(), 
                                                         rSkel->m_parentIndices.begin(), 
                                                         lowResLocalSpace.begin(), 
                                                         lowResModelSpace.begin() );

        // Do the mapping
        const hkQsTransform* localBIn  = thePose.getSyncedPoseLocalSpace().begin();
        hkQsTransform*       modelBOut = thePose.accessSyncedPoseModelSpace().begin();
        res->m_ragdollToHighResMapper->mapPose(  lowResModelSpace.begin(), 
                                                        localBIn, modelBOut, 
                                                        hkaSkeletonMapper::CURRENT_POSE );
    }
}

void RagdollInstance::stopRagdollFeedback()
{
    m_initFeedback = false;
    int dynamicLayer = g_physicsWorld.getFilterLayer(m_resource->m_dynamicLayer);
    for (int b=0; b<m_ragdoll->getNumBones(); b++ )
    {
        const int parentId = m_ragdoll->getParentOfBone(b);
        setDynamicWithCollisions( m_ragdoll->getRigidBodyOfBone(b), b, parentId, dynamicLayer);
    }
}

// Currently in the toolchain all constraints for a single ragdoll share the same motor.
// We could simply grab the first motor and set its params but instead
// we iterate through all the constraints and build a proper list of motors to set.
void RagdollInstance::setMotors(float force, float tau, float propRecoveryVel, float conRecoveryVel)
{
    hkLocalArray<hkpPositionConstraintMotor*> motors( m_ragdoll->getNumBones() );
    for ( int c =1; c < m_ragdoll->getNumBones(); c++)
    {
        hkpConstraintData* constraintData = m_ragdoll->getConstraintOfBone(c)->getDataRw();

        switch (constraintData->getType())
        {
            case hkpConstraintData::CONSTRAINT_TYPE_LIMITEDHINGE:
            {
                hkpLimitedHingeConstraintData* powered = static_cast<hkpLimitedHingeConstraintData*> (constraintData);
                hkpPositionConstraintMotor* motor = (hkpPositionConstraintMotor*)powered->getMotor();
                if (motor && (motors.indexOf(motor) == -1) )
                {
                    motors.pushBack( motor );
                }
                break;
            }
            case hkpConstraintData::CONSTRAINT_TYPE_RAGDOLL:
            {
                hkpRagdollConstraintData* powered = static_cast<hkpRagdollConstraintData*> (constraintData);
                hkpPositionConstraintMotor* motor = (hkpPositionConstraintMotor*)powered->getPlaneMotor();
                if (motor && (motors.indexOf(motor) == -1) )
                {
                    motors.pushBack( motor );
                }
                motor = (hkpPositionConstraintMotor*)powered->getConeMotor();
                if (motor && (motors.indexOf(motor) == -1) )
                {
                    motors.pushBack( motor );
                }
                motor = (hkpPositionConstraintMotor*)powered->getTwistMotor();
                if (motor && (motors.indexOf(motor) == -1) )
                {
                    motors.pushBack( motor );
                }
                break;
            }
        }
    }

    for (int m=0 ;m < motors.getSize(); m++)
    {
        motors[m]->m_maxForce = force;
        motors[m]->m_tau = tau;
        motors[m]->m_proportionalRecoveryVelocity = propRecoveryVel;
        motors[m]->m_constantRecoveryVelocity = conRecoveryVel;
    }
}

void RagdollInstance::setTransform( const hkQsTransform& t )
{
    // Set the pose for the ragdoll bones
    {
        // Get the current animation pose, convert it to model space.
        // We reuse the same array: transformLocalPoseToModelPose is alias safe (but transformModelPoseToLocalPose is not!)
        const hkaSkeleton* skel = m_animSkeleton->getSkeleton();
        hkLocalBuffer< hkQsTransform > animPose( skel->m_bones.getSize() );
        m_animSkeleton->sampleAndCombineAnimations( animPose.begin(), HK_NULL );
        hkaSkeletonUtils::transformLocalPoseToModelPose( skel->m_bones.getSize(), 
            skel->m_parentIndices.begin(), 
            animPose.begin(), 
            animPose.begin() );

        // Now, map the animation pose into a low-res pose we can use for the ragdoll
        // We start with the reference pose (in model space)
        const hkaSkeleton* rSkel = m_ragdoll->getSkeleton();
        hkLocalBuffer<hkQsTransform> ragdollModelSpace( rSkel->m_bones.getSize() );
        hkaSkeletonUtils::transformLocalPoseToModelPose( rSkel->m_bones.getSize(), 
            rSkel->m_parentIndices.begin(), 
            rSkel->m_referencePose.begin(), 
            ragdollModelSpace.begin() );
        m_resource->m_highResToRagdollMapper->mapPose( animPose.begin(), 
            rSkel->m_referencePose.begin(), 
            ragdollModelSpace.begin(), 
            hkaSkeletonMapper::CURRENT_POSE );

        // Set the resulting pose to the ragdoll
        m_ragdoll->setPoseModelSpace( ragdollModelSpace.begin(), t );
    }

    // Tell the ragdoll rigid body controller that the position of the rigid bodies have changes, and we need to
    // start driving based on the new positions.
    m_rigidBodyController->reinitialize();
}

void RagdollInstance::setEnabled( bool bEnable )
{
    if(bEnable) addToSimulation();
    else removeFromSimulation();
}



//===================================================================================================
//          HELPER FUNCTIONS

// Given a rigid body (a ragdoll bone), make it dynamic, enable collisions with all bones except its parent,
// and set the layer and quality properties accordingly
static void setDynamicWithCollisions(hkpRigidBody* rb, int boneId, int parentId, int layerId)
{
    const hkUint32 fi = hkpGroupFilter::calcFilterInfo(layerId, 1, boneId+1, parentId+1);

    if (( rb->getMotionType() == hkpMotion::MOTION_KEYFRAMED ) ||
        ( rb->getQualityType() != HK_COLLIDABLE_QUALITY_MOVING) ||
        ( rb->getCollisionFilterInfo() != fi))
    {
        rb->setMotionType(hkpMotion::MOTION_DYNAMIC);
        rb->setQualityType( HK_COLLIDABLE_QUALITY_MOVING );
        rb->setCollisionFilterInfo(fi);

        if (rb->getWorld())
        {
            rb->getWorld()->updateCollisionFilterOnEntity( rb, HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK, HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS );
        }
    }
}

// Given a rigid body (a ragdoll bone), make it dynamic, disable collisions with all bones in the ragdoll (assign the same system with
// no subsystems), and set the layer and quality properties accordingly
static void setDynamicWithoutCollisions(hkpRigidBody* rb, int layerId)
{
    const hkUint32 newFi = hkpGroupFilter::calcFilterInfo(layerId,1, 0, 0);

    if (( rb->getMotionType() == hkpMotion::MOTION_KEYFRAMED ) ||
        ( rb->getQualityType() != HK_COLLIDABLE_QUALITY_MOVING) ||
        ( rb->getCollisionFilterInfo() != newFi))
    {
        rb->setMotionType(hkpMotion::MOTION_DYNAMIC);
        rb->setQualityType( HK_COLLIDABLE_QUALITY_MOVING );
        rb->setCollisionFilterInfo(newFi);

        if (rb->getWorld())
        {
            rb->getWorld()->updateCollisionFilterOnEntity( rb, HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK, HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS );
        }
    }
}

// Given a rigid body (a ragdoll bone), make it keyframed, disable collisions with all bones in the ragdoll (assign the same system with
// no subsystems), and set the layer and quality properties accordingly
static void setKeyframedWithoutCollisions(hkpRigidBody* rb, int layerId)
{
    const hkUint32 fi = hkpGroupFilter::calcFilterInfo(layerId, 1, 0, 0);

    if (( rb->getMotionType() != hkpMotion::MOTION_KEYFRAMED ) ||
        ( rb->getQualityType() != HK_COLLIDABLE_QUALITY_KEYFRAMED) ||
        ( rb->getCollisionFilterInfo() != fi))
    {
        rb->setMotionType(hkpMotion::MOTION_KEYFRAMED);
        rb->setQualityType( HK_COLLIDABLE_QUALITY_KEYFRAMED );
        rb->setCollisionFilterInfo(fi);

        if (rb->getWorld())
        {
            rb->getWorld()->updateCollisionFilterOnEntity( rb, HK_UPDATE_FILTER_ON_ENTITY_FULL_CHECK, HK_UPDATE_COLLECTION_FILTER_PROCESS_SHAPE_COLLECTIONS );
        }
    }
}

void* load_resource_ragdoll( const char* data, uint32_t size )
{
    RagdollResource* ragdoll = (RagdollResource*)data;
    char* havokData = (char*)data + ragdoll->m_havokDataOffset;
    hkRootLevelContainer* container = (hkRootLevelContainer*)load_havok_inplace(havokData, ragdoll->m_havokDataSize);
    ragdoll->load(container);
    return ragdoll;
}

void destroy_resource_ragdoll( void* resource )
{
    RagdollResource* ragdoll = (RagdollResource*)resource;
    char* havokData = (char*)resource + ragdoll->m_havokDataOffset;
    unload_havok_inplace(havokData, ragdoll->m_havokDataSize);
}
