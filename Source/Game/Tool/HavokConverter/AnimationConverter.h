#pragma once
#include "ActorConverter.h"
#include "Animation.h"

class AnimationConverter : public ActorConverter
{
public:
    AnimationConverter();
    virtual ~AnimationConverter();

    virtual std::string getTypeName() const { return Animation::get_name(); };
    virtual std::string getFormatExt() const { return Animation::get_name(); };
    virtual std::string combieFileName() const {
        return m_name + "." + getFormatExt();
    }

    virtual void process(void* pData);
    virtual void postProcess();
    virtual jsonxx::Object serializeToJson() const;

private:
    hkaAnimationContainer*          m_ac;
    std::string                     m_animationFile;
};