
#include "common.sc"

#ifdef ALPHA_MASK
SAMPLER2D(u_texColor, TEX_COLOR_SLOT);
#endif

void main()
{
#ifdef ALPHA_MASK
    vec4 diffuseMap = texture2D(u_texColor, v_texcoord0);
    clip(diffuseMap.a < ALPHA_THRESHOLD ? -1:1);
#endif
    gl_FragColor = vec4_splat(0.0);
}
