#pragma once
#include "Prerequisites.h"
#include "StringId.h"


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
    uint16_t                    m_data[2];
    uint8_t                     m_type;
    char                        m_padding[3];
};

ENGINE_NATIVE_ALIGN(struct) AnimationState
{
    uint32_t                    m_numTransitions;
    StringId32*                 m_transitionNames;
    AnimationTranstion*         m_transitions;
    uint32_t                    m_numNodes;
    StringId32*                 m_nodeNames;
    AnimationNode*              m_nodes;

    int                         m_maxCycles;

    int find_transition(StringId32 name);
    int find_node(StringId32 name);
};