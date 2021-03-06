#include "MaterialConverter.h"
#include "SamplerConverter.h"
#include "ActorConverter.h"
#include "ModelConverter.h"
#include "Material.h"

MaterialConverter::MaterialConverter(ActorConverter* ownner)
:ComponentConverter(ownner)
,m_model(0)
{

}

MaterialConverter::~MaterialConverter()
{
#ifdef HAVOK_COMPILE
    for (size_t i=0; i<m_samplers.size();++i)
    {
        SAFE_REMOVEREF(m_samplers[i]);
    }
#endif
}

int MaterialConverter::getTextureSlot( const hkxMaterial::TextureStage& stage )
{
    int ret = TEX_COLOR_SLOT;
 #ifdef HAVOK_COMPILE
    switch(stage.m_usageHint)
    {
    case hkxMaterial::TEX_DIFFUSE:
        ret = TEX_COLOR_SLOT;
        break;
    case hkxMaterial::TEX_BUMP:
        ret = TEX_NORMAL_SLOT;
        break;
    case hkxMaterial::TEX_NORMAL:
        ret = TEX_NORMAL_SLOT;
        break;
    case hkxMaterial::TEX_SPECULAR:
        ret = TEX_SPECULAR_SLOT;
        break;
    case hkxMaterial::TEX_EMISSIVE:
        ret = TEX_EMISSIVE_SLOT;
        break;
    case hkxMaterial::TEX_UNKNOWN:
        break;
    default:
        break;
    }

    if(stage.m_tcoordChannel == 1)
    {
        ret = TEX_LIGHTMAP_SLOT;
    }
#endif
    return ret;
}

void MaterialConverter::process(void* pData, int hint)
{
    process((hkxMaterial*)pData);
}

void MaterialConverter::process(hkxMaterial* material)
{
    m_material = material;

 #ifdef HAVOK_COMPILE
    std::string materialName = material->m_name.cString();
    LOGD("material name = %s", materialName.c_str());
    materialName = getFileNameAndExtension(materialName);
    string_replace(materialName, ":", "_");
    setName(materialName);

    extern const char*          g_textureNames[];
    for(int i=0; i<material->m_stages.getSize(); ++i)
    {
        const hkxMaterial::TextureStage& stage = material->m_stages[i];
        std::string fileName = getTextureFileName(stage.m_texture);
        if(fileName == "ERROR") continue;
        SamplerConverter* sampler = new SamplerConverter(m_ownner);
        sampler->m_textureFileName = fileName;
        sampler->m_type = getTextureSlot(stage);
        if(sampler->m_type == TEX_NORMAL_SLOT)
            sampler->m_textureFormat = DDS_NM_FORMAT;
        else if(material->m_transparency == hkxMaterial::transp_alpha)
            sampler->m_textureFormat = DDS_ALPHA_FORMAT;
        sampler->m_textureSlotName = g_textureNames[sampler->m_type];
        sampler->setName(getFileName(sampler->m_textureFileName));
        m_samplers.push_back(sampler);
    }

    if(m_samplers.size() == 0)
        m_name = COMMON_MAT_NAME;
    else
        m_name = m_ownner->m_config->m_exportName + "_" + m_name;

    m_shadowShader = "shadow";
    const char* shader_comb_names[] =
    {
        "diff", "_norm", "_spec"
    };

    for (int i = 0; i <= TEX_SPECULAR_SLOT; ++i)
    {
        if(isTypeExist(i))
        {
            m_shader += shader_comb_names[i];
        }
    }

    if(m_shader.empty())
        m_shader = DEFAULT_SHADER;

    if(m_model->m_type == kModelSkinning)
    {
        m_shader = "skin_" + m_shader;
        m_shadowShader = "skin_" + m_shadowShader;
    }
    else if(m_model->m_type == kModelSky)
    {
        m_shader = "sky";
        m_shadowShader = "";
    }
    else if(m_model->m_type == kModelCollision)
    {
        m_shader = "base";
        m_shadowShader = "";
    }
#endif
}

