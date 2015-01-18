#include "LightCompiler.h"

LightCompiler::LightCompiler()
{

}

LightCompiler::~LightCompiler()
{
    
}

bool LightCompiler::readJSON( const jsonxx::Object& root )
{
    __super::readJSON(root);
    LightResource light;
    memset(&light, 0x00, sizeof(light));
    
    extern const char*  g_lightTypeNames[];
    vec3_make(light.m_color, 255, 255, 255);
    json_to_floats(root.get<jsonxx::Array>("color"), light.m_color, 3);
    for(uint32_t i=0; i<3; ++i)
    {
        light.m_color[i] /= 255;
    }

    json_to_floats(root.get<jsonxx::Array>("direction"), light.m_dir, 3);
    light.m_type = find_enum_index(root.get<std::string>("type").c_str(), g_lightTypeNames);
    light.m_fallOff = root.get<float>("falloff", 0.7f);
    light.m_intensity = root.get<float>("intensity", 1.0f);
    light.m_coneAngle = root.get<float>("cone-angle", 0.46f);
    light.m_attenScale = root.get<float>("atten-scale", 0.0f);
    light.m_hasShadow = root.get<bool>("shadow");
    return write_file(m_output, &light, sizeof(light));
}