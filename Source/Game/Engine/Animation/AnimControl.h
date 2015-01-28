#pragma once
#include "Prerequisites.h"
#include "Animation.h"
#include "DataDef.h"
#ifdef HAVOK_COMPILE
#include <Animation/Animation/Playback/Control/Default/hkaDefaultAnimationControl.h>

struct hk_anim_ctrl : public hkaDefaultAnimationControl
{
	Animation*              m_animation;
	StringId                m_name;

	uint8_t                 m_motionType;
	uint8_t                 m_layer;
	bool                    m_enabled;
	char                    m_padding[1];

	HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_ANIM_CONTROL);
	hk_anim_ctrl(Animation* anim)
		:hkaDefaultAnimationControl(anim ? anim->m_binding : 0, false)
		,m_animation(anim)
		,m_enabled(false)
		,m_motionType(kMotionDefault)
		,m_layer(0)
	{

	}

	virtual void getExtractedMotionDeltaReferenceFrame( hkReal deltaTime, hkQsTransform& deltaMotionOut ) const HK_OVERRIDE
	{
		switch(m_motionType)
		{
		case kMotionDefault:
			__super::getExtractedMotionDeltaReferenceFrame(deltaTime, deltaMotionOut);
			break;
		case kMotionIgnoreRotation:
			__super::getExtractedMotionDeltaReferenceFrame(deltaTime, deltaMotionOut);
			deltaMotionOut.m_rotation.setIdentity();
			break;
		case kMotionIgnoreTranslation:
			__super::getExtractedMotionDeltaReferenceFrame(deltaTime, deltaMotionOut);
			deltaMotionOut.m_translation.setZero4();
			break;
		case kMotionIgnoreAll:
		default: return;
		}
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
};
#else
struct hk_anim_ctrl{};
#endif