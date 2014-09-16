#include <windows.h>
#include <bx/platform.h>
#include "MeshConverter.h"
#include "MaterialConverter.h"
#include "forsythtriangleorderoptimizer.h"
#include "ActorConverter.h"
#include "HC_Utils.h"
#include <bgfx/vertexdecl.h>

//#define FLOAT_WEIGHT

static const char* s_attrName[bgfx::Attrib::Count] = 
{
    "Attrib::Position",
    "Attrib::Normal",
    "Attrib::Tangent",
    "Attrib::Bitangent",
    "Attrib::Color0",
    "Attrib::Color1",
    "Attrib::Indices",
    "Attrib::Weights",
    "Attrib::TexCoord0",
    "Attrib::TexCoord1",
    "Attrib::TexCoord2",
    "Attrib::TexCoord3",
    "Attrib::TexCoord4",
    "Attrib::TexCoord5",
    "Attrib::TexCoord6",
    "Attrib::TexCoord7",
};

static uint32_t bgfx_data_stride[bgfx::AttribType::Count] = 
{
    sizeof(uint8_t), sizeof(int16_t), sizeof(uint16_t), sizeof(float)
};

static bgfx::Attrib::Enum havokAttribToBgfx(const hkxVertexDescription::DataUsage& usage)
{
    switch(usage)
    {
    case hkxVertexDescription::HKX_DU_POSITION:
        return bgfx::Attrib::Position;
    case hkxVertexDescription::HKX_DU_COLOR:
        return bgfx::Attrib::Color0;
    case hkxVertexDescription::HKX_DU_NORMAL:
        return bgfx::Attrib::Normal;
    case hkxVertexDescription::HKX_DU_TANGENT:
        return bgfx::Attrib::Tangent;
    case hkxVertexDescription::HKX_DU_TEXCOORD:
        return bgfx::Attrib::TexCoord0;
    case hkxVertexDescription::HKX_DU_BLENDWEIGHTS:
        return bgfx::Attrib::Weight;
    case hkxVertexDescription::HKX_DU_BLENDINDICES:
        return bgfx::Attrib::Indices;
    case hkxVertexDescription::HKX_DU_BINORMAL:
        //return bgfx::Attrib::Bitangent;
    default:
        return bgfx::Attrib::Count;
    }
}

static bgfx::AttribType::Enum havokDataTypeToBgfx(const hkxVertexDescription::DataType& type)
{
    switch(type)
    {
    case hkxVertexDescription::HKX_DT_UINT8:
        return bgfx::AttribType::Uint8;
    case hkxVertexDescription::HKX_DT_INT16:
        return bgfx::AttribType::Int16;
    case hkxVertexDescription::HKX_DT_FLOAT:
        return bgfx::AttribType::Float;
    case hkxVertexDescription::HKX_DT_UINT32:
        return bgfx::AttribType::Uint8;
    default:
        HK_ASSERT(0, 0);
        return bgfx::AttribType::Count;
    }
}

MeshConverter::MeshConverter(ActorConverter* ownner)
:ComponentConverter(ownner)
,m_mesh(0)
,m_material(0)
,m_model(0)
{
    memset(m_declDatas, 0x00, sizeof(m_declDatas));
}

MeshConverter::~MeshConverter()
{
    SAFE_REMOVEREF(m_material);
}

void MeshConverter::process(void* pData, int hint)
{
    m_mesh = (hkxMeshSection*)pData;
    processVertexBuffer(m_mesh->m_vertexBuffer);
    HK_ASSERT(0, m_mesh->m_indexBuffers.getSize() < 2);
    processIndexBuffer(m_mesh->m_indexBuffers[0]);
    if(m_mesh->m_material)
    {
        m_material = new MaterialConverter(m_ownner);
        m_material->m_model = m_model;
        m_material->process(m_mesh->m_material, 0);
    }
    else
    {
        LOGW("no material in current mesh [%s] !", m_ownner->m_name.c_str());
    }
}

