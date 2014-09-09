#include "MathDefs.h"
#include <cmath>
#include <stdio.h>

//
// Simple and fast atof (ascii to float) function.
//
// - Executes about 5x faster than standard MSCRT library atof().
// - An attractive alternative if the number of calls is in the millions.
// - Assumes input is a proper integer, fraction, or scientific format.
// - Matches library atof() to 15 digits (except at extreme exponents).
// - Follows atof() precedent of essentially no error checking.
//
// 09-May-2009 Tom Van Baak (tvb) www.LeapSecond.com
//

#define white_space(c) ((c) == ' ' || (c) == '\t')
#define valid_digit(c) ((c) >= '0' && (c) <= '9')

double fast_atof (const char *p)
{
    int frac;
    double sign, value, scale;

    // Skip leading white space, if any.

    while (white_space(*p) ) {
        p += 1;
    }

    // Get sign, if any.

    sign = 1.0;
    if (*p == '-') {
        sign = -1.0;
        p += 1;

    } else if (*p == '+') {
        p += 1;
    }

    // Get digits before decimal point or exponent, if any.

    for (value = 0.0; valid_digit(*p); p += 1) {
        value = value * 10.0 + (*p - '0');
    }

    // Get digits after decimal point, if any.

    if (*p == '.') {
        double pow10 = 10.0;
        p += 1;
        while (valid_digit(*p)) {
            value += (*p - '0') / pow10;
            pow10 *= 10.0;
            p += 1;
        }
    }

    // Handle exponent, if any.

    frac = 0;
    scale = 1.0;
    if ((*p == 'e') || (*p == 'E')) {
        unsigned int expon;

        // Get sign of exponent, if any.

        p += 1;
        if (*p == '-') {
            frac = 1;
            p += 1;

        } else if (*p == '+') {
            p += 1;
        }

        // Get digits of exponent, if any.

        for (expon = 0; valid_digit(*p); p += 1) {
            expon = expon * 10 + (*p - '0');
        }
        if (expon > 308) expon = 308;

        // Calculate scaling factor.

        while (expon >= 50) { scale *= 1E50; expon -= 50; }
        while (expon >=  8) { scale *= 1E8;  expon -=  8; }
        while (expon >   0) { scale *= 10.0; expon -=  1; }
    }

    // Return signed and scaled floating point result.

    return sign * (frac ? (value / scale) : (value * scale));
}

float nearestDistToAABB( const float* pos, const float* min, const float* max )
{
    float center[3];
    float extent[3];
    float nearestVec[3];

    center[0] = (min[0] + max[0]) * 0.5f;
    center[1] = (min[1] + max[1]) * 0.5f;
    center[2] = (min[2] + max[2]) * 0.5f;

    extent[0] = (max[0] - min[0]) * 0.5f;
    extent[1] = (max[1] - min[1]) * 0.5f;
    extent[2] = (max[2] - min[2]) * 0.5f;
    
    nearestVec[0] = bx::fmax( 0, fabsf( pos[0] - center[0] ) - extent[0] );
    nearestVec[1] = bx::fmax( 0, fabsf( pos[1] - center[1] ) - extent[1] );
    nearestVec[2] = bx::fmax( 0, fabsf( pos[2] - center[2] ) - extent[2] );
    
    return bx::vec3Length(nearestVec);
}

