#include "Prerequisites.h"


#ifdef HAVOK_COMPILE
//=======================================================================
//  HAVOK LIBS
//=======================================================================
#define HK_EXCLUDE_FEATURE_MemoryTracker
#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
#define HK_EXCLUDE_FEATURE_RegisterVersionPatches
#define HK_EXCLUDE_FEATURE_hkndAssetProcessing
#define HK_EXCLUDE_FEATURE_hkndDebrisFracture_execute
#define HK_EXCLUDE_FEATURE_hkndFxDebrisFracture_execute
#define HK_EXCLUDE_LIBRARY_hkCompat

#ifdef _RETAIL
#define HK_EXCLUDE_LIBRARY_hkSceneData
#define HK_EXCLUDE_LIBRARY_hkGeometryUtilities
#endif

// Register Havok classes.
#include <Common/Base/KeyCode.h>
#define HK_FEATURE_REFLECTION_COMMON_VISUALIZE
#define HK_CLASSES_FILE <Common/Serialize/Classlist/hkKeyCodeClasses.h>
#include <Common/Base/Config/hkProductFeatures.cxx>
#include <Common/Base/keycode.cxx>

//for xinput
#pragma comment(lib, "C:\\Program Files (x86)\\Microsoft DirectX SDK (June 2010)\\Lib\\x86\\XInput.lib")
#pragma comment(lib, "Psapi.lib")

//start of havok link config
#ifdef _DEBUG
#define HAVOK_LIB_PATH "C:\\Project\\hk2014_1_0_r1\\Lib\\win32_vs2010\\dev\\"
#else
#define HAVOK_LIB_PATH "C:\\Project\\hk2014_1_0_r1\\Lib\\win32_vs2010\\release\\"
#endif

#pragma comment(lib, HAVOK_LIB_PATH"hkBase.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkSerialize.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkSceneData.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkInternal.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkGeometryUtilities.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkVisualize.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkCompat.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkpCollide.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkpConstraintSolver.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkpInternal.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkpDynamics.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkpUtilities.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkpVehicle.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkcdInternal.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkaInternal.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkaPhysics2012Bridge.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkaAnimation.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkcdCollide.lib")
#pragma comment(lib, HAVOK_LIB_PATH"hkpConstraint.lib")

#ifndef _RETAIL
#pragma comment(lib, HAVOK_LIB_PATH"hkImageUtilities.lib")
#endif

//=======================================================================
//  HAVOK LIBS
//=======================================================================

#endif