jsonxx::Object MaterialConverter::serializeToJson() const
{
    extern const char*  g_textureNames[];

    jsonxx::Object rootObject;
    rootObject << "name" << getResourceName();
    rootObject << "shader" << m_shader;
    rootObject << "shadow_shader" << m_shadowShader;
 #ifdef HAVOK_COMPILE
    jsonxx::Array uvArray;
    uvArray << m_material->m_uvMapOffset[0];
    uvArray << m_material->m_uvMapOffset[1];
    uvArray << m_material->m_uvMapScale[0];
    uvArray << m_material->m_uvMapScale[1];
    rootObject << "uv_offset_scale" << uvArray;
    jsonxx::Array diffuseArray;
    for (int i=0; i<4; ++i)
    {
        diffuseArray << m_material->m_diffuseColor(i);
    }
    rootObject << "diffuse" << diffuseArray;
    jsonxx::Array specularArray;
    for (int i=0; i<4; ++i)
    {
        specularArray << m_material->m_diffuseColor(i);
    }
    rootObject << "specular" << specularArray;
#endif

    extern const char* g_matFlagNames[];

    jsonxx::Array flagsObject;
    ///TODO....
    rootObject << "flags" << flagsObject;

    jsonxx::Array samplersObject;
    if(!m_samplers.empty())
    {
        for(size_t i=0; i<m_samplers.size(); ++i)
        {
            samplersObject << m_samplers[i]->serializeToJson();
        }
    }
    rootObject << "samplers" << samplersObject;
    return rootObject;
}

void MaterialConverter::serializeToFile( const std::string& fileName )
{
    jsonxx::Object new_json = serializeToJson();

    if (g_hc_config->m_merge) {
        jsonxx::Object old_json;
        if (read_json_from_file(old_json, fileName)) {
            LOGW("ignore material serializeToFile %s", fileName.c_str());
            return;
        }
    }

    if (!write_json_to_file(new_json, fileName))
        g_hc_config->m_error.add_error("%s to %s IO error.", __FUNCTION__, fileName.c_str());
}

bool MaterialConverter::isTypeExist(int type) const
{
    for (size_t i=0; i<m_samplers.size();++i)
    {
        SamplerConverter* sampler = m_samplers[i];
        if(sampler->m_type == type)
            return true;
    }
    return false;
}

std::string MaterialConverter::getTextureFileName( hkRefVariant variant )
{
 #ifdef HAVOK_COMPILE
    hkVariant va(variant);
    if(va.m_class == &hkxTextureFileClass)
    {
        const hkxTextureFile* texFile = (const hkxTextureFile*)va.m_object;
        std::string fileName = texFile->m_filename.cString();
        std::string orginalFileName = texFile->m_originalFilename.cString();
        if(fileName.empty() && orginalFileName.empty())
            return "ERROR"; // <--- magic
        if(isFileExist(orginalFileName))
            return orginalFileName;
        if(isFileExist(fileName))
            return fileName;
        LOGW("file or orignal file %s both do not exit, guesse a nice one.",
            orginalFileName.c_str());
        std::string fName = getFileNameAndExtension(fileName);
        std::string imagePath = m_ownner->m_config->m_workspaceFolder;
        imagePath += "sourceimages/";
        imagePath += fName;
        LOGD("guess source image path %s", imagePath.c_str());
        if(isFileExist(imagePath))
            return imagePath;
        imagePath = m_ownner->m_config->m_assetFolder;
        imagePath += fName;
        LOGD("guess assert folder %s", imagePath.c_str());
        if(isFileExist(imagePath))
            return imagePath;
        g_hc_config->m_error.add_error("texture %s not exist in hard drive. ret %s", fName.c_str(), fileName.c_str());
        return fileName;
    }
    else
    {
        return "ERROR";
    }
#else
    return "ERROR";
#endif
}
