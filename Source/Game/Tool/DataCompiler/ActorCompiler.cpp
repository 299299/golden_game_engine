#include "ActorCompiler.h"
#include "Actor.h"

ActorCompiler::ActorCompiler()
{

}

ActorCompiler::~ActorCompiler()
{

}

bool ActorCompiler::readJSON(const jsonxx::Object& root)
{
    extern const char* g_fact_keynames[];
    extern uint32_t g_fact_valuesizes[];

    BaseCompiler::readJSON(root);
    if(!root.has<jsonxx::Array>("components"))
    {
        g_config->m_error.add_error(" no components in this actor resource json ");
        return false;
    }

    uint32_t numOfData = 0;
    uint32_t numComps = 0;
    jsonxx::Array datasValue;
    jsonxx::Array compsValue = root.get<jsonxx::Array>("components");

    if(root.has<jsonxx::Array>("data"))
    {
        datasValue = root.get<jsonxx::Array>("data");
        numOfData = datasValue.size();
    }
    if(root.has<std::string>("prefix"))
    {
        m_pathPrefix = root.get<std::string>("prefix");
    }

    for(size_t i=0; i<compsValue.size(); ++i)
    {
        const std::string& type =  compsValue.get<jsonxx::Object>(i).get<std::string>("type");
        if(g_config->is_type_valid(type))
            ++numComps;
    }

    uint32_t memSize = sizeof(ActorResource);
    memSize += (numComps * (sizeof(StringId) + sizeof(void*)) * 2);
    memSize += (numOfData * sizeof(Key));

    for (size_t i=0; i<numOfData; ++i)
    {
        memSize += g_fact_valuesizes[json_to_enum(datasValue.get<jsonxx::Object>(i), "type", g_fact_keynames)];
    }

    MemoryBuffer mem(memSize);
    char* offset = mem.m_buf;

    ActorResource* actor = (ActorResource*)mem.m_buf;
    offset += sizeof(ActorResource);
    extern const char* g_actorClassNames[];
    actor->m_class = json_to_enum(root, "class", g_actorClassNames, 0);
    actor->m_numComponents = numComps;
    actor->m_resourceNames = (StringId*)offset;
    offset += sizeof(StringId) * numComps;
    actor->m_resourceTypes = (StringId*)offset;
    offset += sizeof(StringId) * numComps;
    offset += sizeof(void*) * numComps;
    offset += sizeof(void*) * numComps;

    int index = 0;
    for(size_t i=0; i<compsValue.size(); ++i)
    {
        const jsonxx::Object& compValue = compsValue.get<jsonxx::Object>(i);
        bool bPacked = compValue.get<bool>("packed", false);
        const std::string& type = compValue.get<std::string>("type");
        if(!g_config->is_type_valid(type))
            continue;
        LOGD("processing actor %s component %s", m_input.c_str(), type.c_str());
        std::string name = m_pathPrefix + compValue.get<std::string>("name");
        actor->m_resourceNames[index] = stringid_caculate(name.c_str());
        actor->m_resourceTypes[index] = stringid_caculate(type.c_str());
        if(bPacked)
            createChildCompiler(type, compValue);
        addDependency(type, name_to_file_path(name, type));
        ++index;
    }

    Fact& fact = actor->m_fact;
    uint32_t valueSize = 0;
    fact.m_keys = (Key*)offset;
    offset += sizeof(Key) * numOfData;
    fact.m_values = offset;
    fact.m_num_keys = numOfData;
    char* values = fact.m_values;

    for (size_t i=0; i<numOfData; ++i)
    {
        const jsonxx::Object& o = datasValue.get<jsonxx::Object>(i);
        Key& key = fact.m_keys[i];
        int index = json_to_enum(o, "type", g_fact_keynames);
        ENGINE_ASSERT(index >= 0, "Actor Key type not right.");
        key.m_type = index;
        key.m_name = stringid_caculate(o.get<std::string>("name").c_str());
        key.m_offset = (uint32_t)(values - mem.m_buf);
        switch(key.m_type)
        {
        case ValueType::INT:*((int*)values) = json_to_int(o, "value");break;
        case ValueType::FLOAT:*((float*)values) = json_to_float(o, "value");break;
        case ValueType::STRING:*((StringId*)values) = json_to_stringid(o, "value");break;
        case ValueType::FLOAT4:json_to_floats(o, "value", (float*)values, 4);break;
        default: --i; continue;
        }
        values += g_fact_valuesizes[key.m_type];
    }

    ENGINE_ASSERT((values == (mem.m_buf + memSize)), "offset address");
    return write_file(m_output, mem.m_buf, memSize);
}