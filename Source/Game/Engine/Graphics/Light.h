#pragma once
#include "BaseTypes.h"
#include "MathDefs.h"
#include "StringId.h"

struct Light
{
    float                   m_transform[16];
    float                   m_color[3];
    float                   m_dir[3];

    float                   m_fallOff;
    float                   m_intensity;
    float                   m_coneAngle;
    float                   m_attenScale;

    uint8_t                 m_flag;
    bool                    m_hasShadow;
    uint8_t                 m_type;
    char                    m_padding[1];
};


struct ShadingEnviroment;
struct LightWorld
{
    void                    init(int max_light);
    void                    shutdown();

    void                    update(float dt);
    void                    submit_lights(ShadingEnviroment* env);
    void                    update_shadow(float shadowArea,
                                          float shadowSize,
                                          const float* camPos);

    Light**                 m_drawLights;
    uint32_t                m_numLightsToDraw;

    const Light*            m_shadowLight;
    Frustum                 m_shadowFrustum;
    float                   m_shadowView[16];
    float                   m_shadowProj[16];

private:
    void                    reset();
};

extern LightWorld g_lightWorld;