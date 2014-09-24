#pragma once
#include "Prerequisites.h"
#include "StringId.h"

class   hkpEntity;
class   hkpWorld;
class   hkpShape;
class   hkpGroupFilter;
class   hkpPhysicsData;
class   hkpRigidBody;
class   PhysicsPostSimlator;
struct  PhysicsInstance;
struct  PhysicsResource;
struct  ProxyInstance;
struct  ProxyResource;
class   HavokContactListener;
struct  hkpWorldRayCastCommand;
struct  hkpWorldRayCastOutput;
struct  hkpCollisionQueryJobHeader;
class   hkSemaphore;

struct CollisionEvent
{
    PhysicsInstance*            m_objects[2];
    float                       m_normal[3];
    float                       m_position[3];
    float                       m_velocity;
};

struct RaycastJob
{
    float                       m_from[3];
    float                       m_to[3];
    int                         m_filterInfo;
    hkpWorldRayCastOutput*      m_output;
    hkpWorldRayCastCommand*     m_command;
};

struct CollisionFilter
{
    StringId                    m_name;
    uint32_t                    m_mask;
};

struct PhysicsConfig
{
    DECLARE_RESOURCE(physics_config);
    
    CollisionFilter             m_filters[32];
    uint32_t                    m_numFilterLayers;
    float                       m_worldSize;
    float                       m_gravity[3];
};

struct PhysicsWorld
{
    void init();
    void quit();

    void frame_start();
    void kick_in_jobs(float timeStep);
    void tick_finished_jobs();

    void create_world(PhysicsConfig* config);
    void destroy_world();
    void clear_world();
    hkpWorld* world() const { return m_world;};

    int  get_contact_rigidbodies(const hkpRigidBody* body, hkpRigidBody** contactingBodies, int maxLen = 100);

    void add_to_world(PhysicsInstance* instance);
    void remove_from_world(PhysicsInstance* instance);
    
    void add_collision_event(uint64_t key, const CollisionEvent& evt);
    int add_raycast_job(const float* from, const float* to, int32_t filterInfo = -1);
    RaycastJob* get_raycast_job(int handle) const;

    int get_layer(const StringId& name) const;
    void create_plane(float size);

    void sync_actors(struct Actor* actors, uint32_t num);

private:
    void kickin_raycast_jobs();
    void post_simulation();

public:
    hkpWorld*                               m_world;
    HavokContactListener*                   m_contactListener;
    CollisionEvent**                        m_collisionEvents;
    RaycastJob*                             m_raycasts;
    hkSemaphore*                            m_raycastSem;
    uint32_t                                m_numCollisionEvents;
    uint32_t                                m_numRaycasts;
    //======================================================================
    PhysicsConfig*                          m_config;
};

extern PhysicsWorld g_physicsWorld;