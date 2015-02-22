#include "ActorCompiler.h"
#include "Actor.h"
#include "Component.h"
#include "DataDef.h"
#include "ModelCompiler.h"
#include "LightCompiler.h"
#include "PhysicsCompiler.h"

class ComponentCompiler : public BaseCompiler
{
public:
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root) 
    { 
        m_data.m_name = json_to_stringid(root, "name");
        return m_data.m_name != 0; 
    };
    virtual const void* getCompiledData() const { return &m_data; };
    virtual uint32_t getCompiledDataSize() const { return sizeof(m_data);};

    ComponentInstanceData m_data;
};

static BaseCompiler* create_component_compiler(StringId _type)
{
    if(_type == EngineTypes::MODEL)
        return new ModelCompiler;
    else if(_type == EngineTypes::LIGHT)
        return new LightCompiler;
    else 
        return NULL;
}


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
        StringId compType = stringid_caculate(type.c_str());
        int comp_index = g_componentMgr.find_factory_index(compType);
        if(comp_index < 0) 
        {
            g_config->m_error.add_error("can not find any component type of %s", type.c_str());
            continue;
        }

        BaseCompiler* comp = create_component_compiler(compType);
        if(!comp)
            continue;

        m_components.push_back(comp);
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

        int comp_index = g_componentMgr.find_factory_index(stringid_caculate(type.c_str()));
        if(comp_index < 0)
            continue;

        LOGD("processing actor %s component %s", m_input.c_str(), type.c_str());
        
        
        
        createChildCompiler(type, compValue);
        ++index;
    }

    //ENGINE_ASSERT((values == (mem.m_buf + memSize)), "offset address");
    return write_file(m_output, mem.m_buf, memSize);
} 