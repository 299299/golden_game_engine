#include "Texture.h"
#include "Resource.h"
#include "MemorySystem.h"
#include "ShaderInc.h"
#include "EngineAssert.h"

void Texture::bringin(uint32_t flags, uint8_t skip)
{
    if(bgfx::isValid(m_handle))
        return;
    m_handle = bgfx::createTexture(bgfx::makeRef(m_blob, m_size), flags, skip, &m_info);
    ENGINE_ASSERT(bgfx::isValid(m_handle), "bgfx::isValid(m_handle)");
}

void Texture::bringout()
{
    if(!bgfx::isValid(m_handle)) 
        return;
    bgfx::destroyTexture(m_handle);
    m_handle.idx = bgfx::invalidHandle;
}

void Raw2DTexture::bringin()
{
    if(bgfx::isValid(m_handle)) 
        return;
    const bgfx::Memory* memory = bgfx::makeRef(m_blob, m_size);
    m_handle = bgfx::createTexture2D(m_width, m_height, m_numMips, (bgfx::TextureFormat::Enum)m_format,m_flags, memory);
    ENGINE_ASSERT(bgfx::isValid(m_handle), "bgfx::isValid(m_handle)");
}

void Raw2DTexture::bringout()
{
    if(!bgfx::isValid(m_handle)) 
        return;
    bgfx::destroyTexture(m_handle);
    m_handle.idx = bgfx::invalidHandle;
}

void Raw3DTexture::bringin()
{
    if(bgfx::isValid(m_handle)) return;
    const bgfx::Memory* memory = bgfx::makeRef(m_blob, m_size);
    m_handle = bgfx::createTexture3D(m_width, m_height, m_depth, m_numMips, (bgfx::TextureFormat::Enum)m_format,m_flags, memory);
    ENGINE_ASSERT(bgfx::isValid(m_handle), "bgfx::isValid(m_handle)");
}

void Raw3DTexture::bringout()
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
    texture->bringout();
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
    tex2d->bringin();
}

void bringout_resource_texture2d( void* resource )
{
    Raw2DTexture* tex2d = (Raw2DTexture*)resource;
    tex2d->bringout();
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
    tex3d->bringin();
}

void bringout_resource_texture3d( void* resource )
{
    Raw3DTexture* tex3d = (Raw3DTexture*)resource;
    tex3d->bringout();
}
