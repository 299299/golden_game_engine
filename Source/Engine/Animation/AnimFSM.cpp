#include "AnimFSM.h"
#include "Animation.h"
#include "Resource.h"
#include "Log.h"
//========================================================================================
#include <Animation/Animation/Playback/hkaAnimatedSkeleton.h>
#include <Animation/Animation/Playback/Control/Default/hkaDefaultAnimationControl.h>
//========================================================================================

#define TRIGGER_WEIGHT_THRESHOLD            (0.1f)
#define BEAT_TIME_THRESHOLD                 (1.0f/60.0f)

//==========================================================================================
//      STATE
//==========================================================================================
const Transition* State::findTransition(const StringId& name) const
{
    for(uint32_t i=0; i<m_numTransitions; ++i)
    {
        const Transition& t = m_transitions[i];
        if(t.m_event == name)
            return &t;
    }
    return 0;
}

void State::lookup()
{
    for(uint32_t i=0; i<m_numAnimations; ++i)
    {
        m_animations[i] = FIND_RESOURCE(Animation, m_animNames[i]);
    }
}

hk_anim_ctrl* State::create_anim_ctrl(uint32_t index) const
{
    const Animation* anim = m_animations[index];
    return new hk_anim_ctrl(anim->m_binding, false, m_looped ? -1 : 1);
}

//==========================================================================================
//     ANIM_FSM_LAYER
//==========================================================================================
void AnimFSMLayer::lookup()
{
    for(uint32_t i=0; i<m_numStates; ++i)
    {
        m_states[i].lookup();
    }
}


const State* AnimFSMLayer::findState( StringId name ) const
{
    for(uint32_t i=0; i<m_numStates; ++i)
    {
        const State& state = m_states[i];
        if(state.m_name == name)
            return &state;
    }
    return 0;
}

//==========================================================================================
//      ANIM_FSM
//==========================================================================================
void AnimFSM::lookup()
{
    for(uint32_t i=0; i<m_numLayers; ++i)
    {
        m_layers[i].lookup();
    }
}

//==========================================================================================
//      RESOURCE
//==========================================================================================
void* load_resource_anim_fsm(const char* data, uint32_t size)
{
    AnimFSM* fsm = (AnimFSM*)data;
    for(uint32_t i=0; i<fsm->m_numLayers; ++i)
    {
        AnimFSMLayer& layer = fsm->m_layers[i];
        layer.m_states = (State*)(data + layer.m_stateOffset);
        for(uint32_t j=0; j<layer.m_numStates; ++j)
        {
            State& state = layer.m_states[j];
            state.m_animNames = (StringId*)(data + state.m_animNameOffset);
            state.m_transitions = (Transition*)(data + state.m_transitionOffset);
            state.m_animations = (Animation**)(data + state.m_animationOffset);
        }
    }
    return fsm;
}

void  lookup_resource_anim_fsm(void* resource)
{
    AnimFSM* fsm = (AnimFSM*)resource;
    fsm->lookup();
}

//==========================================================================================
//      ANIM_FSM_RUNTIME
//==========================================================================================
static Transition defaultTransition = 
{
    0.2f,
    StringId::ZERO,
    StringId::ZERO,
    0,
    0,
    0,
    0,
};

static void setEaseCurves(hk_anim_ctrl* ac, uint32_t curve_type)
{
    switch(curve_type)
    {
    case kBlendCurveSmooth:
        ac->setEaseInCurve(0, 0, 1, 1);
        ac->setEaseOutCurve(1, 1, 0, 0);
        break;
    case kBlendCurveFast:
        ac->setEaseInCurve(0, 0.33f, 0.66f, 1);
        ac->setEaseOutCurve(1, 0.66f, 0.33f, 0);
        break;
    case kBlendCurveLinear:
        ac->setEaseInCurve(0, 0, 0, 1);
        ac->setEaseOutCurve(1, 0, 0, 0);
        break;
    default:
        return;
    }
}

void RtState::init(const State* state)
{
    m_state = state;
    m_numAnimations = m_state->m_numAnimations;
    for(uint32_t i=0; i<m_numAnimations; ++i)
    {
        m_ctrls[i] = m_state->create_anim_ctrl(i);
    }
}

void RtState::destroy()
{
    for(uint32_t i=0; i<m_numAnimations; ++i)
    {
        SAFE_REMOVEREF(m_ctrls[i]);
    }
}

