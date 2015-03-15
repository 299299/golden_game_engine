#pragma once
#include "StringId.h"

class   hkpEntity;
class   hkpWorld;
class   hkpShape;
class   hkpGroupFilter;
class   hkpPhysicsData;
class   hkpRigidBody;
struct  PhysicsInstance;
struct  PhysicsResource;
struct  ProxyInstance;
struct  ProxyResource;
class   HavokContactListener;
struct  hkpWorldRayCastCommand;
struct  hkpWorldRayCastOutput;
struct  hkpCollisionQueryJobHeader;
class   hkSemaphore;
struct  Actor;
struct  CollisionEvent;
class   hkQsTransformf;

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

ENGINE_NATIVE_ALIGN(struct) PhysicsConfig
{
    CollisionFilter             m_filters[32];
    uint32_t                    m_numFilterLayers;
    float                       m_worldSize;
    float                       m_gravity[3];
};

struct PhysicsWorld
{
    void init(int max_bodies, int max_proxies);
    void shutdown();

    void frame_start();
    void kickin_jobs(float timeStep);
    void tick_finished_jobs();

    void create_world(PhysicsConfig* config);
    void destroy_world();
    void clear_world();
    hkpWorld* world() const { return m_world;};

    int  get_contact_rigidbodies(const hkpRigidBody* body, hkpRigidBody** contactingBodies, int maxLen = 100);

    void add_collision_event(uint64_t key, const CollisionEvent& evt);
    int add_raycast_job(const float* from, const float* to, int filterInfo = -1);
    RaycastJob* get_raycast_job(int handle) const;

    int get_layer(StringId name) const;
    void create_plane(float size);

    void sync_rigidbody_actors(Actor* actors, int num);
    void sync_proxy_actors(Actor* actors, int num);
    void update_character_proxies(float timeStep);

    static void register_factories();

    // check if is not valid for multhread update
    void check_status();
    void set_status(int status);

private:
    void kickin_raycast_jobs();
    void post_simulation();

public:
    hkpWorld*                               m_world;
    HavokContactListener*                   m_contactListener;
    CollisionEvent**                        m_collisionEvents;
    RaycastJob*                             m_raycasts;
    hkSemaphore*                            m_raycastSem;
    int                                     m_numCollisionEvents;
    int                                     m_numRaycasts;
    PhysicsConfig*                          m_config;
    int                                     m_status;
};

extern PhysicsWorld g_physicsWorld;

Id create_physics_object(const void*, ActorId32);
void destroy_physics_object(Id);
void* get_physics_object(Id);
int num_all_physics_object();
void* get_all_physics_object();
void transform_physics_object(Id, const hkQsTransformf&);
void lookup_physics_instance_data(void*);