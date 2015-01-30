#include "AnimationState.h"


int AnimationState::find_transition(StringId32 name)
{
    StringId32* _names = m_transitionNames;
    int _num = (int)m_numTransitions;
    FIND_IN_ARRAY_RET(_names, _num, name);
}

int AnimationState::find_node(StringId32 name)
{
    StringId32* _names = m_transitionNames;
    int _num = (int)m_numTransitions;
    FIND_IN_ARRAY_RET(_names, _num, name);
}