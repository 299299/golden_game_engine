#include "EntityConverter.h"
#include "ComponentConverter.h"
#include "HC_Utils.h"

EntityConverter::EntityConverter()
{
    
}

EntityConverter::~EntityConverter()
{
    for(size_t i=0; i<m_components.size(); ++i)
    {
        SAFE_REMOVEREF(m_components[i]);
    }
}

void EntityConverter::postProcess()
{
    for(size_t i=0; i<m_components.size(); ++i)
    {
        m_components[i]->postProcess();
    }
}

jsonxx::Object 
EntityConverter::serializeToJson() const
{
    jsonxx::Object rootObject;
    rootObject << "name" << m_name;
    rootObject << "class" << m_class;
    std::string srcFile = m_config->m_input;
    string_replace(srcFile, "\\", "/");
    rootObject << "source-file" << srcFile;
    srcFile = m_config->m_assetPath;
    string_replace(srcFile, "\\", "/");
    rootObject << "asset-path" << srcFile;

    jsonxx::Array compsObject;
    for(size_t i=0; i<m_components.size(); ++i)
    {
        jsonxx::Object obj = m_components[i]->serializeToJson();
        obj << "packed" << true;
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

void EntityConverter::serializeToFile(const char* fileName)
{
    std::ofstream s(fileName);
    if(!s.good())
    {
        addError("serializeToFile to %s IO error.", fileName);
        return;
    }
    s << serializeToJson().json();
}

jsonxx::Object EntityConverter::serializeToJsonSplit() const
{
    jsonxx::Object rootObject;
    rootObject << "name" << m_name;
    rootObject << "class" << m_class;

    std::string srcFile = m_config->m_input;
    string_replace(srcFile, "\\", "/");
    rootObject << "source-file" << srcFile;
    srcFile = m_config->m_assetPath;
    string_replace(srcFile, "\\", "/");
    rootObject << "asset-path" << srcFile;

    jsonxx::Array compsObject;
    for(size_t i=0; i<m_components.size(); ++i)
    {
        ComponentConverter* comp = m_components[i];
        std::string fileName = m_config->m_exportFolder + comp->combieFileName();
        comp->serializeToFile(fileName.c_str());
        std::string compName = comp->getResourceName();
        jsonxx::Object compObject;
        compObject << "type" << comp->getTypeName();
        compObject << "name" << compName;
        compObject << "packed" << false;
        compsObject << compObject;
        LOGI("[%s]  %s --> %s", fileName.c_str(), compName.c_str(), fileName.c_str());
    }
    rootObject << "components" << compsObject;
    
    jsonxx::Array dataObject;
    {
        //todo
    }
    rootObject << "data" << dataObject;
    return rootObject;
}

void EntityConverter::serializeToFileSplit( const char* fileName )
{
    std::ofstream s(fileName);
    if(!s.good())
    {
        addError("serializeToFileSplit to %s IO error.", fileName);
        return;
    }
    jsonxx::Object obj = serializeToJsonSplit();
    s << obj.json();
    LOGI(obj.json().c_str());
}
