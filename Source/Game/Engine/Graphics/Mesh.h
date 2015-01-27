#pragma once
#include "StringId.h"
#include "MathDefs.h"
#include <bgfx.h>

ENGINE_NATIVE_ALIGN(struct) SubMesh
{
    Sphere                          m_sphere;
    Aabb                            m_aabb;
    bgfx::VertexBufferHandle        m_vbh;
    bgfx::IndexBufferHandle         m_ibh;

    uint32_t                        m_vertexOffset;
    uint32_t                        m_vertexSize;
    uint32_t                        m_indexOffset;
    uint32_t                        m_indexSize;

    void submit() const;
};

ENGINE_NATIVE_ALIGN(struct) Mesh
{
    DECLARE_RESOURCE(mesh);

    void bringin();
    void bringout();

    uint32_t  get_vertex_num(uint32_t index) const;
    const void* get_vertex_data(uint32_t index) const;
    uint32_t get_index_num(uint32_t index) const;
    const uint16_t* get_index_data(uint32_t index) const;

    bgfx::VertexDecl            m_decl;
    Aabb                        m_aabb;

    uint32_t                    m_subMeshOffset;
    uint32_t                    m_jointOffset;

    SubMesh*                    m_submeshes;
    Matrix*                     m_jointMatrix;

    uint8_t                     m_numSubMeshes;
    uint8_t                     m_numJoints;
    char                        m_padding[2];
};


