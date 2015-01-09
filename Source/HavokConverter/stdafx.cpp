#include "Prerequisites.h"

//=======================================================================
//  HAVOK LIBS
//=======================================================================
#define HK_EXCLUDE_FEATURE_MemoryTracker
#if 1
#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
#define HK_EXCLUDE_FEATURE_RegisterVersionPatches
#endif
#define HK_EXCLUDE_LIBRARY_hkGeometryUtilities

// Register Havok classes.
#include <Common/Base/KeyCode.h>
#define HK_FEATURE_REFLECTION_COMMON_VISUALIZE
#define HK_CLASSES_FILE <Common/Serialize/Classlist/hkKeyCodeClasses.h>
#include <Common/Base/Config/hkProductFeatures.cxx>
#include <Common/Base/keycode.cxx>

//start of havok link config
#ifdef _DEBUG
#define HAVOK_LIB_PATH "C:\\Project\\hk2014_1_0_r1\\Lib\\win32_vs2010\\debug\\"
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

//=======================================================================
//  HAVOK LIBS
//=======================================================================




