#include "ModelConverter.h"
#include "MaterialConverter.h"
#include "MeshConverter.h"
#include "ActorConverter.h"
#include "HC_Utils.h"
#include "bounds.h"

ModelConverter::ModelConverter(ActorConverter* ownner)
:ComponentConverter(ownner)
,m_skin(0)
,m_type(kModelDefault)
{
}

ModelConverter::~ModelConverter()
{
    for(size_t i=0; i<m_meshes.size(); ++i)
    {
        m_meshes[i]->removeReference();
    }
}

void ModelConverter::process(void* pData, int hint)
{
    if(hint == 0)
    {
        process((hkxMesh*)pData);
    }
    else if(hint == 1)
    {
        process((RigSkinData*)pData);
    }
}

void ModelConverter::process(hkxMesh* mesh)
{
    std::vector<hkxMeshSection*> meshes;
    for(int i=0; i<mesh->m_sections.getSize(); ++i)
    {
        meshes.push_back(mesh->m_sections[i]);
    }
    loadMeshes(meshes);
}

void ModelConverter::process(RigSkinData* skinData)
{
    m_skin  = skinData;
    std::vector<hkxMeshSection*> meshes;
    for(size_t i=0; i<skinData->m_skins.size(); ++i)
    {
        hkxMesh* mesh = skinData->m_skins[i]->m_mesh;
        for(int j=0; j<mesh->m_sections.getSize(); ++j)
        {
            meshes.push_back(mesh->m_sections[j]);
        }
    }
    loadMeshes(meshes);

    hkaMeshBinding* skin = skinData->m_skins[0];
    m_joints.resize(skin->m_boneFromSkinMeshTransforms.getSize());
    for(size_t i=0;i <m_joints.size(); ++i)
    {
        const hkTransform& invT = skin->m_boneFromSkinMeshTransforms[i];
        transform_matrix(m_joints[i].m_x, invT);
    }

    ENGINE_ASSERT(m_joints.size() <= BGFX_CONFIG_MAX_BONES, "joint size overflow = %d", m_joints.size());
}

void ModelConverter::loadMeshes(const std::vector<hkxMeshSection*>& meshes)
{
    m_havokMeshes  = meshes;
    for(size_t i=0; i<meshes.size(); ++i)
    {
        hkxMeshSection* mesh = meshes[i];
        MeshConverter* meshConverter = new MeshConverter(m_ownner);
        meshConverter->m_model = this;
        meshConverter->process(mesh, 0);
        m_meshes.push_back(meshConverter);
    }
}

