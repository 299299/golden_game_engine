#include "ComponentConverter.h"
#include "ActorConverter.h"
#include "ToolUtils.h"

ComponentConverter::ComponentConverter(ActorConverter* ownner)
:m_ownner(ownner)
,m_node(0)
{

}


void ComponentConverter::serializeToFile(const char* fileName)
{
    std::ofstream s(fileName);
    if(!s.good())
    {
        addError("%s serializeToFile to %s IO error.", getTypeName().c_str(), fileName);
        return;
    }
    s << serializeToJson().json();
}

std::string ComponentConverter::getOutputFileName() const
{
    return m_ownner->m_config->m_exportFolder + combieFileName();
}

void ComponentConverter::writeOutput()
{
    serializeToFile(getOutputFileName().c_str());
}

std::string ComponentConverter::getResourceName() const
{
    return m_ownner->m_config->m_rootPath + m_name;
}

bool ComponentConverter::isExistInCommonPackage() const
{
    std::string pathName = COMMON_ASSET_PATH;
    pathName += combieFileName();
    return isFileExist(pathName);
}

void ComponentConverter::fillAttributes(jsonxx::Object& object) const
{
    if(!m_node) return;
    fill_object_attributes(object, m_node->findAttributeGroupByName(ENGINE_ATTRIBUTES));
}