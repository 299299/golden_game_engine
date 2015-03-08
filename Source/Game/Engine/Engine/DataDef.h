#pragma once
#include "ShaderInc.h"
#include "StringId.h"

enum ActorClass
{
    kLevelGeometry,
    kProp,
    kCharacter,
    //kTrigger,
    kActorClassNum
};

enum SubsystemTickStatus
{
    kTickFrameStart,
    kTickProcessing,
    kTickFinishedJobs,
};

enum IKMask
{
    kIKNone         = 0,
    kIKLookAt       = (1 << 0),
    kIKReachLeft    = (1 << 1),
    kIKReachRight   = (1 << 2),
    kIKFoot         = (1 << 3)
};

enum ViewId
{
    kShadowViewId  = 0,
    kBackgroundViewId,
    kSceneViewId,
    kDebugDrawViewId,
    kHDRBrightViewId,
    kHDRBlurViewIdStart,
    kCombineViewId = kHDRBlurViewIdStart + N_PASSES * 2,
    // ...
    // OTHERS VIEW ID
    // ...
    kGUIViewId = 255,
};

enum SceneNodeFlag
{
    kNodeFlagNone       = 0,
    kNodeInvisible      = (1 << 0),
    kNodeTransformDirty = (1 << 1),
    kNodeNoShadow       = (1 << 2)
};

enum LightType
{
    kLightDirectional,
    kLightSpot,
    kLightPoint,
    kLightCount
};

enum AppErrorCode
{
    kErrorSuccess   = 0,
    kErrorAction    = -1,
    kErrorArg       = -2,
    kErrorLoadHavok = -3,
};

enum EaseCurveType
{
    kEaseCurveSmooth,
    kEaseCurveLinear,
    kEaseCurveFast
};

enum MotionBlendingType
{
    kMotionBlendingDefault,
    kMotionBlendingIgnoreSrcRotation,
    kMotionBlendingIgnoreDstRotation,
    kMotionBlendingIgnoreSrcMotion,
    kMotionBlendingIgnoreDstMotion,
};

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

struct AnimationNodeType
{
    enum
    {
        Undefined = -1,
        Value,
        Lerp,
        Additive,
        Select,
        Num
    };
};

#define DEFAULT_ANIM_TRANSITION_DURATION    (0.1f)

namespace EngineTypes
{
    extern StringId     ANIMATION;
    extern StringId     ANIMATION_STATES;
    extern StringId     MESH;
    extern StringId     MATERIAL;
    extern StringId     TEXTURE;
    extern StringId     TEXTURE_3D;
    extern StringId     ANIMATION_RIG;
    extern StringId     SHADER;
    extern StringId     PROGRAM;
    extern StringId     SHADING_ENV;
    extern StringId     PHYSICS_CONFIG;
    extern StringId     MODEL;
    extern StringId     LIGHT;
    extern StringId     ACTOR;
    extern StringId     LEVEL;
};


namespace EngineNames
{
    extern const char*  ANIMATION;
    extern const char*  ANIMATION_STATES;
    extern const char*  MESH;
    extern const char*  MATERIAL;
    extern const char*  TEXTURE;
    extern const char*  TEXTURE_3D;
    extern const char*  ANIMATION_RIG;
    extern const char*  SHADER;
    extern const char*  PROGRAM;
    extern const char*  SHADING_ENV;
    extern const char*  PHYSICS_CONFIG;
    extern const char*  MODEL;
    extern const char*  LIGHT;
    extern const char*  ACTOR;
    extern const char*  LEVEL;
};

struct ComponentInstanceData
{
    StringId    m_name;
    void*       m_resource;
};


#define STRING_TABLE_FILE                           ("string_table.txt")