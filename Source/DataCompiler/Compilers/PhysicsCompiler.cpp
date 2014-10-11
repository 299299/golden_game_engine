#include "PhysicsCompiler.h"
#include "PhysicsWorld.h"
#include "DC_Utils.h"

bool PhysicsCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    uint32_t havokOffset = sizeof(PhysicsResource);
    havokOffset = HK_NEXT_MULTIPLE_OF(16, havokOffset);
    
    std::string havokFile = JSON_GetString(root.GetValue("havok_file"));
    FileReader havokReader(havokFile);
    if(havokReader.m_size < 16)
    {
        addError(__FUNCTION__ " can not find havok file [%s]", havokFile.c_str());
        return false;
    }

    uint32_t memSize = havokOffset + havokReader.m_size;
    LOGD("%s total mem-size = %d", m_output.c_str(), memSize);
    MemoryBuffer mem(memSize);
    PhysicsResource* physics = (PhysicsResource*)mem.m_buf;
    extern const char* physics_type_names[];
    physics->m_systemType = JSON_GetEnum(root.GetValue("physics_type"), physics_type_names);
    physics->m_havokDataOffset = havokOffset;
    physics->m_havokDataSize = havokReader.m_size;
    memcpy(mem.m_buf + havokOffset, havokReader.m_buf, havokReader.m_size);
    return write_file(m_output, mem.m_buf, memSize);
}

bool ProxyCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    ProxyResource proxy;
    memset(&proxy, 0x00, sizeof(proxy));

    vec3_make(proxy.m_gravity, 0, -9.8f, 0);
    proxy.m_radius = JSON_GetFloat(root.GetValue("radius"), 0.5f);
    proxy.m_standHeight = JSON_GetFloat(root.GetValue("stand_height"), 2.0f);
    proxy.m_friction = JSON_GetFloat(root.GetValue("friction"), 0.9f);
    proxy.m_strength = JSON_GetFloat(root.GetValue("strength"), 1.0f);
    proxy.m_verticalGain = JSON_GetFloat(root.GetValue("vertical_gain"), 0.2f);
    proxy.m_horizontalGain = JSON_GetFloat(root.GetValue("horizontal_gain"), 0.8f);
    proxy.m_maxVerticalSeparation = JSON_GetFloat(root.GetValue("max_vertical_separation"), 5.0f);
    proxy.m_maxHorizontalSeparation = JSON_GetFloat(root.GetValue("max_horizontal_separation"), 0.15f);
    proxy.m_offset = JSON_GetFloat(root.GetValue("offset"), proxy.m_standHeight/2);
    proxy.m_layerName = JSON_GetStringId(root.GetValue("collision_layer"), StringId("character_proxy"));

    JSON_GetFloats(root.GetValue("gravity"), proxy.m_gravity, 3);
    return write_file(m_output, &proxy, sizeof(proxy));
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

    ENGINE_ASSERT(numOfFilters <= 32, "collsion filter num overflow = %d", numOfFilters);
    
    PhysicsConfig cfg;
    memset(&cfg, 0x00, sizeof(cfg));
    cfg.m_numFilterLayers = numOfFilters;
    cfg.m_worldSize = JSON_GetFloat(root.GetValue("world_size"), 1000.0f);
    vec3_make(cfg.m_gravity, 0, -9.8f, 0);
    JSON_GetFloats(root.GetValue("gravity"), cfg.m_gravity, 3);

    for(uint32_t i=0; i<numOfFilters; ++i)
    {
        JsonValue filterValue = filtersValue[i];
        m_filterNames.push_back(JSON_GetString(filterValue.GetValue("name")));
    }

    for(uint32_t i=0; i<numOfFilters; ++i)
    {
        JsonValue filterValue = filtersValue[i];
        JsonValue colValue = filterValue.GetValue("collides_with");
        JsonValue colExceptValue = filterValue.GetValue("collides_with_all_except");
        CollisionFilter& filter = cfg.m_filters[i];
        uint32_t mask = 0;
        if(colValue.IsValid())
        {
            for(uint32_t i=0; i<colValue.GetElementsCount(); ++i)
            {
                int index = findFilterIndex(JSON_GetString(colValue[i]));
                ADD_BITS(mask, 1 << index);
            }
        }
        else if(colExceptValue.IsValid())
        {
            mask = 0xffffffff;
            for(uint32_t i=0; i<colExceptValue.GetElementsCount(); ++i)
            {
                int index = findFilterIndex(JSON_GetString(colExceptValue[i]));
                REMOVE_BITS(mask, 1 << index);
            }
        }
        filter.m_mask = mask;
        filter.m_name = JSON_GetStringId(filterValue.GetValue("name"));
    }

    return write_file(m_output, &cfg, sizeof(cfg));
}