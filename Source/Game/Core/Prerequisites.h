#pragma once
#include "BaseTypes.h"
#include <bx/os.h>
#include <bx/string.h>

#ifdef HAVOK_COMPILE
#include <Common/Base/hkBase.h>
#include <Common/Base/Math/hkMath.h>
#define ENGINE_ASSERT(expr, msg) HK_ASSERT2(0, expr, msg)
#else
#include <time.h>
#include <assert.h>
#define ENGINE_ASSERT(expr, msg) assert(expr)

struct hkQsTransform{};
struct hkTransform{};
struct hkVector4{};
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


#define STR_NPRINTF(len, ...)\
        char str_buf[len];\
        bx::snprintf(str_buf, sizeof(str_buf), __VA_ARGS__);

#define ENGINE_ASSERT_ARGS(expr, ...)\
        char str_buf[64];\
        bx::snprintf(str_buf, sizeof(str_buf), __VA_ARGS__);\
        ENGINE_ASSERT(expr, str_buf);
