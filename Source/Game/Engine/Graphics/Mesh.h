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

    uint32_t                        m_vertex_offset;
    uint32_t                        m_vertex_size;
    uint32_t                        m_index_offset;
    uint32_t                        m_index_size;
};

ENGINE_NATIVE_ALIGN(struct) Mesh
{
    bgfx::VertexDecl                m_decl;
    Aabb                            m_aabb;

    uint32_t                        m_memory_size;
    uint32_t                        m_submesh_offset;
    uint32_t                        m_joint_offset;

    uint8_t                         m_num_submeshes;
    uint8_t                         m_num_joints;
    char                            m_padding[2];
};


int   bringin_resource_mesh(void* resource);
void  bringout_resource_mesh(void* resource);

uint32_t get_mesh_vertex_num(const Mesh* mesh, uint32_t index);
const void* get_mesh_vertex_data(const Mesh* mesh, uint32_t index);
uint32_t get_mesh_index_num(const Mesh* mesh, uint32_t index);
const uint16_t* get_mesh_index_data(const Mesh* mesh, uint32_t index);
void submit_submesh(const SubMesh* submesh);