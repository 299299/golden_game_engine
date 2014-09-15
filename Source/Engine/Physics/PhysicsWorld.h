#pragma once
#include "Prerequisites.h"
#include "StringId.h"
#include "id_array.h"

#define MAX_PHYSICS     (1024)
#define MAX_PROXY       (64)

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
};

typedef Id PhysicsId;
typedef Id ProxyId;

struct PhysicsWorld
{
    void init(uint32_t maxObjects, uint32_t maxCharacters);
    void quit();

    void frameStart();
    void kickInJobs(float timeStep);
    void tickFinishJobs(float timeStep);

    void createWorld(float worldSize, const hkVector4& gravity, PhysicsConfig* config);
    void destroyWorld();
    void clearWorld();
    inline hkpWorld* getWorld() const { return m_world;};

    void postSimulationCallback();
    int  getContactingRigidBodies(const hkpRigidBody* body, hkpRigidBody** contactingBodies, int maxLen = 100);

    void addToWorld(PhysicsInstance* instance);
    void removeFromWorld(PhysicsInstance* instance);
    
    void addCollisionEvent(uint64_t key, const CollisionEvent& evt);
    int addRaycastJob(const float* from, const float* to, int32_t filterInfo = -1);
    RaycastJob* getRaycastJob(int handle) const;

    int getFilterLayer(const StringId& name) const;
    void createPlane();

    PhysicsId create_physics(const PhysicsResource* resource);
    void      destroy_physics(PhysicsId id);
    PhysicsInstance* get_physics(PhysicsId id);

    ProxyId   create_proxy(const ProxyResource* resource);
    void      destroy_proxy(ProxyId id);
    ProxyInstance*   get_proxy(ProxyId id);


private:
    void updateVDB(float dt);
    void checkStatus();
    void kickInRaycastJob();
public:
    hkpWorld*                               m_world;;
    PhysicsPostSimlator*                    m_postCallback;
    HavokContactListener*                   m_contactListener;
    CollisionEvent**                        m_collisionEvents;
    RaycastJob*                             m_raycasts;
    hkSemaphore*                            m_raycastSem;
    uint32_t                                m_numCollisionEvents;
    uint32_t                                m_numRaycasts;
    int                                     m_status;
    IdArray<MAX_PHYSICS, PhysicsInstance>   m_objects;
    IdArray<MAX_PROXY, ProxyInstance>*      m_proxies;
    //======================================================================
    PhysicsConfig*                          m_config;
};

extern PhysicsWorld g_physicsWorld;