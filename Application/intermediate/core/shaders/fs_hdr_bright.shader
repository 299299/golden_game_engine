$input v_texcoord0
//[def=intermediate/core/shaders/postprocess.def]

#include "postprocess.sc"

SAMPLER2D(u_texColor, TEX_COLOR_SLOT);

void main()
{
    float2 offsets[] = { 
        float2( 0.0,  0.0), 
        float2(-1.0,  0.0), 
        float2( 1.0,  0.0), 
        float2( 0.0, -1.0),
        float2( 0.0,  1.0),
    };

    float4 color = 1e100;
    float exposure = u_bloomParams.x;
    float bloomThreshold = u_bloomParams.y;

    color = min(texture2D(u_texColor,  v_texcoord0 + offsets[0] * u_viewTexel), color);
    color = min(texture2D(u_texColor,  v_texcoord0 + offsets[1] * u_viewTexel), color);
    color = min(texture2D(u_texColor,  v_texcoord0 + offsets[2] * u_viewTexel), color);
    color = min(texture2D(u_texColor,  v_texcoord0 + offsets[3] * u_viewTexel), color);
    color = min(texture2D(u_texColor,  v_texcoord0 + offsets[4] * u_viewTexel), color);
    color.rgb *= exposure;

    gl_FragColor =  float4(max(color.rgb - bloomThreshold / (1.0 - bloomThreshold), 0.0), 1.0);
}
