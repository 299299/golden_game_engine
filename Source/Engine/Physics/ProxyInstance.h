#pragma once
#include "Prerequisites.h"
#include "StringId.h"

class hkpCharacterProxy;
class hkpSimpleShapePhantom;
class hkpCapsuleShape;
struct AnimCharacterListener;

ENGINE_NATIVE_ALIGN struct ProxyResource
{
    DECLARE_RESOURCE(proxy);

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
    bool                        m_pushIfFootInAir;
    char                        m_padding[3];

    
};

struct ProxyInstance
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
        gravity.set(g[0], g[1], g[2]);
    }

    void applyPhysics(float timeStep, 
                      hkVector4& horizontalDisplacement,
                      hkVector4& desiredVelocity);
    void decouplingRenderWithPhysics(float timeStep,
                                     const float verticalDisplacment,
                                     const hkVector4& horizontalDisplacement,
                                     const hkVector4& desiredVelocity, 
                                     hkQsTransform& transformInOut);
    void avoidLevitation(float timeStep,
                         const bool* footInAir,
                         const hkQsTransform& transform,
                         hkVector4& desiredVelocity);

    const hkVector4& getLinearVelocity() const;
    const hkVector4& getPosition() const;
    void setLinearVelocity(const hkVector4& vel);
    void setTransform(const hkTransform& t);

    const ProxyResource*            m_resource;
    hkpCharacterProxy*              m_proxy;
    AnimCharacterListener*          m_listener;
    ID                              m_id;
};


void* load_resource_proxy(const char* data, uint32_t size);
void  destroy_resource_proxy(void * resource);