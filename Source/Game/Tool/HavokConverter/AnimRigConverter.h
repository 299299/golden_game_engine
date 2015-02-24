#pragma once
#include "ComponentConverter.h"

struct RigSkinData;
class AnimRigConverter : public ComponentConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    AnimRigConverter(ActorConverter* ownner);
    ~AnimRigConverter();

    virtual std::string getTypeName() const { return EngineNames::ANIMATION_RIG; };
    virtual void process(void* pData, int hint = 0);
    virtual void postProcess();
    virtual jsonxx::Object serializeToJson() const;

private:
    void process(RigSkinData* skin);
    int findBodyPart(const std::string& boneName, const char** arrayBones);
    void writeRig(const std::string& fileName);
    jsonxx::Object getRigJson() const;
private:
    RigSkinData*                         m_skin;
    std::string                          m_rigFileName;
    std::string                          m_rigJson;
    StringArray                          m_boneNames;
    int                                  m_bodyPart[kBodyPartMax];
};
