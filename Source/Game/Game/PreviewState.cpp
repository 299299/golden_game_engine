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
#include <bx/string.h>
#include <bx/commandline.h>


extern DebugFPSCamera  g_fpsCamera;



INTERNAL void anim_state_debug_imgui(void* _component, ComponentData* _data)
{
    AnimationStateLayer* _layer = (AnimationStateLayer*)_component;
    StringId* _names = _layer->m_stateNames;
    AnimationState* _states = _layer->m_states;
    int _cur_index = _layer->m_curStateIndex;
    StringId _cur_name = _cur_index >= 0 ? _names[_cur_index] : 0;
    imguiLabel("cur state = %s", stringid_lookup(_cur_name));

    if(_cur_index >= 0)
    {
        AnimationState* _cur_state = _states + _cur_index;
        StringId* _t_names = _cur_state->m_transitionNames;
        uint32_t _t_num = _cur_state->m_numTransitions;
        for(uint32_t i=0; i<_t_num; ++i)
        {
            StringId _t_name = _t_names[i];
            bool _clicked = imguiButton(stringid_lookup(_t_name));
            if(_clicked)
            {
                _layer->fire_event(_t_name);
            }
        }
    }

}

PreviewState::PreviewState()
    :m_preview_actor(0)
    ,m_preview_level(0)
    ,m_bgfx_debug(BGFX_DEBUG_TEXT)
    ,m_show_profile(false)
    ,m_draw_debug_graphics(false)
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

#ifdef HAVOK_COMPILE
    if(g_win32Context.is_key_just_pressed(VK_F1))
    {
        m_show_profile = !m_show_profile;
    }
    else if(g_win32Context.is_key_just_pressed(VK_F2))
    {
        m_draw_debug_graphics = !m_draw_debug_graphics;
    }
    else if(g_win32Context.is_key_just_pressed(VK_F3))
    {
        swith_graphics_debug(BGFX_DEBUG_WIREFRAME);
    }
    else if(g_win32Context.is_key_just_pressed(VK_F4))
    {
        swith_graphics_debug(BGFX_DEBUG_STATS);
    }
#endif

    if(m_show_profile)
    {
        g_profiler.dump();
    }
    if(m_draw_debug_graphics)
    {
        extern void draw_debug_models();
        extern void draw_debug_lights();
        extern void draw_debug_animation();
        draw_debug_lights();
        draw_debug_models();
        draw_debug_animation();
    }

#ifdef HAVOK_COMPILE
    g_debugDrawMgr.add_axis(hkQsTransform::getIdentity());
#endif

    extern void resource_hot_reload_update(float);
    resource_hot_reload_update(dt);

    draw_actor_info(m_preview_actor, 0, 25, 400, 600);
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

    if(actor_name)
    {
        LOGD("loading actor %s \n", actor_name);
        hkQsTransform t;
#ifdef HAVOK_COMPILE
        t.setIdentity();
#endif
        m_preview_actor = g_actorWorld.create_actor(stringid_caculate(actor_name), t);
        LOGD("created actor = %x", m_preview_actor);
    }
    if(level_name)
    {
        LOGD("loading level %s \n", level_name);
        m_preview_level = (Level*)g_resourceMgr.find_resource(EngineTypes::LEVEL, stringid_caculate(level_name));
        if(m_preview_level) 
            m_preview_level->load();
    }
}

void PreviewState::swith_graphics_debug( uint32_t flag )
{
    if(!HAS_BITS(m_bgfx_debug,flag)) 
        ADD_BITS(m_bgfx_debug, flag);
    else 
        REMOVE_BITS(m_bgfx_debug, flag);
    bgfx::setDebug(m_bgfx_debug);
}

void PreviewState::draw_actor_info(ActorId32 _actorId, int _x, int _y, int _w, int _h)
{
    Actor* _actor = g_actorWorld.get_actor(_actorId);
    if(!_actor)
        return;

    const ActorResource* _res = _actor->m_resource;
    if(!_res)
        return;

    static int32_t _scroll = 0;
    static bool _enabled = true;

    char _buf[256];
    bx::snprintf(_buf, sizeof(_buf), "Actor %x", _actorId);

    imguiBeginScrollArea(_buf, _x, _y, _w, _h, &_scroll);
    _enabled = imguiBeginScroll(_h, &_scroll, _enabled);
   
    uint32_t _num = _res->m_num_components;
    ComponentData* data = (ComponentData*)((char*)_res + _res->m_component_data_offset);
    int _class = _res->m_class;
    extern const char* g_actorClassNames[];
    imguiLabel("[%s] [%x] has [%d] components: ", g_actorClassNames[_class], _actorId, _num);
    const char* _indent = "    ";

    for(uint32_t i=0; i<_num; ++i)
    {
        StringId _comp_type = data[i].m_type;
        ComponentDebugDrawGUI* _gui = find_component_gui(_comp_type);
        imguiSeparatorLine();
        imguiLabel("%s component type:%s", _indent, stringid_lookup(_comp_type));
        int _index = data->m_index;
        ComponentFactory* _fac = g_componentMgr.get_factory(_index);
        void* _component = _fac->get_component(_actor->m_components[i]);

        if(_gui)
        {
            _gui->m_function(_component, data + i);
        }
    }

    imguiEndScrollArea();
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
