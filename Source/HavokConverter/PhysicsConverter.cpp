#include "PhysicsConverter.h"
#include "EntityConverter.h"
#include "Utils.h"
#include <Common/Serialize/Packfile/Binary/hkBinaryPackfileWriter.h>

static const char*  physics_type_names[] = 
{
    "rigidbody-only", "ragdoll", "trigger", "complex", 0
};

PhysicsConverter::PhysicsConverter(EntityConverter* ownner)
:ComponentConverter(ownner)
,m_physics(0)
,m_type(0)
{
    
}

PhysicsConverter::~PhysicsConverter()
{

}

void PhysicsConverter::exportPhysics(const char* fileName)
{
    LOGD("Write physics file: %s.", fileName);
    hkPackfileWriter::Options options;
    options.m_writeMetaInfo = false;
    hkOstream ostream(fileName);
    hkBinaryPackfileWriter writer;
    writer.setContents(m_physics, hkpPhysicsData::staticClass());
    if(writer.save(ostream.getStreamWriter(), options) != HK_SUCCESS) 
        addError(__FUNCTION__" write error.");
}

void PhysicsConverter::process(void* pData, int hint)
{
    process((hkpPhysicsData*)pData);
}

void PhysicsConverter::process(hkpPhysicsData* data)
{
    m_physics = data;
    m_type = kSystemRBOnly;
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
    exportPhysics(m_phyFileName.c_str());

#if 0
    char* buf = 0;
    uint32_t fileSize = read_file(m_phyFileName, &buf);
    hkpPhysicsData* data = (hkpPhysicsData*)load_havok_inplace(buf, fileSize);
    free(buf);
#endif
}

jsonxx::Object PhysicsConverter::serializeToJson() const
{
    jsonxx::Object phyObject;
    phyObject << "physics-type" << std::string(physics_type_names[m_type]);
    phyObject << "havok-file" << m_phyFileName;
    phyObject << "name" << getResourceName();
    phyObject << "type" << getTypeName();
    return phyObject;
}