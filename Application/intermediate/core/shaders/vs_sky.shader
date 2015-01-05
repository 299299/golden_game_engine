$input a_position, a_texcoord0
$output v_texcoord0
//[def=intermediate/core/shaders/sky.def]
#include "common.sc"

void main()
{
    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
    v_texcoord0 = a_texcoord0;
    v_texcoord0.y *= -1;
}