void ModelConverter::writeMesh(const std::string& fileName)
{
    uint32_t memorySize = sizeof(Mesh);
    memorySize += m_meshes.size() * sizeof(SubMesh);
    for(uint32_t i=0; i<m_meshes.size(); ++i)
    {
        MeshConverter* mesh = m_meshes[i];
        memorySize += mesh->getVertexBufferSize();
        memorySize += mesh->getIndexBufferSize();
    }
    memorySize += m_joints.size() * sizeof(Matrix);
    //LOGI("mesh memory size = %d.", memorySize);
    MemoryBuffer mem(memorySize);
    char* p = mem.m_buf;
    char* head = p;
    Mesh* pMesh = (Mesh*)p;
    pMesh->m_decl = m_meshes[0]->getDecl();
    pMesh->m_numSubMeshes = m_meshes.size();
    pMesh->m_numJoints = m_joints.size();
    p  += sizeof(Mesh);
    SubMesh* submeshes = (SubMesh*)p;
    pMesh->m_subMeshOffset = p - head;
    p  += sizeof(SubMesh) * m_meshes.size();
    float min[3], max[3];
    for(uint32_t i=0; i<pMesh->m_numSubMeshes; ++i)
    {
        MeshConverter* mesh = m_meshes[i];
        SubMesh& subMesh = submeshes[i];
        subMesh.m_vertexSize = mesh->getVertexBufferSize();
        subMesh.m_indexSize = mesh->getIndexBufferSize();
        subMesh.m_vertexOffset = p - head;
        subMesh.m_vbh.idx = bgfx::invalidHandle;
        subMesh.m_ibh.idx = bgfx::invalidHandle;
        
        //------------------------------------------------------------------------------
        uint32_t numVertices = mesh->getNumVertices();
        uint32_t vertexStride = mesh->getVertexStride();
        
        mesh->writeVertexBuffer(p);
        calcMaxBoundingSphere(subMesh.m_sphere, p, numVertices, vertexStride);
        calcAabb(subMesh.m_aabb, p, numVertices, vertexStride);

        if(i == 0)
        {
            memcpy(min, subMesh.m_aabb.m_min, sizeof(min));
            memcpy(max, subMesh.m_aabb.m_max, sizeof(max));
        }

        min[0] = bx::fmin(subMesh.m_aabb.m_min[0], min[0]);
        min[1] = bx::fmin(subMesh.m_aabb.m_min[1], min[1]);
        min[2] = bx::fmin(subMesh.m_aabb.m_min[2], min[2]);
        max[0] = bx::fmax(subMesh.m_aabb.m_min[0], max[0]);
        max[1] = bx::fmax(subMesh.m_aabb.m_max[1], max[1]);
        max[2] = bx::fmax(subMesh.m_aabb.m_max[2], max[2]);

        p += subMesh.m_vertexSize;
        subMesh.m_indexOffset = p - head;

        //------------------------------------------------------------------------------
        mesh->writeIndexBuffer(p);
        p += subMesh.m_indexSize;
    }
    pMesh->m_aabb.m_min[0] = min[0];
    pMesh->m_aabb.m_min[1] = min[1];
    pMesh->m_aabb.m_min[2] = min[2];
    pMesh->m_aabb.m_max[0] = max[0];
    pMesh->m_aabb.m_max[1] = max[1];
    pMesh->m_aabb.m_max[2] = max[2];
    pMesh->m_jointOffset = p - head;
    if(!m_joints.empty())
        memcpy(p, &m_joints[0], m_joints.size() * sizeof(Matrix));
    p += m_joints.size() * sizeof(Matrix);

    ENGINE_ASSERT((head + memorySize) == p, "error offset");
    write_file(fileName, head, memorySize);
}

void ModelConverter::postProcess()
{
    std::string writeMeshFile = m_ownner->m_config->m_exportFolder + m_name + ".mesh";
    m_meshFile = m_ownner->m_config->m_rootPath + m_name;
    writeMesh(writeMeshFile);

    for(size_t i=0; i<m_meshes.size(); ++i)
    {
        m_meshes[i]->postProcess();
    }
}

jsonxx::Object 
ModelConverter::serializeToJson() const
{
    jsonxx::Object modelObject;
    modelObject << "mesh" << m_meshFile;
    modelObject << "name" << getResourceName();
    modelObject << "type" << getTypeName();

    jsonxx::Array matObject;
    for(size_t i=0; i<m_meshes.size(); ++i)
    {
        MaterialConverter* m = m_meshes[i]->getMaterial();
        if(!m) continue;
        if(m->isUsingCommon()) matObject << m->getResourceName();
        else matObject << m->serializeToJson();
    }
    modelObject << "materials" << matObject;

    if(m_type == kModelSky || m_type == kModelCollision)
    {
        extern const char* g_viewGroupNames[];
        modelObject << "view_group" << std::string(g_viewGroupNames[kBackgroundViewId]);
        jsonxx::Array flagsObject;
        flagsObject << "no_shadow";
        modelObject << "flags" << flagsObject;
    }

    fillAttributes(modelObject);
    
    return modelObject;
}

void ModelConverter::processMeshes( const std::vector<hkxMesh*>& meshes )
{
    std::vector<hkxMeshSection*> meshSections;
    for (size_t i=0; i<meshes.size(); ++i)
    {
        hkxMesh* mesh = meshes[i];
        for (int j=0; j<mesh->m_sections.getSize(); ++j)
        {
            meshSections.push_back(mesh->m_sections[j]);
        }
    }
    loadMeshes(meshSections);
}
