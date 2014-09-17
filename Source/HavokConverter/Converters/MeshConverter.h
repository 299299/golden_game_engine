#pragma once
#include "stdafx.h"
#include "ComponentConverter.h"

struct VertexDeclData
{
    const hkxVertexDescription::ElementDecl*    m_havokDecl;
    bgfx::Attrib::Enum                          m_attrib;
    bgfx::AttribType::Enum                      m_attribType;
    uint32_t                                    m_stride;
    uint32_t                                    m_numElements;
};

class MaterialConverter;
class ModelConverter;

class MeshConverter  : public ComponentConverter
{
public:
    HK_DECLARE_CLASS_ALLOCATOR(HK_MEMORY_CLASS_USER);
    MeshConverter(ActorConverter* ownner);
    ~MeshConverter();

    virtual std::string getTypeName() const { return Mesh::getName(); };
    virtual std::string getFormatExt() const { return Mesh::getName(); };
    
    virtual void process(void* pData, int hint = 0);
    virtual jsonxx::Object serializeToJson() const;

    MaterialConverter* getMaterial() const { return m_material; };
    uint32_t getFlags() const { return m_flags; };
    const bgfx::VertexDecl& getDecl() const { return  m_decl; };
    uint32_t getNumVertices() const { return m_numVertices;};
    uint32_t getNumIndices() const { return m_numIndices; };
    uint32_t getVertexBufferSize() const { return m_decl.getSize(getNumVertices()); };
    uint32_t getIndexBufferSize() const { return m_indices.size() * sizeof(uint16_t); };
    uint32_t writeVertexBuffer(char* blob);
    uint32_t writeIndexBuffer(char* blob);
    uint32_t getVertexStride() const { return m_decl.getStride(); };
    void dumpVerterx(char* blob);

private:
    void processVertexBuffer(hkxVertexBuffer* vb);
    void processIndexBuffer(hkxIndexBuffer* ib);
    void processDesc(const hkxVertexDescription& desc);
    void processTangent();

public:
    hkxMeshSection*                     m_mesh;
    MaterialConverter*                  m_material;
    ModelConverter*                     m_model;

    std::vector<uint16_t>               m_indices;
    std::vector<Vec4>                   m_tangents;
    bgfx::VertexDecl                    m_decl;
    uint32_t                            m_flags;
    uint32_t                            m_numVertices;
    uint32_t                            m_numIndices;
    VertexDeclData                      m_declDatas[bgfx::Attrib::Count];
};