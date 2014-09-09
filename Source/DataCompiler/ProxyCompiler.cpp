#include "ProxyCompiler.h"

ProxyCompiler::ProxyCompiler()
{

}

ProxyCompiler::~ProxyCompiler()
{
    
}

bool ProxyCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    ProxyResource proxy;
    memset(&proxy, 0x00, sizeof(proxy));
    
    vec3Make(proxy.m_gravity, 0, -9.8f, 0);
    proxy.m_radius = JSON_GetFloat(root.GetValue("radius"), 0.5f);
    proxy.m_standHeight = JSON_GetFloat(root.GetValue("stand-height"), 2.0f);
    proxy.m_friction = JSON_GetFloat(root.GetValue("friction"), 0.9f);
    proxy.m_strength = JSON_GetFloat(root.GetValue("strength"), 1.0f);
    proxy.m_verticalGain = JSON_GetFloat(root.GetValue("vertical-gain"), 0.2f);
    proxy.m_horizontalGain = JSON_GetFloat(root.GetValue("horizontal-gain"), 0.8f);
    proxy.m_maxVerticalSeparation = JSON_GetFloat(root.GetValue("max-vertical-separation"), 5.0f);
    proxy.m_maxHorizontalSeparation = JSON_GetFloat(root.GetValue("max-horizontal-separation"), 0.15f);
    proxy.m_pushIfFootInAir = JSON_GetBool(root.GetValue("push-foot-in-air"));
    proxy.m_offset = JSON_GetFloat(root.GetValue("offset"), proxy.m_standHeight/2);
    JSON_GetFloats(root.GetValue("gravity"), proxy.m_gravity, 3);
    
    if(!write_file(m_output, &proxy, sizeof(proxy)))
    {
        return false;
    }

#ifdef COMPILER_LOAD_TEST
    char* buf = 0;
    size_t fileLen = read_file(m_output, &buf);  
    HK_ASSERT(0, fileLen == sizeof(ProxyResource));
    ProxyResource* proxy2 = (ProxyResource*)load_resource_proxy(buf, fileLen);
    HK_ASSERT(0, proxy2->m_radius == proxy.m_radius);
    HK_ASSERT(0, proxy2->m_standHeight == proxy.m_standHeight);
    free(buf);
#endif
    return true;
}
