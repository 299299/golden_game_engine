#include "LevelConverter.h"
#include "HC_Utils.h"
#include "ModelConverter.h"
#include "LightConverter.h"
#include <Common/Base/Math/Matrix/hkMatrixDecomposition.h>

void matrix_to_transform(const hkMatrix4& m, hkQsTransform& t)
{
    t.setIdentity();
    hkMatrixDecomposition::Decomposition de;
    hkMatrixDecomposition::decomposeMatrix(m, de);
    if(de.m_hasScale)
    {
        t.m_scale = de.m_scale;
    }
    //HK_ASSERT(0, de.m_hasSkew);
    t.m_translation = de.m_translation;
    t.m_rotation = de.m_rotation;
    HK_ASSERT(0, t.isOk());
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

LevelConverter::LevelConverter()
:m_scene(0)
{
    
}

LevelConverter::~LevelConverter()
{
    
}

void LevelConverter::process(void* pData)
{
    process((hkxScene*)pData);
}

void LevelConverter::process(hkxScene* scene)
{
    m_scene = scene;
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
        toLower(nodeName);
        hkVariant va = node->m_object;
        ModelConverter* mc = new ModelConverter(this);
        if(str_begin_with(nodeName, "sky"))
        {
            mc->m_type = kModelSky;
        }
        mc->setName(m_name + "_" + node->m_name.cString());
        mc->process(va.m_object, 0);
        m_models.push_back(mc);
        m_components.push_back(mc);
    }

    for(size_t i=0; i<m_lightNodes.size(); ++i)
    {
        hkxNode* node = m_lightNodes[i];
        hkVariant va = node->m_object;
        LightConverter* lc = new LightConverter(this);
        lc->setName(m_name + "_" + node->m_name.cString());
        lc->process(va.m_object);
        m_lights.push_back(lc);
        m_components.push_back(lc);
    }
}

jsonxx::Object LevelConverter::serializeToJson() const
{
    jsonxx::Object levelObject;
    jsonxx::Array entityList;
    for (size_t i = 0; i < m_sceneNodes.size(); ++i)
    {
        hkxNode* node = m_sceneNodes[i];
        jsonxx::Object entity;
        json_transform(entity, node, m_scene);

        const hkxAttributeGroup* attrGrp = node->findAttributeGroupByName("engineAttributes");
        for (int i=0; i<attrGrp->m_attributes.getSize(); ++i)
        {
            const hkxAttribute& attrib = attrGrp->m_attributes[i];
            std::string attrName(attrib.m_name.cString());
            hkVariant variant(attrib.m_value);
            if(variant.m_class == &hkxSparselyAnimatedStringClass)
            {
                hkxSparselyAnimatedString* hString = (hkxSparselyAnimatedString*)variant.m_object;
                entity << attrName << std::string(hString->m_strings[0].cString());
            }
            // OTHER Attribute TODO
        }
        entityList << entity;
    }

    jsonxx::Array modelList;
    for(size_t i=0; i<m_models.size(); ++i)
    {
        jsonxx::Object modelObject = m_models[i]->serializeToJson();
        json_transform(modelObject, m_meshNodes[i], m_scene);
        modelList << modelObject;
    }

    jsonxx::Array lightList;
    for(size_t i=0; i<m_lights.size(); ++i)
    {
        jsonxx::Object lightObject = m_lights[i]->serializeToJson();
        json_transform(lightObject, m_lightNodes[i], m_scene);
        lightList << lightObject;
    }

    levelObject << "entities" << entityList;
    levelObject << "models" << modelList;
    levelObject << "lights" << lightList;
    return levelObject;
}

jsonxx::Object LevelConverter::serializeToJsonSplit() const
{
    return serializeToJson();
}