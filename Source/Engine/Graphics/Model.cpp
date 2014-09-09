#include "Model.h"
#include "Material.h"
#include "Mesh.h"
#include "Resource.h"
#include "Memory.h"
#include "Log.h"
#include "DataDef.h"
#include "MathDefs.h"
#include "Graphics.h"


void ModelResource::dump()
{
    LOGI("model ---- dump");
    LOGI("model num of material = %d, mesh name = %s", m_numMaterials, stringid_lookup(m_meshName));
    for (uint32_t i=0; i<m_numMaterials; ++i)
    {
        LOGI("material name = %s", stringid_lookup(m_materialNames[i]));
    }
}

void ModelResource::lookup()
{
    m_mesh = FIND_RESOURCE(Mesh,  m_meshName);
    for(uint32_t i=0; i<m_numMaterials;++i) 
    {
        m_materials[i] = FIND_RESOURCE(Material, m_materialNames[i]);
        HK_ASSERT(0, m_materials[i]);
    }
}

void ModelInstance::init(const void* resource)
{
    //LOGI("init model instance resource = 0x%x old = 0x%x", resource, m_resource);
    m_visibleThisFrame = true;
    m_resource = (const ModelResource*)resource;
    m_viewId = m_resource->m_viewId;
    m_mesh = m_resource->m_mesh;
    m_flag = m_resource->m_flag;
    m_numMaterials = m_resource->m_numMaterials;
    memcpy(m_materials, m_resource->m_materials, m_resource->m_numMaterials*sizeof(void*));
    addFlag(kNodeTransformDirty);
	bx::mtxIdentity(m_transform);
}

void ModelInstance::setTransform(const hkQsTransform& t)
{
    transform_matrix(m_transform, t);
    addFlag(kNodeTransformDirty);
}

void ModelInstance::setTransform(const hkTransform& t)
{
    transform_matrix(m_transform, t);
    addFlag(kNodeTransformDirty);
}

void ModelInstance::setEnabled(bool bEnable)
{
    if(bEnable) removeFlag(kNodeInvisible);
    else addFlag(kNodeInvisible);
}


void ModelInstance::submit()
{
    const SubMesh* submeshes = m_mesh->m_submeshes;
    bool bSkinning = m_mesh->m_numJoints > 0;
    float* t = bSkinning ? m_skinMatrix : m_transform;
    int num = bSkinning ? m_mesh->m_numJoints : 1;
    uint8_t viewId = m_viewId;

    for (uint32_t i=0; i<m_numMaterials; ++i)
    {
        bgfx::setTransform(t, num);
        m_materials[i]->submit();
        submeshes[i].submit();
        bgfx::submit(viewId);
    }
}

void ModelInstance::submitShadow()
{
    const SubMesh* submeshes = m_mesh->m_submeshes;
    bool bSkinning = m_mesh->m_numJoints > 0;
    float* t = bSkinning ? m_skinMatrix : m_transform;
    int num = bSkinning ? m_mesh->m_numJoints : 1;

    for (uint32_t i=0; i<m_numMaterials; ++i)
    {
        bgfx::setTransform(t, num);
        m_materials[i]->submitShadow();
        submeshes[i].submit();
        bgfx::submit(kShadowViewId);
    }
}

void ModelInstance::update()
{
	if(!HAS_BITS(m_flag, kNodeTransformDirty)) return;
	const Aabb& modelAabb = m_mesh->m_aabb;
	transformAabb(m_aabb.m_min, m_aabb.m_max, m_transform, modelAabb.m_min, modelAabb.m_max);
	REMOVE_BITS(m_flag, kNodeTransformDirty);
}

void ModelInstance::allocSkinningMat()
{
    m_skinMatrix = FRAME_ALLOC(float, m_mesh->m_numJoints * 16);
}

bool ModelInstance::checkIntersection( 
    const float* rayOrig, 
    const float* rayDir, 
    float* intsPos,
    float* outNormal ) const
{
    if(!rayAABBIntersection(rayOrig, rayDir, m_aabb.m_min, m_aabb.m_max)) 
        return false;

    if(!m_mesh) return false;

    const bgfx::VertexDecl& decl = m_mesh->m_decl;

    // Transform ray to local space
    float invm[16];
    bx::mtxInverse(invm, m_transform);
    float orig[3], dir[3], od[3], dir1[3];
    bx::vec3Add(od, orig, dir);
    bx::vec3MulMtx(orig, rayOrig, invm);
    bx::vec3MulMtx(dir1, od, invm);
    bx::vec3Sub(dir, dir1, orig);
    float nearestIntsPos[3] = { MAX_FLOAT, MAX_FLOAT, MAX_FLOAT };
    bool intersection = false;

    float tmpPos[3];
    float tmpNormal[3];
    float vert0[3], vert1[3], vert2[3];

    uint16_t posOffset = decl.getOffset(bgfx::Attrib::Position);
    uint32_t posSize = sizeof(float) * 3;

    for(uint32_t i=0; i<m_mesh->m_numSubMeshes; ++i)
    {
        const char* vertData = (const char*)m_mesh->getVertexData(i);
        uint32_t vertNum = m_mesh->getVertexNum(i);
        const uint16_t* indexData = m_mesh->getIndexData(i);
        uint32_t indexNum = m_mesh->getIndexNum(i);
        for( uint32_t j = 0; j < indexNum; j += 3 )
        {
            uint16_t index0 = indexData[j + 0];
            uint16_t index1 = indexData[j + 1];
            uint16_t index2 = indexData[j + 2];
            memcpy(vert0, vertData + decl.getStride() * index0 + posOffset, sizeof(vert0));
            memcpy(vert1, vertData + decl.getStride() * index1 + posOffset, sizeof(vert1));
            memcpy(vert2, vertData + decl.getStride() * index2 + posOffset, sizeof(vert2));
            if(rayTriangleIntersection( orig, dir, vert0, vert1, vert2, tmpPos))
            {
                intersection = true;
                float sub1[3], sub2[3];
                bx::vec3Sub(sub1, tmpPos, orig);
                bx::vec3Sub(sub2, tmpPos, orig);
                if(bx::vec3Length(sub1) < bx::vec3Length(sub2))
                {
                    bx::vec3Move(nearestIntsPos, tmpPos);
                    float plane[4];
                    bx::calcPlane(plane, vert0, vert1, vert2);
                    bx::vec3Move(tmpNormal, plane);
                }
            }
        }
    }

    bx::vec3MulMtx(intsPos, nearestIntsPos, m_transform);
    bx::vec3MulMtx(outNormal, tmpNormal, m_transform);
    return intersection;
}

void* load_resource_model(const char* data, uint32_t size)
{
    ModelResource* model = (ModelResource*)data;
    //LOGI("load resource model = 0x%x", data);
    HK_ASSERT(0, model->m_numMaterials < MAX_MATERIAL_NUM);
#ifdef DUMP_RESOURCE
    model->dump();
#endif
    return model;
}

void lookup_resource_model( void * resource )
{
    ModelResource* model = (ModelResource*)resource;
    model->lookup();
}
