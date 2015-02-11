#include "LightCompiler.h"

LightCompiler::LightCompiler()
{
    memset(&m_light, 0x00, sizeof(m_light));
}

LightCompiler::~LightCompiler()
{

}

bool LightCompiler::readJSON( const jsonxx::Object& root )
{
    BaseCompiler::readJSON(root);
    
    extern const char*  g_lightTypeNames[];
    vec3_make(m_light.m_color, 255, 255, 255);
    json_to_floats(root, "color", m_light.m_color, 3);
    for(uint32_t i=0; i<3; ++i)
    {
        m_light.m_color[i] /= 255;
    }

    json_to_floats(root, "direction", m_light.m_dir, 3);
    m_light.m_type = json_to_enum(root, "light_type", g_lightTypeNames);
    m_light.m_fallOff = json_to_float(root, "falloff", 0.7f);
    m_light.m_intensity = json_to_float(root, "intensity", 1.0f);
    m_light.m_coneAngle = json_to_float(root, "cone_angle", 0.46f);
    m_light.m_attenScale = json_to_float(root, "atten_scale", 0.0f);
    m_light.m_hasShadow = root.get<bool>("shadow");
    return true;
}