#include "LightCompiler.h"
#include "DC_Utils.h"

LightCompiler::LightCompiler()
{

}

LightCompiler::~LightCompiler()
{
    
}

bool LightCompiler::readJSON( const JsonValue& root )
{
    __super::readJSON(root);
    LightResource light;
    memset(&light, 0x00, sizeof(light));
    
    extern const char*  g_lightTypeNames[];
    vec3Make(light.m_color, 255, 255, 255);
    JSON_GetFloats(root.GetValue("color"), light.m_color, 3);
    for(uint32_t i=0; i<3; ++i)
    {
        light.m_color[i] /= 255;
    }

    JSON_GetFloats(root.GetValue("direction"), light.m_dir, 3);
    light.m_type = JSON_GetEnum(root.GetValue("type"), g_lightTypeNames);
    light.m_fallOff = JSON_GetFloat(root.GetValue("falloff"), 0.7f);
    light.m_intensity = JSON_GetFloat(root.GetValue("intensity"), 1.0f);
    light.m_coneAngle = JSON_GetFloat(root.GetValue("cone-angle"), 0.46f);
    light.m_attenScale = JSON_GetFloat(root.GetValue("atten-scale"), 0.0);
    light.m_hasShadow = JSON_GetBool(root.GetValue("shadow"));
    
    if(!write_file(m_output, &light, sizeof(light)))
    {
        return false;
    }

#ifdef COMPILER_LOAD_TEST
    char* buf = 0;
    size_t fileLen = read_file(m_output, &buf);  
    HK_ASSERT(0, fileLen == sizeof(LightResource));
    LightResource* light2 = (LightResource*)buf;
    HK_ASSERT(0, light2->m_hasShadow == light.m_hasShadow);
    HK_ASSERT(0, light2->m_type == light.m_type);
    free(buf);
#endif
    return true;
}