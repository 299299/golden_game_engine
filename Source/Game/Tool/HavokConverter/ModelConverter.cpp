#include "ModelConverter.h"
#include "MaterialConverter.h"
#include "MeshConverter.h"
#include "ActorConverter.h"
#include "MathDefs.h"
#include "Model.h"
#include "Mesh.h"
#include <vertexdecl.h>

ModelConverter::ModelConverter(ActorConverter* ownner)
:ComponentConverter(ownner)
,m_skin(0)
,m_type(kModelDefault)
{
}

ModelConverter::~ModelConverter()
{
#ifdef HAVOK_COMPILE
    for(size_t i=0; i<m_meshes.size(); ++i)
    {
        m_meshes[i]->removeReference();
    }
#endif
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
#ifdef HAVOK_COMPILE
    for(int i=0; i<mesh->m_sections.getSize(); ++i)
    {
        meshes.push_back(mesh->m_sections[i]);
    }
#endif
    loadMeshes(meshes);
}

void ModelConverter::process(RigSkinData* skinData)
{
    HC_PROFILE(model_skin_process);

    m_skin  = skinData;
    std::vector<hkxMeshSection*> meshes;

#ifdef HAVOK_COMPILE
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
    m_joints.setSize(skin->m_boneFromSkinMeshTransforms.getSize());
    for(int i=0;i <m_joints.getSize(); ++i)
    {
        skin->m_boneFromSkinMeshTransforms[i].get4x4ColumnMajor(m_joints[i].m_x);
    }

    ENGINE_ASSERT(m_joints.getSize() <= BGFX_CONFIG_MAX_BONES, "joint size overflow = %d", m_joints.getSize());
#endif
}

void ModelConverter::processMeshes( const std::vector<hkxMesh*>& meshes )
{
    HC_PROFILE(model_mesh_process);

    std::vector<hkxMeshSection*> meshSections;
#ifdef HAVOK_COMPILE
    for (size_t i=0; i<meshes.size(); ++i)
    {
        hkxMesh* mesh = meshes[i];
        for (int j=0; j<mesh->m_sections.getSize(); ++j)
        {
            meshSections.push_back(mesh->m_sections[j]);
        }
    }
#endif
    loadMeshes(meshSections);
}


void ModelConverter::loadMeshes(const std::vector<hkxMeshSection*>& meshes)
{
    m_havokMeshes  = meshes;
#ifdef HAVOK_COMPILE
    for(size_t i=0; i<meshes.size(); ++i)
    {
        hkxMeshSection* mesh = meshes[i];
        MeshConverter* meshConverter = new MeshConverter(m_ownner);
        meshConverter->m_model = this;
        meshConverter->process(mesh, 0);
        m_meshes.push_back(meshConverter);
    }
#endif
}

