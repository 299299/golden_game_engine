#include "ProxyConverter.h"
#include "HC_Utils.h"

ProxyConverter::ProxyConverter(ActorConverter* ownner)
:ComponentConverter(ownner)
{
    
}

ProxyConverter::~ProxyConverter()
{

}

void ProxyConverter::process(void* pData, int hint)
{
    m_node = (hkxNode*)pData;
    m_attributes = m_node->findAttributeGroupByName(ENGINE_ATTRIBUTES);
}

jsonxx::Object ProxyConverter::serializeToJson() const
{
    jsonxx::Object object;
    fill_object_attributes(object, m_attributes);
    return object;
}
