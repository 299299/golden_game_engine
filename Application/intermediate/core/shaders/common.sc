

#define BGFX_CONFIG_MAX_BONES   128
#include "bgfx_shader.sc"
#include "shaderlib.sc"

#define TEX_COLOR_SLOT          0
#define TEX_NORMAL_SLOT         1
#define TEX_SPECULAR_SLOT       2
#define TEX_REFLECTION_SLOT     3
#define TEX_EMISSIVE_SLOT       4
#define TEX_LIGHTMAP_SLOT       5
#define TEX_BLENDNORMAL_SLOT    6
#define TEX_IBL_SLOT            7
#define TEX_SHADOWMAP_SLOT      8
#define TEX_REFLECTIONMASK_SLOT 9
#define TEX_ANISOTROPICDIR_SLOT 10
#define TEX_THICKNESS_SLOT      11

#define TEX_MAX_SLOT            16

#define BGFX_CONFIG_MAX_LIGHTS  4
#define SHADOWMAP_SIZE          1024
#define HDR

#define MAX_UNIFORM_NUM         1024
#define MAX_FRAMEBUFFER_NUM     32

#define N_PASSES                6
#define N_SAMPLES               13

#define COLOR_LUT_SIZE          16

//#define FILM_GAIN
#define COLOR_CORRECTION


#define ALPHA_THRESHOLD 0.1f

uniform float   u_time;
uniform vec3    u_camPos;
uniform vec2    u_camDist;
uniform vec4    u_uvOffsetAndRepeat;
uniform vec4    u_fogParams;

float LinearizeDepth(float depth)
{
    // unoptimal
    return -u_camDist.y * u_camDist.x / (depth * (u_camDist.y - u_camDist.x) - u_camDist.y);
}

float GetFogFactor(float depth)
{
    return clamp((u_fogParams.x - depth) * u_fogParams.y, 0.0, 1.0);
}

float GetHeightFogFactor(float depth, float height)
{
    float fogFactor = GetFogFactor(depth);
    float heightFogFactor = (height - u_fogParams.w);
    heightFogFactor = 1.0 - clamp(exp(-(heightFogFactor * heightFogFactor)), 0.0, 1.0);
    return u_fogParams.z * min(heightFogFactor, fogFactor);
}