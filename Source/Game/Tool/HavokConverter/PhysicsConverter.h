#pragma once
#include "ComponentConverter.h"

class PhysicsConverter   : public ComponentConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    PhysicsConverter(ActorConverter* ownner);
    ~PhysicsConverter();

    virtual std::string getTypeName() const { return EngineNames::PHYSICS; };
    virtual void process(void* pData, int hint = 0);
    virtual jsonxx::Object serializeToJson() const;
    virtual void postProcess();

private:
    void process(hkpPhysicsData* data);
private:
    std::string                 m_phyFileName;
    std::string                 m_compFileName;
    hkpPhysicsData*             m_physics;
    int                         m_type;
};