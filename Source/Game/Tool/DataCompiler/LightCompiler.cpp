#include "LightCompiler.h"
#include "Light.h"

LightCompiler::LightCompiler()
{

}

LightCompiler::~LightCompiler()
{

}

bool LightCompiler::readJSON( const jsonxx::Object& root )
{
    BaseCompiler::readJSON(root);
    Light light;
    memset(&light, 0x00, sizeof(light));

    extern const char*  g_lightTypeNames[];
    vec3_make(light.m_color, 255, 255, 255);
    json_to_floats(root, "color", light.m_color, 3);
    for(uint32_t i=0; i<3; ++i)
    {
        light.m_color[i] /= 255;
    }

    json_to_floats(root, "direction", light.m_dir, 3);
    light.m_type = json_to_enum(root, "light_type", g_lightTypeNames);
    light.m_fallOff = json_to_float(root, "falloff", 0.7f);
    light.m_intensity = json_to_float(root, "intensity", 1.0f);
    light.m_coneAngle = json_to_float(root, "cone_angle", 0.46f);
    light.m_attenScale = json_to_float(root, "atten_scale", 0.0f);
    light.m_hasShadow = root.get<bool>("shadow");
    return write_file(m_output, &light, sizeof(light));
}