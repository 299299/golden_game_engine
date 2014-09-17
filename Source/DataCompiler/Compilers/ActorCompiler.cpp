#include "ActorCompiler.h"
#include "DC_Utils.h"
#include "EngineAssert.h"

ActorCompiler::ActorCompiler()
{

}

ActorCompiler::~ActorCompiler()
{
    
}

bool ActorCompiler::readJSON(const JsonValue& root)
{
    JsonValue compsValue = root.GetValue("components");
    if(!compsValue.IsValid())
    {
        addError(__FUNCTION__" no components in this entity resource json ");
        return false;
    }

    uint32_t numOfData = 0;
    JsonValue datasValue = root.GetValue("data");
    if(datasValue.IsValid()) numOfData = datasValue.GetElementsCount();

    uint32_t numComps = compsValue.GetElementsCount();
    uint32_t memSize = sizeof(ActorResource);
    char* p = (char*)malloc(memSize);
    memset(p, 0x00, memSize);
    char* offset = p;
    
    ActorResource* actor = (ActorResource*)p;
    extern const char* g_actorClassNames[];
    actor->m_class = JSON_GetEnum(root.GetValue("class"), g_actorClassNames);
    
    extern int find_component_type(const StringId&);
    ENGINE_ASSERT(offset == p + memSize, "offset address");
    for(size_t i=0; i<numComps; ++i)
    {
        JsonValue compValue = compsValue[i];
        bool bPacked = JSON_GetBool(compValue.GetValue("packed"));
        std::string type = JSON_GetString(compValue.GetValue("type"));
        std::string name = JSON_GetString(compValue.GetValue("name"));
        int index = find_component_type(StringId(type.c_str()));
        if(index < 0)
        {
            LOGE("error component type --> %s", type.c_str());
            continue;
        }

        StringId& resourceName = actor->m_resourceNames[index];
        if(!resourceName.isZero())
        {
            LOGE("only one component one type !!!! %s", m_name.c_str());
            continue;
        }
    
        resourceName = StringId(name.c_str());
        if(bPacked) createChildCompiler(type, compValue);
        addDependency(type, name_to_file_path(name, type));
    }

#if 0
    for (size_t i=0; i<numOfData; ++i)
    {
        JsonValue dataValue = datasValue[i];
        NamedVariant& variant = entity->m_variants[i];
        variant.m_name = JSON_GetStringId(dataValue.GetValue("name"));
        JSON_GetVariant(dataValue, variant.m_variant);
    }
#endif
    
    if(!write_file(m_output, p, memSize))
    {
        free(p);
        return false;
    }

    free(p);
    return true;
}