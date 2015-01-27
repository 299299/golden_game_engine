#pragma once
#include "StringId.h"
#include <bgfx.h>

ENGINE_NATIVE_ALIGN(struct) Texture
{
    DECLARE_RESOURCE(texture);

    void bringin(uint32_t flags, uint8_t skip = 0);
    void bringout();

    bgfx::TextureHandle         m_handle;
    bgfx::TextureInfo           m_info;
    char*                       m_blob;
    uint32_t                    m_size;
};

ENGINE_NATIVE_ALIGN(struct) Raw2DTexture
{
    DECLARE_RESOURCE(texture_2d);

    void bringin();
    void bringout();

    char*                       m_blob;
    uint32_t                    m_size;
    uint32_t                    m_flags;

    uint16_t                    m_width;
    uint16_t                    m_height;

    bgfx::TextureHandle         m_handle;
    uint8_t                     m_format;
    uint8_t                     m_numMips;
};

ENGINE_NATIVE_ALIGN(struct) Raw3DTexture
{
    DECLARE_RESOURCE(texture_3d);

    void bringin();
    void bringout();

    char*                       m_blob;
    uint32_t                    m_size;
    uint32_t                    m_flags;

    uint16_t                    m_width;
    uint16_t                    m_height;

    bgfx::TextureHandle         m_handle;
    uint8_t                     m_depth;
    uint8_t                     m_format;

    uint8_t                     m_numMips;
    char                        m_padding[3];
};
