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
    else if(_type == EngineTypes::ANIMATION_STATES ||
            _type == EngineTypes::ANIMATION_RIG)
        return new ComponentCompiler;
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

    uint32_t numComps = 0;
    jsonxx::Array compsValue = root.get<jsonxx::Array>("components");

    for(size_t i=0; i<compsValue.size(); ++i)
    {
        const jsonxx::Object& comp_json = compsValue.get<jsonxx::Object>(i);
        const std::string& type =  comp_json.get<std::string>("type");
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

        comp->m_pathPrefix = m_pathPrefix;
        bool bOk = comp->readJSON(comp_json);
        if(!bOk) {
            delete comp;
            continue;
        }

        m_components.push_back(comp);
        ++numComps;
        
        ComponentData data;
        data.m_index = comp_index;
        data.m_type = compType;
        data.m_size = comp->getCompiledDataSize();
        m_components_data.push_back(data);

        g_config->add_compiler(comp);
    }

    uint32_t head_size = sizeof ActorResource + numComps * sizeof ComponentData;
    uint32_t mem_size = head_size;
    for (uint32_t i=0; i<numComps; ++i)
    {
        mem_size += m_components[i]->getCompiledDataSize();
    }

    uint32_t ac_size = mem_size;
    mem_size = NEXT_MULTIPLE_OF(16, mem_size);

    MemoryBuffer mem(mem_size);
    char* offset = mem.m_buf;

    ActorResource* actor = (ActorResource*)mem.m_buf;
    extern const char* g_actorClassNames[];
    actor->m_class = json_to_enum(root, "class", g_actorClassNames, 0);
    actor->m_num_components = numComps;
    actor->m_component_data_offset = sizeof ActorResource;
    offset += actor->m_component_data_offset;
    ComponentData* data_array = (ComponentData*)(offset);
    offset += numComps * sizeof ComponentData;

    for(size_t i=0; i<numComps; ++i)
    {
        BaseCompiler* comp = m_components[i];
        ComponentData& data = data_array[i];
        data = m_components_data[i];
        data.m_offset = (int)(offset - mem.m_buf);
        memcpy(offset, comp->getCompiledData(), comp->getCompiledDataSize());
        offset += data.m_size;
    }

    ENGINE_ASSERT((offset == (mem.m_buf + ac_size)), "offset address");
    return write_file(m_output, mem.m_buf, mem_size);
} 