#include "Mesh.h"
#include "Log.h"

void SubMesh::submit() const
{
    bgfx::setIndexBuffer(m_ibh);
    bgfx::setVertexBuffer(m_vbh);
}

void Mesh::bringIn()
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

void Mesh::bringOut()
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

const void* Mesh::getVertexData( uint32_t index ) const
{
    char* pThis = (char*)this;
    return pThis + m_submeshes[index].m_vertexOffset;
}

uint32_t Mesh::getVertexNum( uint32_t index ) const
{
    return m_submeshes[index].m_vertexSize / m_decl.getStride();
}

uint32_t Mesh::getIndexNum( uint32_t index ) const
{
    return m_submeshes[index].m_indexSize / sizeof(uint16_t);
}

const uint16_t* Mesh::getIndexData( uint32_t index ) const
{
    char* pThis = (char*)this;
    return (const uint16_t*)(pThis + m_submeshes[index].m_indexOffset);
}

void Mesh::dump()
{
    LOGI("********* mesh start ********* dump num-of-submesh %d", m_numSubMeshes);
    for(uint32_t i=0; i<m_numSubMeshes; ++i)
    {
        const SubMesh& subMesh = m_submeshes[i];
        LOGI("sub mesh[%d] vertex: num=%d offset=%d size=%d, index: num=%d offset=%d size=%d", i,
             getVertexNum(i), subMesh.m_vertexOffset, subMesh.m_vertexSize,
             getIndexNum(i), subMesh.m_indexOffset, subMesh.m_indexSize);
        const Aabb& aabb = subMesh.m_aabb;
        LOGI("aabb = %g,%g,%g -> %g,%g,%g", 
             aabb.m_min[0], aabb.m_min[1], aabb.m_min[2],
             aabb.m_max[0], aabb.m_max[1], aabb.m_max[2]);
    }
    LOGI("joint offset = %d, num-of-joints=%d", m_jointOffset, m_numJoints);
    const Aabb& aabb = m_aabb;
    LOGI("big aabb = %g,%g,%g -> %g,%g,%g", 
         aabb.m_min[0], aabb.m_min[1], aabb.m_min[2],
         aabb.m_max[0], aabb.m_max[1], aabb.m_max[2]);
    LOGI("********* mesh end *********");
}

void* load_resource_mesh(const char* data, uint32_t size)
{
    Mesh* pMesh = (Mesh*)data;
    pMesh->m_submeshes = (SubMesh*)(data + pMesh->m_subMeshOffset);
    pMesh->m_jointMatrix = (Matrix*)(data + pMesh->m_jointOffset);
#ifdef DUMP_RESOURCE
    pMesh->dump();
#endif
    return pMesh;
}

void  bringin_resource_mesh(void* resource)
{
    Mesh* pMesh = (Mesh*)resource;
    pMesh->bringIn();
}

void  bringout_resource_mesh(void* resource)
{
    Mesh* pMesh = (Mesh*)resource;
    pMesh->bringOut();
}
