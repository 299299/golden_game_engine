#pragma once
#include "Entity.h"
#include "Prerequisites.h"
#include "Locomotion.h"

struct ModelInstance;
struct AnimRigInstance;
struct AnimFSMInstance;
struct ProxyInstance;

ENGINE_ALIGN(16) struct Character : public EntityInstance
{
    void start(const hkQsTransform& t);
    void stop();
    void preStep(float dt);
    void postStep(float dt);
    
    Locomotion                          m_locomotion;
    hkVector4                           m_reachWS[2];
    hkVector4                           m_lookAtWS;

    int                                 m_modelIndex;
    int                                 m_animRigIndex;
    int                                 m_animFSMIndex;
    int                                 m_proxyIndex;

    ModelInstance*                      m_model;
    AnimRigInstance*                    m_rig;
    AnimFSMInstance*                    m_animFSM;
    ProxyInstance*                      m_proxy;

private:
    void doSkinning();
    void doRagdoll(float dt);
    void doIK(float dt);
    void applyAnimations(float dt);
    void updateFSM(float dt);
};