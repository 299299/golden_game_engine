#pragma once
#include "BaseTypes.h"
#include <bx/os.h>
#ifdef HAVOK_COMPILE
////////////////////// HAVOK HEADERS /////////////////////////////////////////
#include <Common/Base/hkBase.h>
#include <Common/Base/Math/hkMath.h>
#else
#include <time.h>

struct hkQsTransform
{};
struct hkVector4
{};
struct hkCriticalSection
{};
struct hkCriticalSectionLock
{
    hkCriticalSectionLock(hkCriticalSection* ){};
};
typedef uint64_t hkUint64;



inline unsigned long GetTickCount()
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}



#endif