void ModelConverter::writeMesh(const std::string& fileName)
{
    HC_PROFILE(model_write_mesh);
#ifdef HAVOK_COMPILE
    uint32_t memorySize = sizeof(Mesh);
    memorySize += m_meshes.size() * sizeof(SubMesh);
    for(uint32_t i=0; i<m_meshes.size(); ++i)
    {
        MeshConverter* mesh = m_meshes[i];
        memorySize += mesh->getVertexBufferSize();
        memorySize += mesh->getIndexBufferSize();
    }
    memorySize = NATIVE_ALGIN_SIZE(memorySize);
    memorySize += m_joints.getSize() * sizeof(Matrix);
    memorySize = NATIVE_ALGIN_SIZE(memorySize);

    LOGI("mesh memory size = %d.", memorySize);
    MemoryBuffer mem(memorySize);
    char* head = mem.m_buf;
    Mesh* pMesh = (Mesh*)head;
    pMesh->m_memory_size = memorySize;
    pMesh->m_decl = m_meshes[0]->getDecl();
    pMesh->m_num_submeshes = m_meshes.size();
    pMesh->m_num_joints = m_joints.getSize();
    int offset = sizeof(Mesh);
    SubMesh* submeshes = (SubMesh*)(head + offset);
    pMesh->m_submesh_offset = offset;
    offset  += sizeof(SubMesh) * m_meshes.size();
    float min[3], max[3];
    for(uint32_t i=0; i<pMesh->m_num_submeshes; ++i)
    {
        MeshConverter* mesh = m_meshes[i];
        SubMesh& subMesh = submeshes[i];
        subMesh.m_vertex_size = mesh->getVertexBufferSize();
        subMesh.m_index_size = mesh->getIndexBufferSize();
        subMesh.m_vertex_offset = offset;
        subMesh.m_vbh.idx = bgfx::invalidHandle;
        subMesh.m_ibh.idx = bgfx::invalidHandle;

        uint32_t numVertices = mesh->getNumVertices();
        uint32_t vertexStride = mesh->getVertexStride();

        mesh->writeVertexBuffer(head + offset);
        calcMaxBoundingSphere(subMesh.m_sphere, head + offset, numVertices, vertexStride);
        calcAabb(subMesh.m_aabb, head + offset, numVertices, vertexStride);

        if(i == 0)
        {
            memcpy(min, subMesh.m_aabb.m_min, sizeof(min));
            memcpy(max, subMesh.m_aabb.m_max, sizeof(max));
        }
        else
        {
            min[0] = bx::fmin(subMesh.m_aabb.m_min[0], min[0]);
            min[1] = bx::fmin(subMesh.m_aabb.m_min[1], min[1]);
            min[2] = bx::fmin(subMesh.m_aabb.m_min[2], min[2]);
            max[0] = bx::fmax(subMesh.m_aabb.m_min[0], max[0]);
            max[1] = bx::fmax(subMesh.m_aabb.m_max[1], max[1]);
            max[2] = bx::fmax(subMesh.m_aabb.m_max[2], max[2]);
        }

        offset += subMesh.m_vertex_size;
        subMesh.m_index_offset = offset;

        mesh->writeIndexBuffer(head + offset);
        offset += subMesh.m_index_size;
    }

    pMesh->m_aabb.m_min[0] = min[0];
    pMesh->m_aabb.m_min[1] = min[1];
    pMesh->m_aabb.m_min[2] = min[2];
    pMesh->m_aabb.m_max[0] = max[0];
    pMesh->m_aabb.m_max[1] = max[1];
    pMesh->m_aabb.m_max[2] = max[2];
    offset = NATIVE_ALGIN_SIZE(offset);
    pMesh->m_joint_offset = offset;
    LOGI("mesh-joint_offset=%d", pMesh->m_joint_offset);

    if(!m_joints.isEmpty()) {
        memcpy(head + offset, &m_joints[0], m_joints.getSize() * sizeof(Matrix));
    }

    offset += m_joints.getSize() * sizeof(Matrix);
    ENGINE_ASSERT(offset == memorySize, "error offset %d != %d", offset, memorySize);
    write_file(fileName, head, memorySize);

    if(g_hc_config->m_verbose)
    {
        LOGI("******************** verbose mesh information %s ********************", m_meshName.c_str());
        Mesh* p_mesh = (Mesh*)head;
        bgfx::dump(p_mesh->m_decl);
        for(uint32_t i=0; i<p_mesh->m_num_submeshes; ++i)
        {
            LOGI("verbose dumpping sub mesh %d", i);
            const void* d = get_mesh_vertex_data(p_mesh, i);
            m_meshes[0]->dumpVerterx((char*)d, 8);
        }
        LOGI("******************** end of verbose mesh ********************");
    }

#endif
}

void ModelConverter::postProcess()
{
    std::string writeMeshFile = m_ownner->m_config->m_exportFolder + m_name + ".mesh";
    m_meshName = m_ownner->m_config->m_rootPath + m_name;
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
    modelObject << "mesh" << m_meshName;
    modelObject << "name" << getResourceName();
    modelObject << "type" << getTypeName();

    jsonxx::Array matObject;
    for(size_t i=0; i<m_meshes.size(); ++i)
    {
        MaterialConverter* m = m_meshes[i]->getMaterial();
        if(!m) continue;
        matObject << m->getResourceName();
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

