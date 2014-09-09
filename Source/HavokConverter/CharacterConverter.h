#pragma once
#include "EntityConverter.h"

struct RigSkinData;
class CharacterConverter : public EntityConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    CharacterConverter();
    ~CharacterConverter();
    virtual void process(void* pData);
    virtual jsonxx::Object serializeToJson() const;
private:
    void process(hkaAnimationContainer* ac);
    void collectRigSkinData(hkaSkeleton* rig);

private:
    hkaAnimationContainer*               m_ac;
    RigSkinData*                         m_skin;
};
