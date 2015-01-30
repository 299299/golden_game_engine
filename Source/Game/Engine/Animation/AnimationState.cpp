#include "AnimationState.h"


int AnimationState::find_transition(StringId name)
{
    StringId* _names = m_transitionNames;
    int _num = (int)m_numTransitions;
    FIND_IN_ARRAY_RET(_names, _num, name);
}

int AnimationState::find_node(StringId name)
{
    StringId* _names = m_transitionNames;
    int _num = (int)m_numTransitions;
    FIND_IN_ARRAY_RET(_names, _num, name);
}

int AnimationStateLayer::find_state(StringId name)
{
    StringId* _names = m_stateNames;
    int _num = (int)m_numStates;
    FIND_IN_ARRAY_RET(_names, _num, name);
}



void AnimationLayerInstance::init(const void* resource, ActorId32 id)
{

}

void AnimationLayerInstance::update(float dt)
{

}

void AnimationLayerInstance::destroy()
{

}