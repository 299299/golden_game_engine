#include "PhysicsCompiler.h"

static const char*   physics_type_names[] = 
{
    "rigidbody-only", "ragdoll", "trigger", "complex", 0
};

PhysicsCompiler::PhysicsCompiler()
{

}

PhysicsCompiler::~PhysicsCompiler()
{
    
}

bool PhysicsCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    uint32_t havokOffset = sizeof(PhysicsResource);
    havokOffset = HK_NEXT_MULTIPLE_OF(16, havokOffset);
    
    std::string havokFile = JSON_GetString(root.GetValue("havok-file"));
    char* havokData = 0;
    uint32_t havokFileSize = read_file(havokFile.c_str(), &havokData);
    if(havokFileSize < 16)
    {
        addError(__FUNCTION__ " can not find havok file [%s]", havokFile.c_str());
        return false;
    }

    uint32_t memSize = havokOffset + havokFileSize;
    LOGD("%s total mem-size = %d", m_output.c_str(), memSize);
    char* p = (char*)malloc(memSize);
    memset(p, 0x00, memSize);
    PhysicsResource* physics = (PhysicsResource*)p;
    physics->m_systemType = JSON_GetEnum(root.GetValue("physics-type"), physics_type_names);
    physics->m_havokDataOffset = havokOffset;
    physics->m_havokDataSize = havokFileSize;
    memcpy(p + havokOffset, havokData, havokFileSize);
    free(havokData);
    bool bRet = write_file(m_output, p, memSize);
    free(p);
    return bRet;
}