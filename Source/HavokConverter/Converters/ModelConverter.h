#pragma once
#include "stdafx.h"
#include "ComponentConverter.h"
#include "Model.h"

struct RigSkinData
{
    const hkaSkeleton*                              m_rig;
    std::vector<hkaMeshBinding*>                    m_skins;
    std::vector<hkaBoneAttachment*>                 m_attachments;
};

enum ModelType
{
    kModelDefault = 0,
    kModelSky,
    kModelSkinning,
    kModelTypeNum
};

class MaterialConverter;
class MeshConverter;

class ModelConverter   : public ComponentConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    ModelConverter(ActorConverter* ownner);
    ~ModelConverter();

    virtual std::string getTypeName() const { return ModelResource::get_name(); };
    virtual std::string getFormatExt() const { return ModelResource::get_name(); };

    virtual void process(void* pData, int hint = 0);
    virtual void postProcess();
    virtual jsonxx::Object serializeToJson() const;

private:
    void process(hkxMesh* mesh);
    void process(RigSkinData* skinData);
    void loadMeshes(const std::vector<hkxMeshSection*>& meshes);
    void writeMesh(const std::string& fileName);

public:
    std::vector<hkxMeshSection*>        m_havokMeshes;
    std::vector<MeshConverter*>         m_meshes;
    std::vector<Matrix>                 m_joints;
    Aabb                                m_bbox;
    RigSkinData*                        m_skin;
    std::string                         m_meshFile;
    int                                 m_type;
};
