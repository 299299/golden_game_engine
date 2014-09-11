#include "PhysicsCompiler.h"
#include "PhysicsWorld.h"
#include "DC_Utils.h"

static const char*   physics_type_names[] = 
{
    "rigidbody-only", "ragdoll", "trigger", "complex", 0
};

bool PhysicsCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    uint32_t havokOffset = sizeof(PhysicsResource);
    havokOffset = HK_NEXT_MULTIPLE_OF(16, havokOffset);
    
    std::string havokFile = JSON_GetString(root.GetValue("havok-file"));
    char* havokData = 0;
    uint32_t havokFileSize = read_file(havokFile.c_str(), &havokData);
    if(havokFileSize < 16)
    {
        addError(__FUNCTION__ " can not find havok file [%s]", havokFile.c_str());
        return false;
    }

    uint32_t memSize = havokOffset + havokFileSize;
    LOGD("%s total mem-size = %d", m_output.c_str(), memSize);
    char* p = (char*)malloc(memSize);
    memset(p, 0x00, memSize);
    PhysicsResource* physics = (PhysicsResource*)p;
    physics->m_systemType = JSON_GetEnum(root.GetValue("physics-type"), physics_type_names);
    physics->m_havokDataOffset = havokOffset;
    physics->m_havokDataSize = havokFileSize;
    memcpy(p + havokOffset, havokData, havokFileSize);
    free(havokData);
    bool bRet = write_file(m_output, p, memSize);
    free(p);
    return bRet;
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

int PhysicsConfigCompiler::findFilterIndex(const std::string& name) const
{
    for(size_t i=0; i<m_filterNames.size(); ++i)
    {
        if(m_filterNames[i] == name)
            return i;
    }
    return -1;
}

bool PhysicsConfigCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    
    uint32_t numOfFilters = 0;
    JsonValue filtersValue = root.GetValue("collision_filters");
    if(filtersValue.IsValid()) numOfFilters = filtersValue.GetElementsCount();

    HK_ASSERT(0, numOfFilters <= 32);
    
    PhysicsConfig cfg;
    memset(&cfg, 0x00, sizeof(cfg));
    cfg.m_numFilterLayers = numOfFilters;

    for(uint32_t i=0; i<numOfFilters; ++i)
    {
        JsonValue filterValue = filtersValue[i];
        m_filterNames.push_back(JSON_GetString(filterValue.GetValue("name")));
    }

    for(uint32_t i=0; i<numOfFilters; ++i)
    {
        JsonValue filterValue = filtersValue[i];
        JsonValue colValue = filterValue.GetValue("collides_with");
        if(!colValue.IsValid()) continue;
        CollisionFilter& filter = cfg.m_filters[i];
        uint32_t mask = 0;        
        for(uint32_t i=0; i<colValue.GetElementsCount(); ++i)
        {
            mask |= (1 << findFilterIndex(colName));
        }
        filter.m_mask = mask;
    }
    return true;
}