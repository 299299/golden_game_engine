

#include "../../../../Source/Game/Engine/Graphics/ShaderInc.h"
#include "bgfx_shader.sh"
#include "shaderlib.sh"

#define ALPHA_THRESHOLD 0.1f

uniform float   u_time;
uniform vec3    u_camPos;
uniform vec2    u_camDist;
uniform vec4    u_uvOffsetAndScale;
uniform vec4    u_fogParams;

float LinearizeDepth(float depth)
{
    // unoptimal
    return -u_camDist.y * u_camDist.x / (depth * (u_camDist.y - u_camDist.x) - u_camDist.y);
}

float GetFogFactor(float depth)
{
    return clamp((u_fogParams.x - depth) * u_fogParams.y, 0.0, 1.0);
}

float GetHeightFogFactor(float depth, float height)
{
    float fogFactor = GetFogFactor(depth);
    float heightFogFactor = (height - u_fogParams.w);
    heightFogFactor = 1.0 - clamp(exp(-(heightFogFactor * heightFogFactor)), 0.0, 1.0);
    return u_fogParams.z * min(heightFogFactor, fogFactor);
}