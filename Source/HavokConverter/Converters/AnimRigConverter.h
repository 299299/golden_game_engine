#pragma once
#include "ComponentConverter.h"

struct RigSkinData;
class AnimRigConverter : public ComponentConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    AnimRigConverter(ActorConverter* ownner);
    ~AnimRigConverter();
    
    virtual std::string getTypeName() const { return AnimRig::getName(); };
    virtual std::string getFormatExt() const { return AnimRig::getName(); };

    virtual void process(void* pData, int hint = 0);
    virtual void postProcess();
    virtual jsonxx::Object serializeToJson() const;

private:
    void process(RigSkinData* skin);
    void exportRig(const char* fileName);
    int findBodyPart(const std::string& boneName, const char** arrayBones);

private:
    RigSkinData*                         m_skin;
    std::string                          m_rigFileName;
    std::vector<std::string>             m_boneNames;
    int                                  m_bodyPart[kBodyPartMax];
};