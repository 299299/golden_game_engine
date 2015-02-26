#include "ShadingEnviromentCompiler.h"
#include "Texture.h"
#include "ShadingEnviroment.h"

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
    memcpy(shading.m_fog_params, fogParams, sizeof(fogParams));

    vec3_make(shading.m_ambient_sky_color, 0.37f, 0.55f, 0.66f);

    shading.m_shadow_area_size = 30.0f;
    shading.m_shadow_far = 100;
    vec3_make(shading.m_shadow_params, 0.01f, 0.001f, 0.0f);

    if(root.has<jsonxx::Object>("fog"))
    {
        const jsonxx::Object& o = root.get<jsonxx::Object>("fog");
        shading.m_fog_params[0] = json_to_float(o, "near", 10.0f);
        shading.m_fog_params[1] = json_to_float(o, "far", 40.0f);
        shading.m_fog_params[2] = json_to_float(o, "density", 0.0f);
        shading.m_fog_params[3] = json_to_float(o, "density", 0.0f);
    }

    json_to_floats(root, "ambient_sky_color", shading.m_ambient_sky_color, 3);
    json_to_floats(root, "ambient_ground_color", shading.m_ambient_ground_color, 3);

    if(root.has<jsonxx::Object>("shadow"))
    {
        const jsonxx::Object& o = root.get<jsonxx::Object>("shadow");
        shading.m_shadow_area_size = json_to_float(o, "area", 1.0f);
        shading.m_shadow_far = json_to_float(o, "far", 1.0f);
        shading.m_shadow_params[0] = json_to_float(o, "offset", 1.0f);
        shading.m_shadow_params[1] = json_to_float(o, "bias", 1.0f);
    }

    if(root.has<jsonxx::Object>("color_grading"))
    {
        const jsonxx::Object& o = root.get<jsonxx::Object>("color_grading");
        const jsonxx::Array& texturesValue = o.get<jsonxx::Array>("textures");
        shading.m_num_colorgrading_textures = texturesValue.size();
        for (uint32_t i=0; i<shading.m_num_colorgrading_textures; ++i)
        {
            const std::string& lutTexture = texturesValue.get<std::string>(i);
            shading.m_color_grading_texturenames[i] = stringid_caculate(lutTexture.c_str());
            addDependency("color_grading_texture", name_to_file_path(lutTexture.c_str(), EngineNames::TEXTURE_3D));
        }
        shading.m_colorgrading_index = json_to_int(o, "grading_index");
    }

    return write_file(m_output, &shading, sizeof(shading));
}