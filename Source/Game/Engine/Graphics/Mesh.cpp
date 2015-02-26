#include "Mesh.h"
#include "Log.h"


void  bringin_resource_mesh(void* resource)
{
    Mesh* pMesh = (Mesh*)resource;
    char* p = (char*)resource;
    uint32_t num = pMesh->m_num_submeshes;
    SubMesh* submeshes = (SubMesh*)(p + pMesh->m_submesh_offset);

    for(uint32_t i=0; i<num; ++i)
    {
        SubMesh& _sub_mesh = submeshes[i];
        _sub_mesh.m_vbh = bgfx::createVertexBuffer(
            bgfx::makeRef(p + _sub_mesh.m_vertex_offset, _sub_mesh.m_vertex_size),
            pMesh->m_decl);
        _sub_mesh.m_ibh = bgfx::createIndexBuffer(
            bgfx::makeRef(p + _sub_mesh.m_index_offset, _sub_mesh.m_index_size));
    }
}

void  bringout_resource_mesh(void* resource)
{
    Mesh* pMesh = (Mesh*)resource;
    char* p = (char*)resource;
    uint32_t num = pMesh->m_num_submeshes;
    SubMesh* submeshes = (SubMesh*)(p + pMesh->m_submesh_offset);

    for(uint32_t i=0; i<num; ++i)
    {
        SubMesh& _sub_mesh = submeshes[i];
        if(bgfx::isValid(_sub_mesh.m_vbh))
            bgfx::destroyVertexBuffer(_sub_mesh.m_vbh);
        _sub_mesh.m_vbh.idx = bgfx::invalidHandle;
        if(bgfx::isValid(_sub_mesh.m_ibh))
            bgfx::destroyIndexBuffer(_sub_mesh.m_ibh);
        _sub_mesh.m_ibh.idx = bgfx::invalidHandle;
    }
}


uint32_t get_mesh_vertex_num(const Mesh* mesh, uint32_t index)
{
    SubMesh* submeshes = (SubMesh*)((char*)mesh + mesh->m_submesh_offset);
    return submeshes[index].m_vertex_size / mesh->m_decl.getStride();
}

const void* get_mesh_vertex_data(const Mesh* mesh, uint32_t index)
{
    char* p = (char*)mesh;
    SubMesh* submeshes = (SubMesh*)(p + mesh->m_submesh_offset);
    return p + submeshes[index].m_vertex_offset;
}

uint32_t get_mesh_index_num(const Mesh* mesh, uint32_t index)
{
    SubMesh* submeshes = (SubMesh*)((char*)mesh + mesh->m_submesh_offset);
    return submeshes[index].m_index_size / sizeof(uint16_t);
}

const uint16_t* get_mesh_index_data(const Mesh* mesh, uint32_t index)
{
    char* p = (char*)mesh;
    SubMesh* submeshes = (SubMesh*)(p + mesh->m_submesh_offset);
    return (const uint16_t*)(p + submeshes[index].m_index_offset);
}

void submit_submesh(const SubMesh* submesh)
{
    bgfx::setVertexBuffer(submesh->m_vbh);
    bgfx::setIndexBuffer(submesh->m_ibh);
}