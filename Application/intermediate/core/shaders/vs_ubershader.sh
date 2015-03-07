
#include "common.sh"

uniform mat4  u_lightMtx;
uniform vec3  u_shadowParams;

void main()
{
    vec4 pos = vec4(a_position, 1);
    vec4 normal = vec4(a_normal, 1);
    vec4 worldTangent = vec4_splat(0.0);

#ifdef SKINNING
    float weightw = 1.0f - a_blendWeights.x - a_blendWeights.y - a_blendWeights.z;
    v_wpos = mul(u_model[a_blendIndices.x], pos) * a_blendWeights.x +
             mul(u_model[a_blendIndices.y], pos) * a_blendWeights.y +
             mul(u_model[a_blendIndices.z], pos) * a_blendWeights.z +
             mul(u_model[a_blendIndices.w], pos) * weightw;
    v_normal =  mul(u_model[a_blendIndices.x], normal) * a_blendWeights.x +
                mul(u_model[a_blendIndices.y], normal) * a_blendWeights.y +
                mul(u_model[a_blendIndices.z], normal) * a_blendWeights.z +
                mul(u_model[a_blendIndices.w], normal) * weightw;
    worldTangent =  mul(u_model[a_blendIndices.x], a_tangent) * a_blendWeights.x +
                 mul(u_model[a_blendIndices.y], a_tangent) * a_blendWeights.y +
                 mul(u_model[a_blendIndices.z], a_tangent) * a_blendWeights.z +
                 mul(u_model[a_blendIndices.w], a_tangent) * weightw;
#else
    v_wpos = mul(u_model[0], pos);
    v_normal = mul(u_model[0], normal).xyz;
    worldTangent = mul(u_model[0], a_tangent);
#endif

    const float shadowMapOffset = u_shadowParams.x;
    vec3 posOffset = v_wpos.xyz + v_normal * shadowMapOffset;
    v_shadowcoord = mul(u_lightMtx, vec4(posOffset, 1));

    v_normal = mul(u_model[0], vec4(a_normal, 0.0) ).xyz;
    v_view = normalize(u_camPos - v_wpos.xyz);

    vec2 tex = float2(a_texcoord0.x, (1.0-a_texcoord0.y));
    tex *= u_uvOffsetAndScale.zw;
    v_texcoord0 = u_uvOffsetAndScale.xy + tex;

    v_normal = normalize(v_normal);
    v_tangent = normalize(worldTangent.xyz);
    v_binormal = cross(v_normal, v_tangent);
    v_binormal *= worldTangent.w;

#ifdef LIGHTMAP_MAPING
    v_texcoord1 = a_texcoord1;
#endif

    gl_Position = mul(u_viewProj, v_wpos);
}
