#include "ActorCompiler.h"
#include "DC_Utils.h"

static const char* g_keynames[] = 
{
    "int", "float", "string", "float4", 0
};
static int g_valuesizes[] =
{
    sizeof(int), sizeof(float), sizeof(StringId), sizeof(float)*4, 
};

ActorCompiler::ActorCompiler()
{

}

ActorCompiler::~ActorCompiler()
{
    
}

bool ActorCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    JsonValue compsValue = root.GetValue("components");
    if(!compsValue.IsValid())
    {
        addError(__FUNCTION__" no components in this actor resource json ");
        return false;
    }

    uint32_t numOfData = 0;
    JsonValue datasValue = root.GetValue("data");
    if(datasValue.IsValid()) numOfData = datasValue.GetElementsCount();

    uint32_t numComps = compsValue.GetElementsCount();
    uint32_t memSize = sizeof(ActorResource);
    memSize += (numOfData * sizeof(Key));
    uint32_t resSize = memSize;
    memSize += (numOfData * sizeof(float) * 4);

    char* p = (char*)malloc(memSize);
    memset(p, 0x00, memSize);
    char* offset = p;
    
    ActorResource* actor = (ActorResource*)p;
    extern const char* g_actorClassNames[];
    actor->m_class = JSON_GetEnum(root.GetValue("class"), g_actorClassNames);
    
    extern int find_component_type(const StringId&);
    for(size_t i=0; i<numComps; ++i)
    {
        JsonValue compValue = compsValue[i];
        bool bPacked = JSON_GetBool(compValue.GetValue("packed"));
        std::string type = JSON_GetString(compValue.GetValue("type"));
        std::string name = JSON_GetString(compValue.GetValue("name"));
        int index = find_component_type(StringId(type.c_str()));
        if(index < 0)
        {
            addError("error component type --> %s", type.c_str());
            continue;
        }

        StringId& resourceName = actor->m_resourceNames[index];
        if(!resourceName.is_zero())
        {
            addError("only one component one type !!!! %s", m_name.c_str());
            continue;
        }
    
        resourceName = StringId(name.c_str());
        if(bPacked) createChildCompiler(type, compValue);
        addDependency(type, name_to_file_path(name, type));
    }

    Fact& fact = actor->m_fact;
    offset += sizeof(ActorResource);
    uint32_t valueSize = 0;
    fact.m_keys = (Key*)offset;
    offset += sizeof(Key) * numOfData;
    fact.m_values = offset;
    char* values = fact.m_values;

    for (size_t i=0; i<numOfData; ++i)
    {
        JsonValue dataValue = datasValue[i];
        Key& key = fact.m_keys[i];
        key.m_type = JSON_GetEnum(dataValue.GetValue("type"), g_keynames);
        key.m_name = JSON_GetStringId(dataValue.GetValue("name"));
        key.m_offset = (uint32_t)(values - p);

        JsonValue jValue = dataValue.GetValue("value");
        switch(key.type)
        {
        case ValueType::INT:
            *((int*)values) = JSON_GetInt(jValue);
            values += sizeof(int);
            break;
        case ValueType::FLOAT:
            *((float*)values) = JSON_GetFloat(jValue);
            values += sizeof(float);
            break;
        case ValueType::STRING:
            *((StringId*)values) = JSON_GetStringId(jValue);
            values += sizeof(StringId);
            break;
        case ValueType::FLOAT4:
            JSON_GetFloats(jValue, (float*)values, 4);
            values += sizeof(float)*4;
            break;    
        }
    }
    ENGINE_ASSERT(values == p + resSize, "offset address");

    if(!write_file(m_output, p, memSize))
    {
        free(p);
        return false;
    }

    free(p);
    return true;
}