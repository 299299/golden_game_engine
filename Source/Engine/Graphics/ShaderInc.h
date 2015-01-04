#ifndef BGFX_SHADER_INC
#define BGFX_SHADER_INC

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

#define BGFX_CONFIG_MAX_BONES   128
#define BGFX_CONFIG_MAX_LIGHTS  4
#define SHADOWMAP_SIZE          1024
//#define HDR

#define MAX_UNIFORM_NUM         1024
#define MAX_FRAMEBUFFER_NUM     32

#define N_PASSES                6
#define N_SAMPLES               13

#define COLOR_LUT_SIZE          16

//#define FILM_GAIN
#define COLOR_CORRECTION
#define GAMMA_CORRECTION

#endif