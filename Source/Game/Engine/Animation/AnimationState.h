#pragma once
#include "Prerequisites.h"
#include "StringId.h"

struct Animation;
struct hk_anim_ctrl;

struct BlendNodeType
{
    enum
    {
        Undefined = -1,
        Value,
        Lerp,
        Additive
    };
};

struct AnimationTranstion
{
    float                       m_duration;
    uint16_t                    m_dstStateIndex;
    uint8_t                     m_easeType;
    uint8_t                     m_motionBlendingType;

};

struct AnimationNode
{
    // animation node, data = animtion index in state layer
    // blend nod, data[0] = left child, data[1] = right child
    uint16_t                    m_data[2];
    uint8_t                     m_type;
    char                        m_padding[3];
};

struct AnimationState
{
    uint32_t                    m_numTransitions;
    StringId*                   m_transitionNames;
    AnimationTranstion*         m_transitions;
    uint32_t                    m_numNodes;
    StringId*                   m_nodeNames;
    AnimationNode*              m_nodes;

    int                         m_maxCycles;

    int find_transition(StringId name);
    int find_node(StringId name);
};

struct AnimationData
{
    StringId                    m_name;
    Animation*                  m_animation;
};

ENGINE_NATIVE_ALIGN(struct) AnimationStateLayer
{
    DECLARE_RESOURCE(states);

    uint32_t                    m_numStates;
    StringId*                   m_stateNames;
    AnimationState*             m_states;

    uint32_t                    m_numAnimations;
    AnimationData*              m_animations;

    uint32_t                    m_instanceMemorySize;

    int find_state(StringId name);
};


struct AnimationStateInstance
{

};

struct AnimationLayerInstance
{
    const AnimationStateLayer*   m_resource;
    int                          m_curState;

    void init(const void* resource, ActorId32 id);
    void update(float dt);
    void destroy();
};