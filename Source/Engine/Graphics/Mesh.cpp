#include "Mesh.h"
#include "Log.h"

void SubMesh::submit() const
{
    bgfx::setIndexBuffer(m_ibh);
    bgfx::setVertexBuffer(m_vbh);
}

void Mesh::bringin()
{
    char* pThis = (char*)this;
    for(uint32_t i=0; i<m_numSubMeshes; ++i)
    {
        SubMesh& subMesh = m_submeshes[i];
        const bgfx::Memory* vmem = bgfx::makeRef(pThis + subMesh.m_vertexOffset, subMesh.m_vertexSize);
        const bgfx::Memory* imem = bgfx::makeRef(pThis + subMesh.m_indexOffset, subMesh.m_indexSize);
        subMesh.m_vbh = bgfx::createVertexBuffer(vmem, m_decl);
        subMesh.m_ibh = bgfx::createIndexBuffer(imem);
    }
}

void Mesh::bringout()
{
    for(uint32_t i=0; i<m_numSubMeshes; ++i)
    {
        SubMesh& subMesh = m_submeshes[i];
        if(bgfx::isValid(subMesh.m_vbh)) bgfx::destroyVertexBuffer(subMesh.m_vbh);
        subMesh.m_vbh.idx = bgfx::invalidHandle; 
        if(bgfx::isValid(subMesh.m_ibh)) bgfx::destroyIndexBuffer(subMesh.m_ibh);
        subMesh.m_ibh.idx = bgfx::invalidHandle;
    }
}

const void* Mesh::get_vertex_data( uint32_t index ) const
{
    char* pThis = (char*)this;
    return pThis + m_submeshes[index].m_vertexOffset;
}

uint32_t Mesh::get_vertex_num( uint32_t index ) const
{
    return m_submeshes[index].m_vertexSize / m_decl.getStride();
}

uint32_t Mesh::get_index_num( uint32_t index ) const
{
    return m_submeshes[index].m_indexSize / sizeof(uint16_t);
}

const uint16_t* Mesh::get_index_data( uint32_t index ) const
{
    char* pThis = (char*)this;
    return (const uint16_t*)(pThis + m_submeshes[index].m_indexOffset);
}

void* load_resource_mesh(const char* data, uint32_t size)
{
    Mesh* pMesh = (Mesh*)data;
    pMesh->m_submeshes = (SubMesh*)(data + pMesh->m_subMeshOffset);
    pMesh->m_jointMatrix = (Matrix*)(data + pMesh->m_jointOffset);
    return pMesh;
}

void  bringin_resource_mesh(void* resource)
{
    Mesh* pMesh = (Mesh*)resource;
    pMesh->bringin();
}

void  bringout_resource_mesh(void* resource)
{
    Mesh* pMesh = (Mesh*)resource;
    pMesh->bringout();
}
