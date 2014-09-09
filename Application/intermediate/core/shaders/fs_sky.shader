$input v_texcoord0
//[def=intermediate/core/shaders/sky.def]
#include "common.sc"
SAMPLER2D(u_texColor, TEX_COLOR_SLOT);

void main()
{
    gl_FragColor = toLinear(texture2D(u_texColor, v_texcoord0) );
    //gl_FragColor = vec4(1,0,0,1);
}
