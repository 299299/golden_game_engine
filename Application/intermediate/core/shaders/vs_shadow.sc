
#include "common.sc"

void main()
{
#ifdef SKINNING
    vec4 pos = vec4(a_position, 1);
    vec4 wpos =  mul(u_model[a_blendIndices.x], pos) * a_blendWeights.x +
                 mul(u_model[a_blendIndices.y], pos) * a_blendWeights.y +
                 mul(u_model[a_blendIndices.z], pos) * a_blendWeights.z +
                 mul(u_model[a_blendIndices.w], pos) * a_blendWeights.w;
    wpos.w = 1;
    gl_Position = mul(u_viewProj, wpos);
#else
    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
#endif

#ifdef ALPHA_MASK
    v_texcoord0 = a_texcoord0;
#endif
}
