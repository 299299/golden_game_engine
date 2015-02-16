#include "ActorCompiler.h"
#include "Actor.h"
#include "Component.h"

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

    m_pathPrefix = root.get<std::string>("prefix", "");

    uint32_t numOfData = 0;
    uint32_t numComps = 0;
    jsonxx::Array compsValue = root.get<jsonxx::Array>("components");

    for(size_t i=0; i<compsValue.size(); ++i)
    {
        const std::string& type =  compsValue.get<jsonxx::Object>(i).get<std::string>("type");
        int comp_index = g_componentMgr.find_factory(stringid_caculate(type.c_str()));
        ENGINE_ASSERT(comp_index >= 0, "Component type %s not valid ", type.c_str());
        if(comp_index >= 0)
            ++numComps;
    }

    uint32_t memSize = sizeof(ActorResource) + numComps * sizeof(ComponentData);
    memSize = NEXT_MULTIPLE_OF(16, memSize);

    MemoryBuffer mem(memSize);
    char* offset = mem.m_buf;

    ActorResource* actor = (ActorResource*)mem.m_buf;
    offset += sizeof(ActorResource);
    extern const char* g_actorClassNames[];
    actor->m_class = json_to_enum(root, "class", g_actorClassNames, 0);
    actor->m_num_components = numComps;
    actor->m_component_data_offset = sizeof(ActorResource);

    int index = 0;
    for(size_t i=0; i<compsValue.size(); ++i)
    {
        const jsonxx::Object& compValue = compsValue.get<jsonxx::Object>(i);
        const std::string& type = compValue.get<std::string>("type");

        int comp_index = g_componentMgr.find_factory(stringid_caculate(type.c_str()));
        if(comp_index < 0)
            continue;

        LOGD("processing actor %s component %s", m_input.c_str(), type.c_str());
        
        
        
        createChildCompiler(type, compValue);
        ++index;
    }

    ENGINE_ASSERT((values == (mem.m_buf + memSize)), "offset address");
    return write_file(m_output, mem.m_buf, memSize);
} 