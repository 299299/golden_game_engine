#pragma once
#include "stdafx.h"
#include "ComponentConverter.h"
#include "ProxyInstance.h"

class ProxyConverter   : public ComponentConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    ProxyConverter(ActorConverter* ownner);
    ~ProxyConverter();

    virtual std::string getTypeName() const { return ProxyResource::get_name(); };
    virtual std::string getFormatExt() const { return ProxyResource::get_name(); };

    virtual void process(void* pData, int hint = 0);
    virtual jsonxx::Object serializeToJson() const;
    
private:
    hkxNode*                        m_node;
    const hkxAttributeGroup*        m_attributes;
};