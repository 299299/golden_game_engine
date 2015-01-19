#pragma once
#include "ComponentConverter.h"
#include "Material.h"

class SamplerConverter;
class ModelConverter;
#ifndef HAVOK_COMPILE
struct hkxMaterial { struct TextureStage{}; };
struct hkRefVariant {};
#endif

class MaterialConverter  : public ComponentConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    MaterialConverter(ActorConverter* ownner);
    ~MaterialConverter();

    virtual std::string getTypeName() const { return Material::get_name(); };
    virtual std::string getFormatExt() const { return Material::get_name(); };
    virtual std::string getResourceName() const;

    virtual void process(void* pData, int hint = 0);
    virtual jsonxx::Object serializeToJson() const;
    bool isUsingCommon() const { return m_existInCommonPackage; };

private:
    void process(hkxMaterial* material);
    int  getTextureSlot( const hkxMaterial::TextureStage& stage);
    bool isTypeExist(int type) const;
    virtual void serializeToFile(const char* fileName);
    std::string getTextureFileName(hkRefVariant variant);

public:
    std::vector<SamplerConverter*>          m_samplers;
    std::string                             m_shader;
    std::string                             m_shadowShader;
    hkxMaterial*                            m_material;
    ModelConverter*                         m_model;
    bool                                    m_existInCommonPackage;
};

