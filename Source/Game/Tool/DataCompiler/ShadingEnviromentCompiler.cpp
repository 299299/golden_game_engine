#include "ShadingEnviromentCompiler.h"
#include "Texture.h"

ShadingEnviromentCompiler::ShadingEnviromentCompiler()
{

}

ShadingEnviromentCompiler::~ShadingEnviromentCompiler()
{

}

bool ShadingEnviromentCompiler::readJSON(const jsonxx::Object& root)
{
    BaseCompiler::readJSON(root);
    ShadingEnviroment shading;
    memset(&shading, 0x00, sizeof(shading));

    //init shading variables
    float fogParams[] = {10, 40, 0, 0};
    memcpy(shading.m_fogParams, fogParams, sizeof(fogParams));
    float bloomParams[] = {2.0f, 0.63f, 1.0f, 1.0f};
    memcpy(shading.m_bloomParams, bloomParams, sizeof(bloomParams));
    float dofParams[] = {1.0f, 2.0f, 2.5f, 10.0f};
    memcpy(shading.m_dofParams, dofParams, sizeof(dofParams));
    vec3_make(shading.m_ambientSkyColor, 0.37f, 0.55f, 0.66f);
    shading.m_ppParams[2] = 0.2f;
    shading.m_ppParams[3] = 0.25f;
    shading.m_shadowAreaSize = 30.0f;
    shading.m_shadowFar = 100;
    vec3_make(shading.m_shadowParams, 0.01f, 0.001f, 0.0f);

    if(root.has<jsonxx::Object>("fog"))
    {
        const jsonxx::Object& fogValue = root.get<jsonxx::Object>("fog");
        shading.m_fogParams[0] = fogValue.get<float>("near", 10.0f);
        shading.m_fogParams[1] = fogValue.get<float>("far", 40.0f);
        shading.m_fogParams[2] = fogValue.get<float>("density", 0.0f);
        shading.m_fogParams[3] = fogValue.get<float>("density", 0.0f);
    }

    if(root.has<jsonxx::Object>("bloom"))
    {
        const jsonxx::Object& bloomValue = root.get<jsonxx::Object>("bloom");
        shading.m_bloomParams[0] = bloomValue.get<float>("expose", 2.0f);
        shading.m_bloomParams[1] = bloomValue.get<float>("bloomThreshold", 0.63f);
        shading.m_bloomParams[2] = bloomValue.get<float>("bloomWidth", 1.0f);
        shading.m_bloomParams[3] = bloomValue.get<float>("bloomIntensity", 1.0f);
    }

    if(root.has<jsonxx::Object>("dof"))
    {
        const jsonxx::Object& dofValue = root.get<jsonxx::Object>("dof");
        shading.m_dofParams[0] = dofValue.get<float>("focusDistance", 1.0f);
        shading.m_dofParams[1] = dofValue.get<float>("focusRange", 2.0f);
        shading.m_dofParams[2] = dofValue.get<float>("dof-blur-width", 2.5f);
        shading.m_dofParams[3] = dofValue.get<float>("focusFalloff", 10.0f);
    }

    json_to_floats(root.get<jsonxx::Array>("ambient-sky-color"), shading.m_ambientSkyColor, 3);
    json_to_floats(root.get<jsonxx::Array>("ambient-ground-color"), shading.m_ambientGroundColor, 3);

    if(root.has<jsonxx::Object>("shadow"))
    {
        const jsonxx::Object& shadowValue = root.get<jsonxx::Object>("shadow");
        shading.m_shadowAreaSize = shadowValue.get<float>("area", 1.0f);
        shading.m_shadowFar = shadowValue.get<float>("far", 1.0f);
        shading.m_shadowParams[0] = shadowValue.get<float>("offset", 1.0f);
        shading.m_shadowParams[1] = shadowValue.get<float>("bias", 1.0f);
    }

    shading.m_ppParams[2] = root.get<float>("defocus", 0.2f);
    shading.m_ppParams[3] = root.get<float>("film_gain_noise", 0.25f);

    if(root.has<jsonxx::Object>("color-grading"))
    {
        const jsonxx::Object& colorGradingValue = root.get<jsonxx::Object>("shadow");
        const jsonxx::Array& texturesValue = colorGradingValue.get<jsonxx::Array>("textures");
        shading.m_numColorgradingTextures = texturesValue.size();
        for (uint32_t i=0; i<shading.m_numColorgradingTextures; ++i)
        {
            const std::string& lutTexture = texturesValue.get<std::string>(i);
            shading.m_colorgradingTextureNames[i] = StringId(lutTexture.c_str());
            addDependency("color_grading_texture", name_to_file_path(lutTexture.c_str(), Raw3DTexture::get_name()));
        }
        shading.m_colorGradingIndex = colorGradingValue.get<int>("grading_index");
    }

    return write_file(m_output, &shading, sizeof(shading));
}