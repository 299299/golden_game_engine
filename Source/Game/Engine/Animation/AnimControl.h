#pragma once
#include "Prerequisites.h"
#include "Animation.h"
#include "DataDef.h"
#ifdef HAVOK_COMPILE
#include <Animation/Animation/Playback/Control/Default/hkaDefaultAnimationControl.h>
#include <Animation/Animation/Playback/hkaAnimatedSkeleton.h>

struct hk_anim_ctrl : public hkaDefaultAnimationControl
{
    Animation*              m_animation;
    StringId                m_name;
    bool                    m_enabled;
    char                    m_padding[3];

    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIM_CONTROL);
    hk_anim_ctrl(Animation* anim)
        :hkaDefaultAnimationControl(anim ? anim->m_binding : 0, false)
        ,m_animation(anim)
        ,m_enabled(false)
    {

    }

    void ease_in(float time, int type)
    {
        setOverflowCount(0);
        setUnderflowCount(0);
        setLocalTime(0.0f);
        switch(type)
        {
        case kEaseCurveLinear:setEaseInCurve(0, 0.33f, 0.66f, 1);break;
        case kEaseCurveFast:setEaseInCurve(0, 0, 0, 1);break;
        case kEaseCurveSmooth:
        default:setEaseInCurve(0, 0, 1, 1);break;
        }
        easeIn(time);
    }

    void ease_out(float time, int type)
    {
        switch(type)
        {
        case kEaseCurveLinear:setEaseInCurve(1, 0.66f, 0.33f, 0);break;
        case kEaseCurveFast:setEaseInCurve(1, 1, 0, 0);break;
        case kEaseCurveSmooth:
        default:setEaseInCurve(1, 1, 0, 0);break;
        }
        easeOut(time);
    }

    void set_weight(float fWeight){ setMasterWeight(fWeight); }
    float get_weight() const { return getMasterWeight(); };
    float get_peroid() const {return m_binding->m_animation->m_duration; }
    void set_loop(bool bLooped) { m_maxCycles = bLooped ? -1 : 1; }
    bool is_loop() const { return m_maxCycles < 0;}

    void add_to_skeleton(hkaAnimatedSkeleton* s)
    {
        if(m_enabled)
            return;
        s->addAnimationControl(this);
        m_enabled = true;
    }

    void remove_from_skeleton(hkaAnimatedSkeleton* s)
    {
        if(!m_enabled)
            return;
        s->removeAnimationControl(this);
        m_enabled = false;
    }
};
#else
struct hkaAnimatedSkeleton;
struct hk_anim_ctrl
{
    Animation* m_animation;
    hk_anim_ctrl(Animation* anim):m_animation(anim) {};
    void removeReference() {};
    void getExtractedMotionDeltaReferenceFrame( hkReal deltaTime, hkQsTransform& deltaMotionOut ) {}
    void ease_in(float time, int type) {}
    void ease_out(float time, int type) {}
    void set_weight(float fWeight){}
    float get_weight() const { return 1.0f; }
    float get_peroid() const {return 2.0f; }
    void set_loop(bool bLooped) {}
    bool is_loop() const { return true;}
    void add_to_skeleton(hkaAnimatedSkeleton* s) {}
    void remove_from_skeleton(hkaAnimatedSkeleton* s) {}
    void setLocalTime(float time) {}
    void setPlaybackSpeed(float speed) {}
    void setUnderflowCount(int c) {}
    void setOverflowCount(int c) {}
};
#endif