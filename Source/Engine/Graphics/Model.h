#pragma once
#include "BaseTypes.h"
#include "StringId.h"
#include "id_array.h"

struct Material;
struct Mesh;
struct Frustum;

#define MAX_MATERIAL_NUM        (8)
#define MAX_MODELS              (1024)

ENGINE_NATIVE_ALIGN struct ModelResource
{
    DECLARE_RESOURCE(model);

    Material*                      m_materials[MAX_MATERIAL_NUM];
    StringId                       m_materialNames[MAX_MATERIAL_NUM];
    Mesh*                          m_mesh;
    StringId                       m_meshName;
    
    uint8_t                        m_numMaterials;
    uint8_t                        m_viewId;
    uint8_t                        m_flag;
    char                           m_padding[1];
};

struct ModelInstance
{
    float                           m_transform[16];
    Aabb                            m_aabb;
    Material*                       m_materials[MAX_MATERIAL_NUM];
    float*                          m_skinMatrix;
    const ModelResource*            m_resource;
    
    uint8_t                         m_numMaterials;
    uint8_t                         m_flag;
    uint8_t                         m_viewId;
    bool                            m_visibleThisFrame;

    void init(const void* resource);
    void submit();
    void submitShadow();

    void update();
    void allocSkinningMat();
    bool checkIntersection( const float* rayOrig, 
                            const float* rayDir, 
                            float* intsPos,
                            float* outNormal ) const;
};

typedef Id ModelId;
struct ModelWorld
{
    void                    init();
    void                    update(float dt);
    void                    sumibt_models();
    void                    submit_shadows();
    ModelId                 create_model(const ModelResource* modelResource);
    void                    destroy_model(ModelId id);
    ModelInstance*          get_model(ModelId id);

    void                    cull_models(const Frustum& frust);
    void                    cull_shadows(const Frustum& lightFrust);

    IdArray<MAX_MODELS, ModelInstance>      m_models;
    ModelInstance**                         m_modelsToDraw;
    uint32_t                                m_numModels;
    ModelInstance**                         m_shadowsToDraw;
    uint32_t                                m_numShadows;

private:
    void                    reset();
};

extern ModelWorld g_modelWorld;