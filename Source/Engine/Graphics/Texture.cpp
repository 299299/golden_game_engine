#include "Texture.h"
#include "Resource.h"
#include "Memory.h"
#include "ShaderInc.h"
#include <string.h>

void Texture::bringIn(uint32_t flags, uint8_t skip)
{
    if(bgfx::isValid(m_handle))
        return;
    m_handle = bgfx::createTexture(bgfx::makeRef(m_blob, m_size), flags, skip, &m_info);
    HK_ASSERT(0, bgfx::isValid(m_handle));
}

void Texture::bringOut()
{
    if(!bgfx::isValid(m_handle)) 
        return;
    bgfx::destroyTexture(m_handle);
    m_handle.idx = bgfx::invalidHandle;
}

void Raw2DTexture::bringIn()
{
    if(bgfx::isValid(m_handle)) 
        return;
    const bgfx::Memory* memory = bgfx::makeRef(m_blob, m_size);
    m_handle = bgfx::createTexture2D(m_width, m_height, m_numMips, (bgfx::TextureFormat::Enum)m_format,m_flags, memory);
    HK_ASSERT(0, bgfx::isValid(m_handle));
}

void Raw2DTexture::bringOut()
{
    if(!bgfx::isValid(m_handle)) 
        return;
    bgfx::destroyTexture(m_handle);
    m_handle.idx = bgfx::invalidHandle;
}

void Raw3DTexture::bringIn()
{
    if(bgfx::isValid(m_handle)) return;
    const bgfx::Memory* memory = bgfx::makeRef(m_blob, m_size);
    m_handle = bgfx::createTexture3D(m_width, m_height, m_depth, m_numMips, (bgfx::TextureFormat::Enum)m_format,m_flags, memory);
    HK_ASSERT(0, bgfx::isValid(m_handle));
}

void Raw3DTexture::bringOut()
{
    if(!bgfx::isValid(m_handle)) 
        return;
    bgfx::destroyTexture(m_handle);
    m_handle.idx = bgfx::invalidHandle;
}

void* load_resource_texture(const char* data, uint32_t size)
{
    Texture* texture = (Texture*)data;
    texture->m_blob = (char*)data + sizeof(Texture);
    return texture;
}

void  bringout_resource_texture(void* resource)
{
    Texture* texture = (Texture*)resource;
    texture->bringOut();
}

void* load_resource_texture2d( const char* data, uint32_t size)
{
    Raw2DTexture* tex = (Raw2DTexture*)data;
    tex->m_blob = (char*)data + sizeof(Raw2DTexture);
    return tex;
}

void bringin_resource_texture2d( void* resource )
{
    Raw2DTexture* tex2d = (Raw2DTexture*)resource;
    tex2d->bringIn();
}

void bringout_resource_texture2d( void* resource )
{
    Raw2DTexture* tex2d = (Raw2DTexture*)resource;
    tex2d->bringOut();
}

void* load_resource_texture3d( const char* data, uint32_t size)
{
    Raw3DTexture* tex = (Raw3DTexture*)data;
    tex->m_blob = (char*)data + sizeof(Raw3DTexture);
    return tex;
}

void bringin_resource_texture3d( void* resource )
{
    Raw3DTexture* tex3d = (Raw3DTexture*)resource;
    tex3d->bringIn();
}

void bringout_resource_texture3d( void* resource )
{
    Raw3DTexture* tex3d = (Raw3DTexture*)resource;
    tex3d->bringOut();
}
