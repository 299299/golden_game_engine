#include "ActorCompiler.h"

ActorCompiler::ActorCompiler()
{

}

ActorCompiler::~ActorCompiler()
{

}

bool ActorCompiler::readJSON(const jsonxx::Object& root)
{
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

    numComps = compsValue.size();
    uint32_t memSize = sizeof(ActorResource);
    memSize += (numOfData * sizeof(Key));
    uint32_t resSize = memSize;
    memSize += (numOfData * sizeof(float) * 4);

    MemoryBuffer mem(memSize);
    char* offset = mem.m_buf;

    ActorResource* actor = (ActorResource*)mem.m_buf;
    offset += sizeof(ActorResource);
    extern const char* g_actorClassNames[];
    actor->m_class = find_enum_index(root.get<std::string>("name").c_str(), g_actorClassNames);
    actor->m_numComponents = numComps;
    actor->m_resourceNames = (StringId*)offset;
    offset += sizeof(StringId) * numComps;
    actor->m_resourceTypes = (StringId*)offset;
    offset += sizeof(StringId) * numComps;
    offset += sizeof(void*) * numComps;
    offset += sizeof(void*) * numComps;

    for(size_t i=0; i<numComps; ++i)
    {
        const jsonxx::Object& compValue = compsValue.get<jsonxx::Object>(i);
        bool bPacked = compValue.get<bool>("packed", false);
        const std::string& type = compValue.get<std::string>("type");
        const std::string& name = compValue.get<std::string>("name");
        actor->m_resourceNames[i] = StringId(name.c_str());
        actor->m_resourceTypes[i] = StringId(type.c_str());
        if(bPacked)
            createChildCompiler(type, compValue);
        addDependency(type, name_to_file_path(name, type));
    }

    Fact& fact = actor->m_fact;
    offset += sizeof(ActorResource);
    uint32_t valueSize = 0;
    fact.m_keys = (Key*)offset;
    offset += sizeof(Key) * numOfData;
    fact.m_values = offset;
    fact.m_num_keys = numOfData;
    char* values = fact.m_values;

    extern const char* g_fact_keynames[];
    extern uint32_t g_fact_valuesizes[];

    for (size_t i=0; i<numOfData; ++i)
    {
        jsonxx::Object dataValue = datasValue.get<jsonxx::Object>(i);
        Key& key = fact.m_keys[i];
        key.m_type = find_enum_index(dataValue.get<std::string>("type").c_str(), g_fact_keynames);
        key.m_name = StringId(dataValue.get<std::string>("name").c_str());
        key.m_offset = (uint32_t)(values - mem.m_buf);
        switch(key.m_type)
        {
        case ValueType::INT:*((int*)values) = dataValue.get<int>("value");break;
        case ValueType::FLOAT:*((float*)values) = dataValue.get<float>("value");break;
        case ValueType::STRING:*((StringId*)values) = StringId(dataValue.get<std::string>("value").c_str());break;
        case ValueType::FLOAT4:json_to_floats(dataValue.get<jsonxx::Array>("value"), (float*)values, 4);break;
        default: --i; continue;
        }
        values += g_fact_valuesizes[key.m_type];
    }
    ENGINE_ASSERT(values == mem.m_buf + resSize, "offset address");
    return write_file(m_output, mem.m_buf, memSize);
}