#pragma once
#include "BaseTypes.h"
#include "StringId.h"
#include "GameConfig.h"
#include "MathDefs.h"

struct Material;
struct Mesh;
struct Frustum;
class hkQsTransformf;

struct Model
{
    float                           m_transform[16];
    Aabb                            m_aabb;
    StringId                        m_materialNames[MAX_MATERIAL_NUM];
    Material*                       m_materials[MAX_MATERIAL_NUM];
    Mesh*                           m_mesh;
    StringId                        m_meshName;

    float*                          m_skinMatrix;

    uint8_t                         m_numMaterials;
    uint8_t                         m_flag;
    uint8_t                         m_viewId;
    bool                            m_visibleThisFrame;

    void submit();
    void submit_shadow();

    void update();
    float* alloc_skinning_mat();
    bool check_intersection( const float* rayOrig,
                            const float* rayDir,
                            float* intsPos,
                            float* outNormal ) const;
};

struct ModelWorld
{
    void                    init(int max_model);
    void                    shutdown();

    void                    update(float dt);
    void                    submit_models();
    void                    submit_shadows();
    void                    cull_models(const Frustum& frust);
    void                    cull_shadows(const Frustum& lightFrust);

    Model**                 m_modelsToDraw;
    uint32_t                m_numModels;
    Model**                 m_shadowsToDraw;
    uint32_t                m_numShadows;

private:
    void                    reset();
};

extern ModelWorld g_modelWorld;

void lookup_model_instance_data( void * );
Id create_model(const void*, ActorId32);
void destroy_model(Id);
void* get_model(Id);
uint32_t num_all_model();
void* get_all_model();
void transform_model(Id, const hkQsTransformf&);