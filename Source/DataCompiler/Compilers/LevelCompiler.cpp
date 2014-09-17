#include "LevelCompiler.h"
#include "ModelCompiler.h"
#include "LightCompiler.h"
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
    JsonValue entitiesValue = root.GetValue("actors");
    uint32_t numOfEntities = entitiesValue.GetElementsCount();
    JsonValue modelsValue = root.GetValue("models");
    JsonValue lightsValue = root.GetValue("lights");
    uint32_t numOfModels = 0;
    if(modelsValue.IsValid()) numOfModels = modelsValue.GetElementsCount();
    uint32_t numOfLights = 0;
    if(lightsValue.IsValid()) numOfLights = lightsValue.GetElementsCount();
    
        
    std::vector<uint32_t>                       resourceNames;
    int* entityIndices = new int[numOfEntities];

    std::string typeName;
    for (uint32_t i = 0; i < numOfEntities; ++i)
    {
        JsonValue entityValue = entitiesValue[i];
        typeName = JSON_GetString(entityValue.GetValue("type"));
        uint32_t key = StringId::calculate(typeName.c_str());
        int index = -1;
        ResourceKeyMap::iterator iter = m_resourceKeys.find(key);
        if(iter == m_resourceKeys.end())
        {
            resourceNames.push_back(key);
            index = (int)resourceNames.size() - 1;
            m_resourceKeys[key] = index;
            addDependency("entity", name_to_file_path(typeName, EntityResource::getName()));
        }
        else {
            index = iter->second;
        }
        entityIndices[i] = index;
    }

    uint32_t numOfResources = resourceNames.size();
    uint32_t memSize = sizeof(Level) + sizeof(LevelObject) * numOfEntities + \
                       sizeof(LevelEntityResource) * numOfResources + \
                       + sizeof(LevelModel) * numOfModels + \
                       + sizeof(LevelLight) * numOfLights;
    char* p = (char*)malloc(memSize);
    memset(p, 0x00, memSize);
    char* offset = p;

    LOGI("num of entities = %d, num of entity resources = %d", numOfEntities, numOfResources);

    Level* level = (Level*)p;
    level->m_numObject = numOfEntities;
    level->m_numResources = numOfResources;
    level->m_numModels = numOfModels;
    level->m_numLights = numOfLights;
    //============================================================
    offset += sizeof(Level);
    level->m_objects = (LevelObject*)offset;
    level->m_objectOffset = (uint32_t)(offset - p);
    offset += (sizeof(LevelObject) * numOfEntities);
    //============================================================
    level->m_resources = (LevelEntityResource*)offset;
    level->m_resourceOffset = (uint32_t)(offset - p);
    offset += (sizeof(LevelEntityResource) * numOfResources);
    //============================================================
    level->m_models = (LevelModel*)offset;
    level->m_modelOffset = (uint32_t)(offset - p);
    offset += (sizeof(LevelModel) * numOfModels);
    //============================================================
    level->m_lights = (LevelLight*)offset;
    level->m_lightOffset = (uint32_t)(offset - p);
    offset += (sizeof(LevelLight) * numOfLights);
    HK_ASSERT(0, offset == p + memSize);

    for (uint32_t i = 0; i < numOfEntities; ++i)
    {
        JsonValue entityValue = entitiesValue[i];
        LevelObject& object = level->m_objects[i];
        object.m_resourceIndex = entityIndices[i];
        object.m_name = JSON_GetStringId(entityValue.GetValue("name"));
        json_transform(entityValue, object.m_translation, object.m_rotation, object.m_scale);
    }

    for (uint32_t i = 0; i < numOfResources; ++i)
    {
        level->m_resources[i].m_name = StringId(resourceNames[i]);
    }

    for (uint32_t i = 0; i < numOfModels; ++i)
    {
        JsonValue modelValue = modelsValue[i];
        LevelModel& model = level->m_models[i];
        ModelCompiler* mc = (ModelCompiler*)createChildCompiler(ModelResource::getName(), modelValue);
        std::string modelName = JSON_GetString(modelValue.GetValue("name"));
        model.m_modelName = StringId(modelName.c_str());
        json_transform(modelValue, model.m_translation, model.m_rotation, model.m_scale);
        addDependency("level-model", name_to_file_path(modelName, ModelResource::getName()));
        std::string meshName = JSON_GetString(modelValue.GetValue("mesh"));
        uint32_t key = StringId::calculate(meshName.c_str());
        m_resourceKeys[key] = 0;
    }

    for (uint32_t i = 0; i < numOfLights; ++i)
    {
        JsonValue lightValue = lightsValue[i];
        LevelLight& light = level->m_lights[i];
        LightCompiler* lc = (LightCompiler*)createChildCompiler(LightResource::getName(), lightValue);
        std::string lightName = JSON_GetString(lightValue.GetValue("name"));
        light.m_lightName = StringId(lightName.c_str());
        json_transform(lightValue, light.m_translation, light.m_rotation, 0);
        addDependency("level-model", name_to_file_path(lightName, LightResource::getName()));
    }

    delete []entityIndices;
    bool bRet = write_file(m_output, p, memSize);
    free(p);
    return bRet;
}

bool LevelCompiler::isResourceInLevel( const std::string& resourceName ) const
{
    uint32_t key = StringId::calculate(resourceName.c_str());
    return m_resourceKeys.find(key) != m_resourceKeys.end();
}
