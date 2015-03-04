$input a_position, a_normal, a_tangent, a_texcoord0, a_blendWeights, a_blendIndices
$output v_wpos,  v_normal, v_tangent, v_texcoord0, v_view, v_shadowcoord, v_binormal
//[def=intermediate/core/shaders/ubershader.def]
#define SKINNING
#include "vs_ubershader.sh"



