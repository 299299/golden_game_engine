#include "Prop.h"
#include "Component.h"
#include "MathDefs.h"
#include "Model.h"
#include "Scene.h"
#include "PhysicsInstance.h"
#include "PhysicsWorld.h"
#include "PhysicsAutoLock.h"

void Prop::start(const hkQsTransform& t)
{
    m_transform = t;
    m_modelIndex = getFirstCompIndexTypeOf(ModelResource::getType());
    m_physicsIndex = getFirstCompIndexTypeOf(PhysicsResource::getType());
    ModelInstance* model = (ModelInstance*)getComponent(m_modelIndex);
    if(model) transform_matrix(model->m_transform, t);
}

void Prop::stop()
{
}

void Prop::preStep( float dt )
{
    m_model = (ModelInstance*)getComponent(m_modelIndex);
    m_physics = (PhysicsInstance*)getComponent(m_physicsIndex);
}

void Prop::postStep( float dt )
{
    if(!m_physics || !m_model) return;
    hkTransform t;
    PHYSICS_LOCKREAD(g_physicsWorld.getWorld());
    for (uint32_t i = 0; i < m_physics->m_numData; ++i)
    {
        if(!m_physics || !m_physics->m_dirty) continue;
        m_physics->fetchTransform(0, t);
        m_model->setTransform(t);
    }
}


