#pragma once
#include "ActorConverter.h"

class AnimationConverter : public ActorConverter
{
public:
    AnimationConverter();
    virtual ~AnimationConverter();

    virtual std::string getTypeName() const { return EngineNames::ANIMATION; };
    virtual void process(void* pData);
    virtual void postProcess();
    virtual jsonxx::Object serializeToJson() const;
    virtual void serializeToFile(const std::string& fileName);

private:
    hkaAnimationContainer*          m_ac;
    std::string                     m_animationFile;
};