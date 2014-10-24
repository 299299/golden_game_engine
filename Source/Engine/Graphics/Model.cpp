#include "Model.h"
#include "Material.h"
#include "Mesh.h"
#include "Resource.h"
#include "MemorySystem.h"
#include "Log.h"
#include "DataDef.h"
#include "MathDefs.h"
#include "Graphics.h"
#include "id_array.h"
#include "config.h"
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

    uint32_t mat_num = m_numMaterials;
    Material** head = m_materials;

    for (uint32_t i=0; i<mat_num; ++i)
    {
        bgfx::setTransform(t, num);
        head[i]->submit();
        submeshes[i].submit();
        bgfx::submit(viewId);
    }
}

void ModelInstance::submit_shadow()
{
    const Mesh* mesh = m_resource->m_mesh;
    const SubMesh* submeshes = mesh->m_submeshes;
    bool bSkinning = mesh->m_numJoints > 0;
    float* t = bSkinning ? m_skinMatrix : m_transform;
    int num = bSkinning ? mesh->m_numJoints : 1;

    uint32_t mat_num = m_numMaterials;
    Material** head = m_materials;

    for (uint32_t i=0; i<mat_num; ++i)
    {
        bgfx::setTransform(t, num);
        head[i]->submit_shadow();
        submeshes[i].submit();
        bgfx::submit(kShadowViewId);
    }
}

void ModelInstance::update()
{
	if(!HAS_BITS(m_flag, kNodeTransformDirty)) return;
    const Mesh* mesh = m_resource->m_mesh;
	const Aabb& modelAabb = mesh->m_aabb;
	transform_aabb(m_aabb.m_min, m_aabb.m_max, m_transform, modelAabb.m_min, modelAabb.m_max);
	REMOVE_BITS(m_flag, kNodeTransformDirty);
}

float* ModelInstance::alloc_skinning_mat()
{
    m_skinMatrix = FRAME_ALLOC(float, m_resource->m_mesh->m_numJoints * 16);
    return m_skinMatrix;
}

bool ModelInstance::check_intersection( const float* rayOrig, 
                                        const float* rayDir, 
                                        float* intsPos,
                                        float* outNormal ) const
{
    if(!ray_aabb_intersection(rayOrig, rayDir, m_aabb.m_min, m_aabb.m_max)) 
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

    uint32_t num = mesh->m_numSubMeshes;

    for(uint32_t i=0; i<num; ++i)
    {
        const char* vertData = (const char*)mesh->get_vertex_data(i);
        uint32_t vertNum = mesh->get_vertex_num(i);
        const uint16_t* indexData = mesh->get_index_data(i);
        uint32_t indexNum = mesh->get_index_num(i);
        for( uint32_t j = 0; j < indexNum; j += 3 )
        {
            uint16_t index0 = indexData[j + 0];
            uint16_t index1 = indexData[j + 1];
            uint16_t index2 = indexData[j + 2];
            memcpy(vert0, vertData + decl.getStride() * index0 + posOffset, sizeof(vert0));
            memcpy(vert1, vertData + decl.getStride() * index1 + posOffset, sizeof(vert1));
            memcpy(vert2, vertData + decl.getStride() * index2 + posOffset, sizeof(vert2));
            if(ray_triangle_intersection( orig, dir, vert0, vert1, vert2, tmpPos))
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

void lookup_resource_model( void * resource )
{
    ModelResource* model = (ModelResource*)resource;
    model->m_mesh = FIND_RESOURCE(Mesh,  model->m_meshName);
    uint32_t num = model->m_numMaterials;
    Material** head = model->m_materials;
    StringId* matNames = model->m_materialNames;
    for(uint32_t i=0; i<num;++i) 
    {
        head[i] = FIND_RESOURCE(Material, matNames[i]);
    }
}

ModelWorld g_modelWorld;
static IdArray<MAX_MODELS, ModelInstance>      m_models;

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
    uint32_t num = id_array::size(m_models);
    ModelInstance* begin = id_array::begin(m_models);
    for(uint32_t i=0; i<num; ++i)
    {
        begin[i].update();
    }
}

void ModelWorld::submit_models()
{
    uint32_t num = m_numModels;
    ModelInstance** head = m_modelsToDraw;

    for(uint32_t i=0; i<num; ++i)
    {
        head[i]->submit();
    }
}

void ModelWorld::submit_shadows()
{
    uint32_t num = m_numShadows;
    ModelInstance** head = m_shadowsToDraw;

    for(uint32_t i=0; i<num; ++i)
    {
        head[i]->submit_shadow();
    }
}

void ModelWorld::cull_models(const Frustum& frust)
{
    uint32_t numModels = id_array::size(m_models);
    m_modelsToDraw = FRAME_ALLOC(ModelInstance*, numModels);

    ModelInstance* begin = id_array::begin(m_models);
    ModelInstance** head = m_modelsToDraw;
    uint32_t num = 0;

    for(uint32_t i=0; i<numModels; ++i)
    {
        ModelInstance* model = begin + i;
        if(model->m_flag & kNodeInvisible) continue;
        bool bVisible = !frust.cull_box(model->m_aabb.m_min, model->m_aabb.m_max);
        model->m_visibleThisFrame = bVisible;
        if(!bVisible) continue;
        head[num++] = model;
    }
    m_numModels = num;
}

void ModelWorld::cull_shadows(const Frustum& lightFrust)
{
    uint32_t numModels = id_array::size(m_models);
    m_shadowsToDraw = FRAME_ALLOC(ModelInstance*, numModels);

    ModelInstance* begin = id_array::begin(m_models);
    ModelInstance** head = m_shadowsToDraw;
    uint32_t num = 0;

    for(uint32_t i=0; i<numModels; ++i)
    {
        ModelInstance* model = begin + i;
        uint32_t flag = model->m_flag;
        if((flag & kNodeInvisible) || (flag & kNodeNoShadow))
            continue;
        bool bVisible = !lightFrust.cull_box(model->m_aabb.m_min, model->m_aabb.m_max);
        if(!bVisible) continue;
        head[num++] = model;
    }

    m_numShadows = num;
}

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
Id create_render_model(const void* modelResource, ActorId32)
{
    ModelInstance inst;
    memset(&inst, 0x00, sizeof(inst));
    inst.init(modelResource);
    return id_array::create(m_models, inst);
}

void destroy_render_model(Id id)
{
    if(!id_array::has(m_models, id)) return;
    id_array::destroy(m_models, id);
}

void* get_render_model(Id id)
{
    if(!id_array::has(m_models, id)) return 0;
    return &id_array::get(m_models, id);
}

uint32_t num_render_models()
{
    return id_array::size(m_models);
}

void* get_render_models()
{
    return id_array::begin(m_models);
}


#include "DebugDraw.h"
void draw_debug_models()
{
    uint32_t num = id_array::size(m_models);
    ModelInstance* models = id_array::begin(m_models);
    for (uint32_t i=0; i<num; ++i)
    {
        const Aabb& aabb = models[i].m_aabb;
        g_debugDrawMgr.add_aabb(aabb.m_min, aabb.m_max, RGBA(0,255,0,255), true);
    }
}
//-----------------------------------------------------------------
//
//-----------------------------------------------------------------