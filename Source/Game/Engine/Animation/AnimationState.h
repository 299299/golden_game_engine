#pragma once
#include "Prerequisites.h"

struct AnimationTranstion
{
    float               m_duration;
    uint16_t            m_dstStateIndex;
    uint8_t             m_easeType;
    uint8_t             m_motionBlendingType;

};