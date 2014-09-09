#include "Locomotion.h"
#include "Profiler.h"
//==============physics==================//
#include "ProxyInstance.h"
#include "PhysicsWorld.h"
#include "PhysicsAutoLock.h"
//==============Animation==================//
#include "AnimationSystem.h"
#include "IK.h"
#include "DataDef.h"
#include "AnimRig.h"
//====================================================================
#include <Physics2012/Utilities/CharacterControl/CharacterProxy/hkpCharacterProxy.h>
//====================================================================

static hkVector4 UP(0,1,0);
//#define SIMPLE_ANIMATION_PHYSICS

static float selectAnimation(float angle, float slice)
{
    //as 0 --> [-22.5, 22.5] range
    //we should move it a bit.
    angle += 180.0f/slice;
    float anglePerSlice = 360.0f/slice;
    float ret = angle/anglePerSlice;
    if(ret < 0.0f)
        ret += slice;
    return ret;
}
//-- clamps an angle to the rangle of [-PI, PI]
static float angleDiff( float diff )
{
    if (diff > 180.0f)
        diff -= 360.0f;
    if (diff < -180.0f) 
        diff += 360.0f;
    return diff;
}


void Locomotion::init()
{
    m_horizontalDisplacement.setZero4();
    m_verticalDisplacement = 0.0f;
    m_turnAngleFrameDelta = 0.0f;
    m_state = kLocomotion_Stand;
    m_input.reset();
}

void Locomotion::update(float dt, hkQsTransform& worldFromModel)
{
    updateState(dt);
    applyState(dt, worldFromModel);
}


void Locomotion::updateState(float dt)
{
    switch(m_state)
    {
    case kLocomotion_Stand:
        break;
    case kLocomotion_Move:
        break;
    }
}

void Locomotion::applyState(float dt, hkQsTransform& worldFromModel)
{
    PHYSICS_LOCK(g_physicsWorld.getWorld());
    // Check support
    ProxyInstance* proxy = m_proxy;
    //IKInstance* ik = (IKInstance*)lookup_component_ik(m_ik);
    if(!proxy) return;

    bool bSupport = proxy->checkSupport();
    hkVector4 gravity; proxy->getGravity(gravity);

    // Update character controller based on the animation (extracted motion)
    // Compute the motion for the proxy
    hkQsTransform desiredMotion;
    desiredMotion.setIdentity();
    //m_animation->getRootmotion(dt, desiredMotion);

    //animation drive the rotation
    hkQuaternion q;
    q.setAxisAngle(UP, m_turnAngleFrameDelta * dt);
    worldFromModel.m_rotation.mul(q);
    worldFromModel.m_rotation.mul(desiredMotion.m_rotation);
    worldFromModel.m_rotation.normalize();

    //Apply the player character controller
    //Calculate the velocity we need stateInput order to achieve the desired motion
    hkVector4 desiredVelocity;
    {
        hkVector4 desiredMotionWorld;
        desiredMotionWorld.setRotatedDir( worldFromModel.m_rotation, 
                                          desiredMotion.getTranslation() );
        // Divide motion by time
        desiredVelocity.setMul4 (1.0f / dt, desiredMotionWorld );
    }

    // in these states we ignore the motion coming from the animation
    if ((m_state == kLocomotion_InAir) || 
        (m_state == kLocomotion_Dying) || 
        (m_state == kLocomotion_Dead))
    {
        desiredVelocity = proxy->getLinearVelocity();
    }
    else
    {
        // this is the common case: add the motion velocity to 
        //the downward part of the proxy velocity (not upward though)
        hkReal vertComponent = hkMath::min2(0.0f, (hkReal)proxy->getLinearVelocity().dot3(UP));
        desiredVelocity.addMul4(vertComponent, UP);
    }

    // Add some gravity
    if (m_state != kLocomotion_Stand || !bSupport)
    {
        desiredVelocity.addMul4( dt,  gravity);
    }

/*
    if(m_state == kLocomotion_Stand && bSupport && 
       ik && (ik->m_resource->m_ikMask & kIKFoot))
    {
        bool footInAir[2] = {ik->m_foot.m_footOnAir[0], ik->m_foot.m_footOnAir[1]};
        proxy->avoidLevitation(dt, footInAir, worldFromModel, desiredVelocity);
    }
*/


#ifndef SIMPLE_ANIMATION_PHYSICS
    proxy->applyPhysics(dt, m_horizontalDisplacement, desiredVelocity);
    // Keep track on the decoupling between the proxy and the character (in the vertical axis)
    if (( m_state != kLocomotion_Dying) && ( m_state != kLocomotion_Dead))
        proxy->decouplingRenderWithPhysics(dt, 
                 m_verticalDisplacement,
                 m_horizontalDisplacement,
                 desiredVelocity,
                 worldFromModel);
#else
    proxy->setLinearVelocity(desiredVelocity);
    hkStepInfo si;
    si.m_deltaTime = dt;
    si.m_invDeltaTime = 1.0f / dt;
    proxy->m_proxy->integrate( si, gravity);
    worldFromModel.setTranslation(proxy->getPosition());
#endif
}
