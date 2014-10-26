#include "ActorConverter.h"
#include "ComponentConverter.h"
#include "HC_Utils.h"
#include "ComponentNodeConverter.h"
#include "ProxyInstance.h"
#include "Script.h"
#include <bx/bx.h>

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

    jsonxx::Array compsObject;
	const std::string pack_key("packed");
    for(size_t i=0; i<m_components.size(); ++i)
    {
        jsonxx::Object obj = m_components[i]->serializeToJson();
		if(!obj.has<bool>(pack_key)) obj << pack_key << true;
        compsObject << obj;
    }
    rootObject << "components" << compsObject;
    
    jsonxx::Array dataObject;
    {
        //todo
    }
    rootObject << "data" << dataObject;
    return rootObject;
}

void ActorConverter::serializeToFile(const char* fileName)
{
    std::ofstream s(fileName);
    if(!s.good())
    {
        addError("serializeToFile to %s IO error.", fileName);
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
    return m_config->m_scene->findNodeByName(name);
}

void ActorConverter::processComponentNodes()
{
    static const char* s_componet_node_names[] =
    {
        ProxyResource::get_name(),
        ScriptResource::get_name(),
    };

    for (int i=0; i<BX_COUNTOF(s_componet_node_names); ++i)
    {
        hkxNode* p_node = findNode(s_componet_node_names[i]);
        if(!p_node) continue;
        ComponentNodeConverter* node = new ComponentNodeConverter(this);
        node->setName(m_name);
		node->m_typeName = s_componet_node_names[i];
        node->process(p_node, 0);
        m_components.push_back(node);
    }
}
