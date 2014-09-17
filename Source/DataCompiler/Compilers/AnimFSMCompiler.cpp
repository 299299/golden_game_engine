#include "AnimFSMCompiler.h"
#include "DC_Utils.h"
#include "Animation.h"

static const char* motion_blend_names[] = 
{
    "default",
    "ignore source",
    "ignore dest",
    "ignore source rotation",
    "ignore dest rotation",
    0
};

static const char* blend_curve_names[] = 
{
    "smooth",
    "fast",
    "linear",
    0
};

static const char* transition_mode_names[] = 
{
    "smooth",
    "frozen",
    0
};

static const char* state_flag_names[] = 
{
    "in_air",
    "no_adjust_to_ground",
    0
};


struct CompilerState
{
    State*                              m_state;
    std::vector<std::string>            m_animations;
    std::vector<Transition*>            m_transitions;
    std::vector<StringId>               m_transitionTargetNames;
    CompilerState()
    {
        m_state = new State;
    }
    ~CompilerState()
    {
        delete m_state;
        for(size_t i=0; i<m_transitions.size(); ++i)
        {
            delete m_transitions[i];
        }
    }
};

struct CompilerLayer
{
    std::vector<CompilerState>          m_states;
    uint32_t                            m_numAnimations;
    
    int findStateIndex(const StringId& name)
    {
        for(size_t i=0; i<m_states.size();++i)
        {
            if(m_states[i].m_state->m_name == name)
                return i;
        }
        return -1;
    }
};


AnimFSMCompiler::AnimFSMCompiler()
{

}

AnimFSMCompiler::~AnimFSMCompiler()
{
    
}

bool AnimFSMCompiler::readJSON(const JsonValue& root)
{
    __super::readJSON(root);
    uint32_t totalNumState = 0, totalNumTransition = 0, totalNumAnimation = 0;
    std::vector<CompilerLayer> layers;
    JsonValue layersValue = root.GetValue("layers");
    for(uint32_t i=0; i<layersValue.GetElementsCount(); ++i)
    {
        JsonValue layerValue = layersValue[i];
        JsonValue statesValue = layerValue.GetValue("states");
        layers.push_back(CompilerLayer());
        CompilerLayer& layer = layers.back();
        layer.m_numAnimations = 0;
        
        for(uint32_t j=0; j<statesValue.GetElementsCount(); ++j)
        {
            JsonValue stateValue = statesValue[j];
            layer.m_states.push_back(CompilerState());
            CompilerState& state = layer.m_states.back();
            State* pState = state.m_state;
            pState->m_name = JSON_GetStringId(stateValue.GetValue("name"));
            pState->m_speed = JSON_GetFloat(stateValue.GetValue("speed"));
            pState->m_looped = JSON_GetBool(stateValue.GetValue("looped"), true); //default looped.
            pState->m_flags = JSON_GetFlags(stateValue.GetValue("flags"), state_flag_names);
            ++totalNumState;
            
            //collection animations
            JsonValue animationsValue = stateValue.GetValue("animations");
            for(uint32_t k=0; k<animationsValue.GetElementsCount(); ++k)
            {
                state.m_animations.push_back(JSON_GetString(animationsValue[k]));
                ++totalNumAnimation;
            }
            layer.m_numAnimations += state.m_animations.size();
            
            //collection transitions
            JsonValue transitionsValue = stateValue.GetValue("transitions");
            for(uint32_t k=0; k<transitionsValue.GetElementsCount(); ++k)
            {
                JsonValue transitionValue = transitionsValue[k];
                Transition* t = new Transition;
                t->m_event = JSON_GetStringId(transitionValue.GetValue("event"));
                t->m_duration = JSON_GetFloat(transitionValue.GetValue("duration"), 0.2f);
                t->m_motionBlendType = JSON_GetEnum(transitionValue.GetValue("motion_blend_type"), motion_blend_names);
                t->m_blendCurve = JSON_GetEnum(transitionValue.GetValue("blend_curve"), blend_curve_names);
                t->m_mode = JSON_GetEnum(transitionValue.GetValue("mode"), transition_mode_names);
                t->m_beat = JSON_GetStringId(transitionValue.GetValue("beat"));
                state.m_transitions.push_back(t);
                state.m_transitionTargetNames.push_back(JSON_GetStringId(transitionValue.GetValue("to")));
                ++totalNumTransition;
            }    
        }
    }
       
    uint32_t memSize = sizeof(AnimFSM) + totalNumState * sizeof(State) + totalNumAnimation * (sizeof(void*) + sizeof(StringId)) + totalNumTransition * sizeof(Transition);
    LOGI("TOTAL STATES = %d, ANIMATION = %d, TRANSITION = %d, MEMSIZE=%d", totalNumState, totalNumAnimation, totalNumTransition, memSize);

    char* p = (char*)malloc(memSize);
    char* head = p;
    
    AnimFSM* fsm = (AnimFSM*)p;
    fsm->m_numLayers = layers.size();
    fsm->m_numStates = totalNumState;
    fsm->m_numAnimations = totalNumAnimation;
    
    p += sizeof(AnimFSM);
    for(uint32_t i=0; i<fsm->m_numLayers; ++i)
    {
        AnimFSMLayer& layer = fsm->m_layers[i];
        CompilerLayer& in_layer = layers[i];
        layer.m_numStates = in_layer.m_states.size();
        layer.m_numAnimations = in_layer.m_numAnimations;
        
        layer.m_states = (State*)p;
        layer.m_stateOffset = (uint32_t)(p - head);
        p += layer.m_numStates * sizeof(State);
        
        for(uint32_t j=0; j<layer.m_numStates; ++j)
        {
            State& state = layer.m_states[j];
            CompilerState& in_state = in_layer.m_states[j];
            memcpy(&state, in_state.m_state, sizeof(State));
            
            state.m_numTransitions = in_state.m_transitions.size();
            state.m_transitions = (Transition*)p;
            state.m_transitionOffset = (uint32_t)(p - head);
            p += state.m_numTransitions * sizeof(Transition);
            
            for(uint32_t k=0; k<state.m_numTransitions; ++k)
            {
                Transition& t = state.m_transitions[k];
                Transition* in_t = in_state.m_transitions[k];
                memcpy(&t, in_t, sizeof(Transition));
                t.m_destStateIndex = in_layer.findStateIndex(in_state.m_transitionTargetNames[k]);
            }
            
            state.m_numAnimations = in_state.m_animations.size();
            state.m_animations = (Animation**)p;
            state.m_animationOffset = (uint32_t)(p - head);
            p += state.m_numAnimations * sizeof(void*);
            
            state.m_animNames = (StringId*)p;
            state.m_animNameOffset = (uint32_t)(p - head);
            p += state.m_numAnimations * sizeof(StringId);
            
            for(uint32_t k=0; k<state.m_numAnimations; ++k)
            {
                const std::string& animName = in_state.m_animations[k];
                state.m_animNames[k] = StringId(animName.c_str());
                addDependency("animation", name_to_file_path(animName, Animation::getName()));
            }
        }
    }    
    
    HK_ASSERT(0, p == head + memSize);
    bool bRet = write_file(m_output, head, memSize);
    free(head);
    return bRet;
}