void RtState::getRootmotion(float dt, hkQsTransform& motionOut)
{
    hkQsTransform tmpMotion;
    for(uint32_t i=0; i<m_numAnimations; ++i)
    {
        hk_anim_ctrl* ac = m_ctrls[i];
        if(!ac->hasExtractedMotion()) continue;
        ac->getExtractedMotionDeltaReferenceFrame(dt, tmpMotion);
        motionOut.setMulEq(tmpMotion);
    }
}

uint32_t RtState::collectTriggers(float dt, AnimationTrigger* outTriggers)
{
    uint32_t ret = 0;
    for(uint32_t i=0; i<m_numAnimations; ++i)
    {
        const Animation* animation = m_state->m_animations[i];
        hk_anim_ctrl* ac = m_ctrls[i];
        if(ac->getWeight() < TRIGGER_WEIGHT_THRESHOLD)
            continue;
        float localTime = ac->getLocalTime();
        uint32_t num = animation->collectTriggers(localTime, dt, outTriggers);
        outTriggers += num;
        ret += num;
    }
    return ret;
}

void RtState::add(hk_anim_skel* skeleton, float fLocalTime, float fSpeed)
{
    for(uint32_t i=0; i<m_numAnimations; ++i)
    {
        hk_anim_ctrl* ac = m_ctrls[i];
        ac->easeIn(0.0f);
        ac->setOverflowCount(0);
        ac->setUnderflowCount(0);
        ac->setLocalTime(fLocalTime);
        ac->setPlaybackSpeed(fSpeed);
        skeleton->addAnimationControl(ac);
    }
}

void RtState::remove(hk_anim_skel* skeleton)
{
    for(uint32_t i=0; i<m_numAnimations; ++i)
    {
        skeleton->removeAnimationControl(m_ctrls[i]);
    }
}

void RtState::setWeight(float fBaseWeight)
{
    for(uint32_t i=0; i<m_numAnimations; ++i)
    {
        m_ctrls[i]->setMasterWeight(fBaseWeight * m_weights[i]);
    }
}

void RtState::setPlaybackSpeed(float fSpeed)
{
    for(uint32_t i=0; i<m_numAnimations; ++i)
    {
        m_ctrls[i]->setPlaybackSpeed(fSpeed);
    }
}

void RtState::setLocalTime(float fLocalTime)
{
    for(uint32_t i=0; i<m_numAnimations; ++i)
    {
        m_ctrls[i]->setLocalTime(fLocalTime);
    }
}

void RtLayer::init(const AnimFSMLayer* resource)
{
    m_layer = resource;
    m_transition.m_easeInCtrl = new hk_anim_ctrl(NULL);
    m_transition.m_easeOutCtrl = new hk_anim_ctrl(NULL);
    uint32_t numStates = m_layer->m_numStates;
    for(uint32_t i=0; i<numStates; ++i)
    {
        m_states[i].init(&m_layer->m_states[i]);
    }
    defaultTransition.m_destStateIndex = 0;
    doTransition(&defaultTransition);
}

void RtLayer::destroy()
{
    uint32_t numStates = m_layer->m_numStates;
    for(uint32_t i=0; i<numStates; ++i)
    {
        m_states[i].destroy();
    }
    SAFE_REMOVEREF(m_transition.m_easeInCtrl);
    SAFE_REMOVEREF(m_transition.m_easeOutCtrl);
}

void RtLayer::changeStatus(uint8_t newStatus)
{
    if(m_status == newStatus) return;
    m_status = newStatus;
    
    RtState* lastState = m_transition.m_lastState;
    RtState* nextState = m_transition.m_nextState;
    
    switch(m_status)
    {
    case kStateNormal:
        {
            lastState->remove(m_skeleton);
        }
        break;
    case kStateTransitioning:
        {
            const Transition* t = m_transition.m_transition;
            float easeTime = m_transition.m_transition->m_duration;
            hk_anim_ctrl* easeInCtrl = m_transition.m_easeInCtrl;
            hk_anim_ctrl* easeOutCtrl = m_transition.m_easeOutCtrl;
            
            //make sure easeIn/Out ctrl
            easeInCtrl->easeOut(0.0f);
            easeInCtrl->update(0.0f);
            easeOutCtrl->easeIn(0.0f);
            easeOutCtrl->update(0.0f);
            
            setEaseCurves(easeInCtrl, t->m_blendCurve);
            setEaseCurves(easeOutCtrl, t->m_blendCurve);
            easeInCtrl->easeIn(easeTime);
            easeOutCtrl->easeOut(easeTime);
            
            nextState->add(m_skeleton, m_transition.m_nextTime);
            if(t->m_mode == kTransitionFrozen ||
               t->m_mode == kTransitionFrozenSync)
                lastState->setPlaybackSpeed(0.0f);
        }
        break;
    case kStateWaitForAlgin:
        {
            //DO NOTHING ???            
        }
        break;
    default:
        break;
    }
}

