#pragma once
#include "Prerequisites.h"
#include "StringId.h"

struct AnimationTranstion
{
    float                       m_duration;
    uint16_t                    m_dstStateIndex;
    uint8_t                     m_easeType;
    uint8_t                     m_motionBlendingType;

};

ENGINE_NATIVE_ALIGN(struct) AnimationState
{
    StringId*                   m_transitionNames;
    AnimationTranstion*         m_transitions;

    AnimationTranstion* find_transition(const StringId& name);
};