#include "Model.h"
#include "Material.h"
#include "Mesh.h"
#include "Resource.h"
#include "MemorySystem.h"
#include "Log.h"
#include "DataDef.h"
#include "MathDefs.h"
#include "Graphics.h"
#include <bgfx.h>

void ModelInstance::init(const void* resource)
{
    m_visibleThisFrame = true;
    m_resource = (const ModelResource*)resource;
    m_viewId = m_resource->m_viewId;
    m_flag = m_resource->m_flag;
    m_numMaterials = m_resource->m_numMaterials;
    memcpy(m_materials, m_resource->m_materials, m_resource->m_numMaterials*sizeof(void*));
    ADD_BITS(m_flag, kNodeTransformDirty);
	bx::mtxIdentity(m_transform);
}

void ModelInstance::submit()
{
    const Mesh* mesh = m_resource->m_mesh;
    const SubMesh* submeshes = mesh->m_submeshes;
    bool bSkinning = mesh->m_numJoints > 0;
    float* t = bSkinning ? m_skinMatrix : m_transform;
    int num = bSkinning ? mesh->m_numJoints : 1;
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
    const Mesh* mesh = m_resource->m_mesh;
    const SubMesh* submeshes = mesh->m_submeshes;
    bool bSkinning = mesh->m_numJoints > 0;
    float* t = bSkinning ? m_skinMatrix : m_transform;
    int num = bSkinning ? mesh->m_numJoints : 1;

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
    const Mesh* mesh = m_resource->m_mesh;
	const Aabb& modelAabb = mesh->m_aabb;
	transformAabb(m_aabb.m_min, m_aabb.m_max, m_transform, modelAabb.m_min, modelAabb.m_max);
	REMOVE_BITS(m_flag, kNodeTransformDirty);
}

void ModelInstance::allocSkinningMat()
{
    m_skinMatrix = FRAME_ALLOC(float, m_resource->m_mesh->m_numJoints * 16);
}

bool ModelInstance::checkIntersection( 
    const float* rayOrig, 
    const float* rayDir, 
    float* intsPos,
    float* outNormal ) const
{
    if(!rayAABBIntersection(rayOrig, rayDir, m_aabb.m_min, m_aabb.m_max)) 
        return false;

    const Mesh* mesh = m_resource->m_mesh;
    if(!mesh) return false;

    const bgfx::VertexDecl& decl = mesh->m_decl;

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

    for(uint32_t i=0; i<mesh->m_numSubMeshes; ++i)
    {
        const char* vertData = (const char*)mesh->getVertexData(i);
        uint32_t vertNum = mesh->getVertexNum(i);
        const uint16_t* indexData = mesh->getIndexData(i);
        uint32_t indexNum = mesh->getIndexNum(i);
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
    ENGINE_ASSERT(model->m_numMaterials < MAX_MATERIAL_NUM, 
        "Material num = %d > %d", model->m_numMaterials, MAX_MATERIAL_NUM);
    return model;
}

void lookup_resource_model( void * resource )
{
    ModelResource* model = (ModelResource*)resource;
    model->m_mesh = FIND_RESOURCE(Mesh,  model->m_meshName);
    for(uint32_t i=0; i<model->m_numMaterials;++i) 
    {
        model->m_materials[i] = FIND_RESOURCE(Material, m_materialNames[i]);
    }
}

ModelWorld g_modelWorld;
void ModelWorld::init()
{
    reset();
}

void ModelWorld::reset()
{
    m_modelsToDraw = 0;
    m_numModels = 0;
    m_shadowsToDraw = 0;
    m_numShadows = 0;
}

void ModelWorld::update(float dt)
{
    uint32_t numModels = id_array::size(m_models);
    ModelInstance* begin = id_array::begin(m_models);
    for(uint32_t i=0; i<numModels; ++i)
    {
        begin[i].update();
    }
}

void ModelWorld::submit_models()
{
    for(uint32_t i=0; i<m_numModels; ++i)
    {
        m_modelsToDraw[i]->submit();
    }
}

void ModelWorld::submit_shadows()
{
    for(uint32_t i=0; i<m_numShadows; ++i)
    {
        m_shadowsToDraw[i]->submitShadow();
    }
}

ModelId ModelWorld::create_model(const ModelResource* modelResource)
{
    ModelInstance inst;
    inst.init(modelResource);
    return id_array::create(m_models, inst);
}

void ModelWorld::destroy_model(ModelId id)
{
    if(!id_array::has(m_models, id)) return;
    id_array::destroy(m_models, id);
}

ModelInstance* ModelWorld::get_model(ModelId id)
{
    if(!id_array::has(m_models, id)) return 0;
    return &id_array::get(m_models, id);
}

void ModelWorld::cull_models(const Frustum& frust)
{
    uint32_t numModels = id_array::size(m_models);
    m_modelsToDraw = FRAME_ALLOC(ModelInstance*, numModels);
    m_numModels = 0;

    ModelInstance* begin = id_array::begin(m_models);
    for(uint32_t i=0; i<numModels; ++i)
    {
        ModelInstance* model = begin + i;
        if(model->m_flag & kNodeInvisible)
            continue;
        bool bVisible = !frust.cullBox(model->m_aabb.m_min, model->m_aabb.m_max);
        model->m_visibleThisFrame = bVisible;
        if(!bVisible) continue;
        m_modelsToDraw[m_numModels++] = model;
    }
}

void ModelWorld::cull_shadows(const Frustum& lightFrust)
{
    uint32_t numModels = id_array::size(m_models);
    m_shadowsToDraw = FRAME_ALLOC(ModelInstance*, numModels);
    m_numShadows = 0;

    ModelInstance* begin = id_array::begin(m_models);
    for(uint32_t i=0; i<numModels; ++i)
    {
        ModelInstance* model = begin + i;
        uint32_t flag = model->m_flag;
        if(flag & kNodeInvisible) || (flag & kNodeNoShadow) continue;
        bool bVisible = !lightFrust.cullBox(model->m_aabb.m_min, model->m_aabb.m_max);
        if(!bVisible) continue;
        m_shadowsToDraws[m_numShadows++] = model;
    }
}