void RtLayer::udpate(float dt)
{
    switch(m_status)
    {
    case kStateNormal:
        {
            if(m_dirty) 
            {
                m_curState->setWeight(m_weight);
                m_dirty = false;
            }
        }
        break;
    case kStateTransitioning:
        {
            hk_anim_ctrl* easeInCtrl = m_transition.m_easeInCtrl;
            hk_anim_ctrl* easeOutCtrl = m_transition.m_easeOutCtrl;
            
            RtState* lastState = m_transition.m_lastState;
            RtState* nextState = m_transition.m_nextState;
            
            easeInCtrl->update(dt);
            easeOutCtrl->update(dt);
            
            float cur_state_weight = easeInCtrl->getWeight();
            float prev_state_weight = easeOutCtrl->getWeight();
            
            lastState->setWeight(cur_state_weight * m_weight);
            nextState->setWeight(prev_state_weight * m_weight);
            
            if(easeInCtrl->getEaseStatus() == hk_anim_ctrl::EASED_IN &&
               easeOutCtrl->getEaseStatus() == hk_anim_ctrl::EASED_OUT)
            {
                changeStatus(kStateNormal);
            }
            
        }
        break;
    case kStateWaitForAlgin:
        {
            m_transition.m_waitAlignTime -= dt;
            if(m_transition.m_waitAlignTime <= 0.0f)
            {
                changeStatus(kStateTransitioning);
            }
        }
        break;
    default:
        break;
    }
}

void RtLayer::doTransition(const Transition* t)
{
    if(m_status == kStateTransitioning)
        return; //-->TODO 

    RtState* lastState = m_curState;
    RtState* nextState = &m_states[t->m_destStateIndex];
    if(nextState == lastState) return;

    m_transition.m_nextTime = 0.0f;
    m_transition.m_waitAlignTime = 0.0f;
    m_transition.m_lastState = lastState;
    m_transition.m_nextState = nextState;
    m_transition.m_transition = t;

    //a sync transition will find beat to 
    //sync like left/right foot.
    if(t->m_mode == kTransitionCrossFadeSync || 
       t->m_mode == kTransitionFrozenSync)
    {
        //TODO -----> just check the first animation ???
        const State* lState = lastState->m_state;
        const State* nState = nextState->m_state;
        const Animation* anim_src = lState->m_animations[0];
        const Animation* anim_dst = nState->m_animations[0];
        float localtime_src = lastState->m_ctrls[0]->getLocalTime();
        float localtime_dst = nextState->m_ctrls[0]->getLocalTime();
        bool bLooped = lState->m_looped;
        const AnimationBeat* beat_src = anim_src->findNextClosestBeat(localtime_src, bLooped);
        const AnimationBeat* beat_dst = 0;
        if(beat_src) beat_dst = anim_dst->findBeat(beat_src->m_type);
        
        if(beat_src && beat_dst)
        {
            float timeDiff = 0.0f;
            float beatTime = beat_src->m_time;
            if(bLooped)
            {
                if(beatTime > localtime_src)
                    timeDiff = beatTime - localtime_src;
                else
                {
                    timeDiff = anim_src->getLength() - localtime_src;
                    timeDiff += beatTime;
                }
            }
            else timeDiff = beatTime - localtime_src;

            if(timeDiff > BEAT_TIME_THRESHOLD)
            {
                m_transition.m_waitAlignTime = timeDiff;
                changeStatus(kStateWaitForAlgin);
                return;
            }
            m_transition.m_nextTime = beat_dst->m_time;
        }
        else LOGW("can not find all animation beat, do normal transition");
    }
    changeStatus(kStateTransitioning);
    markDirty();
}

