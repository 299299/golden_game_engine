#include "common.sc"

#define SHADER_DEBUG

// x -->  exposure
// y -->  bloomThreshold
// z -->  bloomWidth
// w -->  bloomIntensity
uniform vec4 u_bloomParams;

// x --> focusDistance
// y --> focusRange
// z -->  dof blur width
// w,w --> focusFalloff
uniform vec4 u_dofParams;

// xy -->  blur direction
// z -->  defocus
// w --> film gain noise
uniform vec4 u_ppParams;


vec3 ColorCorrection(vec3 color, sampler3D lut)
{
    float lutSize = COLOR_LUT_SIZE;
    float scale = (lutSize - 1.0) / lutSize;
    float offset = 1.0 / (2.0 * lutSize);
    return texture3D(lut, clamp(color, 0.0, 1.0) * scale + offset).rgb;
}

float3 Overlay(float3 a, float3 b){
    return pow(abs(b), 2.2) < 0.5? 2 * a * b : 1.0 - 2 * (1.0 - a) * (1.0 - b);
}