#ifndef BGFX_SHADER_INC
#define BGFX_SHADER_INC

#define TEX_COLOR_SLOT          0
#define TEX_NORMAL_SLOT         1
#define TEX_SPECULAR_SLOT       2
#define TEX_EMISSIVE_SLOT       3
#define TEX_LIGHTMAP_SLOT       4
#define TEX_SHADOWMAP_SLOT      5

#define TEX_MAX_SLOT            16

#define BGFX_CONFIG_MAX_BONES   128
#define BGFX_CONFIG_MAX_LIGHTS  4
#define SHADOWMAP_SIZE          1024

#define MAX_UNIFORM_NUM         1024
#define MAX_FRAMEBUFFER_NUM     32

#define N_PASSES                6
#define N_SAMPLES               13

#define COLOR_LUT_SIZE          16


//#define HDR
//#define FILM_GAIN
#define COLOR_CORRECTION
#define GAMMA_CORRECTION

#endif