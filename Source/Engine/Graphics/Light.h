#pragma once
#include "Prerequisites.h"
#include "StringId.h"
#include "ShaderI"

enum LightType
{
    kLightDirectional,
    kLightSpot,
    kLightPoint,
    kLightCount
};

struct Material;
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
    
    //=====================================================================
    void init(const void* resource);
    void destroy() {};
    void setTransform(const hkQsTransform& t);
    void setEnabled(bool bEnable);
    //======================================================================
    
    void update();

    inline void addFlag(uint32_t flag) { ADD_BITS(m_flag, flag); };
    inline void removeFlag(uint32_t flag) { REMOVE_BITS(m_flag, flag); };
};


struct LightManager
{
    void update();
    void draw();

    LightInstance**             m_drawLights;
    uint32_t                    m_numLightsToDraw;
};

extern LightManager g_lightMgr;