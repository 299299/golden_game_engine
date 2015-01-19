#include "LevelCompiler.h"
#include "ModelCompiler.h"
#include "LightCompiler.h"
#include "ActorCompiler.h"
#include "Model.h"
#include "Light.h"
#include "ToolUtils.h"

void json_transform(const jsonxx::Object& jValue, float* t, float* r, float* s)
{
    vec3_make(t, 0,0,0);
    vec3_make(r, 0,0,0);
    r[3] = 1;
    if(s) vec3_make(s, 1,1,1);

    json_to_floats(jValue.get<jsonxx::Array>("translation"), t, 3);
    int nRet = json_to_floats(jValue.get<jsonxx::Array>("rotation"), r, 4);
    if(nRet == 3)
    {
    #ifdef HAVOK_COMPILE
        hkQuaternion q;
        q.setFromEulerAngles(r[0], r[1],r[2]);
        transform_vec4(r, q.m_vec);
    #endif
    }
    if(s)
        json_to_floats(jValue.get<jsonxx::Array>("scale"), s, 3);
}

LevelCompiler::LevelCompiler()
{

}

LevelCompiler::~LevelCompiler()
{

}

bool LevelCompiler::readJSON( const jsonxx::Object& root )
{
    BaseCompiler::readJSON(root);
    const jsonxx::Array& actorsValue = root.get<jsonxx::Array>("actors");
    uint32_t numOfActors = actorsValue.size();

    std::vector<uint32_t>   resourceNames;
    std::vector<int>        actorIndices;

    actorIndices.resize(numOfActors);
    LOGI("level %s num-of-actors = %d", m_input.c_str(), numOfActors);

    std::string typeName;
    for (uint32_t i = 0; i < numOfActors; ++i)
    {
        const jsonxx::Object& actorValue = actorsValue.get<jsonxx::Object>(i);
        const std::string& typeName = actorValue.get<std::string>("type");
        const std::string& actorName = actorValue.get<std::string>("name");
        uint32_t key = StringId::calculate(typeName.c_str());
        int index = -1;
        ResourceKeyMap::iterator iter = m_resourceKeys.find(key);
        ENGINE_ASSERT(typeName.length(), "type name null");
        if(iter == m_resourceKeys.end())
        {
            resourceNames.push_back(key);
            index = (int)resourceNames.size() - 1;
            m_resourceKeys[key] = index;
            addDependency("actor resource", name_to_file_path(typeName, ActorResource::get_name()));
        }
        else
        {
            index = iter->second;
        }
        actorIndices[i] = index;
        createChildCompiler(ActorResource::get_name(), actorValue);
    }

    uint32_t numOfResources = resourceNames.size();
    uint32_t memSize = sizeof(Level) + sizeof(LevelObject) * numOfActors + sizeof(LevelActorResource) * numOfResources;
    MemoryBuffer mem(memSize);
    char* offset = mem.m_buf;

    LOGI("num of entities = %d, num of actor resources = %d", numOfActors, numOfResources);

    Level* level = (Level*)mem.m_buf;
    level->m_numObject = numOfActors;
    level->m_numResources = numOfResources;
    //============================================================
    offset += sizeof(Level);
    level->m_objects = (LevelObject*)offset;
    level->m_objectOffset = (uint32_t)(offset - mem.m_buf);
    offset += (sizeof(LevelObject) * numOfActors);
    //============================================================
    level->m_resources = (LevelActorResource*)offset;
    level->m_resourceOffset = (uint32_t)(offset - mem.m_buf);
    offset += (sizeof(LevelActorResource) * numOfResources);
    ENGINE_ASSERT(offset == mem.m_buf + memSize, "offset error.");

    for (uint32_t i = 0; i < numOfActors; ++i)
    {
        const jsonxx::Object& actorValue = actorsValue.get<jsonxx::Object>(i);
        LevelObject& object = level->m_objects[i];
        object.m_resourceIndex = actorIndices[i];
        object.m_name = StringId(actorValue.get<std::string>("name").c_str());
        json_transform(actorValue, object.m_translation, object.m_rotation, object.m_scale);
    }

    for (uint32_t i = 0; i < numOfResources; ++i)
    {
        level->m_resources[i].m_name = StringId(resourceNames[i]);
    }

    return write_file(m_output, mem.m_buf, memSize);
}