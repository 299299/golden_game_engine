#include "PhysicsCompiler.h"
#include "PhysicsWorld.h"
#include "PhysicsInstance.h"
#include "ProxyInstance.h"

bool PhysicsCompiler::readJSON(const jsonxx::Object& root)
{
    BaseCompiler::readJSON(root);
    uint32_t havokOffset = NATIVE_ALGIN_SIZE(sizeof(PhysicsResource));

    const std::string& havokFile = root.get<std::string>("havok_file");
    FileReader havokReader(havokFile);
    if(havokReader.m_size < 16)
    {
        g_config->m_error.add_error("%s can not find havok file [%s]", BX_FUNCTION, havokFile.c_str());
        return false;
    }

    uint32_t memSize = havokOffset + havokReader.m_size;
    LOGD("%s total mem-size = %d", m_output.c_str(), memSize);
    MemoryBuffer mem(memSize);
    PhysicsResource* physics = (PhysicsResource*)mem.m_buf;
    extern const char* physics_type_names[];
    physics->m_systemType = json_to_enum(root, "physics_type", physics_type_names);
    physics->m_havokDataOffset = havokOffset;
    physics->m_havokDataSize = havokReader.m_size;
    memcpy(mem.m_buf + havokOffset, havokReader.m_buf, havokReader.m_size);
    return write_file(m_output, mem.m_buf, memSize);
}

bool ProxyCompiler::readJSON(const jsonxx::Object& root)
{
    BaseCompiler::readJSON(root);
    ProxyResource proxy;
    memset(&proxy, 0x00, sizeof(proxy));

    vec3_make(proxy.m_gravity, 0, -9.8f, 0);
    proxy.m_radius = json_to_float(root, "radius", 0.5f);
    proxy.m_standHeight = json_to_float(root, "stand_height", 2.0f);
    proxy.m_friction = json_to_float(root, "friction", 0.9f);
    proxy.m_strength = json_to_float(root, "strength", 1.0f);
    proxy.m_verticalGain = json_to_float(root, "vertical_gain", 0.2f);
    proxy.m_horizontalGain = json_to_float(root, "horizontal_gain", 0.8f);
    proxy.m_maxVerticalSeparation = json_to_float(root, "max_vertical_separation", 5.0f);
    proxy.m_maxHorizontalSeparation = json_to_float(root, "max_horizontal_separation", 0.15f);
    proxy.m_offset = json_to_float(root, "offset", proxy.m_standHeight/2);
    proxy.m_layerName = json_to_stringid(root, "collision_layer", stringid_caculate("character_proxy"));

    json_to_floats(root, "gravity", proxy.m_gravity, 3);
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

bool PhysicsConfigCompiler::readJSON(const jsonxx::Object& root)
{
    BaseCompiler::readJSON(root);

    const jsonxx::Array& filtersValue = root.get<jsonxx::Array>("collision_filters");
    uint32_t numOfFilters = filtersValue.size();

    ENGINE_ASSERT_ARGS(numOfFilters <= 32, "collsion filter num overflow = %d", numOfFilters);

    PhysicsConfig cfg;
    memset(&cfg, 0x00, sizeof(cfg));
    cfg.m_numFilterLayers = numOfFilters;
    cfg.m_worldSize = json_to_float(root, "world_size", 1000.0f);
    vec3_make(cfg.m_gravity, 0, -9.8f, 0);
    json_to_floats(root, "gravity", cfg.m_gravity, 3);

    for(uint32_t i=0; i<numOfFilters; ++i)
    {
        const jsonxx::Object& o = filtersValue.get<jsonxx::Object>(i);
        m_filterNames.push_back(o.get<std::string>("name"));
    }

    for(uint32_t i=0; i<numOfFilters; ++i)
    {
        const jsonxx::Object& o = filtersValue.get<jsonxx::Object>(i);
        CollisionFilter& filter = cfg.m_filters[i];
        uint32_t mask = 0;
        if(o.has<jsonxx::Array>("collides_with"))
        {
            const jsonxx::Array& colValue = o.get<jsonxx::Array>("collides_with");
            for(uint32_t i=0; i<colValue.size(); ++i)
            {
                int index = findFilterIndex(colValue.get<std::string>(i));
                ADD_BITS(mask, 1 << index);
            }
        }
        else if(o.has<jsonxx::Array>("collides_with_all_except"))
        {
            const jsonxx::Array& colExceptValue = o.get<jsonxx::Array>("collides_with_all_except");
            mask = 0xffffffff;
            for(uint32_t i=0; i<colExceptValue.size(); ++i)
            {
                int index = findFilterIndex(colExceptValue.get<std::string>(i));
                REMOVE_BITS(mask, 1 << index);
            }
        }
        filter.m_mask = mask;
        filter.m_name = json_to_stringid(o, "name");
    }

    return write_file(m_output, &cfg, sizeof(cfg));
}