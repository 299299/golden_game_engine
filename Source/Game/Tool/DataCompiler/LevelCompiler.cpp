#include "LevelCompiler.h"
#include "ModelCompiler.h"
#include "LightCompiler.h"
#include "ActorCompiler.h"
#include "Model.h"
#include "Light.h"
#include "ToolUtils.h"
#include "Level.h"

void json_transform(const jsonxx::Object& jValue, float* t, float* r, float* s)
{
    vec3_make(t, 0,0,0);
    vec3_make(r, 0,0,0);
    r[3] = 1;
    if(s) vec3_make(s, 1,1,1);

    json_to_floats(jValue, "translation", t, 3);
    int nRet = json_to_floats(jValue, "rotation", r, 4);
    if(nRet == 3)
    {
    #ifdef HAVOK_COMPILE
        hkQuaternion q;
        q.setFromEulerAngles(r[0], r[1],r[2]);
        transform_vec4(r, q.m_vec);
    #endif
    }
    if(s)
        json_to_floats(jValue, "scale", s, 3);
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
        uint32_t key = stringid_caculate(typeName.c_str());
        int index = -1;
        ResourceKeyMap::iterator iter = m_resourceKeys.find(key);
        ENGINE_ASSERT(typeName.length(), "type name null");
        if(iter == m_resourceKeys.end())
        {
            resourceNames.push_back(key);
            index = (int)resourceNames.size() - 1;
            m_resourceKeys[key] = index;
            addDependency("actor resource", name_to_file_path(typeName, EngineNames::ACTOR));
        }
        else
        {
            index = iter->second;
        }
        actorIndices[i] = index;
        if(!actorValue.get<bool>("packed" ,false))
            continue;
        createChildCompiler(EngineNames::ACTOR, actorValue);
    }

    uint32_t numOfResources = resourceNames.size();
    uint32_t memSize = sizeof(Level) + sizeof(LevelObject) * numOfActors + sizeof(LevelActorResource) * numOfResources;
    memSize = NATIVE_ALGIN_SIZE(memSize);

    MemoryBuffer mem(memSize);
    char* offset = mem.m_buf;

    LOGI("num of entities = %d, num of actor resources = %d", numOfActors, numOfResources);

    Level* level = (Level*)mem.m_buf;
    level->m_num_objects = numOfActors;
    level->m_num_resources = numOfResources;
    //============================================================
    offset += sizeof(Level);
    LevelObject* objects = (LevelObject*)offset;
    level->m_object_offset = (uint32_t)(offset - mem.m_buf);
    offset += (sizeof(LevelObject) * numOfActors);
    //============================================================
    LevelActorResource* resources = (LevelActorResource*)offset;
    level->m_resource_offset = (uint32_t)(offset - mem.m_buf);
    offset += (sizeof(LevelActorResource) * numOfResources);
    ENGINE_ASSERT(offset == mem.m_buf + memSize, "offset error.");

    for (uint32_t i = 0; i < numOfActors; ++i)
    {
        const jsonxx::Object& actorValue = actorsValue.get<jsonxx::Object>(i);
        LevelObject& object = objects[i];
        object.m_resourceIndex = actorIndices[i];
        object.m_name = json_to_stringid(actorValue, "name");
        json_transform(actorValue, object.m_translation, object.m_rotation, object.m_scale);
    }

    for (uint32_t i = 0; i < numOfResources; ++i)
    {
        resources[i].m_name = resourceNames[i];
    }

    return write_file(m_output, mem.m_buf, memSize);
}