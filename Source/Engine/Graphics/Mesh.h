#pragma once
#include "StringId.h"
#include "MathDefs.h"
#include <bgfx.h>

ENGINE_NATIVE_ALIGN struct SubMesh
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

ENGINE_NATIVE_ALIGN struct Mesh
{
    DECLARE_RESOURCE(mesh);

    void bringIn();
    void bringOut();

    uint32_t  getVertexNum(uint32_t index) const;
    const void* getVertexData(uint32_t index) const;
    uint32_t getIndexNum(uint32_t index) const;
    const uint16_t* getIndexData(uint32_t index) const;

    bgfx::VertexDecl            m_decl;
    Aabb                        m_aabb;
    
    uint32_t                    m_subMeshOffset;
    uint32_t                    m_jointOffset;
    
    SubMesh*                    m_submeshes;
    Matrix*                     m_jointMatrix;
    
    uint8_t                     m_numSubMeshes;
    uint8_t                     m_numJoints;
    char                        m_padding[2];


    void dump();
};