jsonxx::Object MeshConverter::serializeToJson() const
{
    return jsonxx::Object();
}
void MeshConverter::processDesc(const hkxVertexDescription& desc)
{
    m_decl.begin(bgfx::RendererType::Direct3D11);
    for(int i=0; i<desc.m_decls.getSize(); ++i)
    {
        const hkxVertexDescription::ElementDecl& decl = desc.m_decls[i];
        bgfx::Attrib::Enum attrib = havokAttribToBgfx(decl.m_usage);
        bgfx::AttribType::Enum type = havokDataTypeToBgfx(decl.m_type);
        bool bPacked = false;
        uint32_t elementNum = decl.m_numElements;

        if(attrib == bgfx::Attrib::Count)
        {
            //LOGW("unknow attrib");
            continue;
        }

        if(attrib == bgfx::Attrib::TexCoord0)
        {
            for(int i=1; i<8; ++i)
            {
                if(desc.getElementDecl(hkxVertexDescription::HKX_DU_TEXCOORD, i) == &decl)
                {
                    //----> check texcoord from 1 -> 7
                    LOGI("has TexCoord%d", i);
                    attrib = (bgfx::Attrib::Enum)((int)bgfx::Attrib::TexCoord0 + i);
                    break;
                }
            }

            if(g_config.m_packUV)
            {
                LOGI("--> Pack UV <--");
                type = bgfx::AttribType::Half;
                bPacked= true;
            }
        }

        if(g_config.m_packNormal && attrib == bgfx::Attrib::Normal)
        {
            LOGI("--> Pack Normal <--");
            type = bgfx::AttribType::Uint8;
            bPacked= true;
        }
        
        if(attrib == bgfx::Attrib::Tangent)
        {
            //LOGD("Tangent set element num from %d to %d", decl.m_numElements, 4);
            elementNum = 4;
        }
        else if(attrib == bgfx::Attrib::Weight)
        {
            elementNum = 3;
#ifdef FLOAT_WEIGHT
            type = bgfx::AttribType::Float;
#endif
        }

        VertexDeclData data;
        data.m_havokDecl = &decl;
        data.m_attrib = attrib;
        data.m_attribType = type;
        data.m_stride = bgfx_data_stride[type] * elementNum;
        data.m_numElements = elementNum;

        m_declDatas[attrib] = data;
#ifndef FLOAT_WEIGHT
        if(attrib == bgfx::Attrib::Weight)
            m_decl.add(attrib, elementNum, type, true, true);
        else
#endif
            m_decl.add(attrib, elementNum, type);
    }
    m_decl.end();
    bgfx::dump(m_decl);
}

void MeshConverter::processVertexBuffer(hkxVertexBuffer* vb)
{
    m_numVertices = vb->getNumVertices();
    processDesc(vb->getVertexDesc());
    processTangent();   
}

void MeshConverter::processTangent()
{
    hkxVertexBuffer* vb = m_mesh->m_vertexBuffer;
    const hkxVertexDescription::ElementDecl* ed_normal = vb->getVertexDesc().getElementDecl(hkxVertexDescription::HKX_DU_NORMAL,0);
    const hkxVertexDescription::ElementDecl* ed_tang = vb->getVertexDesc().getElementDecl(hkxVertexDescription::HKX_DU_TANGENT,0);
    const hkxVertexDescription::ElementDecl* ed_bn = vb->getVertexDesc().getElementDecl(hkxVertexDescription::HKX_DU_BINORMAL,0);
    if(ed_normal && ed_tang && ed_bn)
    {
        m_tangents.resize(m_numVertices);
        uint8_t* data_normal = (uint8_t*)vb->getVertexDataPtr(*ed_normal);
        uint8_t* data_tang = (uint8_t*)vb->getVertexDataPtr(*ed_tang);
        uint8_t* data_bn = (uint8_t*)vb->getVertexDataPtr(*ed_bn);

        int normal_stride = ed_normal->m_byteStride;
        int tang_stride = ed_tang->m_byteStride;
        int bn_stride = ed_bn->m_byteStride;

        for (size_t i=0; i<m_numVertices; ++i)
        {
            const hkReal* p_normal = (const hkReal*)(data_normal + (normal_stride * i));
            const hkReal* p_tang = (const hkReal*)(data_tang + (tang_stride * i));
            const hkReal* p_bn = (const hkReal*)(data_bn + (bn_stride * i));
            Vec4 tangent;
            bx::vec3Move(tangent.m_vec, p_tang);
            float nxt[3];
            bx::vec3Cross(nxt, p_normal, p_tang);
            tangent.m_vec[3] = bx::vec3Dot(nxt, p_bn) < 0.0f ? -1.0f : 1.0f;
            m_tangents[i] = tangent;
        }
    }
}

void MeshConverter::processIndexBuffer(hkxIndexBuffer* ib)
{
    HK_ASSERT(0, ib->m_indexType == hkxIndexBuffer::INDEX_TYPE_TRI_LIST);
    int numIndices = ib->m_indices16.getSize();
    HK_ASSERT(0, numIndices > 0);

    m_numIndices = numIndices;
    m_indices.resize(m_numIndices);

    for(int i=0; i<numIndices; ++i)
    {
        m_indices[i] = ib->m_indices16[i];
    }

#if 1
    std::vector<uint16_t> newIndices;
    newIndices.resize(m_numIndices);
    Forsyth::OptimizeFaces(&m_indices[0], m_numIndices, m_numVertices, &newIndices[0], 32);
    m_indices = newIndices;
#endif
}

