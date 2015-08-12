#include "PhysicsConverter.h"
#include "ActorConverter.h"
#include "PhysicsInstance.h"
#include "HC_Config.h"

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
#ifdef HAVOK_COMPILE
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
#endif
}

void PhysicsConverter::postProcess()
{
#ifdef HAVOK_COMPILE
#ifndef HKX_BINARY_TO_TEXT
    m_phyFileName = m_ownner->m_config->m_exportFolder + m_name + ".havok";
#else
    m_phyFileName = HKX_TMP;
#endif

    LOGD("Write physics file: %s.", m_phyFileName.c_str());
    hkPackfileWriter::Options options;
    options.m_writeMetaInfo = false;
    hkOstream ostream(m_phyFileName.c_str());
    hkBinaryPackfileWriter writer;
    writer.setContents(m_physics, hkpPhysicsData::staticClass());
    if(writer.save(ostream.getStreamWriter(), options) != HK_SUCCESS)
        g_hc_config->m_error.add_error("%s write error.", BX_FUNCTION);

    std::string convert_string;
    uint32_t havok_size = 0;
#ifdef HKX_BINARY_TO_TEXT
    {
        FileReader reader(m_phyFileName);
        binary_to_string((const unsigned char*)reader.m_buf, reader.m_size, convert_string);
        havok_size = reader.m_size;
    }
    delete_file(m_phyFileName);
#endif

    m_compFileName = m_ownner->m_config->m_exportFolder + m_name + ".physics";
    jsonxx::Object new_json;
    extern const char* physics_type_names[];
    new_json << "physics_type" << std::string(physics_type_names[m_type]);
    new_json << "havok_file" << m_phyFileName;
    new_json << "name" << getResourceName();
    new_json << "type" << getTypeName();
#ifdef HKX_BINARY_TO_TEXT
    new_json << "havok_data" << convert_string;
    new_json << "havok_size" << havok_size;
#endif

    if (g_hc_config->m_merge) {
        jsonxx::Object old_json;
        if (read_json_from_file(old_json, m_compFileName))
            merge_json(new_json, old_json);
    }

    if (!write_json_to_file(new_json, m_compFileName))
        g_hc_config->m_error.add_error("%s to %s IO error.", __FUNCTION__, m_compFileName.c_str());
#endif
}

jsonxx::Object PhysicsConverter::serializeToJson() const
{
    jsonxx::Object o;
    o << "name" << getResourceName();
    o << "type" << getTypeName();
    return o;
}