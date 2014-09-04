$input v_texcoord0
//[def=intermediate/core/shaders/postprocess.def]
#include "postprocess.sc"

SAMPLER2D(u_texColor, TEX_COLOR_SLOT);
SAMPLER2D(u_texNormal, TEX_NORMAL_SLOT);
SAMPLER2D(u_texSpecular, TEX_SPECULAR_SLOT);
SAMPLER2D(u_texRelfection, TEX_REFLECTION_SLOT);
SAMPLER2D(u_texEmissive, TEX_EMISSIVE_SLOT);
SAMPLER2D(u_texLightmap, TEX_LIGHTMAP_SLOT);
SAMPLER2D(u_texBlendNormalMask, TEX_BLENDNORMAL_SLOT);
#ifdef COLOR_CORRECTION
SAMPLER3D(u_texIBL, TEX_IBL_SLOT); //--->color grading.
#endif

float4 PyramidFilter(sampler2D tex, float2 texcoord, float2 width) {
    float4 color = texture2D(tex, texcoord + float2(0.5, 0.5) * width);
    color += texture2D(tex, texcoord + float2(-0.5,  0.5) * width);
    color += texture2D(tex, texcoord + float2( 0.5, -0.5) * width);
    color += texture2D(tex, texcoord + float2(-0.5, -0.5) * width);
    return 0.25 * color;
}

float3 FilmicTonemap(float3 x) {
    float A = 0.15;
    float B = 0.50;
    float C = 0.10;
    float D = 0.20;
    float E = 0.02;
    float F = 0.30;
    float W = 11.2;
    return ((x*(A*x+C*B)+D*E) / (x*(A*x+B)+D*F))- E / F;
}

float3 DoToneMap(float3 color) {
    color = 2.0f * FilmicTonemap(u_bloomParams.x * color);
    float3 whiteScale = 1.0f / FilmicTonemap(11.2);
    color *= whiteScale;
    return color;
}

void main()
{
    float w[] = {64.0, 32.0, 16.0, 8.0, 4.0, 2.0, 1.0};

    sampler2D srcTex[N_PASSES] = 
    {
        u_texNormal, 
        u_texSpecular,
        u_texRelfection,
        u_texEmissive,
        u_texLightmap,
        u_texBlendNormalMask
    };

    float bloomIntensity = u_bloomParams.w;
    float defocus = u_ppParams.z;

    float4 color = PyramidFilter(u_texColor, v_texcoord0, u_viewTexel * defocus);
    [unroll]
    for (int i = 0; i < N_PASSES; i++) {
        float4 sample = texture2D(srcTex[i], v_texcoord0);
        color.rgb += bloomIntensity * w[i] * sample.rgb / 127.0;
        color.a += sample.a / N_PASSES;
    }

    color.rgb = DoToneMap(color.rgb);

    //-->set back to gamma space.
    color.rgb = toGamma(color.rgb);

#ifdef COLOR_CORRECTION
    //-->do color correction
    color.rgb = ColorCorrection(color.rgb, u_texIBL);
#endif

    gl_FragColor = color;

}
