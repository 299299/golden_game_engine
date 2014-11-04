#include "Movement.h"
#include "AnimRig.h"
#include "ProxyInstance.h"

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

uint32_t num_movement()
{
    return id_array::size(m_movements);
}

void* get_movements()
{
    return id_array::begin(m_movements);
}


void MovementInstance::init(const void* resource, ActorId32 actor)
{
    m_resource = (const MovementResource*)resource;
    m_actor = actor;
    m_worldVelocity = false;
    m_moveState = m_resource->m_moveState;
    m_targetAngle = 0;
    m_velocity.setZero4();
}

#if 0
void AnimationSystem::apply_animation_rootmotion( Actor* actors, uint32_t num, float dt )
{
    PROFILE(Animation_ApplyRootmotion);
    extern void* get_anim_rig(Id);
    extern void* get_physics_proxy(Id);
    hkQsTransform t;
    for (uint32_t i=0; i<num; ++i)
    {
        Actor& actor = actors[i];
        Id rigId = actor.m_components[kComponentAnimRig];
        Id proxyId = actor.m_components[kComponentProxy];
        AnimRigInstance* rig = (AnimRigInstance*)get_anim_rig(rigId);
        ProxyInstance* proxy = (ProxyInstance*)get_physics_proxy(proxyId);
        if(!proxy||!rig) continue;
        if(!rig->m_applyRootmotion) continue;
        rig->get_rootmotion(dt, t);

        hkQsTransform& transform = proxy->m_transform;
        transform.m_rotation.mul(t.m_rotation);

        hkVector4 desiredMotionWorld;
        hkQuaternion currentOrient;
        desiredMotionWorld.setRotatedDir( transform.m_rotation, t.m_translation );
        proxy->m_targetVelocity.setMul4 (1.0f / dt, desiredMotionWorld );
    }
}
#endif

MovementManager g_moveMgr;
void MovementManager::move_characters(Actor* actors, uint32_t num, float dt)
{
    extern void* get_anim_rig(Id);
    extern void* get_physics_proxy(Id);

    for (uint32_t i = 0; i < num; ++i)
    {
        Actor& actor = actors[i];
        Id* components = actor.m_components;
        ProxyInstance* proxy = (ProxyInstance*)get_physics_proxy(components[kComponentProxy]);
        AnimRig* rig = (AnimRig*)get_anim_rig(components[kComponentAnimRig]);
        MovementInstance* move = (MovementInstance*)get_movement(components[kComponentMovement]);
        if(!proxy || !rig || !move) continue;

        hkVector4 velocity;
        switch(move->m_moveState)
        {
        case kMoveByVelocity:
            {
                if(move->m_worldVelocity)
                {

                }
                break;
            }
        case kMoveByAnimation:
            {

                break;
            }
        case kMoveByVelocityAndAnimation:
            {

                break;
            }
        default:
            break;
        }
    }
}