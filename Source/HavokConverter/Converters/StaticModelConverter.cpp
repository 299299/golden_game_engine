#include "StaticModelConverter.h"
#include "PhysicsConverter.h"
#include "ModelConverter.h"
#include "LightConverter.h"
#include "HC_Utils.h"

StaticModelConverter::StaticModelConverter()
:m_scene(0)
,m_type(kModelDefault)
{
    
}

StaticModelConverter::~StaticModelConverter()
{
    
}

void StaticModelConverter::process(void* pData)
{
    process((hkxScene*)pData);
}

void StaticModelConverter::process(hkxScene* scene)
{
    m_scene = scene;
    processNode(m_scene->m_rootNode);
}

void StaticModelConverter::processNode( hkxNode* node )
{
    std::vector<hkxNode*> meshNodes;
    findNodesRec(node, &hkxMeshClass, meshNodes);
    for(size_t i=0; i<meshNodes.size(); ++i)
    {
        hkxNode* node = meshNodes[i];
        hkVariant va = node->m_object;
        ModelConverter* mc = new ModelConverter(this);

        char buf[128];
        if(i == 0)
            sprintf_s(buf, "%s", m_name.c_str());
        else
            sprintf_s(buf, "%s_%d", m_name.c_str(), i);

        mc->m_type = m_type;
        mc->setName(buf);
        mc->process(va.m_object, 0);
        m_components.push_back(mc);
    }

    std::vector<hkxNode*> skinNodes;
    findNodesRec(node, &hkxSkinBindingClass, skinNodes);
    for(size_t i=0; i<skinNodes.size(); ++i)
    {
        hkxNode* node = skinNodes[i];
        hkVariant va = node->m_object;
        hkxSkinBinding* skin = (hkxSkinBinding*)va.m_object;
        ModelConverter* mc = new ModelConverter(this);

        char buf[128];
        if(i == 0) sprintf_s(buf, "%s", m_name.c_str());
        else sprintf_s(buf, "%s_%d", m_name.c_str(), i);

        mc->setName(buf);
        mc->process((void*)skin->m_mesh, 0);
        m_components.push_back(mc);
    }

    std::vector<hkxNode*> lightNodes;
    findNodesRec(node, &hkxLightClass, lightNodes);
    for(size_t i=0; i<lightNodes.size(); ++i)
    {
        hkxNode* node = lightNodes[i];
        hkVariant va = node->m_object;
        LightConverter* lc = new LightConverter(this);

        char buf[128];
        if(i == 0) sprintf_s(buf, "%s", m_name.c_str());
        else sprintf_s(buf, "%s_%d", m_name.c_str(), i);

        lc->setName(buf);
        lc->process(va.m_object);
        m_components.push_back(lc);
    }

    if(m_config->m_physics)
    {
        PhysicsConverter* physics = new PhysicsConverter(this);
        physics->setName(m_name);
        physics->process((void*)m_config->m_physics);
        m_components.push_back(physics);
    }
}
