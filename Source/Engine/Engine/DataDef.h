#pragma once
#include "ShaderInc.h"

enum EntityClasss
{
    kLevelGeometry,
    kProp,
    kCharacter,
    //kTrigger,
    kEntityClassNum
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
    kGUIViewId = 31,
    kNumOfViewId
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


enum ComponentType
{
    kComponentModel,
    kComponentLight,
    kComponentPhysics,
    kComponentProxy,
    kComponentAnimRig,
    kComponentAnimFSM,
    kComponentIk,
    kComponentScript,
    kComponentTypeNum
};


#define RESOURCE_WORKER_THREAD_ID                   (1)
#define STRING_TABLE_FILE                           ("string_table.txt")
