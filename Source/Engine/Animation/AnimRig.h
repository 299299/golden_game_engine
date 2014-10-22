#pragma once
#include "StringId.h"
#include "Prerequisites.h"

class   hkaSkeleton;
class   hkaMirroredSkeleton;
class   hkaPose;
class   hkaAnimatedSkeleton;
struct  AnimationTrigger;
class   hkaDefaultAnimationControl;
struct  Animation;
struct  hk_anim_ctrl;
struct  CommandMachine;

enum HumanBodypart
{
    kBodyHead,
    kBodyNeck,
    kBodyShoulder_L,
    kBodyArm_L,
    kBodyForeArm_L,
    kBodyHand_L,
    kBodyShoulder_R,
    kBodyArm_R,
    kBodyForeArm_R,
    kBodyHand_R,
    kBodyHip,
    kBodyUpLeg_L,
    kBodyLeg_L,
    kBodyFoot_L,
    kBodyUpLeg_R,
    kBodyLeg_R,
    kBodyFoot_R,
    kBodyPartMax
};

enum EaseCurveType
{
	kEaseCurveSmooth,
	kEaseCurveLinear,
	kEaseCurveFast
};

enum MotionType
{
    kMotionDefault,
    kMotionIgnoreRotation,
    kMotionIgnoreTranslation,
    kMotionIgnoreAll
};

struct BoneAttachment
{
    float               m_boneFromAttachment[16];
    StringId            m_name;
    int                 m_boneIndex;
};

ENGINE_NATIVE_ALIGN struct AnimRig
{
    DECLARE_RESOURCE(rig);

    int  find_joint_index(const StringId& jointName) const;
	int  find_animation_index(const StringId& name) const;

    void create_mirrored_skeleton();

    int                             m_humanJointIndices[kBodyPartMax];
    hkaSkeleton*                    m_skeleton;
    hkaMirroredSkeleton*            m_mirroredSkeleton;
    BoneAttachment*                 m_attachments;

    StringId*                       m_jointNames;
    uint32_t                        m_havokDataOffset;
    uint32_t                        m_havokDataSize;

	StringId*						m_animNames;
	uint32_t						m_numAnimations;
	Animation**						m_animations;
	
    uint16_t                        m_jointNum;
    uint8_t                         m_attachNum;
    bool                            m_mirrored;
};

ENGINE_NATIVE_ALIGN struct AnimRigInstance
{
    CommandMachine*                 m_animMachine;
    const AnimRig*                  m_resource;
    hkaPose*                        m_pose;
    hkaAnimatedSkeleton*            m_skeleton;
    float*                          m_attachmentTransforms;
    hk_anim_ctrl**                  m_controls;
    uint32_t                        m_numControls;
	char*							m_blob;
	bool							m_applyRootmotion;

    void init(const void* resource);
    void destroy();
    void update(float dt);
    bool is_playing_animation() const;
    void update_attachments(const hkQsTransform& worldFromModel);
    hk_anim_ctrl* get_control(int index) const;
    int find_control(const StringId& name) const;
    void test_animation(const char* name);
	//----------------------------------------------------------------------
	// ANIMATION API
	void easein_animation(int index, float blend_time, bool bloop, float when = 0.0f, int type = kEaseCurveSmooth);
	void easeout_animation(int index, float blend_time, float when = 0.0f, int type = kEaseCurveSmooth);
	void easeout_layers(int layer, float time, int type = kEaseCurveSmooth);
	void set_animation_weight(int index, float weight, float when = 0.0f);
	void set_animation_speed(int index, float speed, float when = 0.0f);
	void set_animation_time(int index, float local_time, float when = 0.0f);
	float get_animation_weight(int index) const;
	float get_animation_speed(int index) const;
	float get_animation_time(int index) const;
	float get_animation_period(int index) const;
	void  get_rootmotion(float dt, hkQsTransform& t) const;
	void  get_rootmotion(int index, float dt, hkQsTransform& t) const;
	//----------------------------------------------------------------------
}; 
