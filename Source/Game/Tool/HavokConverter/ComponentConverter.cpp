#include "ComponentConverter.h"
#include "ActorConverter.h"

ComponentConverter::ComponentConverter(ActorConverter* ownner)
:m_ownner(ownner)
,m_node(0)
{

}

std::string ComponentConverter::getResourceName() const
{
    return m_ownner->m_config->m_rootPath + m_name;
}

void ComponentConverter::fillAttributes(jsonxx::Object& object) const
{
    if(!m_node) 
        return;
#ifdef HAOVK_COMPILE
    fill_object_attributes(object, m_node);
#endif
}

void ComponentConverter::serializeToFile( const std::string& fileName )
{
    write_json_to_file(serializeToJson(), fileName);
}

std::string ComponentConverter::getOutputFileName() const
{
    return m_ownner->m_config->m_exportFolder + m_name + "." + getTypeName();
}
