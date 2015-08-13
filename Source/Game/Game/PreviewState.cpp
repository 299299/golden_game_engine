#include <imgui/imgui.h>
#include "PreviewState.h"
#include "RenderCamera.h"
#include "Profiler.h"
#include "Model.h"
#include "Light.h"
#include "RenderCamera.h"
#include "DebugDraw.h"
#include "Log.h"
#include "Actor.h"
#include "Animation.h"
#include "Resource.h"
#include "Win32Context.h"
#include "AnimRig.h"
#include "Component.h"
#include "Level.h"
#include "AnimationState.h"
#include "AnimControl.h"
#include "AnimationSystem.h"
#include "Engine.h"
#include <bx/string.h>
#include <bx/commandline.h>

extern DebugFPSCamera  g_fpsCamera;

static void anim_state_debug_imgui(void* component, ComponentData* data)
{
    AnimationStatesInstance* states = (AnimationStatesInstance*)component;
    const AnimationState* cur_state = states->m_state;

    StringId cur_name = cur_state ? cur_state->m_name : 0;
    imguiLabel("cur state = %s, dirty = %d", stringid_lookup(cur_name), states->m_dirty);

    if(cur_state)
    {
        StringId* t_names = (StringId*)((char*)cur_state + cur_state->m_transition_name_offset);
        int t_num = cur_state->m_num_transitions;
        for(int i=0; i<t_num; ++i)
        {
            StringId t_name = t_names[i];
            bool clicked = imguiButton(stringid_lookup(t_name));
            if(clicked)
            {
                states->fire_event(t_name);
            }
        }

        int n_num = cur_state->m_num_nodes;
        StringId* n_names = (StringId*)((char*)cur_state + cur_state->m_node_name_offset);
        char* nodes = (char*)cur_state + cur_state->m_node_offset;
        extern const char* g_anim_node_names[];

        for(int i=0; i<n_num; ++i)
        {
            int type = *((uint32_t*)nodes);
            imguiLabel("    node name: %s, type %s", stringid_lookup(n_names[i]), g_anim_node_names[type]);
            switch(type)
            {
            case AnimationNodeType::Lerp:
            case AnimationNodeType::Additive:
                {
                    BinaryNode* node = (BinaryNode*)nodes;
                    float* f = (float*)(states->m_dynamic_data + node->m_dynamic_data_offset);
                    if(imguiSlider("     value: ", *f, 0.0f, 1.0f, 0.01f))
                        states->m_dirty = 1;
                }
                break;
            case AnimationNodeType::Value:
                {
                    ValueNode* node = (ValueNode*)nodes;
                    hk_anim_ctrl* ac = (hk_anim_ctrl*)(states->m_dynamic_data + node->m_dynamic_data_offset);
                    imguiLabel("     animation = %s", get_anim_debug_name(ac->m_animation));
                }
                break;
            case AnimationNodeType::Select:
                {
                    SelectNode* node = (SelectNode*)nodes;
                    int32_t* i = (int32_t*)(states->m_dynamic_data + node->m_dynamic_data_offset);
                    if(imguiSlider("     value:", *i, 0, node->m_num_children - 1))
                        states->m_dirty = 1;
                }
                break;
            default:
                break;
            }
            nodes += NODE_SIZE;
        }
    }

    imguiLabel("animation skeleton control info:");

#ifdef HAVOK_COMPILE
    hkaAnimatedSkeleton* s = states->m_skeleton;
    int num = s->getNumAnimationControls();
    for (int i=0; i<num; ++i)
    {
        hk_anim_ctrl* ac = (hk_anim_ctrl*)s->getAnimationControl(i);
        imguiLabel("%s weight = %f, time = %f", get_anim_debug_name(ac->m_animation), ac->getMasterWeight(), ac->getLocalTime());
    }
#endif
}

static void draw_fact(ActorId32 id)
{
    Actor* actor = g_actorWorld.get_actor(id);
    if(!actor)
        return;
    const Fact* fact = (const Fact*)((char*)actor->m_resource + actor->m_resource->m_fact_offset);
    void* fact_value = actor->m_blob;
    imguiLabel("Fact: num_of_keys = %d, value_size = %d", fact->m_num_keys, fact->m_value_size);
    int num = (int)fact->m_num_keys;
    const StringId* names = (const StringId*)((char*)fact + fact->m_name_offset);
    const Key* keys = (const Key*)((char*)fact + fact->m_key_offset);
    char buf[1024] = {0};
    for (int i=0; i<num; ++i)
    {
        const Key* key = keys + i;
        char* value = (char*)fact_value + key->m_value_offset;
        int value_size = key->m_size;
        memcpy(buf, value, value_size);
        imguiLabel("key=%s, value size=%d, str=%s", stringid_lookup(names[i]), value_size, buf);
    }
}

PreviewState::PreviewState()
    :m_preview_actor(INVALID_U32)
    ,m_preview_level(0)
    ,m_actor_name(0)
    ,m_level_name(0)
    ,m_num_component_gui(0)
{
    memset(m_component_gui, 0x00, sizeof(m_component_gui));

    ComponentDebugDrawGUI _states_gui = {EngineTypes::ANIMATION_STATES,  anim_state_debug_imgui};
    m_component_gui[m_num_component_gui++] = _states_gui;
}

