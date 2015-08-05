#pragma once
#include "Prerequisites.h"
#include <bx/fpumath.h>
#include <bounds.h>

#define MAX_FLOAT (3.402823466e+38F)

inline bool isPower2(unsigned int v) { return (v & (v - 1)) == 0; }

double fast_atof (const char *p);

#ifdef HAVOK_COMPILE
inline void transform_matrix(float* m, const hkQsTransform& t)
{
    t.get4x4ColumnMajor(m);
}
inline void transform_matrix(hkQsTransform& t, const float* m)
{
    t.set4x4ColumnMajor(m);
}
inline void transform_matrix(float* m, const hkTransform& t)
{
    t.get4x4ColumnMajor(m);
}
inline void transform_matrix(hkTransform& t, const float* m)
{
    t.set4x4ColumnMajor(m);
}
inline void transform_matrix(float* m, const hkMatrix4f& m4)
{
    m4.get4x4ColumnMajor(m);
}
inline void transform_matrix(hkMatrix4f& m4, const float* m)
{
    m4.set4x4ColumnMajor(m);
}
inline void transform_vec3(hkVector4& vec4, const float* vec3)
{
    vec4.set(vec3[0], vec3[1], vec3[2], 0);
}
inline void transform_vec3(float* vec3, const hkVector4& vec4)
{
    vec3[0] = vec4.getSimdAt(0);
    vec3[1] = vec4.getSimdAt(1);
    vec3[2] = vec4.getSimdAt(2);
}
inline void transform_qua(hkQuaternion& qua, const float* vec4)
{
    qua.set(vec4[0], vec4[1], vec4[2], vec4[3]);
}
inline void pointOnSphere(float* p, const float* pos, float radius, float theta, float phi)
{
    theta = bx::toRad(theta);
    phi = bx::toRad(phi);
    p[0] = pos[0] + radius * sinf(theta) * sinf(phi);
    p[1] = pos[1] + radius * cosf(phi);
    p[2] = pos[2] + radius * cosf(theta) * sinf(phi);
}

inline void translateOfMtx(float* p, const float* mtx)
{
  p[0] = mtx[12]; p[1] = mtx[13]; p[2] = mtx[14];
}

inline void transform_vec4(hkVector4& outVec4, const float* inVec4)
{
    outVec4.set(inVec4[0], inVec4[1], inVec4[2], inVec4[3]);
}
inline void transform_vec4(float* outVec4, const hkVector4& inVec4)
{
    outVec4[0] = inVec4.getSimdAt(0);
    outVec4[1] = inVec4.getSimdAt(1);
    outVec4[2] = inVec4.getSimdAt(2);
    outVec4[3] = inVec4.getSimdAt(3);
}

inline float get_up_axis_angle(const hkQuaternion &r)
{
#if 0
    hkVector4 dir;
    hkVector4 fwd;
    fwd.set(0, 0, 1, 0);
    dir.setRotatedDir(r, fwd);
    return hkMath::atan2(dir.getSimdAt(1), dir.getSimdAt(0));
#else
    hkVector4 up;
    up.set(0, 1, 0, 0);
    hkQuaternion rstOut;
    hkSimdFloat32 angle_out = 0;
    r.decomposeRestAxis(up, rstOut, angle_out);
    return angle_out.getReal();
#endif
}

#endif

struct Vec3
{
    float m_vec[3];
};

struct Vec4
{
    float m_vec[4];
};

struct Matrix
{
    float m_x[16];
};

struct Plane
{
    float m_data[4];
};

float neareast_to_aabb( const float* pos, const float* min, const float* max );
bool ray_aabb_intersection( const float* rayOrig, const float* rayDir, const float* min, const float* max );
bool ray_triangle_intersection( float* intsPoint, const float* rayOrig, const float* rayDir, const float* vert0, const float* vert1, const float* vert2);

inline void build_plane(float* plane, const float a, const float b, const float c, const float d)
{
    float normal[3];
    normal[0] = a;
    normal[1] = b;
    normal[2] = c;
    float invLen = 1.0f / bx::vec3Length(normal);
    bx::vec3Mul(plane, normal, invLen);
    plane[3] = d * invLen;
}

inline float plane_dist_to_point(const float* __restrict plane, const float* __restrict point)
{
    return bx::vec3Dot(plane, point) + plane[3];
}

inline void vec3_make(float* __restrict _result, const float a, const float b, const float c)
{
    _result[0] = a;
    _result[1] = b;
    _result[2] = c;
}

inline void vec3_min(float* __restrict _result, const float* __restrict _a, const float* __restrict _b)
{
    _result[0] = bx::fmin(_a[0], _b[0]);
    _result[1] = bx::fmin(_a[1], _b[1]);
    _result[2] = bx::fmin(_a[2], _b[2]);
}

inline void vec3_max(float* __restrict _result, const float* __restrict _a, const float* __restrict _b)
{
    _result[0] = bx::fmax(_a[0], _b[0]);
    _result[1] = bx::fmax(_a[1], _b[1]);
    _result[2] = bx::fmax(_a[2], _b[2]);
}

inline void transform_aabb(float* outMin, float* outMax, const float* mtx, const float* min, const float* max)
{
    // Efficient algorithm for transforming an AABB, taken from Graphics Gems
    for( uint32_t i = 0; i < 3; ++i )
    {
        outMin[i] = mtx[12 + i];
        outMax[i] = mtx[12 + i];

        for( uint32_t j = 0; j < 3; ++j )
        {
            float x = min[j] * mtx[j*4 + i];
            float y = max[j] * mtx[j*4 + i];
            outMin[i] += bx::fmin( x, y );
            outMax[i] += bx::fmax( x, y );
        }
    }
}

struct Frustum
{
    void build_view_frustum( const float* mtx, float fov, float aspect, float nearPlane, float farPlane );
    void build_view_frustum( const float* mtx, float left, float right, float bottom, float top, float nearPlane, float farPlane );
    void build_view_frustum( const float* viewmtx, const float* projmtx );
    void build_box_frustum( const float* mtx, float left, float right, float bottom, float top, float front, float back );
    bool cull_sphere( const float* pos, float radius ) const;
    bool cull_box( const float* min, const float* max ) const;
    bool cull_frustum( const Frustum &frust ) const;
    void calc_aabb( float* min, float* max ) const;

    Plane   m_planes[6];
    Vec3    m_corners[8];
    float   m_origin[3];
};



inline float low_pass_filter(float unfilteredInput, float lastFramesFilteredInput, float rc, float dt)
{
    float a = dt / (rc + dt);
    return (1 - a) * lastFramesFilteredInput + a * unfilteredInput;
};

inline float aabb_get_height(const Aabb& aabb)
{
    float extent[3];
    bx::vec3Sub(extent, aabb.m_max, aabb.m_min);
    return extent[1];
}


