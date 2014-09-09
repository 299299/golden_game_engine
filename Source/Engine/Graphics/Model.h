#pragma once
#include "Prerequisites.h"
#include "StringId.h"
#include "MathDefs.h"
#include <bgfx.h>

struct Material;
struct Mesh;

#define MAX_MATERIAL_NUM        (8)

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

    void lookup();
    void dump();
};

struct ModelInstance
{
    float                           m_transform[16];
    Aabb                            m_aabb;
    Material*                       m_materials[MAX_MATERIAL_NUM];
    ID                              m_id;
    float*                          m_skinMatrix;
    const Mesh*                     m_mesh;
    
    const ModelResource*            m_resource;
    
    uint8_t                         m_numMaterials;
    uint8_t                         m_flag;
    uint8_t                         m_viewId;
    bool                            m_visibleThisFrame;

    //=====================================================================
    void init(const void* resource);
    void destroy() {};
    void setTransform(const hkQsTransform& t);
    void setTransform(const hkTransform& t);
    void setEnabled(bool bEnable);
    //======================================================================

    void submit();
    void submitShadow();

    void update();

    inline void addFlag(uint32_t flag) { ADD_BITS(m_flag, flag); };
    inline void removeFlag(uint32_t flag) { REMOVE_BITS(m_flag, flag); };

    void allocSkinningMat();
    bool checkIntersection( const float* rayOrig, 
                            const float* rayDir, 
                            float* intsPos,
                            float* outNormal ) const;
};

void* load_resource_model(const char* data, uint32_t size);
void  lookup_resource_model(void * resource);
