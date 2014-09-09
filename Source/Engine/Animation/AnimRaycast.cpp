#include "AnimRaycast.h"
#include "PhysicsAutoLock.h"
#include "PhysicsWorld.h"
//==========================================================
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Physics2012/Collide/Filter/Group/hkpGroupFilter.h>
#include <Physics2012/Collide/Query/CastUtil/hkpWorldRayCastInput.h>
#include <Physics2012/Collide/Query/CastUtil/hkpWorldRayCastOutput.h>
#include <Common/Base/Monitor/hkMonitorStream.h>
#include <Physics2012/Collide/Shape/Convex/ConvexTranslate/hkpConvexTranslateShape.h>
#include <Physics2012/Collide/Query/Collector/RayCollector/hkpClosestRayHitCollector.h>
#include <Common/Visualize/hkDebugDisplay.h>
//==========================================================


AnimRaycastInterface::AnimRaycastInterface()
    :m_type(0)
{

}

hkBool AnimRaycastInterface::castRay (const hkVector4& fromWS,
                                      const hkVector4& toWS,
                                      hkReal& hitFractionOut,
                                      hkVector4& normalWSOut )
{
    return castRay(fromWS, toWS,  0, hitFractionOut, normalWSOut);
}


hkBool
AnimRaycastInterface::castRay ( const hkVector4& fromWS,
                                const hkVector4& toWS,
                                hkUint32 collisionFilterInfo,
                                hkReal& hitFractionOut,
                                hkVector4& normalWSOut )
{
    if(m_type == 0)
    {
        return castPhysicsRay(fromWS, 
                              toWS,
                              collisionFilterInfo,
                              hitFractionOut,
                              normalWSOut);
    }
    else if(m_type == 1)
    {
        return castGraphicsRay(fromWS, 
                               toWS,
                               collisionFilterInfo,
                               hitFractionOut,
                               normalWSOut);
    }
    return false;
}

hkBool 
AnimRaycastInterface::castPhysicsRay(const hkVector4& fromWS, 
                                     const hkVector4& toWS, 
                                     hkUint32 collisionFilterInfo, 
                                     hkReal& hitFractionOut, 
                                     hkVector4& normalWSOut )
{
    HK_TIMER_BEGIN("Raycast", HK_NULL);

    // Raycast info structures, we use the RAYCAST layer to filter hits
    hkpWorldRayCastInput raycastIn;
    raycastIn.m_from = fromWS;
    raycastIn.m_to = toWS;
    raycastIn.m_filterInfo = collisionFilterInfo;

    // Cast the ray into the landscape
    // We only collect the closest hit
    hkpClosestRayHitCollector rayCollector;
    {
        hkpWorld* world = g_physicsWorld.getWorld();
        PHYSICS_LOCKREAD(world);
        world->castRay( raycastIn, rayCollector );
    }
    
    const hkBool didHit = rayCollector.hasHit();

    if (didHit)
    {
        const hkpWorldRayCastOutput& raycastOut = rayCollector.getHit();

        #if 1   
        hkVector4 intersectionPointWorld;
        intersectionPointWorld.setInterpolate4( raycastIn.m_from, raycastIn.m_to, raycastOut.m_hitFraction );
        HK_DISPLAY_LINE( raycastIn.m_from, intersectionPointWorld, hkColor::YELLOW);
        HK_DISPLAY_ARROW( intersectionPointWorld, raycastOut.m_normal, hkColor::CYAN);
        #endif

        normalWSOut = raycastOut.m_normal;
        hitFractionOut = raycastOut.m_hitFraction;

        const hkVector4 upWS(0,1,0);

        // Ignore surfaces too steep. Let's pick an angle of 70 degrees. Cos(70) ~= 0.34
        if (normalWSOut.dot3(upWS) < 0.34f)
            return false;

        // For movable convex shapes (crates), we need to consider that the object they represent is slightly bigger
        // Therefore we move the result up by the radius.

        const hkpShape* shape = raycastOut.m_rootCollidable->getShape();
        if (shape->getType() == hkcdShapeType::CONVEX_TRANSLATE)
        {
            // Add radius
            hkVector4 ray; ray.setSub4( raycastIn.m_to, raycastIn.m_from);
            hkReal rayLength = ray.length3();
            hitFractionOut -= ((const hkpConvexTranslateShape*)shape)->getRadius() / rayLength;
            hitFractionOut = hkMath::max2(0.0f, hitFractionOut);
        }
    }

    HK_TIMER_END();
    return didHit;
}

hkBool 
AnimRaycastInterface::castGraphicsRay(const hkVector4& fromWS, 
                                      const hkVector4& toWS, 
                                      hkUint32 collisionFilterInfo, 
                                      hkReal& hitFractionOut, 
                                      hkVector4& normalWSOut )
{
    return false;
}