$input a_position
$output v_wpos
//[def=intermediate/core/shaders/sky.def]
#include "common.sc"


void main()
{
    vec4 pos = vec4(a_position, 1);
    v_wpos = mul(u_model[0], vec4(a_position, 1.0) ).xyz;
    gl_Position = mul(u_viewProj, vec4(v_wpos, 1.0) );
}