void RtLayer::getRootmotion(float dt, hkQsTransform& motionOut)
{
    switch(m_status)
    {
    case kStateTransitioning:
        {
            getTransitionRootmotion(dt, motionOut);
        }
        break;
    default:
        m_skeleton->getDeltaReferenceFrame(dt, motionOut);
        break;
    }
}

void RtLayer::getTransitionRootmotion(float dt, hkQsTransform& motionOut)
{
    const Transition* t = m_transition.m_transition;
    RtState* lastState = m_transition.m_lastState;
    RtState* nextState = m_transition.m_nextState;

    hk_anim_ctrl* easeInCtrl = m_transition.m_easeInCtrl;
    hk_anim_ctrl* easeOutCtrl = m_transition.m_easeOutCtrl;
    
    switch(t->m_motionBlendType)
    {
    case kMotionBlendIgnoreSrc:
        {
            nextState->getRootmotion(dt, motionOut);
            break;
        }
    case kMotionBlendIgnoreDst:
        {
            lastState->getRootmotion(dt, motionOut);
            break;
        }
    case kMotionBlendIgnoreSrcRotation:
        {
            hkQsTransform srcMotion;
            srcMotion.setIdentity();
            hkQsTransform dstMotion;
            dstMotion.setIdentity();
            lastState->getRootmotion(dt, srcMotion);
            nextState->getRootmotion(dt, dstMotion);

            float dstWeight = easeInCtrl->getWeight();
            float scrWeight = easeOutCtrl->getWeight();
            motionOut.m_rotation = dstMotion.m_rotation;
            hkVector4 sourceTranslation, destTranslation;
            sourceTranslation.setMul4(scrWeight, srcMotion.m_translation);
            destTranslation.setMul4(dstWeight, dstMotion.m_translation);
            motionOut.m_translation.setAdd4(sourceTranslation, destTranslation);
            break;
        }
    case kMotionBlendIgnoreDstRotation:
        {
            hkQsTransform srcMotion;
            srcMotion.setIdentity();
            hkQsTransform dstMotion;
            dstMotion.setIdentity();
            lastState->getRootmotion(dt, srcMotion);
            nextState->getRootmotion(dt, dstMotion);

            float dstWeight = easeInCtrl->getWeight();
            float scrWeight = easeOutCtrl->getWeight();
            motionOut.m_rotation = srcMotion.m_rotation;
            hkVector4 sourceTranslation, destTranslation;
            sourceTranslation.setMul4(scrWeight, srcMotion.m_translation);
            destTranslation.setMul4(dstWeight, dstMotion.m_translation);
            motionOut.m_translation.setAdd4(sourceTranslation, destTranslation);
            break;
        }
    default:
        m_skeleton->getDeltaReferenceFrame(dt, motionOut);
        break;
    }
}


uint32_t RtLayer::collectTriggers(float dt, AnimationTrigger* outTriggers)
{
    if(!m_curState) return 0;
    return m_curState->collectTriggers(dt, outTriggers);
}

void RtLayer::sendEvent(const StringId& evtName)
{
    if(!m_curState) return;
    const Transition* t = m_curState->m_state->findTransition(evtName);
    if(!t) return;
    doTransition(t);
}

bool RtLayer::isStateActive(const StringId& stateName) const
{
    switch(m_status)
    {
    case kStateNormal:
        return m_curState->m_state->m_name == stateName;   
    case kStateTransitioning:
        return (m_transition.m_lastState->m_state->m_name == stateName) ||
               (m_transition.m_nextState->m_state->m_name == stateName) ;
    default:
        return false;
    }
}

bool RtLayer::isInState(const StringId& stateName) const
{
    return m_curState->m_state->m_name == stateName;
}


