$input a_position, a_blendWeights, a_blendIndices, a_texcoord0
$output v_texcoord0
//[def=intermediate/core/shaders/shadow.def]
#define SKINNING
#define ALPHA_MASK
#include "vs_shadow.sc"