bool rayAABBIntersection( const float* rayOrig, const float* rayDir, 
                                 const float* min, const float* max )
{
    // SLAB based optimized ray/AABB intersection routine
    // Idea taken from http://ompf.org/ray/
    float l1 = (min[0] - rayOrig[0]) / rayDir[0];
    float l2 = (max[0] - rayOrig[0]) / rayDir[0];
    float lmin = bx::fmin( l1, l2 );
    float lmax = bx::fmax( l1, l2 );

    l1 = (min[1] - rayOrig[1]) / rayDir[1];
    l2 = (max[1] - rayOrig[1]) / rayDir[1];
    lmin = bx::fmax( bx::fmin( l1, l2 ), lmin );
    lmax = bx::fmin( bx::fmax( l1, l2 ), lmax );
        
    l1 = (min[2] - rayOrig[2]) / rayDir[2];
    l2 = (max[2] - rayOrig[2]) / rayDir[2];
    lmin = bx::fmax( bx::fmin( l1, l2 ), lmin );
    lmax = bx::fmin( bx::fmax( l1, l2 ), lmax );

    if( (lmax >= 0.0f) & (lmax >= lmin) )
    {
        // Consider length
        float rayDest[3];
        float rayMin[3];
        float rayMax[3];

        bx::vec3Add(rayDest, rayOrig, rayDir);
        rayMin[0] = bx::fmin( rayDest[0], rayOrig[0]);
        rayMin[1] = bx::fmin( rayDest[1], rayOrig[1]);
        rayMin[2] = bx::fmin( rayDest[2], rayOrig[2]);

        rayMax[0] = bx::fmax( rayDest[0], rayOrig[0]);
        rayMax[1] = bx::fmax( rayDest[1], rayOrig[1]);
        rayMax[2] = bx::fmax( rayDest[2], rayOrig[2]);

        return 
            (rayMin[0] < max[0]) && (rayMax[0] > min[0]) &&
            (rayMin[1] < max[1]) && (rayMax[1] > min[1]) &&
            (rayMin[2] < max[2]) && (rayMax[2] > min[2]);
    }
    else
        return false;
}

bool rayTriangleIntersection( float* intsPoint, const float* rayOrig, const float* rayDir, 
                              const float* vert0, const float* vert1, const float* vert2)
{
    // Idea: Tomas Moeller and Ben Trumbore
    // in Fast, Minimum Storage Ray/Triangle Intersection 
    
    // Find vectors for two edges sharing vert0
    float edge1[3];
    float edge2[3];
    bx::vec3Sub(edge1, vert1, vert0);
    bx::vec3Sub(edge2, vert2, vert0);

    // Begin calculating determinant - also used to calculate U parameter
    float pvec[3];
    bx::vec3Cross(pvec, rayDir, edge2);

    // If determinant is near zero, ray lies in plane of triangle
    float det = bx::vec3Dot(edge1, pvec);

    // *** Non-culling branch ***
    if( det > -0.000001f && det < 0.000001f ) return 0;
    float inv_det = 1.0f / det;

    // Calculate distance from vert0 to ray origin
    float tvec[3];
    bx::vec3Sub(tvec, rayOrig, vert0);

    // Calculate U parameter and test bounds
    float u = bx::vec3Dot(tvec, pvec) * inv_det;
    if( u < 0.0f || u > 1.0f ) return 0;

    // Prepare to test V parameter
    float qvec[3];
    bx::vec3Cross(qvec, tvec, edge1);

    // Calculate V parameter and test bounds
    float v = bx::vec3Dot(rayDir, qvec) * inv_det;
    if( v < 0.0f || u + v > 1.0f ) return 0;

    // Calculate t, ray intersects triangle
    float t = bx::vec3Dot(edge2, qvec) * inv_det;


    // Calculate intersection point and test ray length and direction
    float mulDir[3];
    bx::vec3Mul(mulDir, rayDir, t);
    bx::vec3Sub(intsPoint, rayOrig, mulDir);

    float vec[3];
    bx::vec3Sub(vec, intsPoint, rayOrig);
    if( bx::vec3Dot(vec, rayDir) < 0 || 
        bx::vec3Length(vec) > bx::vec3Length(rayDir) ) 
        return false;
    return true;
}

