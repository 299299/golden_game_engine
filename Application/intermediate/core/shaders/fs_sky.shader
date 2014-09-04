$input v_wpos
//[def=intermediate/core/shaders/sky.def]
#include "common.sc"

uniform vec3 u_ambientSkyColor;
uniform vec3 u_ambientGroundColor;

void main()
{
    float blend = (v_wpos.y * 0.5) + 0.5;
    vec3 color = mix(u_ambientGroundColor, u_ambientSkyColor, blend);
    gl_FragColor = vec4(color, 1);
}
