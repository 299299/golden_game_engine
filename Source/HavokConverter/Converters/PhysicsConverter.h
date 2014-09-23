#pragma once
#include "stdafx.h"
#include "ComponentConverter.h"
#include "PhysicsInstance.h"

class PhysicsConverter   : public ComponentConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    PhysicsConverter(ActorConverter* ownner);
    ~PhysicsConverter();

    virtual std::string getTypeName() const { return PhysicsResource::get_name(); };
    virtual std::string getFormatExt() const { return PhysicsResource::get_name(); };
    
    virtual void process(void* pData, int hint = 0);
    virtual jsonxx::Object serializeToJson() const;
    virtual void postProcess();

private:
    void process(hkpPhysicsData* data);
    void exportPhysics(const char* fileName);

private:
    std::string                 m_phyFileName;
    hkpPhysicsData*             m_physics;
    int                         m_type;
};