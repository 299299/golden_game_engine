#pragma once
#include "Prerequisites.h"

#ifdef HAVOK_COMPILE
#include <Animation/Animation/Ik/FootPlacement/hkaFootPlacementIkSolver.h>

enum AnimRaycastType
{
    kRaycastPhysics = 0,
    kRaycastGraphics
};

//@TODO
//Use the raycast result from last frame.
class AnimRaycastInterface : public hkaRaycastInterface
{
public:
    HK_DECLARE_NONVIRTUAL_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER,AnimRaycastInterface);
    AnimRaycastInterface();
    virtual hkBool castRay ( const hkVector4& fromWS,
                             const hkVector4& toWS,
                             hkReal& hitFractionOut,
                             hkVector4& normalWSOut );
    virtual hkBool castRay ( const hkVector4& fromWS,
                             const hkVector4& toWS,
                             hkUint32 collisionFilterInfo,
                             hkReal& hitFractionOut,
                             hkVector4& normalWSOut );

private:
    hkBool castPhysicsRay(const hkVector4& fromWS,
                          const hkVector4& toWS,
                          hkUint32 collisionFilterInfo,
                          hkReal& hitFractionOut,
                          hkVector4& normalWSOut );
    hkBool castGraphicsRay(const hkVector4& fromWS,
                           const hkVector4& toWS,
                           hkUint32 collisionFilterInfo,
                           hkReal& hitFractionOut,
                           hkVector4& normalWSOut );

public:
    int             m_type;
};
#else
class AnimRaycastInterface
{
public:
    int m_type;
};
#endif

