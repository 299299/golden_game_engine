#include "ActorConverter.h"
#include "ComponentConverter.h"
#include "Actor.h"
#include "Component.h"

ActorConverter::ActorConverter()
:m_config(NULL)
{

}

ActorConverter::~ActorConverter()
{
    for(size_t i=0; i<m_components.size(); ++i)
    {
        SAFE_REMOVEREF(m_components[i]);
    }
}

void ActorConverter::postProcess()
{
    for(size_t i=0; i<m_components.size(); ++i)
    {
        m_components[i]->postProcess();
    }
}

jsonxx::Object
ActorConverter::serializeToJson() const
{
    jsonxx::Object rootObject;
    rootObject << "name" << m_name;
    rootObject << "class" << m_class;
    std::string srcFile = m_config->m_input;
    string_replace(srcFile, "\\", "/");
    rootObject << "source_file" << srcFile;
    srcFile = m_config->m_assetPath;
    string_replace(srcFile, "\\", "/");
    rootObject << "asset_path" << srcFile;

    hkxScene* scene = m_config->m_scene;
    jsonxx::Array compsObject;
    for(size_t i=0; i<m_components.size(); ++i)
    {
        compsObject << m_components[i]->serializeToJson();
    }

#ifdef HAVOK_COMPILE
    if(scene)
    {
        hkxNode* root_node = scene->m_rootNode;
        if (root_node)
        {
            for (int i=0; i<root_node->m_children.getSize(); ++i)
            {
                hkxNode* node = root_node->m_children[i];
                printf("root child = %s\n", node->m_name.cString());
                StringId type = stringid_caculate(node->m_name.cString());
                if (!g_componentMgr.find_factory(type))
                    continue;
                
                LOGI("processing other components node %s", node->m_name.cString());
                jsonxx::Object o;
                fill_object_attributes(o, node);
                o << "type" << std::string(node->m_name.cString());
                compsObject << o;
            }
        }
    }
#endif

    rootObject << "components" << compsObject;

#ifdef HAVOK_COMPILE
    hkxNode* data_node = scene->findNodeByName("data");
    if(data_node)
    {
        jsonxx::Object dataObject;
        dumpNodeRec(data_node);
        fill_object_attributes(dataObject, data_node);
        rootObject << "data" << dataObject;
    }
#endif

    return rootObject;
}

void ActorConverter::serializeToFile(const std::string& fileName)
{
    std::ofstream s(fileName.c_str());
    if(!s.good())
    {
        g_hc_config->m_error.add_error("%s to %s IO error.", __FUNCTION__, fileName.c_str());
        return;
    }
    s << serializeToJson().json();
}

std::string ActorConverter::getResourceName() const
{
    return m_config->m_rootPath + m_name;
}

hkxNode* ActorConverter::findNode(const char* name)
{
#ifdef HAVOK_COMPILE
    return m_config->m_scene->findNodeByName(name);
#else
    return 0;
#endif
}
