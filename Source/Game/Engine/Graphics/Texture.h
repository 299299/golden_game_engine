#pragma once
#include "StringId.h"
#include <bgfx.h>

struct Texture
{
    bgfx::TextureInfo           m_info;
    uint32_t                    m_data_offset;
    uint32_t                    m_data_size;

    bgfx::TextureHandle         m_handle;
};

struct Texture3D
{
    uint32_t                    m_data_offset;
    uint32_t                    m_data_size;
    uint32_t                    m_flags;

    uint16_t                    m_width;
    uint16_t                    m_height;

    bgfx::TextureHandle         m_handle;
    uint8_t                     m_depth;
    uint8_t                     m_format;

    uint8_t                     m_num_mips;
};


int   bringin_resource_texture(void* resource, uint32_t flags, uint32_t skip = 0);
void* load_resource_texture(void* data, uint32_t size);
void  bringout_resource_texture(void* resource);

void* load_resource_texture3d( void* data, uint32_t size);
int  bringin_resource_texture3d( void* resource );
void bringout_resource_texture3d( void* resource );
