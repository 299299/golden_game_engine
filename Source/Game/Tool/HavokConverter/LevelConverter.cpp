#include "LevelConverter.h"
#include "ModelConverter.h"
#include "LightConverter.h"
#include "StaticModelConverter.h"
#include "Level.h"

#ifdef HAVOK_COMPILE
void matrix_to_transform(const hkMatrix4& m, hkQsTransform& t)
{
    t.setIdentity();
    hkMatrixDecomposition::Decomposition de;
    hkMatrixDecomposition::decomposeMatrix(m, de);
    if(de.m_hasScale) t.m_scale = de.m_scale;
    t.m_translation = de.m_translation;
    t.m_rotation = de.m_rotation;
    ENGINE_ASSERT(t.isOk(), "t is ok ?");
}

void json_transform(jsonxx::Object& object, hkxNode* pNode, hkxScene* pScene)
{
    hkQsTransform t;
    hkMatrix4 m;
    pScene->getWorldFromNodeTransform(pNode, m, 0);
    matrix_to_transform(m, t);
    jsonxx::Array pos,rot,scale;
    const hkVector4& hkPos = t.m_translation;
    const hkQuaternion& hkRot = t.m_rotation;
    const hkVector4& hkScale = t.m_scale;
    pos << (float)hkPos.getSimdAt(0);
    pos << (float)hkPos.getSimdAt(1);
    pos << (float)hkPos.getSimdAt(2);

    rot << (float)hkRot.m_vec.getSimdAt(0);
    rot << (float)hkRot.m_vec.getSimdAt(1);
    rot << (float)hkRot.m_vec.getSimdAt(2);
    rot << (float)hkRot.m_vec.getSimdAt(3);

    scale << (float)hkScale.getSimdAt(0);
    scale << (float)hkScale.getSimdAt(1);
    scale << (float)hkScale.getSimdAt(2);

    object << "translation" << pos;
    object << "rotation" << rot;
    object << "scale" << scale;
}
#endif

void fixNodeName(std::string& nodeName)
{
    size_t pos = nodeName.find_last_of('|');
    if(pos == std::string::npos) return;
    pos += 1;
    nodeName = nodeName.substr(pos, nodeName.length()-pos);
}

LevelConverter::LevelConverter()
:m_scene(0)
,m_collisionActor(0)
{

}

LevelConverter::~LevelConverter()
{
#ifdef HAVOK_COMPILE
    for (size_t i=0; i<m_levelMeshes.size(); ++i)
    {
        SAFE_REMOVEREF(m_levelMeshes[i]);
    }
    for (size_t i=0; i<m_levelLights.size(); ++i)
    {
        SAFE_REMOVEREF(m_levelLights[i]);
    }
    for (size_t i=0; i<m_configs.size(); ++i)
    {
        SAFE_DELETE(m_configs[i]);
    }
    SAFE_REMOVEREF(m_collisionActor);
#endif
}

void LevelConverter::process(void* pData)
{
    process((hkxScene*)pData);
}

