#pragma once
#include "Prerequisites.h"
#include "StringId.h"
#include "Component.h"
#include "id_array.h"

enum LightType
{
    kLightDirectional,
    kLightSpot,
    kLightPoint,
    kLightCount
};

ENGINE_NATIVE_ALIGN struct LightResource
{
    DECLARE_RESOURCE(light);

    float                   m_color[3];
    float                   m_dir[3];
    float                   m_fallOff;
    float                   m_intensity;
    float                   m_coneAngle;
    float                   m_attenScale;

    bool                    m_hasShadow;
    uint8_t                 m_type;
    char                    m_padding[2];
};

struct LightInstance
{
    float                       m_color[3];
    float                       m_vec[3];
    ID                          m_id;
    const LightResource*        m_resource;
    uint8_t                     m_flag;
    char                        m_padding[3];
};

struct LightManager : public IdComponentSystem<100, LightInstance>
{
    virtual const char*         getName() const { return LightResource::getName(); };
    virtual void                update(float dt);
    virtual void                transformComponent(ComponentId id, const hkQsTransform& t);
    virtual void                enableComponent(ComponentId id, bool bEnable);
    void                        draw();

    LightInstance**             m_drawLights;
    uint32_t                    m_numLightsToDraw;

protected:
    virtual void initComponent(LightInstance* inst, const void* resource);
};

extern LightManager g_lightMgr;