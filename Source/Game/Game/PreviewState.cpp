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
#include <bx/string.h>

static uint32_t g_bgfx_debug = BGFX_DEBUG_TEXT;
static bool g_show_profile = false;
static bool g_draw_debug_graphics = false;

extern DebugFPSCamera  g_fpsCamera;

static void swith_graphics_debug(uint32_t flag)
{
    bool is_wireframe = HAS_BITS(g_bgfx_debug,flag);
    is_wireframe = !is_wireframe;
    if(is_wireframe) ADD_BITS(g_bgfx_debug, flag);
    else REMOVE_BITS(g_bgfx_debug, flag);
    bgfx::setDebug(g_bgfx_debug);
}

static void list_resources_gui(const StringId& type)
{
    static int32_t _scroll = 0;
    static bool _enabled = true;
    _enabled = imguiBeginScroll(600, &_scroll, _enabled);

    ResourceInfo* _animations[32];
    uint32_t _len = g_resourceMgr.find_resources_type_of(
        Animation::get_type(),
        _animations,
        BX_COUNTOF(_animations));

    for(uint32_t i=0; i<_len; ++i)
    {
        ResourceInfo* _info = _animations[i];
        if(imguiButton(stringid_lookup(_info->m_name)))
        {
            // load animation --->
            // FIXME:TODO
        }
    }

    imguiEndScroll();
}

static void actor_information_imgui(const char* _name, int _x, int _y, int _texHeight)
{
    const ActorResource* _res = FIND_RESOURCE_NAMED(ActorResource, _name);
    if(!_res)
        return;
    ImguiTextAlign::Enum _align = ImguiTextAlign::Left;
    uint32_t _argb = imguiRGBA(255, 125, 125);
    char _buf[256];
    uint32_t _num = _res->m_numComponents;
    int _class = _res->m_class;
    extern const char* g_actorClassNames[];
    bx::snprintf(_buf, sizeof(_buf), "[%s] [%s] has [%d] components: ", g_actorClassNames[_class], _name, _num);
    imguiDrawText(_x, _y, _align, _buf, _argb);
    const char* _indent = "    ";
    for(uint32_t i=0; i<_num; ++i)
    {
        _y += _texHeight;
        StringId _comp_name = _res->m_resourceNames[i];
        StringId _comp_type = _res->m_resourceTypes[i];
        bx::snprintf(_buf, sizeof(_buf), "%s component type:%s name:%s",
            _indent, stringid_lookup(_comp_type), stringid_lookup(_comp_name));
        imguiDrawText(_x, _y, _align, _buf, _argb);
    }
}

PreviewState::PreviewState()
{

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
        g_show_profile = !g_show_profile;
    }
    else if(g_win32Context.is_key_just_pressed(VK_F2))
    {
        g_draw_debug_graphics = !g_draw_debug_graphics;
    }
    else if(g_win32Context.is_key_just_pressed(VK_F3))
    {
        swith_graphics_debug(BGFX_DEBUG_WIREFRAME);
    }
    else if(g_win32Context.is_key_just_pressed(VK_F4))
    {
        swith_graphics_debug(BGFX_DEBUG_STATS);
    }

    if(g_show_profile)
    {
        g_profiler.dump();
    }
    if(g_draw_debug_graphics)
    {
        extern void draw_debug_models();
        extern void draw_debug_lights();
        extern void draw_debug_animation();
        draw_debug_lights();
        draw_debug_models();
        draw_debug_animation();
    }

    g_debugDrawMgr.add_axis(hkQsTransform::getIdentity());

    extern void resource_hot_reload_update(float);
    resource_hot_reload_update(dt);

    actor_information_imgui("core/batman", 0, 25, 15);
#endif
}

void PreviewState::on_enter( GameState* prev_state )
{
    LOGD("preview-state-enter");
    float eye[] = {-5,5,0};
    float at[] = {0,0,0};
    g_camera.update(eye, at);
    g_fpsCamera.set(eye, at);
}
