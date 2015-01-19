#include "PhysicsCompiler.h"
#include "PhysicsWorld.h"

bool PhysicsCompiler::readJSON(const jsonxx::Object& root)
{
    BaseCompiler::readJSON(root);
    uint32_t havokOffset = sizeof(PhysicsResource);
    havokOffset = NEXT_MULTIPLE_OF(16, havokOffset);

    const std::string& havokFile = root.get<std::string>("havok_file");
    FileReader havokReader(havokFile);
    if(havokReader.m_size < 16)
    {
        g_config->m_error.add_error(__FUNCTION__ " can not find havok file [%s]", havokFile.c_str());
        return false;
    }

    uint32_t memSize = havokOffset + havokReader.m_size;
    LOGD("%s total mem-size = %d", m_output.c_str(), memSize);
    MemoryBuffer mem(memSize);
    PhysicsResource* physics = (PhysicsResource*)mem.m_buf;
    extern const char* physics_type_names[];
    physics->m_systemType = find_enum_index(root.get<std::string>("physics_type").c_str(), physics_type_names);
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
    proxy.m_radius = root.get<float>("radius", 0.5f);
    proxy.m_standHeight = root.get<float>("stand_height", 2.0f);
    proxy.m_friction = root.get<float>("friction", 0.9f);
    proxy.m_strength = root.get<float>("strength", 1.0f);
    proxy.m_verticalGain = root.get<float>("vertical-gain", 0.2f);
    proxy.m_horizontalGain = root.get<float>("horizontal-gain", 0.8f);
    proxy.m_maxVerticalSeparation = root.get<float>("max-vertical-separation", 5.0f);
    proxy.m_maxHorizontalSeparation = root.get<float>("max-horizontal-separation", 0.15f);
    proxy.m_offset = root.get<float>("offset", proxy.m_standHeight/2);
    proxy.m_layerName = StringId(root.get<std::string>("collision-layer", "character-proxy").c_str());

    json_to_floats(root.get<jsonxx::Array>("gravity"), proxy.m_gravity, 3);
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

    const jsonxx::Array& filtersValue = root.get<jsonxx::Array>("collision-filters");
    uint32_t numOfFilters = filtersValue.size();

    ENGINE_ASSERT_ARGS(numOfFilters <= 32, "collsion filter num overflow = %d", numOfFilters);

    PhysicsConfig cfg;
    memset(&cfg, 0x00, sizeof(cfg));
    cfg.m_numFilterLayers = numOfFilters;
    cfg.m_worldSize = root.get<float>("world_size", 1000.0f);
    vec3_make(cfg.m_gravity, 0, -9.8f, 0);
    if(root.has<jsonxx::Array>("gravity"))
        json_to_floats(root.get<jsonxx::Array>("gravity"), cfg.m_gravity, 3);

    for(uint32_t i=0; i<numOfFilters; ++i)
    {
        const jsonxx::Object& filterValue = filtersValue.get<jsonxx::Object>(i);
        m_filterNames.push_back(filterValue.get<std::string>("name"));
    }

    for(uint32_t i=0; i<numOfFilters; ++i)
    {
        const jsonxx::Object& filterValue = filtersValue.get<jsonxx::Object>(i);
        CollisionFilter& filter = cfg.m_filters[i];
        uint32_t mask = 0;
        if(filterValue.has<jsonxx::Array>("collides-with"))
        {
            const jsonxx::Array& colValue = filterValue.get<jsonxx::Array>("collides-with");
            for(uint32_t i=0; i<colValue.size(); ++i)
            {
                int index = findFilterIndex(colValue.get<std::string>(i));
                ADD_BITS(mask, 1 << index);
            }
        }
        else if(filterValue.has<jsonxx::Array>("collides-with-all-except"))
        {
            const jsonxx::Array& colExceptValue = filterValue.get<jsonxx::Array>("collides-with-all-except");
            mask = 0xffffffff;
            for(uint32_t i=0; i<colExceptValue.size(); ++i)
            {
                int index = findFilterIndex(colExceptValue.get<std::string>(i));
                REMOVE_BITS(mask, 1 << index);
            }
        }
        filter.m_mask = mask;
        filter.m_name = StringId(filterValue.get<std::string>("name").c_str());
    }

    return write_file(m_output, &cfg, sizeof(cfg));
}