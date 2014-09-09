$input a_position, a_color0
$output v_color0
//[def=intermediate/core/shaders/debug.def]
#include "common.sc"

void main()
{
    gl_Position = mul(u_modelViewProj, vec4(a_position, 1.0) );
    v_color0 = a_color0;
}