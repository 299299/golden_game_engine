#include "Texture.h"
#include "Resource.h"
#include "MemorySystem.h"
#include "ShaderInc.h"
#include "Prerequisites.h"


#define DESTROY_TEXTURE(handle) \
        if(bgfx::isValid(handle)) {\
            bgfx::destroyTexture(handle);\
            handle.idx = bgfx::invalidHandle;\
        }


int  bringin_resource_texture(void* resource, uint32_t flags, uint32_t skip)
{
    Texture* tex = (Texture*)resource;
    if(bgfx::isValid(tex->m_handle))
        return 0;
    tex->m_handle = bgfx::createTexture(
        bgfx::makeRef((char*)resource + tex->m_data_offset, tex->m_data_size),
        flags,
        skip,
        &tex->m_info);
    return bgfx::isValid(tex->m_handle) ? 0 : -1;
}

void  bringout_resource_texture(void* resource)
{
    Texture* tex = (Texture*)resource;
    DESTROY_TEXTURE(tex->m_handle);
}

int bringin_resource_texture3d( void* resource )
{
    Texture3D* tex3d = (Texture3D*)resource;
    if(bgfx::isValid(tex3d->m_handle))
        return 0;
    tex3d->m_handle = bgfx::createTexture3D(
        tex3d->m_width,
        tex3d->m_height,
        tex3d->m_depth,
        tex3d->m_num_mips,
        (bgfx::TextureFormat::Enum)tex3d->m_format,
        tex3d->m_flags,
        bgfx::makeRef((char*)resource + tex3d->m_data_offset, tex3d->m_data_size));
    return bgfx::isValid(tex3d->m_handle) ? 0 : -1;
}

void bringout_resource_texture3d( void* resource )
{
    Texture3D* tex3d = (Texture3D*)resource;
    DESTROY_TEXTURE(tex3d->m_handle);
}
