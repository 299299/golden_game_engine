#include "PhysicsConverter.h"
#include "ActorConverter.h"

PhysicsConverter::PhysicsConverter(ActorConverter* ownner)
:ComponentConverter(ownner)
,m_physics(0)
,m_type(0)
{
    
}

PhysicsConverter::~PhysicsConverter()
{

}

void PhysicsConverter::process(void* pData, int hint)
{
    process((hkpPhysicsData*)pData);
}

void PhysicsConverter::process(hkpPhysicsData* data)
{
    m_physics = data;
    m_type = kSystemRigidBody;
    for(int i=0; i<m_physics->getPhysicsSystems().getSize(); ++i)
    {
        hkpPhysicsSystem* system = m_physics->getPhysicsSystems()[i];
        if(!system->getPhantoms().isEmpty())
            m_type = kSystemComplex;
        else if(!system->getConstraints().isEmpty())
            m_type = kSystemComplex;
        else if(!system->getActions().isEmpty())
            m_type = kSystemComplex;
    }

    if(m_type == kSystemComplex)
    {
        //
    }
}

void PhysicsConverter::postProcess()
{
    m_phyFileName = m_ownner->m_config->m_exportFolder + m_name + ".havok";
    {
        LOGD("Write physics file: %s.", m_phyFileName.c_str());
        hkPackfileWriter::Options options;
        options.m_writeMetaInfo = false;
        hkOstream ostream(m_phyFileName.c_str());
        hkBinaryPackfileWriter writer;
        writer.setContents(m_physics, hkpPhysicsData::staticClass());
        if(writer.save(ostream.getStreamWriter(), options) != HK_SUCCESS) 
            g_config->m_error.add_error(__FUNCTION__" write error.");
    }
}

jsonxx::Object PhysicsConverter::serializeToJson() const
{
    jsonxx::Object phyObject;
    extern const char* physics_type_names[];
    phyObject << "physics_type" << std::string(physics_type_names[m_type]);
    phyObject << "havok_file" << m_phyFileName;
    phyObject << "name" << getResourceName();
    phyObject << "type" << getTypeName();
    return phyObject;
}