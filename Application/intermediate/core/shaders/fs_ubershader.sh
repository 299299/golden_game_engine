#include "common.sh"

//#define DIFFUSE_MAPPING
//#define NORMAL_MAPPING
//#define SPECULAR_MAPPING 
//#define LIGHTMAP_MAPING

//uniforms
uniform vec4 u_matParams1;
uniform vec3 u_ambientSkyColor;
uniform vec3 u_ambientGroundColor;
uniform vec4 u_diffuseColor;
uniform vec4 u_specularColor;

uniform vec3 u_lightColor[BGFX_CONFIG_MAX_LIGHTS];
uniform vec3 u_lightVec[BGFX_CONFIG_MAX_LIGHTS];
uniform vec4 u_lightInfo[BGFX_CONFIG_MAX_LIGHTS];
uniform int  u_lightType[BGFX_CONFIG_MAX_LIGHTS];

#ifdef DIFFUSE_MAPPING
SAMPLER2D(u_texColor, TEX_COLOR_SLOT);
#endif

#ifdef NORMAL_MAPPING
SAMPLER2D(u_texNormal, TEX_NORMAL_SLOT);
#endif

#ifdef SPECULAR_MAPPING
SAMPLER2D(u_texSpecular, TEX_SPECULAR_SLOT);
#endif

#ifdef LIGHTMAP_MAPING
SAMPLER2D(u_texLightmap, TEX_LIGHTMAP_SLOT);
#endif

#ifdef SHADOW
SAMPLER2DSHADOW(u_shadowMap, TEX_SHADOWMAP_SLOT);
uniform vec3  u_shadowParams;
#endif


void main()
{
    gl_FragColor = vec4(1,0,0,1);   
}
