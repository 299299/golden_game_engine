#include "StaticModelConverter.h"
#include "PhysicsConverter.h"
#include "ModelConverter.h"
#include "LightConverter.h"

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
#ifdef HAVOK_COMPILE
    processNode(m_scene->m_rootNode);
#endif
}

void StaticModelConverter::processNode( hkxNode* node )
{
#ifdef HAVOK_COMPILE
    std::vector<hkxNode*> meshNodes;
    findNodesRec(node, &hkxMeshClass, meshNodes);

#if 0
    for(size_t i=0; i<meshNodes.size(); ++i)
    {
        hkxNode* node = meshNodes[i];
        hkVariant va = node->m_object;
        ModelConverter* mc = new ModelConverter(this);

        char buf[128];
        if(i == 0)
            bx::vsnprintf(buf, sizeof(buf), "%s", m_name.c_str());
        else
            bx::vsnprintf(buf, sizeof(buf), "%s_%d", m_name.c_str(), i);
        mc->m_type = m_type;
        mc->setName(buf);
        mc->process(va.m_object, 0);
        m_components.push_back(mc);
    }
#else
    if(!meshNodes.empty())
    {
        ModelConverter* mc = new ModelConverter(this);
        mc->m_type = m_type;
        mc->setName(m_name);
        std::vector<hkxMesh*> meshes;
        hkxNode* first_node = 0;
        for(size_t i=0; i< meshNodes.size(); ++i)
        {
            hkxNode* node = meshNodes[i];
            hkVariant va = node->m_object;
            meshes.push_back((hkxMesh*)va.m_object);
            if(!first_node) first_node = node;
        }
        mc->m_node = first_node;
        mc->processMeshes(meshes);
        m_components.push_back(mc);
    }
#endif

    std::vector<hkxNode*> skinNodes;
    findNodesRec(node, &hkxSkinBindingClass, skinNodes);
#if 0
    for(size_t i=0; i<skinNodes.size(); ++i)
    {
        hkxNode* node = skinNodes[i];
        hkVariant va = node->m_object;
        hkxSkinBinding* skin = (hkxSkinBinding*)va.m_object;
        ModelConverter* mc = new ModelConverter(this);

        char buf[128];
        if(i == 0)
            bx::vsnprintf(buf, sizeof(buf), "%s", m_name.c_str());
        else
            bx::vsnprintf(buf, sizeof(buf), %s_%d", m_name.c_str(), i);

        mc->setName(buf);
        mc->process((void*)skin->m_mesh, 0);
        m_components.push_back(mc);
    }
#else
    if(!skinNodes.empty())
    {
        ModelConverter* mc = new ModelConverter(this);
        std::vector<hkxMesh*> meshes;
        hkxNode* first_node = 0;
        for(size_t i=0; i<skinNodes.size(); ++i)
        {
            hkxNode* node = skinNodes[i];
            hkVariant va = node->m_object;
            hkxSkinBinding* skin = (hkxSkinBinding*)va.m_object;
            meshes.push_back(skin->m_mesh);
            if(!first_node) first_node = node;
        }
        mc->m_node = first_node;
        mc->setName(m_name);
        mc->processMeshes(meshes);
        m_components.push_back(mc);
    }
#endif

    std::vector<hkxNode*> lightNodes;
    findNodesRec(node, &hkxLightClass, lightNodes);
    for(size_t i=0; i<lightNodes.size(); ++i)
    {
        hkxNode* node = lightNodes[i];
        hkVariant va = node->m_object;
        LightConverter* lc = new LightConverter(this);
        lc->m_node = node;

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
        physics->m_node = node;
        physics->setName(m_name);
        physics->process((void*)m_config->m_physics);
        m_components.push_back(physics);
    }
#endif
}

void StaticModelConverter::processPhysics( hkpPhysicsData* data )
{
    PhysicsConverter* physics = new PhysicsConverter(this);
    physics->setName(m_name);
    physics->process((void*)data);
    m_components.push_back(physics);
}