PreviewState::~PreviewState()
{

}

void PreviewState::step( float dt )
{
    GameState::step(dt);
    g_fpsCamera.update(dt);

    step_debug_ctrl(dt);

    if(m_preview_level)
        draw_level_info(m_level_name, m_preview_level, 5, 25, 400, 400);
    else {
        draw_actor_info(m_actor_name, m_preview_actor, 5, 25, 400, 400);
        Actor *a = g_actorWorld.get_actor(m_preview_actor);
        if (a) {
            AnimationStatesInstance *s = (AnimationStatesInstance*)a->get_first_component_of(EngineTypes::ANIMATION_STATES);
            if (s) {
                hkQsTransform t = a->m_transform;
                hkQsTransform deltaMotion;
                s->get_rootmotion(dt, deltaMotion);
                t.setMulEq(deltaMotion);
                a->set_transform(t);
            }
        }
        g_debugDrawMgr.add_axis(a->m_transform);
    }

    g_debugDrawMgr.add_grid(20, 5, RGBCOLOR(175,175,175), true);
    //g_debugDrawMgr.add_axis(hkQsTransform::getIdentity(), 5);
}

void PreviewState::on_enter( GameState* prev_state )
{
    LOGD("preview-state-enter");
    float eye[] = {-5,5,0};
    float at[] = {0,0,0};
    g_camera.update(eye, at);
    g_fpsCamera.set(eye, at);
}

void PreviewState::process_cmd_args( void* p )
{
    bx::CommandLine* cmd = (bx::CommandLine*)p;
    const char* actor_name = cmd->findOption("actor");
    const char* level_name = cmd->findOption("level");
    m_actor_name = actor_name;
    m_level_name = level_name;

    if(actor_name)
    {
        LOGD("loading actor %s \n", actor_name);
        hkQsTransform t;
        t.setIdentity();
        m_preview_actor = g_actorWorld.create_actor(stringid_caculate(actor_name), t, stringid_caculate("preview-actor"));
        LOGD("created actor = %x", m_preview_actor);
    }

    if(level_name)
    {
        LOGD("loading level %s \n", level_name);
        m_preview_level = (Level*)g_resourceMgr.find_resource(EngineTypes::LEVEL, stringid_caculate(level_name));
        if(m_preview_level)
            start_level(m_preview_level);
    }
}

ComponentDebugDrawGUI* PreviewState::find_component_gui( StringId _type )
{
    int _num = m_num_component_gui;
    ComponentDebugDrawGUI* _head = m_component_gui;
    for (int i=0; i<_num; ++i)
    {
        if(_head[i].m_name == _type)
            return _head + i;
    }
    return 0;
}


void PreviewState::draw_actor_info(const char* name, ActorId32 _actorId, int _x, int _y, int _w, int _h)
{
    PROFILE(IMGUI_Actor_Info);
    static int32_t _scroll = 0;
    char _buf[256];
    bx::snprintf(_buf, sizeof(_buf), "Actor %s", name);
    imguiBeginScrollArea(_buf, _x, _y, _w, _h, &_scroll);
    draw_components_info(_actorId);
    draw_fact(_actorId);
    imguiEndScrollArea();
}

void PreviewState::draw_level_info( const char* name, Level* level, int _x, int _y, int _w, int _h )
{
    PROFILE(IMGUI_Level_Info);

    if(!level)
        return;

    static int32_t _scroll = 0;
    static bool _enabled = true;

    char _buf[256];
    bx::snprintf(_buf, sizeof(_buf), "Level %s", name);

    _enabled = imguiBeginScrollArea(_buf, _x, _y, _w, _h, &_scroll);
    int num = level->m_num_objects;
    LevelObject* objects = (LevelObject*)((char*)level + level->m_object_offset);
    for (int i=0; i<num; ++i)
    {
        LevelObject& object = objects[i];
        imguiSeparatorLine();
        imguiLabel("Actor %s", stringid_lookup(object.m_name));
        draw_components_info(object.m_actor);
    }
    imguiEndScrollArea();
}

void PreviewState::draw_components_info( ActorId32 actorId )
{
    Actor* _actor = g_actorWorld.get_actor(actorId);
    if(!_actor)
        return;

    const ActorResource* _res = _actor->m_resource;
    if(!_res)
        return;

    uint32_t _num = _res->m_num_components;
    ComponentData* data = (ComponentData*)((char*)_res + _res->m_component_data_offset);
    int _class = _res->m_class;
    extern const char* g_actorClassNames[];
    imguiLabel("[%s] [%x] has [%d] components: ", g_actorClassNames[_class], actorId, _num);
    const char* _indent = "    ";

    for(uint32_t i=0; i<_num; ++i)
    {
        StringId _comp_type = data[i].m_type;
        ComponentDebugDrawGUI* _gui = find_component_gui(_comp_type);
        imguiLabel("%s component type:%s", _indent, stringid_lookup(_comp_type));
        int _index = data[i].m_index;
        ComponentFactory* _fac = g_componentMgr.get_factory(_index);
        void* _component = _fac->get_component(_actor->m_components[i]);

        if(_gui)
        {
            _gui->m_function(_component, data + i);
        }

        imguiSeparator();
    }
}
