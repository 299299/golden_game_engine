#pragma once
#include "EntityConverter.h"

class StaticModelConverter : public EntityConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    StaticModelConverter();
    ~StaticModelConverter();
    virtual void process(void* pData);
private:
    void process(hkxScene* scene);
private:
    hkxScene*                                   m_scene;
};
