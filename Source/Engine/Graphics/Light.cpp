#include "Light.h"
#include "Resource.h"
#include "Material.h"
#include "Log.h"
#include "DataDef.h"
#include "Graphics.h"
#include "MathDefs.h"

void LightInstance::init(const void* resource)
{
    m_resource = (const LightResource*)resource;
    memcpy(m_color, m_resource->m_color, sizeof(m_color));
    memcpy(m_vec, m_resource->m_dir, sizeof(m_vec));
    addFlag(kNodeTransformDirty);
}

void LightInstance::setTransform(const hkQsTransform& t)
{
    //transform_matrix(m_transform, t);
    if(m_resource->m_type == kLightDirectional)
        return;
    transform_vec3(m_vec, t.m_translation);
    addFlag(kNodeTransformDirty);
}

void LightInstance::setEnabled(bool bEnable)
{
    if(bEnable) removeFlag(kNodeInvisible);
    else addFlag(kNodeInvisible);
}

void LightInstance::update()
{
    if(!HAS_BITS(m_flag, kNodeTransformDirty)) return;
    //
    REMOVE_BITS(m_flag, kNodeTransformDirty);
}

