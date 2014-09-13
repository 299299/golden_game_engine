#include "ShadingEnviromentCompiler.h"
#include "DC_Utils.h"
#include "Texture.h"

ShadingEnviromentCompiler::ShadingEnviromentCompiler()
{

}

ShadingEnviromentCompiler::~ShadingEnviromentCompiler()
{
    
}

bool ShadingEnviromentCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    ShadingEnviroment shading;
    memset(&shading, 0x00, sizeof(shading));

    //init shading variables
    float fogParams[] = {10, 40, 0, 0};
    memcpy(shading.m_fogParams, fogParams, sizeof(fogParams));
    float bloomParams[] = {2.0f, 0.63f, 1.0f, 1.0f};
    memcpy(shading.m_bloomParams, bloomParams, sizeof(bloomParams));
    float dofParams[] = {1.0f, 2.0f, 2.5f, 10.0f};
    memcpy(shading.m_dofParams, dofParams, sizeof(dofParams));
    vec3Make(shading.m_ambientSkyColor, 0.37f, 0.55f, 0.66f);
    shading.m_ppParams[2] = 0.2f;
    shading.m_ppParams[3] = 0.25f;
    shading.m_shadowAreaSize = 30.0f;
    shading.m_shadowFar = 100;
    vec3Make(shading.m_shadowParams, 0.01f, 0.001f, 0.0f);

    JsonValue fogValue = root.GetValue("fog");
    if(fogValue.IsValid())
    {
        shading.m_fogParams[0] = JSON_GetFloat(fogValue.GetValue("near"), 10.0f);
        shading.m_fogParams[1] = JSON_GetFloat(fogValue.GetValue("far"), 40.0f);
        shading.m_fogParams[2] = JSON_GetFloat(fogValue.GetValue("density"), 0.0f);
        shading.m_fogParams[3] = JSON_GetFloat(fogValue.GetValue("density"), 0.0f);
    }

    JsonValue bloomValue = root.GetValue("bloom");
    if(bloomValue.IsValid())
    {
        shading.m_bloomParams[0] = JSON_GetFloat(bloomValue.GetValue("expose"), 2.0f);
        shading.m_bloomParams[1] = JSON_GetFloat(bloomValue.GetValue("bloomThreshold"), 0.63f);
        shading.m_bloomParams[2] = JSON_GetFloat(bloomValue.GetValue("bloomWidth"), 1.0f);
        shading.m_bloomParams[3] = JSON_GetFloat(bloomValue.GetValue("bloomIntensity"), 1.0f);
    }

    JsonValue dofValue = root.GetValue("dof");
    if(dofValue.IsValid())
    {
        shading.m_dofParams[0] = JSON_GetFloat(dofValue.GetValue("focusDistance"), 1.0f);
        shading.m_dofParams[1] = JSON_GetFloat(dofValue.GetValue("focusRange"), 2.0f);
        shading.m_dofParams[2] = JSON_GetFloat(dofValue.GetValue("dof_blur_width"), 2.5f);
        shading.m_dofParams[3] = JSON_GetFloat(dofValue.GetValue("focusFalloff"), 10.0f);
    }

    JSON_GetFloats(root.GetValue("ambient_sky_color"), shading.m_ambientSkyColor, 3);
    JSON_GetFloats(root.GetValue("ambient_ground_color"), shading.m_ambientGroundColor, 3);

    JsonValue shadowValue = root.GetValue("shadow");
    if(shadowValue.IsValid())
    {
        shading.m_shadowAreaSize = JSON_GetFloat(shadowValue.GetValue("area"), 1.0f);
        shading.m_shadowFar = JSON_GetFloat(shadowValue.GetValue("far"), 1.0f);
        shading.m_shadowParams[0] = JSON_GetFloat(shadowValue.GetValue("offset"), 1.0f);
        shading.m_shadowParams[1] = JSON_GetFloat(shadowValue.GetValue("bias"), 1.0f);
    }

    shading.m_ppParams[2] = JSON_GetFloat(root.GetValue("defocus"), 0.2f);
    shading.m_ppParams[3] = JSON_GetFloat(root.GetValue("film_gain_noise"), 0.25f);

    JsonValue colorGradingValue = root.GetValue("color_grading");
    if(colorGradingValue.IsValid())
    {
        JsonValue texturesValue = colorGradingValue.GetValue("textures");
        shading.m_numColorgradingTextures = texturesValue.GetElementsCount();
        for (uint32_t i=0; i<shading.m_numColorgradingTextures; ++i)
        {
            std::string lutTexture = JSON_GetString(texturesValue[i]);
            shading.m_colorgradingTextureNames[i] = StringId(lutTexture.c_str());
            addDependency("color_grading_texture", name_to_file_path(lutTexture.c_str(), Raw3DTexture::getName()));
        }
        shading.m_colorGradingIndex = JSON_GetInt(colorGradingValue.GetValue("grading_index"));
    }

    if(!write_file(m_output, &shading, sizeof(shading)))
        return false;

#if COMPILER_LOAD_TEST
    char* buf = 0;
    uint32_t size = read_file(m_output, &buf);
    ShadingEnviroment* shading2 = (ShadingEnviroment*)buf;
    HK_ASSERT(0, shading2->m_skyShaderName == shading.m_skyShaderName);
    HK_ASSERT(0, shading2->m_numColorgradingTextures == shading.m_numColorgradingTextures);
    free(buf);
#endif
    return true;
}