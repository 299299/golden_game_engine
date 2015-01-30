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
        const jsonxx::Object& o = root.get<jsonxx::Object>("fog");
        shading.m_fogParams[0] = json_to_float(o, "near", 10.0f);
        shading.m_fogParams[1] = json_to_float(o, "far", 40.0f);
        shading.m_fogParams[2] = json_to_float(o, "density", 0.0f);
        shading.m_fogParams[3] = json_to_float(o, "density", 0.0f);
    }

    if(root.has<jsonxx::Object>("bloom"))
    {
        const jsonxx::Object& o = root.get<jsonxx::Object>("bloom");
        shading.m_bloomParams[0] = json_to_float(o, "expose", 2.0f);
        shading.m_bloomParams[1] = json_to_float(o, "bloomThreshold", 0.63f);
        shading.m_bloomParams[2] = json_to_float(o, "bloomWidth", 1.0f);
        shading.m_bloomParams[3] = json_to_float(o, "bloomIntensity", 1.0f);
    }

    if(root.has<jsonxx::Object>("dof"))
    {
        const jsonxx::Object& o = root.get<jsonxx::Object>("dof");
        shading.m_dofParams[0] = json_to_float(o, "focusDistance", 1.0f);
        shading.m_dofParams[1] = json_to_float(o, "focusRange", 2.0f);
        shading.m_dofParams[2] = json_to_float(o, "dof_blur_width", 2.5f);
        shading.m_dofParams[3] = json_to_float(o, "focusFalloff", 10.0f);
    }

    json_to_floats(root, "ambient_sky_color", shading.m_ambientSkyColor, 3);
    json_to_floats(root, "ambient_ground_color", shading.m_ambientGroundColor, 3);

    if(root.has<jsonxx::Object>("shadow"))
    {
        const jsonxx::Object& o = root.get<jsonxx::Object>("shadow");
        shading.m_shadowAreaSize = json_to_float(o, "area", 1.0f);
        shading.m_shadowFar = json_to_float(o, "far", 1.0f);
        shading.m_shadowParams[0] = json_to_float(o, "offset", 1.0f);
        shading.m_shadowParams[1] = json_to_float(o, "bias", 1.0f);
    }

    shading.m_ppParams[2] = json_to_float(root, "defocus", 0.2f);
    shading.m_ppParams[3] = json_to_float(root, "film_gain_noise", 0.25f);

    if(root.has<jsonxx::Object>("color_grading"))
    {
        const jsonxx::Object& o = root.get<jsonxx::Object>("color_grading");
        const jsonxx::Array& texturesValue = o.get<jsonxx::Array>("textures");
        shading.m_numColorgradingTextures = texturesValue.size();
        for (uint32_t i=0; i<shading.m_numColorgradingTextures; ++i)
        {
            const std::string& lutTexture = texturesValue.get<std::string>(i);
            shading.m_colorgradingTextureNames[i] = stringid_caculate(lutTexture.c_str());
            addDependency("color_grading_texture", name_to_file_path(lutTexture.c_str(), Raw3DTexture::get_name()));
        }
        shading.m_colorGradingIndex = json_to_int(o, "grading_index");
    }

    return write_file(m_output, &shading, sizeof(shading));
}