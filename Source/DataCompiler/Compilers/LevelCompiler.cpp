#include "LevelCompiler.h"
#include "ModelCompiler.h"
#include "LightCompiler.h"
#include "ActorCompiler.h"
#include "Model.h"
#include "Light.h"
#include "DC_Utils.h"

void json_transform(const JsonValue& jValue, float* t, float* r, float* s)
{
    vec3Make(t, 0,0,0);
    vec3Make(r, 0,0,0);
    r[3] = 1;
    if(s) vec3Make(s, 1,1,1);

    JSON_GetFloats(jValue.GetValue("translation"), t, 3);
    int nRet = JSON_GetFloats(jValue.GetValue("rotation"), r, 4);
    if(nRet == 3)
    {
        hkQuaternion q;
        q.setFromEulerAngles(r[0], r[1],r[2]);
        transform_vec4(r, q.m_vec);
    }
    if(s) JSON_GetFloats(jValue.GetValue("scale"), s, 3);
}

LevelCompiler::LevelCompiler()
{

}

LevelCompiler::~LevelCompiler()
{
    
}

bool LevelCompiler::readJSON( const JsonValue& root )
{
    __super::readJSON(root);
    JsonValue actorsValue = root.GetValue("actors");
    uint32_t numOfActors = actorsValue.GetElementsCount();
        
    std::vector<uint32_t>   resourceNames;
    std::vector<int>        actorIndices;

    actorIndices.resize(numOfActors);

    std::string typeName;
    for (uint32_t i = 0; i < numOfActors; ++i)
    {
        JsonValue actorValue = actorsValue[i];
        typeName = JSON_GetString(actorValue.GetValue("type"));
        uint32_t key = StringId::calculate(typeName.c_str());
        int index = -1;
        ResourceKeyMap::iterator iter = m_resourceKeys.find(key);
        if(iter == m_resourceKeys.end())
        {
            resourceNames.push_back(key);
            index = (int)resourceNames.size() - 1;
            m_resourceKeys[key] = index;
            addDependency("actor resource", name_to_file_path(typeName, ActorResource::getName()));
        }
        else {
            index = iter->second;
        }
        actorIndices[i] = index;
    }

    uint32_t numOfResources = resourceNames.size();
    uint32_t memSize = sizeof(Level) + sizeof(LevelObject) * numOfActors + 
                       sizeof(LevelActorResource) * numOfResources;
    char* p = (char*)malloc(memSize);
    memset(p, 0x00, memSize);
    char* offset = p;

    LOGI("num of entities = %d, num of actor resources = %d", numOfActors, numOfResources);

    Level* level = (Level*)p;
    level->m_numObject = numOfActors;
    level->m_numResources = numOfResources;
    //============================================================
    offset += sizeof(Level);
    level->m_objects = (LevelObject*)offset;
    level->m_objectOffset = (uint32_t)(offset - p);
    offset += (sizeof(LevelObject) * numOfActors);
    //============================================================
    level->m_resources = (LevelActorResource*)offset;
    level->m_resourceOffset = (uint32_t)(offset - p);
    offset += (sizeof(LevelActorResource) * numOfResources);
    ENGINE_ASSERT(offset == p + memSize, "offset error.");

    for (uint32_t i = 0; i < numOfActors; ++i)
    {
        JsonValue actorValue = actorsValue[i];
        LevelObject& object = level->m_objects[i];
        object.m_resourceIndex = actorIndices[i];
        object.m_name = JSON_GetStringId(actorValue.GetValue("name"));
        json_transform(actorValue, object.m_translation, object.m_rotation, object.m_scale);
    }

    for (uint32_t i = 0; i < numOfResources; ++i)
    {
        level->m_resources[i].m_name = StringId(resourceNames[i]);
    }

    bool bRet = write_file(m_output, p, memSize);
    free(p);
    return bRet;
}

bool LevelCompiler::isResourceInLevel( const std::string& resourceName ) const
{
    uint32_t key = StringId::calculate(resourceName.c_str());
    return m_resourceKeys.find(key) != m_resourceKeys.end();
}
