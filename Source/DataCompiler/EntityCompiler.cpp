#include "EntityCompiler.h"
#include "DC_Utils.h"

EntityCompiler::EntityCompiler()
{

}

EntityCompiler::~EntityCompiler()
{
    
}

bool EntityCompiler::readJSON(const JsonValue& root)
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
    uint32_t memSize = sizeof(EntityResource) + numComps * sizeof(ComponentResource) + numOfData * sizeof(NamedVariant);
    char* p = (char*)malloc(memSize);
    memset(p, 0x00, memSize);
    char* offset = p;
    
    EntityResource* entity = (EntityResource*)p;
    extern const char* g_entityClassNames[];
    entity->m_class = JSON_GetEnum(root.GetValue("class"), g_entityClassNames);
    entity->m_numComps = numComps;
    entity->m_numVariants = numOfData;
    //=================================================================
    //  HERE MUST SAME ORDER AS LOADING IN Entity.cpp
    //=================================================================
    offset += sizeof(EntityResource);
    entity->m_resources = (ComponentResource*)(offset);
    entity->m_resourceOffset = (uint32_t)(offset - p);
    offset += sizeof(ComponentResource) * numComps;

    entity->m_variants = (NamedVariant*)offset;
    entity->m_varentOffset = (uint32_t)(offset - p);
    offset += sizeof(NamedVariant) * entity->m_numVariants;

    HK_ASSERT(0, offset == p + memSize);
    for(size_t i=0; i<numComps; ++i)
    {
        ComponentResource resource;
        JsonValue compValue = compsValue[i];
        bool bPacked = JSON_GetBool(compValue.GetValue("packed"));
        std::string type = JSON_GetString(compValue.GetValue("type"));
        std::string name = JSON_GetString(compValue.GetValue("name"));
        resource.m_type = StringId(type.c_str());       
        resource.m_resourceName = StringId(name.c_str());
        memcpy(&entity->m_resources[i], &resource, sizeof(resource));
        if(bPacked) createChildCompiler(type, compValue);
        addDependency(type, name_to_file_path(name, type));
    }

    for (size_t i=0; i<numOfData; ++i)
    {
        JsonValue dataValue = datasValue[i];
        NamedVariant& variant = entity->m_variants[i];
        variant.m_name = JSON_GetStringId(dataValue.GetValue("name"));
        JSON_GetVariant(dataValue, variant.m_variant);
    }
    
    if(!write_file(m_output, p, memSize))
    {
        free(p);
        return false;
    }
    
#ifdef COMPILER_LOAD_TEST
    char* buf = 0;
    size_t fileLen = read_file(m_output, &buf);  
    HK_ASSERT(0, fileLen == memSize);
    EntityResource* entity2 = (EntityResource*)load_resource_entity(buf, fileLen);
    HK_ASSERT(0, entity2->m_numComps == entity->m_numComps);
    for (uint32_t i=0; i<entity->m_numComps; ++i)
    {
        HK_ASSERT(0, entity2->m_resources[i].m_type == entity->m_resources[i].m_type);
        HK_ASSERT(0, entity2->m_resources[i].m_resourceName == entity->m_resources[i].m_resourceName);
    }
    for (uint32_t i=0; i<entity->m_numVariants; ++i)
    {
        HK_ASSERT(0, entity2->m_variants[i].m_name == entity->m_variants[i].m_name);
    }
    free(buf);
#endif

    free(p);
    return true;
}