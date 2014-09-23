#pragma once
#include <bgfx.h>
#include "StringId.h"

#define MAX_COLOR_GRADING_NUM               (6)

struct Texture;
struct Raw3DTexture;
struct ShaderProgram;

ENGINE_NATIVE_ALIGN struct ShadingEnviroment
{
    DECLARE_RESOURCE(shading_enviroment);

    void update(float dt);
    void submit();
    void lookup();

    bgfx::TextureHandle get_colorgrading_tex() const;

    float                               m_ambientSkyColor[3];
    float                               m_ambientGroundColor[3];
    float                               m_fogParams[4];
    
    // x -->  exposure
    // y -->  bloomThreshold
    // z -->  bloomWidth
    // w -->  bloomIntensity
    float                               m_bloomParams[4];


    // x --> focusDistance
    // y --> focusRange
    // z -->  dof blur width
    // w,w --> focusFalloff
    float                               m_dofParams[4];

        
    // xy -->  blur direction
    // z -->  defocus
    // w --> film gain noise
    float                               m_ppParams[4];

    float                               m_shadowAreaSize;
    float                               m_shadowFar;
    float                               m_shadowParams[3];
    
    uint32_t                            m_numColorgradingTextures;
    int                                 m_colorGradingIndex;
    Raw3DTexture*                       m_colorGradingTextures[MAX_COLOR_GRADING_NUM];
    StringId                            m_colorgradingTextureNames[MAX_COLOR_GRADING_NUM];
};

void  lookup_resource_shading_enviroment(void* resource);