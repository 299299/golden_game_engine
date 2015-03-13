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
    LOGD("%s %s", __FUNCTION__, fileName.c_str());
    std::ofstream s(fileName);
    if(!s.good())
    {
        g_hc_config->m_error.add_error("%s to %s IO error.", __FUNCTION__, fileName.c_str());
        return;
    }
    s << serializeToJson().json();
}

std::string ComponentConverter::getOutputFileName() const
{
    return m_ownner->m_config->m_exportFolder + m_name + "." + getTypeName();
}