void Frustum::buildViewFrustum( const float* mtx, float left, float right, float bottom, float top, float nearPlane, float farPlane )
{
    // Use intercept theorem to get params for far plane
    float left_f = left * farPlane / nearPlane;
    float right_f = right * farPlane / nearPlane;
    float bottom_f = bottom * farPlane / nearPlane;
    float top_f = top * farPlane / nearPlane;

    // Get points on near plane
    vec3Make(m_corners[0].m_vec, left, bottom, -nearPlane);
    vec3Make(m_corners[1].m_vec, right, bottom, -nearPlane);
    vec3Make(m_corners[2].m_vec, right, top, -nearPlane);
    vec3Make(m_corners[3].m_vec, left, top, -nearPlane);

    // Get points on far plane
    vec3Make(m_corners[4].m_vec, left_f, bottom_f, -farPlane);
    vec3Make(m_corners[5].m_vec, right_f, bottom_f, -farPlane);
    vec3Make(m_corners[6].m_vec, right_f, top_f, -farPlane);
    vec3Make(m_corners[7].m_vec, left_f, top_f, -farPlane);

    // Transform points to fit camera position and rotation
    vec3Make(m_origin, mtx[12], mtx[13], mtx[14]);
    for( uint32_t i = 0; i < 8; ++i )
    {
        float corner[3] = {m_corners[i].m_vec[0], m_corners[i].m_vec[1], m_corners[i].m_vec[2]};
        bx::vec3MulMtx(m_corners[i].m_vec, mtx, corner);
    }

    // Build planes
    bx::calcPlane(m_planes[0].m_data, m_origin, m_corners[3].m_vec, m_corners[0].m_vec); // Left
    bx::calcPlane(m_planes[1].m_data, m_origin, m_corners[1].m_vec, m_corners[2].m_vec); // Right
    bx::calcPlane(m_planes[2].m_data, m_origin, m_corners[0].m_vec, m_corners[1].m_vec); // Bottom
    bx::calcPlane(m_planes[3].m_data, m_origin, m_corners[2].m_vec, m_corners[3].m_vec); // Top
    bx::calcPlane(m_planes[4].m_data, m_corners[0].m_vec, m_corners[1].m_vec, m_corners[2].m_vec); // Near
    bx::calcPlane(m_planes[5].m_data, m_corners[5].m_vec, m_corners[4].m_vec, m_corners[7].m_vec); // Far
}

void Frustum::buildViewFrustum( const float* viewmtx, const float* projmtx )
{
    // This routine works with the OpenGL projection matrix
    // The view matrix is the inverse camera transformation matrix
    // Note: Frustum corners are not updated!
    float m[16];
    bx::mtxMul(m, viewmtx, projmtx);
    buildPlane(m_planes[0].m_data, -(m[3] + m[0]), -(m[7] + m[4]), -(m[11] + m[8]), -(m[15] + m[12]));//Left
    buildPlane(m_planes[1].m_data,  -(m[3] - m[0]), -(m[7] - m[4]), -(m[11] - m[8]), -(m[15] - m[12]) );//Right
    buildPlane(m_planes[2].m_data,  -(m[3] + m[1]), -(m[7] + m[5]), -(m[11] + m[9]), -(m[15] + m[13]) );//Bottom
    buildPlane(m_planes[3].m_data, -(m[3] - m[1]), -(m[7] - m[5]), -(m[11] - m[9]), -(m[15] - m[13]) );//Top
    buildPlane(m_planes[4].m_data, -(m[3] + m[2]), -(m[7] + m[6]), -(m[11] + m[10]), -(m[15] + m[14]) );//Near
    buildPlane(m_planes[5].m_data, -(m[3] - m[2]), -(m[7] - m[6]), -(m[11] - m[10]), -(m[15] - m[14]) );//Far

    float invview[16];
    bx::mtxInverse(invview, viewmtx);
    vec3Make(m_origin, invview[12], invview[13], invview[14]);

    float mm[16];
    bx::mtxInverse(mm, m);

    float corner[4];
    float mv[4];
    // 0.
    mv[0] = -1; mv[1] = -1; mv[2] = -1; mv[3] = 1;
    bx::vec4MulMtx(corner, mv, mm);
    vec3Make(m_corners[0].m_vec, corner[0]/corner[3], corner[1]/corner[3], corner[2]/corner[3]);
    // 1.
    mv[0] = 1; mv[1] = -1; mv[2] = -1; mv[3] = 1;
    bx::vec4MulMtx(corner, mv, mm);
    vec3Make(m_corners[1].m_vec, corner[0]/corner[3], corner[1]/corner[3], corner[2]/corner[3]);
    // 2.
    mv[0] = 1; mv[1] = 1; mv[2] = -1; mv[3] = 1;
    bx::vec4MulMtx(corner, mv, mm);
    vec3Make(m_corners[2].m_vec, corner[0]/corner[3], corner[1]/corner[3], corner[2]/corner[3]);
    //3.
    mv[0] = -1; mv[1] = 1; mv[2] = -1; mv[3] = 1;
    bx::vec4MulMtx(corner, mv, mm);
    vec3Make(m_corners[3].m_vec, corner[0]/corner[3], corner[1]/corner[3], corner[2]/corner[3]);
    //4.
    mv[0] = -1; mv[1] = -1; mv[2] = 1; mv[3] = 1;
    bx::vec4MulMtx(corner, mv, mm);
    vec3Make(m_corners[4].m_vec, corner[0]/corner[3], corner[1]/corner[3], corner[2]/corner[3]);
    //5.
    mv[0] = 1; mv[1] = -1; mv[2] = 1; mv[3] = 1;
    bx::vec4MulMtx(corner, mv, mm);
    vec3Make(m_corners[5].m_vec, corner[0]/corner[3], corner[1]/corner[3], corner[2]/corner[3]);
    //6.
    mv[0] = 1; mv[1] = 1; mv[2] = 1; mv[3] = 1;
    bx::vec4MulMtx(corner, mv, mm);
    vec3Make(m_corners[6].m_vec, corner[0]/corner[3], corner[1]/corner[3], corner[2]/corner[3]);
    //7.
    mv[0] = -1; mv[1] = 1; mv[2] = 1; mv[3] = 1;
    bx::vec4MulMtx(corner, mv, mm);
    vec3Make(m_corners[7].m_vec, corner[0]/corner[3], corner[1]/corner[3], corner[2]/corner[3]);
}