void LevelConverter::process(hkxScene* scene)
{
    m_scene = scene;
#ifdef HAVOK_COMPILE
    findNodesRec(m_scene->m_rootNode, PROXY_NAME, m_sceneNodes);
    LOGI("scene proxy node num = %d.", m_sceneNodes.size());
    findNodesRec(m_scene->m_rootNode, &hkxMeshClass, m_meshNodes);
    LOGI("scene mesh node num = %d.", m_meshNodes.size());
    findNodesRec(m_scene->m_rootNode, &hkxLightClass, m_lightNodes);
    LOGI("scene light node num = %d.", m_lightNodes.size());

    for(size_t i=0; i<m_meshNodes.size(); ++i)
    {
        hkxNode* node = m_meshNodes[i];
        std::string nodeName(node->m_name.cString());
        fixNodeName(nodeName);
        LOGI("mesh node name = %s", nodeName.c_str());
        StaticModelConverter* actor = new StaticModelConverter();
        if(str_begin_with(nodeName, "sky"))
        {
            //hack here for sky dome material
            actor->setType(kModelSky);
        }
        else if(str_begin_with(nodeName, "collision_"))
        {
            //hack here for collision material
            actor->setType(kModelCollision);
        }
        Actor_Config* cfg = createConfig(nodeName);
        actor->m_config = cfg;
        actor->setName(cfg->m_exportName);
        actor->setClass(cfg->m_exportClass);
        actor->processNode(node);
        m_levelMeshes.push_back(actor);
    }

    for(size_t i=0; i<m_lightNodes.size(); ++i)
    {
        hkxNode* node = m_lightNodes[i];
        StaticModelConverter* actor = new StaticModelConverter();
        std::string nodeName(node->m_name.cString());
        fixNodeName(nodeName);
        LOGI("light node name = %s", nodeName.c_str());
        Actor_Config* cfg = createConfig(nodeName);
        actor->m_config = cfg;
        actor->setName(cfg->m_exportName);
        actor->setClass(cfg->m_exportClass);
        actor->processNode(node);
        m_levelLights.push_back(actor);
    }

    if(m_config->m_physics)
    {
        std::string nodeName = "Physics";
        LOGI("processing level physics %s", nodeName.c_str());
        StaticModelConverter* actor = new StaticModelConverter();
        m_collisionActor = actor;
        Actor_Config* cfg = createConfig(nodeName);
        actor->m_config = cfg;
        actor->setName(cfg->m_exportName);
        actor->setClass(cfg->m_exportClass);
        actor->processPhysics(m_config->m_physics);
    }
#endif
}

jsonxx::Object LevelConverter::serializeToJson() const
{
    jsonxx::Object levelObject;
    jsonxx::Array actorList;
#ifdef HAVOK_COMPILE
    for (size_t i = 0; i < m_sceneNodes.size(); ++i)
    {
        hkxNode* node = m_sceneNodes[i];
        jsonxx::Object actor;
        json_transform(actor, node, m_scene);
        fill_object_attributes(actor, node->findAttributeGroupByName(ENGINE_ATTRIBUTES));
        actorList << actor;
    }

    for(size_t i=0; i<m_levelMeshes.size(); ++i)
    {
        ActorConverter* mesh = m_levelMeshes[i];
        jsonxx::Object actorObject = mesh->serializeToJson();
        json_transform(actorObject, m_meshNodes[i], m_scene);
        actorObject << "packed" << true;
        actorObject << "type" << mesh->getResourceName();
        actorList << actorObject;
    }

    for(size_t i=0; i<m_levelLights.size(); ++i)
    {
        ActorConverter* light = m_levelLights[i];
        jsonxx::Object actorObject = light->serializeToJson();
        json_transform(actorObject, m_lightNodes[i], m_scene);
        actorObject << "packed" << true;
        actorObject << "type" << light->getResourceName();
        actorList << actorObject;
    }
#endif

    if(m_collisionActor)
    {
        jsonxx::Object actorObject = m_collisionActor->serializeToJson();
        actorObject << "packed" << true;
        actorObject << "type" << m_collisionActor->getResourceName();
        actorList << actorObject;
    }

    LOGI("level %s num-of-actors = %d", m_name.c_str(), actorList.size());
    levelObject << "actors" << actorList;
    return levelObject;
}

jsonxx::Object LevelConverter::serializeToJsonSplit() const
{
    return serializeToJson();
}

void LevelConverter::postProcess()
{
    for(size_t i=0; i<m_levelMeshes.size(); ++i)
    {
        m_levelMeshes[i]->postProcess();
    }
    for(size_t i=0; i<m_levelLights.size(); ++i)
    {
        m_levelLights[i]->postProcess();
    }
    if(m_collisionActor) m_collisionActor->postProcess();
}

Actor_Config* LevelConverter::createConfig(const std::string& nodeName)
{
    Actor_Config* cfg = new Actor_Config;
    cfg->m_assetFolder = m_config->m_assetFolder;
    cfg->m_workspaceFolder = m_config->m_workspaceFolder;
    cfg->m_exportFolder = m_config->m_exportFolder;
    cfg->m_exportName = nodeName;//m_name + "_" + nodeName;
    cfg->m_rootPath = m_config->m_rootPath;
    cfg->m_assetPath = m_config->m_assetPath;
    cfg->m_exportClass = "level_geometry";
    m_configs.push_back(cfg);
    return cfg;
}
