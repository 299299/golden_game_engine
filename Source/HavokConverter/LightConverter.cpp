#include "LightConverter.h"
#include "HC_Utils.h"

LightConverter::LightConverter(ActorConverter* ownner)
:ComponentConverter(ownner)
{
    
}

LightConverter::~LightConverter()
{

}

void LightConverter::process(void* pData, int hint)
{
    process((hkxLight*)pData);
}

void LightConverter::process(hkxLight* light)
{
    m_light = light;
}

jsonxx::Object LightConverter::serializeToJson() const
{
    extern const char*          g_lightTypeNames[];
    
    jsonxx::Object lightObject;
    unsigned wValue = m_light->m_color;
    unsigned R = wValue & 0xff;
    unsigned G = (wValue>>8)&0xff;
    unsigned B = (wValue >>16) & 0xff;
    unsigned color[3] = {R, G, B};
    jsonxx::Array colorObject;
    colorObject << R;
    colorObject << G;
    colorObject << B;
    lightObject << "color" << colorObject;
    int lightType = kLightSpot;
    if(m_light->m_type == hkxLight::DIRECTIONAL_LIGHT) lightType = kLightDirectional;
    if(m_light->m_type == hkxLight::POINT_LIGHT) lightType = kLightPoint;
    lightObject << "type" << std::string(g_lightTypeNames[lightType]);
    lightObject << "shadow" << (bool)m_light->m_shadowCaster;
    float dir[3];
    transform_vec3(dir, m_light->m_direction);
    jsonxx::Array dirObject;
    dirObject << dir[0];
    dirObject << dir[1];
    dirObject << dir[2];
    lightObject << "direction" << dirObject;
    lightObject << "cone_angle" << m_light->m_angle;
    lightObject << "falloff" << m_light->m_range;
    lightObject << "name" << getResourceName();
    lightObject << "type" << getTypeName();

    return lightObject;
}


