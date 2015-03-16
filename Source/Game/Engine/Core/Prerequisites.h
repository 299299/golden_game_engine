#pragma once
#include "BaseTypes.h"
#include <bx/os.h>
#include <bx/string.h>


extern void error_abort(const char* file, int line, const char* message, ...);
#define ENGINE_ASSERT(condition, msg, ...) do { if (!(condition)) {\
    error_abort(__FILE__, __LINE__, "\nAssertion failed: %s\n\t" msg "\n", #condition, ##__VA_ARGS__); }} while (0)

#ifdef HAVOK_COMPILE
#include <Common/Base/hkBase.h>
#include <Common/Base/Math/hkMath.h>
#else
#include <time.h>

struct hkQsTransformf{};
typedef hkQsTransformf hkQsTransform;
struct hkTransformf{};
typedef hkTransformf hkTransform;
struct hkVector4f{};
typedef hkVector4f hkVector4;
struct hkaSampleBlendJob{};
typedef uint64_t hkUint64;
typedef float    hkReal;
typedef bool     hkBool;
typedef int16_t  hkInt16;
typedef uint32_t hkUint32;
typedef void*    HWND;
typedef int      LRESULT;
typedef uint32_t UINT;
typedef uint32_t WPARAM;
typedef uint32_t LPARAM;
struct RECT {};
#define HK_ALIGN16
inline unsigned long GetTickCount()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
#endif
