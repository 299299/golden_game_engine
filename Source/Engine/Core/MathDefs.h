#pragma once
#include "Prerequisites.h"
#include <bx/fpumath.h>

#define MAX_FLOAT (3.402823466e+38F)

/// Update a hash with the given 8-bit value using the SDBM algorithm.
inline unsigned SDBMHash(unsigned hash, unsigned char c) 
{ 
    return c + (hash << 6) + (hash << 16) - hash; 
}

inline bool isPower2(unsigned int v) { return (v & (v - 1)) == 0; }

double fast_atof (const char *p);

inline void transform_matrix(float* m, const hkQsTransform& t)
{
    HK_ALIGN16(hkReal s_m[4][4]);
    hkReal* s_p = &(s_m[0][0]);
    t.get4x4ColumnMajor(s_p);
    memcpy(m, s_p, sizeof(hkReal)*16);
}
inline void transform_matrix(hkQsTransform& t, const float* m)
{
    HK_ALIGN16(hkReal s_m[4][4]);
    hkReal* s_p = &(s_m[0][0]);
    memcpy(s_p, m, sizeof(hkReal)*16);
    t.set4x4ColumnMajor(s_p);
}
inline void transform_matrix(float* m, const hkTransform& t)
{
    HK_ALIGN16(hkReal s_m[4][4]);
    hkReal* s_p = &(s_m[0][0]);
    t.get4x4ColumnMajor(s_p);
    memcpy(m, s_p, sizeof(hkReal)*16);
}
inline void transform_matrix(hkTransform& t, const float* m)
{
    HK_ALIGN16(hkReal s_m[4][4]);
    hkReal* s_p = &(s_m[0][0]);
    memcpy(s_p, m, sizeof(hkReal)*16);
    t.set4x4ColumnMajor(s_p);
}
inline void transform_matrix(float* m, const hkMatrix4f& m4)
{
    HK_ALIGN16(hkReal s_m[4][4]);
    hkReal* s_p = &(s_m[0][0]);
    m4.get4x4ColumnMajor(s_p);
    memcpy(m, s_p, sizeof(hkReal)*16);
}
inline void transform_matrix(hkMatrix4f& m4, const float* m)
{
    HK_ALIGN16(hkReal s_m[4][4]);
    hkReal* s_p = &(s_m[0][0]);
    memcpy(s_p, m, sizeof(hkReal)*16);
    m4.set4x4ColumnMajor(s_p);
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

struct Vec3
{
    float m_vec[3];
};

struct Vec4
{
    float m_vec[4];
};

struct Aabb
{
    float m_min[3];
    float m_max[3];
};

struct Obb
{
    float m_mtx[16];
};

struct Sphere
{
    float m_center[3];
    float m_radius;
};

struct Matrix
{
    float m_x[16];
};

struct Plane
{
    float m_data[4];
};

inline int ftoi_r( double val )
{
    // Fast round (banker's round) using Sree Kotay's method
    // This function is much faster than a naive cast from float to int

    union
    {
        double dval;
        int ival[2];
    } u;

    u.dval = val + 6755399441055744.0;  // Magic number: 2^52 * 1.5;
    return u.ival[0];         // Needs to be [1] for big-endian
}

float nearestDistToAABB( const float* pos, const float* min, const float* max );
bool rayAABBIntersection( const float* rayOrig, const float* rayDir, const float* min, const float* max );
bool rayTriangleIntersection( float* intsPoint, const float* rayOrig, const float* rayDir, 
                              const float* vert0, const float* vert1, const float* vert2);

inline void buildPlane(float* plane, const float a, const float b, 
                       const float c, const float d)
{
    float normal[3];
    normal[0] = a;
    normal[1] = b;
    normal[2] = c;
    float invLen = 1.0f / bx::vec3Length(normal);
    bx::vec3Mul(plane, normal, invLen);
    plane[3] = d * invLen;
}

inline float planeDistToPoint(const float* __restrict plane, const float* __restrict point)
{
    return bx::vec3Dot(plane, point) + plane[3];
}

inline void vec3Make(float* __restrict _result, const float a, const float b, const float c)
{
    _result[0] = a;
    _result[1] = b;
    _result[2] = c;
}

inline void getAabbCorner(float* __restrict corner,
                          const float* __restrict min, 
                          const float* __restrict max, 
                          int index)
{
    switch( index )
    {
    case 0: vec3Make(corner, min[0], min[1], max[2]); break;
    case 1: vec3Make(corner, max[0], min[1], max[2]); break;
    case 2: vec3Make(corner, max[0], max[1], max[2]); break;
    case 3: vec3Make(corner, min[0], max[1], max[2]); break;
    case 4: vec3Make(corner, min[0], min[1], min[2]); break;
    case 5: vec3Make(corner, max[0], min[1], min[2]); break;
    case 6: vec3Make(corner, max[0], max[1], min[2]); break;
    case 7: vec3Make(corner, min[0], max[1], min[2]); break;
    default:
        break;
    }
}

inline void vec3Min(float* __restrict _result, const float* __restrict _a, const float* __restrict _b)
{
    _result[0] = bx::fmin(_a[0], _b[0]);
    _result[1] = bx::fmin(_a[1], _b[1]);
    _result[2] = bx::fmin(_a[2], _b[2]);
}

inline void vec3Max(float* __restrict _result, const float* __restrict _a, const float* __restrict _b)
{
    _result[0] = bx::fmax(_a[0], _b[0]);
    _result[1] = bx::fmax(_a[1], _b[1]);
    _result[2] = bx::fmax(_a[2], _b[2]);
}

inline void transformAabb(float* outMin, float* outMax, const float* mtx, const float* min, const float* max)
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
    void buildViewFrustum( const float* mtx, float fov,
                           float aspect, float nearPlane, float farPlane )
    {
        float ymax = nearPlane * tanf( bx::toRad( fov / 2 ) );
        float xmax = ymax * aspect;
        buildViewFrustum( mtx, -xmax, xmax, -ymax, ymax, nearPlane, farPlane );
    }

    void buildViewFrustum( const float* mtx, float left, float right, float bottom, float top, 
                           float nearPlane, float farPlane );

    void buildViewFrustum( const float* viewmtx, const float* projmtx );

    void buildBoxFrustum( const float* mtx, float left, float right, float bottom, float top, float front, float back );

    bool cullSphere( const float* pos, float radius ) const
    {
        // Check the distance of the center to the planes
        for( uint32_t i = 0; i < 6; ++i )
        {
            if(planeDistToPoint(m_planes[i].m_data, pos) > radius) 
                return true;
        }
        return false;
    }

    bool cullBox( const float* min, const float* max ) const
    {
        // Idea for optimized AABB testing from www.lighthouse3d.com
        for( uint32_t i = 0; i < 6; ++i )
        {
            const float* n = m_planes[i].m_data;
            float positive[3] = { min[0], min[1], min[2] };
            if( n[0] <= 0 ) positive[0] = max[0];
            if( n[1] <= 0 ) positive[1] = max[1];
            if( n[2] <= 0 ) positive[2] = max[2];
            if(planeDistToPoint(n, positive) > 0) 
                return true;
        }
        
        return false;
    }

    bool cullFrustum( const Frustum &frust ) const
    {
        for( uint32_t i = 0; i < 6; ++i )
        {
            bool allOut = true;
            
            for( uint32_t j = 0; j < 8; ++j )
            {
                if(planeDistToPoint(m_planes[i].m_data, frust.m_corners[j].m_vec) < 0) 
                {
                    allOut = false;
                    break;
                }
            }

            if( allOut ) return true;
        }
        return false;
    }

    void calcAABB( float* min, float* max ) const
    {
        min[0] = MAX_FLOAT; min[1] = MAX_FLOAT; min[2] = MAX_FLOAT;
        max[0] = -MAX_FLOAT; max[1] = -MAX_FLOAT; max[2] = -MAX_FLOAT;
        
        for( uint32_t i = 0; i < 8; ++i )
        {
            const Vec3& corner = m_corners[i];
            min[0] = bx::fmin(corner.m_vec[0], min[0]);
            min[1] = bx::fmin(corner.m_vec[1], min[1]);
            min[2] = bx::fmin(corner.m_vec[2], min[2]);
            max[0] = bx::fmax(corner.m_vec[0], max[0]);
            max[1] = bx::fmax(corner.m_vec[1], max[1]);
            max[2] = bx::fmax(corner.m_vec[2], max[2]);
        }
    }

    Plane   m_planes[6];
    Vec3    m_corners[8];
    float   m_origin[3];
};



inline float lowPassFilter(float unfilteredInput, float lastFramesFilteredInput, float rc, float dt)
{
    float a = dt / (rc + dt);
    return (1 - a) * lastFramesFilteredInput + a * unfilteredInput;
};