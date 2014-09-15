#pragma once
#include "BaseTypes.h"
#include "StringId.h"
#include "MathDefs.h"
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

ENGINE_NATIVE_ALIGN struct LightInstance
{
    float                   m_color[3];
    float                   m_vec[3];
    const LightResource*    m_resource;
    uint8_t                 m_flag;
    char                    m_padding[3];
};


typedef Id LightId;
struct LightWorld
{
    LightWorld(uint32_t max_num_light);
    ~LightWorld();

    void                    update(float dt);
    void                    sumibt_lights();
    LightId                 create_light(const LightResource* lightResource);
    void                    destroy_light(LightId id);
    LightInstance*          get_light(LightId id);
    void                    update_shadow(float shadowArea, 
                                          float shadowSize, 
                                          const float* camPos);

    IdArray<LightInstance>  m_lights;
    LightInstance*          m_drawLights;
    uint32_t                m_numLightsToDraw;

    LightInstance*          m_shadowLight;
    Frustum                 m_shadowFrustum;
    float                   m_shadowView[16];
    float                   m_shadowProj[16];

private:
    void                    reset();
};