void AnimFSMInstance::init(const void* resource)
{
    m_resource = (AnimFSM*)resource;
    uint32_t memSize = m_resource->m_numStates * sizeof(RtState) + m_resource->m_numAnimations * (sizeof(void*) * 2);
    m_blob = (char*)malloc(memSize);
    LOGD(__FUNCTION__" blob size = %d", memSize);
    memset(m_blob, 0x00, memSize);
    char* p = m_blob;
    
    for(uint32_t i=0; i<m_resource->m_numLayers; ++i)
    {
        const AnimFSMLayer& layerResource = m_resource->m_layers[i];
        RtLayer& layer = m_layers[i];
        layer.m_states = (RtState*)p;
        p += sizeof(RtState) * layerResource.m_numStates;
        for(uint32_t j=0; j<layerResource.m_numStates; ++j)
        {
            const State& state = layerResource.m_states[j];
            uint32_t numAnimations = state.m_numAnimations;  
            RtState& rtState = layer.m_states[j];
            rtState.m_ctrls = (hk_anim_ctrl**)p;
            p += sizeof(void*) * numAnimations;
            rtState.m_weights = (float*)p;
            p += sizeof(float) * numAnimations;
        }
    }
    
    for(uint32_t i=0; i<m_resource->m_numLayers; ++i)
    {
        const AnimFSMLayer& layerResource = m_resource->m_layers[i];
        RtLayer& layer = m_layers[i];
        layer.init(&layerResource);
    }
}

void AnimFSMInstance::destroy()
{
    for(uint32_t i=0; i<m_resource->m_numLayers; ++i)
    {
        m_layers[i].destroy();
    }
    free(m_blob);
}

void AnimFSMInstance::update(float dt)
{
    for(uint32_t i=0; i<m_resource->m_numLayers; ++i)
    {
        m_layers[i].udpate(dt);
    }
}

uint32_t AnimFSMInstance::collectTriggers(float dt, AnimationTrigger* outTriggers)
{
    uint32_t ret = 0;
    for(uint32_t i=0; i<m_resource->m_numLayers; ++i)
    {
        uint32_t num = m_layers[i].collectTriggers(dt, outTriggers);
        ret += num;
        outTriggers += num;
    }
    return ret;
}

void AnimFSMInstance::sendEvent(const StringId& evtName, int index)
{
    if(index < 0)
    {
        m_layers[index].sendEvent(evtName);
    }
    else
    {
        for(uint32_t i=0; i<m_resource->m_numLayers; ++i)
        {
            m_layers[i].sendEvent(evtName);
        }
    }
}













//*********************************************************************
// DUMPPING FUNCTIONS HIDE IN .CPP
//*********************************************************************
#ifndef _RETAIL
#include "Graphics.h"
void dumpState(const RtState* state, uint32_t color)
{
    const State* s = state->m_state;
    const char* stateName = stringid_lookup(s->m_name);
    DBG_TEX_PRINTF(color, "state name = %s, num-animations=%d, looped=%d", stateName, s->m_numAnimations, s->m_looped);
    for(uint32_t i=0; i<state->m_numAnimations; ++i)
    {
        DBG_TEX_PRINTF(color, "animation = %s, weight = %f", 
        stringid_lookup(s->m_animNames[i]), state->m_weights[i]);
    }
}
void dumpTransition(const RtTransition& rt, uint32_t color)
{
    const RtState* lastState = rt.m_lastState;
    const RtState* nextState = rt.m_nextState;
    const Transition* t = rt.m_transition;
    hk_anim_ctrl* inCtrl = rt.m_easeInCtrl;
    hk_anim_ctrl* outCtrl = rt.m_easeOutCtrl;
    const char* eventName = stringid_lookup(t->m_event);
    const char* beatName = stringid_lookup(t->m_beat);
    dumpState(lastState, color);
    DBG_TEX_PRINTF(color, "last state fade-out current weight = %f", inCtrl->getWeight());
    DBG_TEX_PRINTF(color, "transition event=%s, beat=%s, motion-type=%d, mode=%d", 
                        eventName, beatName, t->m_motionBlendType, t->m_mode);
    DBG_TEX_PRINTF(color, "next state fade-in current weight = %f", outCtrl->getWeight());
    dumpState(nextState, color);
}

void dumpFSM(AnimFSMInstance* fsm)
{
    uint32_t color = 0x4f;
    for(uint32_t i=0; i<fsm->m_resource->m_numLayers; ++i)
    {
        const RtLayer& layer = fsm->m_layers[i];
        DBG_TEX_PRINTF(color, "==================layer[%d]====================", i);
        switch(layer.m_status)
        {
        case kStateNormal: dumpState(layer.m_curState, color); break;
        case kStateTransitioning: dumpTransition(layer.m_transition, color); break;
        default:
            break;  
        }
    }
}
#endif

