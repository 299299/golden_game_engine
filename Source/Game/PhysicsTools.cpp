#include "PhysicsWorld.h"
#include "PhysicsAutoLock.h"
#include "Camera.h"
#include "Log.h"
#include "Win32Context.h"
//===================================================
#include <Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Physics2012/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>
#include <Physics2012/Utilities/Actions/MouseSpring/hkpMouseSpringAction.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Common/Visualize/hkDebugDisplay.h>
//===================================================


static hkpMouseSpringAction*        g_mouseSpring = 0;
static float                        g_lastMouseDist = 0;
static float                        g_cameraRayDist = 100;

void getCameraRay(hkVector4& outFrom, hkVector4& outTo, hkVector4& outDir)
{
    int32_t x = g_win32Context.m_mx;
    int32_t y = g_win32Context.m_my;
    float pos2d[3] = {(float)x, (float)y, g_cameraRayDist};
    float camTo[3] = {0, 0, 0};
    g_camera.project_2d_to_3d(camTo, pos2d);
    transform_vec3(outFrom, g_camera.m_eye);
    transform_vec3(outTo, camTo);
    outDir.setSub(outTo, outFrom);
    outDir.normalize3();
    HK_DISPLAY_LINE(outFrom, outTo, hkColor::RED);
}

void destroyMouseSpring()
{
    if(!g_mouseSpring)
        return;

    if(g_mouseSpring)
    {
        hkpWorld* world = g_physicsWorld.getWorld();
        PHYSICS_LOCKWRITE(world);
        world->removeAction(g_mouseSpring);
        g_mouseSpring = HK_NULL;
    }
}

void createMouseSpring()
{
    destroyMouseSpring();

    hkVector4 rayOrigin, rayTo, rayDirection;
    getCameraRay(rayOrigin, rayTo, rayDirection);

    hkpWorld* world = g_physicsWorld.getWorld();
    hkpWorldRayCastInput input;
    input.m_from = rayOrigin;
    input.m_to = rayTo;

    hkpWorldRayCastOutput output;
    {
        PHYSICS_LOCKWRITE(world);
        world->castRay(input, output);
    }
    if(!output.m_rootCollidable)
        return;

    hkpRigidBody* rb = hkpGetRigidBody(output.m_rootCollidable);
    LOGI("LeftMouse PhysicsRaycast RB name %s", rb->getName());
    if(rb->isFixedOrKeyframed())
        return;

    g_lastMouseDist = output.m_hitFraction * g_cameraRayDist;
    hkVector4 mousePositionInWorld;
    mousePositionInWorld.setAddMul4(rayOrigin, rayDirection, g_lastMouseDist);

    const hkTransform& t = rb->getTransform();
    hkVector4 posInRBLS;
    posInRBLS.setTransformedInversePos(t, mousePositionInWorld);

    const hkReal springDamping = 0.5f;
    const hkReal springElasticity = 0.3f;
    const hkReal objectDamping = 0.95f;
    const hkReal mouseSpringMaxRelativeForce = 1000;

    PHYSICS_LOCKWRITE(world);
    g_mouseSpring = new hkpMouseSpringAction(posInRBLS, 
        mousePositionInWorld, 
        springDamping, 
        springElasticity, 
        objectDamping, 
        rb);
    g_mouseSpring->setMaxRelativeForce(mouseSpringMaxRelativeForce * 0.1f);
    world->addAction(g_mouseSpring);
    g_mouseSpring->removeReference();
}


void moveMouseSpring()
{
    if(!g_mouseSpring)
        return;
    hkVector4 rayOrigin, rayTo, rayDirection;
    getCameraRay(rayOrigin, rayTo, rayDirection);
    hkVector4 pos;
    pos.setAddMul4(rayOrigin, rayDirection, g_lastMouseDist);
    hkpWorld* world = g_physicsWorld.getWorld();
    {
        PHYSICS_LOCKWRITE(world);
        g_mouseSpring->setMousePosition(pos);
    }
    HK_DISPLAY_STAR(pos, 1.0f, hkColor::RED);
}