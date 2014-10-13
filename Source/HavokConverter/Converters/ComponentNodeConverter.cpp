#include "ComponentNodeConverter.h"
#include "HC_Utils.h"

ComponentNodeConverter::ComponentNodeConverter(ActorConverter* ownner)
:ComponentConverter(ownner)
{
    
}

ComponentNodeConverter::~ComponentNodeConverter()
{

}

void ComponentNodeConverter::process(void* pData, int hint)
{
    m_node = (hkxNode*)pData;
    m_attributes = m_node->findAttributeGroupByName(ENGINE_ATTRIBUTES);
}

jsonxx::Object ComponentNodeConverter::serializeToJson() const
{
    jsonxx::Object object;
    object << "type" << getTypeName();
    object << "packaged" << true;
    object << "name" << getResourceName();
    fill_object_attributes(object, m_attributes);
    return object;
}
