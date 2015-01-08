#include "Movement.h"
#include "AnimRig.h"
#include "ProxyInstance.h"
#include "Profiler.h"
#include "id_array.h"
#include "Actor.h"

static IdArray<MAX_MOVEMENT_INSTNACE, MovementInstance>      m_movements;

//-----------------------------------------------------------------
//
//-----------------------------------------------------------------
Id create_movement( const void* resource, ActorId32 id)
{
    MovementInstance inst;
    inst.init(resource, id);
    return id_array::create(m_movements, inst);
}

void destroy_movement( Id id )
{
    if(!id_array::has(m_movements, id)) return;
    id_array::destroy(m_movements, id);
}

void* get_movement( Id id )
{
    if(!id_array::has(m_movements, id)) return 0;
    return &id_array::get(m_movements, id);
}

uint32_t num_movements()
{
    return id_array::size(m_movements);
}

void* get_movements()
{
    return id_array::begin(m_movements);
}


void MovementInstance::init(const void* resource, ActorId32 actor)
{
    m_actor = actor;
    m_linearVelocity.setZero4();
    m_motionWeight = 1.0f;
    m_velocityWeight = 1.0f;
    m_rotateSpeed = 0.0f;
}

MovementManager g_moveMgr;
void MovementManager::move_characters(Actor* actors, uint32_t num, float dt)
{
    PROFILE(move_characters);
    extern void* get_anim_rig(Id);
    extern void* get_physics_proxy(Id);

    for (uint32_t i = 0; i < num; ++i)
    {
        Actor& actor = actors[i];
        Id* components = actor.m_components;
        ProxyInstance* proxy = (ProxyInstance*)get_physics_proxy(components[kComponentProxy]);
        AnimRigInstance* rig = (AnimRigInstance*)get_anim_rig(components[kComponentAnimRig]);
        MovementInstance* move = (MovementInstance*)get_movement(components[kComponentMovement]);
        if(!proxy || !rig || !move) continue;

        hkVector4 motion_velocity;
        hkQsTransform& t = proxy->m_transform;
        hkQsTransform motion_transform;
        rig->get_rootmotion(dt, motion_transform);
        t.m_rotation.mul(motion_transform.m_rotation);

        hkQuaternion q;
        q.setAxisAngle(hkVector4(0,1,0), move->m_rotateSpeed*dt);
        t.m_rotation.mul(q);

        hkVector4 desiredMotionWorld;
        desiredMotionWorld.setRotatedDir( t.m_rotation,  motion_transform.m_translation);
        motion_velocity.setMul4 (1.0f / dt, desiredMotionWorld );

        proxy->m_targetVelocity.setMul4(move->m_motionWeight, motion_velocity);

        hkVector4 velocityWorld;
        velocityWorld.setRotatedDir( t.m_rotation,  move->m_linearVelocity);
        proxy->m_targetVelocity.addMul4(move->m_velocityWeight, velocityWorld);
    }
}