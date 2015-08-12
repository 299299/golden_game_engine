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
    jsonxx::Object new_json = serializeToJson();

    if (g_hc_config->m_merge) {
        jsonxx::Object old_json;
        if (read_json_from_file(old_json, fileName))
            merge_json(new_json, old_json);
    }

    if (!write_json_to_file(new_json, fileName))
        g_hc_config->m_error.add_error("%s to %s IO error.", __FUNCTION__, fileName.c_str());
}

std::string ComponentConverter::getOutputFileName() const
{
    return m_ownner->m_config->m_exportFolder + m_name + "." + getTypeName();
}
