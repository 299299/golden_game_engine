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


PhysicsConfigCompiler::PhysicsConfigCompiler()
{

}

PhysicsConfigCompiler::~PhysicsConfigCompiler()
{
    
}

int findFilterIndex(const std::string& name) const
{
    for(size_t i=0; i<m_filterNames.size(); ++i)
    {
        if(m_filterNames[i] == name)
            return i;
    }
    return -1;
}

bool PhysicsConfigCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    
    uint32_t numOfFilters = 0;
    JsonValue filtersValue = root.GetValue("collision_filters");
    if(filtersValue.IsValid()) numOfFilters = filtersValue.GetElementsCount();

    uint32_t memSize = sizeof(PhysicsConfig) + numOfFilters * sizeof(CollisionFilter);
    char* p = malloc(memSize);
    memset(p, 0x00, memSize);
    PhysicsConfig* cfg = (PhysicsConfig*)p;
    cfg->m_numFilters = numOfFilters;

    for(uint32_t i=0; i<m_numFilters; ++i)
    {
        JsonValue filterValue = filtersValue[i];
        m_filterNames.push(JSON_GetString(filterValue.GetValue("name"));
    }


    for(uint32_t i=0; i<m_numFilters; ++i)
    {
        JsonValue filterValue = filtersValue[i];
        JsonValue colValue = filterValue.GetValue("collides_with");
        JsonValue notColValue = filterValue.GetValue("not_collides_with");
        CollisionFilter& filter = cfg->m_filters[i];

        uint32_t mask = 0;
        
        if(colValue.IsValid())
        {
            for(uint32_t i=0; i<colValue.GetElementsCount(); ++i)
            {
                mask |= (1 << findFilterIndex(JSON_GetString(colValue[i])));
            }
        }
        if(notColValue.IsValid())
        {
            for(uint32_t i=0; i<notColValue.GetElementsCount(); ++i)
            {
                mask &= ~(1 << findFilterIndex(JSON_GetString(colValue[i])));
            }
        }
        filter.m_mask = mask;
    }
}