void Frustum::buildBoxFrustum( const float* mtx, float left, float right, float bottom, float top, 
                          float front, float back )
{
    // Get points on front plane
    vec3Make(m_corners[0].m_vec, left, bottom, front);
    vec3Make(m_corners[1].m_vec, right, bottom, front);
    vec3Make(m_corners[2].m_vec, right, top, front);
    vec3Make(m_corners[3].m_vec, left, top, front);

    // Get points on far plane
    vec3Make(m_corners[4].m_vec, left, bottom, back);
    vec3Make(m_corners[5].m_vec, right, bottom, back);
    vec3Make(m_corners[6].m_vec, right, top, back);
    vec3Make(m_corners[7].m_vec, left, top, back);

    // Transform points to fit camera position and rotation
    vec3Make(m_origin, mtx[12], mtx[13], mtx[14]);
    for( uint32_t i = 0; i < 8; ++i )
    {
        float corner[3] = {m_corners[i].m_vec[0], m_corners[i].m_vec[1], m_corners[i].m_vec[2]};
        bx::vec3MulMtx(m_corners[i].m_vec, mtx, corner);
    }

    // Build planes
    bx::calcPlane(m_planes[0].m_data, m_corners[0].m_vec, m_corners[3].m_vec, m_corners[7].m_vec);//Left
    bx::calcPlane(m_planes[1].m_data, m_corners[2].m_vec, m_corners[1].m_vec, m_corners[6].m_vec);//Right
    bx::calcPlane(m_planes[2].m_data, m_corners[0].m_vec, m_corners[4].m_vec, m_corners[5].m_vec);//Bottom
    bx::calcPlane(m_planes[3].m_data, m_corners[3].m_vec, m_corners[2].m_vec, m_corners[6].m_vec);//Top
    bx::calcPlane(m_planes[4].m_data, m_corners[0].m_vec, m_corners[1].m_vec, m_corners[2].m_vec);//Front
    bx::calcPlane(m_planes[5].m_data, m_corners[4].m_vec, m_corners[7].m_vec, m_corners[6].m_vec);//Back
}


