$input v_texcoord0
//[def=intermediate/core/shaders/sky.def]
#include "common.sh"
SAMPLER2D(u_texColor, TEX_COLOR_SLOT);

void main()
{
#ifdef HDR
    gl_FragColor = toLinear(texture2D(u_texColor, v_texcoord0) );
#else
    gl_FragColor = texture2D(u_texColor, v_texcoord0);
#endif
    //gl_FragColor = vec4(1,0,0,1);
}
