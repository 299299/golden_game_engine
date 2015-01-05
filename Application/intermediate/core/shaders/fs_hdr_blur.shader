$input v_texcoord0
//[def=intermediate/core/shaders/postprocess.def]

#include "postprocess.sc"

SAMPLER2D(u_texColor, TEX_COLOR_SLOT);

void main()
{
     #if N_SAMPLES == 13
    float offsets[] = { -1.7688, -1.1984, -0.8694, -0.6151, -0.3957, -0.1940, 0, 0.1940, 0.3957, 0.6151, 0.8694, 1.1984, 1.7688 };
    const float n = 13.0;
    #elif N_SAMPLES == 11
    float offsets[] = { -1.6906, -1.0968, -0.7479, -0.4728, -0.2299, 0, 0.2299, 0.4728, 0.7479, 1.0968, 1.6906 };
    const float n = 11.0;
    #elif N_SAMPLES == 9
    float offsets[] = { -1.5932, -0.9674, -0.5895, -0.2822, 0, 0.2822, 0.5895, 0.9674, 1.5932 };
    const float n = 9.0;
    #elif N_SAMPLES == 7
    float offsets[] = { -1.4652, -0.7916, -0.3661, 0, 0.3661, 0.7916, 1.4652 };
    const float n = 7.0;
    #else
    float offsets[] = { -1.282, -0.524, 0.0, 0.524, 1.282 };
    const float n = 5.0;
    #endif

    float bloomWidth = u_bloomParams.z;
    vec2 step = u_viewTexel * u_ppParams.xy * bloomWidth;

    float4 color = float4(0.0, 0.0, 0.0, 0.0);
    [unroll]
    for (int i = 0; i < int(n); i++)
        color += texture2D(u_texColor, v_texcoord0 + step * offsets[i]);
    
    gl_FragColor = color / n;
}