uint32_t MeshConverter::writeVertexBuffer(char* blob)
{
    hkxVertexBuffer* vb = m_mesh->m_vertexBuffer;
    uint32_t ret = getVertexBufferSize();
    char* head = blob;
    uint32_t stride = getVertexStride();
    for (uint32_t i=0; i<m_numVertices; ++i)
    {
        for(uint32_t j=0; j<bgfx::Attrib::Count; ++j)
        {
            const VertexDeclData& data = m_declDatas[j];
            if(!data.m_havokDecl) 
                continue;

            const hkxVertexDescription::ElementDecl& decl = *data.m_havokDecl;
            uint8_t* vData = (uint8_t*)vb->getVertexDataPtr(decl)+decl.m_byteStride*i;
            uint8_t* outData = (uint8_t*)head + m_decl.getOffset(data.m_attrib);

            if(g_config.m_packNormal && decl.m_usage == hkxVertexDescription::HKX_DU_NORMAL)
            {
                float* input = (float*)vData;
                float norm[4] = {0,0,0,0}; norm[0] = input[0]; norm[1] = input[1]; norm[2] = input[2];
                bgfx::vertexPack(norm, true, data.m_attrib, m_decl, head);
            }
            else if(g_config.m_packUV && decl.m_usage == hkxVertexDescription::HKX_DU_TEXCOORD)
            {
                float* input = (float*)vData;
                float uv[4] = {0,0,0,0}; uv[0] = input[0]; uv[1] = input[1];
                bgfx::vertexPack(uv, true, data.m_attrib, m_decl, head);
            }
#ifdef FLOAT_WEIGHT
            else if(decl.m_usage == hkxVertexDescription::HKX_DU_BLENDWEIGHTS)
            {
                float* p = (float*)outData;
                p[0] = (float)vData[0]/255.0f;
                p[1] = (float)vData[1]/255.0f;
                p[2] = (float)vData[2]/255.0f;
                p[3] = (float)vData[3]/255.0f;
            }
#endif
            else if(data.m_attrib == bgfx::Attrib::Tangent)
            {
                memcpy(outData, m_tangents[i].m_vec, data.m_stride);
            }
            else
            {
                memcpy(outData, vData, data.m_stride);
            }
        }
        head += stride;
    }
    return ret;
}

uint32_t MeshConverter::writeIndexBuffer(char* blob)
{
    uint32_t ret = getIndexBufferSize();
    memcpy(blob, &m_indices[0], ret);
    return ret;
}

void MeshConverter::dumpVerterx( char* blob )
{
    uint32_t dumpNum = 6;
    if(dumpNum > m_numVertices) dumpNum = m_numVertices;
    char* vStart = blob;
    for(uint32_t j=0; j<dumpNum; ++j)
    {
        LOGI("Vertex_%d", j);
        for(uint32_t i=0; i<bgfx::Attrib::Count; ++i)
        {
            bgfx::Attrib::Enum attrib = (bgfx::Attrib::Enum)i;
            if(!m_decl.has(attrib))
                continue;
            uint32_t offset = m_decl.getOffset(attrib);
            char* attribData = vStart + offset;
            const VertexDeclData& data = m_declDatas[i];
            if(data.m_attribType == bgfx::AttribType::Float)
            {
                float* pData = (float*)attribData;
                if(data.m_numElements == 2)
                {
                    LOGI("%s: %g,%g", s_attrName[i], pData[0], pData[1]);
                }
                else if (data.m_numElements == 3)
                {
                    LOGI("%s: %g,%g,%g", s_attrName[i], pData[0], pData[1], pData[2]);
                }
                else if (data.m_numElements == 4)
                {
                    LOGI("%s: %g,%g,%g,%g", s_attrName[i], pData[0], pData[1], pData[2], pData[3]);
                }
            }
            else if(data.m_attribType == bgfx::AttribType::Uint8)
            {
                uint8_t* pData = (uint8_t*)attribData;
                if(data.m_numElements == 2)
                {
                    LOGI("%s: %d,%d", s_attrName[i], pData[0], pData[1]);
                }
                else if (data.m_numElements == 3)
                {
                    LOGI("%s: %d,%d,%d", s_attrName[i], pData[0], pData[1], pData[2]);
                }
                else if (data.m_numElements == 4)
                {
                    LOGI("%s: %d,%d,%d,%d", s_attrName[i], pData[0], pData[1], pData[2], pData[3]);
                }
            }
        }
        vStart += getVertexStride();
    }
}
