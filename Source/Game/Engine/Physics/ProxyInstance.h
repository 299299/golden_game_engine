#pragma once
#include "Prerequisites.h"
#include "StringId.h"

class hkpCharacterProxy;
class hkpSimpleShapePhantom;
class hkpCapsuleShape;
struct AnimCharacterListener;

ENGINE_NATIVE_ALIGN(struct) ProxyResource
{
    void createShape();
    void destroyShape();

    float                       m_gravity[3];
    hkpCapsuleShape*            m_standShape;
    float                       m_radius;
    float                       m_offset;
    float                       m_standHeight;
    float                       m_friction;
    float                       m_strength;
    float                       m_verticalGain;
    float                       m_horizontalGain;
    float                       m_maxVerticalSeparation;
    float                       m_maxHorizontalSeparation;
    StringId                    m_layerName;
};

ENGINE_NATIVE_ALIGN(struct) ProxyInstance
{
    void init(const void* resource);
    void destroy();
    void setTransform(const hkQsTransform& t);
    void setEnabled(bool bEnable);

    void addToSimulation();
    void removeFromSimulation();
    bool checkSupport();
    bool isInWorld() const;
    inline void getGravity(hkVector4& gravity)
    {
        const float* g = m_resource->m_gravity;
#ifdef HAVOK_COMPILE
        gravity.set(g[0], g[1], g[2]);
#endif
    }

    const hkVector4& getLinearVelocity() const;
    const hkVector4& getPosition() const;
    void setLinearVelocity(const hkVector4& vel);
    void setTransform(const hkTransform& t);
    void update(float timeStep);

    hkQsTransform                   m_transform;
    hkVector4                       m_targetVelocity;
    hkVector4                       m_horizontalDisplacement;
    float                           m_verticalDisplacement;

    const ProxyResource*            m_resource;
    hkpCharacterProxy*              m_proxy;
    AnimCharacterListener*          m_listener;
    bool                            m_enabled;
    char                            m_padding[3];
};