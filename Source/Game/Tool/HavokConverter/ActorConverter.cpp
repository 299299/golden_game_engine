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

static bool is_component_exist(const jsonxx::Array& components, const jsonxx::Object& o1)
{
    const std::string& type = o1.get<std::string>("type");
    const std::string& name = o1.get<std::string>("name");

    for(size_t i=0; i<components.size(); ++i)
    {
        const jsonxx::Object& component = components.get<jsonxx::Object>(i);
        if (component.get<std::string>("type") == type &&
            component.get<std::string>("name") == name ) {
            return true;
        }
    }

    return false;
}

void ActorConverter::serializeToFile(const std::string& fileName)
{
    jsonxx::Object new_json = serializeToJson();
    if (g_hc_config->m_merge) {
        jsonxx::Object old_json;

        if (read_json_from_file(old_json, fileName)) {

            merge_json(new_json, old_json);

            if (old_json.has<jsonxx::Array>("components")) {
                const jsonxx::Array& old_components = old_json.get<jsonxx::Array>("components");
                jsonxx::Array& new_components = new_json.get<jsonxx::Array>("components");

                LOGW("old-components -->");
                for(size_t i=0; i<old_components.size(); ++i)
                {
                    const jsonxx::Object& comp = old_components.get<jsonxx::Object>(i);
                    LOGW("name:%s, type:%s", comp.get<std::string>("type").c_str(), comp.get<std::string>("name").c_str());
                }

                LOGW("new-components -->");
                for(size_t i=0; i<new_components.size(); ++i)
                {
                    const jsonxx::Object& comp = new_components.get<jsonxx::Object>(i);
                    LOGW("name:%s, type:%s", comp.get<std::string>("type").c_str(), comp.get<std::string>("name").c_str());
                }

                for(size_t i=0; i<old_components.size(); ++i)
                {
                    const jsonxx::Object& old_component = old_components.get<jsonxx::Object>(i);
                    if (!is_component_exist(new_components, old_component)) {
                        LOGW("%s find a not exist component !!!!  [%s,%s]",
                            fileName.c_str(),
                            old_component.get<std::string>("type").c_str(),
                            old_component.get<std::string>("name").c_str());
                        new_components << old_component;
                    }
                }
            }
        }
    }

    if (!write_json_to_file(new_json, fileName))
        g_hc_config->m_error.add_error("%s to %s IO error.", __FUNCTION__, fileName.c_str());
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
