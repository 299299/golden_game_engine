#include "Engine.h"
#include "Win32Context.h"
#include "XBoxInput.h"
#include "Resource.h"
#include "EngineAssert.h"
#include "Gui.h"
#include "Graphics.h"
#include "DebugDraw.h"
#include "Profiler.h"
#include "Actor.h"
#include "DataDef.h"
#include <bx/bx.h>
#include <gamemonkey/gmThread.h>
#include <imgui/imgui.h>
#include <bgfx/bgfx.h>

#ifdef GetObject
#undef GetObject
#endif

struct gmVariableEntry
{
    const char* m_name;
    gmVariable  m_value;
};

//-------------------------------------------------------------------------
// CORE
static int GM_CDECL script_shutdown_game(gmThread* a_thread)
{
    g_engine.shutdown();
    return GM_OK;
}
static int GM_CDECL string_to_id(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(str, 0);
    a_thread->PushInt(StringId::calculate(str));
    return GM_OK;
}
#ifndef _RETAIL
static int GM_CDECL id_to_string(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(id, 0);
    a_thread->PushNewString(stringid_lookup(StringId(id)));
    return GM_OK;
}
#endif
static int GM_CDECL rgba_to_int(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_INT_PARAM(r, 0);
    GM_CHECK_INT_PARAM(g, 1);
    GM_CHECK_INT_PARAM(b, 2);
    GM_INT_PARAM(a, 3, 255);
    a_thread->PushInt(imguiRGBA(r,g,b,a));
    return GM_OK;
}
static int GM_CDECL get_window_width(gmThread* a_thread)
{
    a_thread->PushInt(g_win32Context.m_width);
    return GM_OK;
}
static int GM_CDECL get_window_height(gmThread* a_thread)
{
    a_thread->PushInt(g_win32Context.m_height);
    return GM_OK;
}
static int GM_CDECL subsystems_ready(gmThread* a_thread)
{
    Graphics::ready();
    g_debugDrawMgr.ready();
    return GM_OK;
}
static int GM_CDECL begin_profile(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(name, 0);
    g_profiler.begin_block(name);
    return GM_OK;
}
static int GM_CDECL end_profile(gmThread* a_thread)
{
    g_profiler.end_block();
    return GM_OK;
}
static int GM_CDECL show_profile(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_INT_PARAM(show_unused, 0);
    GM_CHECK_INT_PARAM(show_total, 1);
    GM_CHECK_INT_PARAM(max_depth, 2);
    g_profiler.dump(show_unused, show_total, max_depth);
    return GM_OK;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// INPUT
static int GM_CDECL input_is_key_down(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(key_code, 0);
    a_thread->PushInt(g_win32Context.is_key_down(key_code));
    return GM_OK;
}

static int GM_CDECL input_is_key_just_pressed(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(key_code, 0);
    a_thread->PushInt(g_win32Context.is_key_just_pressed(key_code));
    return GM_OK;
}

static int GM_CDECL input_is_mouse_down(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(mouse_btn, 0);
    a_thread->PushInt(g_win32Context.is_mouse_down(mouse_btn));
    return GM_OK;
}

static int GM_CDECL input_is_mouse_just_pressed(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(mouse_btn, 0);
    a_thread->PushInt(g_win32Context.is_mouse_just_pressed(mouse_btn));
    return GM_OK;
}

static int GM_CDECL input_mouse_pos(gmThread* a_thread)
{
    a_thread->PushInt(g_win32Context.m_mx);
    a_thread->PushInt(g_win32Context.m_my);
    return GM_OK;
}
static int GM_CDECL input_mouse_last_pos(gmThread* a_thread)
{
    a_thread->PushInt(g_win32Context.m_last_mx);
    a_thread->PushInt(g_win32Context.m_last_my);
    return GM_OK;
}

static int GM_CDECL input_is_mouse_moved(gmThread* a_thread)
{
    a_thread->PushInt(g_win32Context.m_mouseMoved);
    return GM_OK;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// RESOURCE
static int GM_CDECL resource_package_load(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(pack_name, 0);
    g_resourceMgr.load_package(pack_name);
    return GM_OK;
}

static int GM_CDECL resource_package_load_and_wait(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(pack_name, 0);
    g_resourceMgr.load_package_and_wait(pack_name);
    return GM_OK;
}

static int GM_CDECL resource_package_unload(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(pack_name, 0);
    g_resourceMgr.unload_package(StringId(pack_name));
    return GM_OK;
}

static int GM_CDECL resource_package_get_status(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(pack_name, 0);
    a_thread->PushInt(g_resourceMgr.get_package_status(StringId(pack_name)));
    return GM_OK;
}

static int GM_CDECL resource_package_flush(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(pack_name, 0);
    GM_CHECK_INT_PARAM(max_num, 1);
    g_resourceMgr.flush_package(StringId(pack_name), max_num);
    return GM_OK;
}

static int GM_CDECL resource_find(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(res_type, 0);
    GM_CHECK_INT_PARAM(res_name, 1);
    a_thread->PushInt((int)g_resourceMgr.find_resource(StringId(res_type), StringId(res_name)));
    return GM_OK;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// GUI
static int GM_CDECL gui_dbg_print(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(color, 0);
    GM_CHECK_STRING_PARAM(text, 1);
    DBG_TEX_PRINTF(color, text);
    return GM_OK;
}

static int GM_CDECL imgui_draw_text(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(5);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 1);
    GM_CHECK_INT_PARAM(align, 2);
    GM_CHECK_STRING_PARAM(text, 3);
    GM_CHECK_INT_PARAM(color, 4);
    imguiDrawText((int)x, (int)y, (ImguiTextAlign::Enum)align, text, color);
    return GM_OK;
}

static int GM_CDECL imgui_draw_line(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(6);
    GM_CHECK_FLOAT_OR_INT_PARAM(x0, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y0, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(x1, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(y1, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(r, 4);
    GM_CHECK_INT_PARAM(color, 5);
    imguiDrawLine(x0, y0, x1, y1, r, color);
    return GM_OK;
}

static int GM_CDECL imgui_draw_round_rect(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(6);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(w, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(h, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(r, 4);
    GM_CHECK_INT_PARAM(color, 5);
    imguiDrawRoundedRect(x, y, w, h, r, color);
    return GM_OK;
}

static int GM_CDECL imgui_draw_rect(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(5);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(w, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(h, 3);
    GM_CHECK_INT_PARAM(color, 4);
    imguiDrawRect(x, y, w, h, color);
    return GM_OK;
}


static int GM_CDECL imgui_border_button(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_INT_PARAM(border, 0);
    GM_CHECK_INT_PARAM(checked, 1);
    GM_CHECK_INT_PARAM(enabled, 2);
    a_thread->PushInt(imguiBorderButton((ImguiBorder::Enum)border, checked, enabled));
    return GM_OK;
}

static int GM_CDECL imgui_begin_area(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(6);
    GM_CHECK_STRING_PARAM(name, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(w, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(h, 4);
    GM_CHECK_INT_PARAM(enabled, 5);
    imguiBeginArea(name, (int)x, (int)y, (int)w, (int)h, enabled);
    return GM_OK;
}

static int GM_CDECL imgui_end_area(gmThread* a_thread)
{
    imguiEndArea();
    return GM_OK;
}

static int GM_CDECL imgui_indent(gmThread* a_thread)
{
    imguiIndent();
    return GM_OK;
}

static int GM_CDECL imgui_unindent(gmThread* a_thread)
{
    imguiUnindent();
    return GM_OK;
}


static int GM_CDECL imgui_separator(gmThread* a_thread)
{
    imguiSeparator();
    return GM_OK;
}

static int GM_CDECL imgui_separator_line(gmThread* a_thread)
{
    imguiSeparatorLine();
    return GM_OK;
}

static int GM_CDECL imgui_button(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_STRING_PARAM(text, 0);
    GM_CHECK_INT_PARAM(enabled, 1);
    GM_CHECK_INT_PARAM(align, 1);
    a_thread->PushInt(imguiButton(text, enabled, (ImguiAlign::Enum)align));
    return GM_OK;
}

static int GM_CDECL imgui_item(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_STRING_PARAM(text, 0);
    GM_CHECK_INT_PARAM(enabled, 1);
    a_thread->PushInt(imguiItem(text, enabled));
    return GM_OK;
}

static int GM_CDECL imgui_check(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_STRING_PARAM(text, 0);
    GM_CHECK_INT_PARAM(checked, 1);
    GM_CHECK_INT_PARAM(enabled, 2);
    a_thread->PushInt(imguiCheck(text, checked, enabled));
    return GM_OK;
}

static int GM_CDECL imgui_collapse(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(4);
    GM_CHECK_STRING_PARAM(text, 0);
    GM_CHECK_STRING_PARAM(sub_text, 1);
    GM_CHECK_INT_PARAM(checked, 2);
    GM_CHECK_INT_PARAM(enabled, 3);
    a_thread->PushInt(imguiCollapse(text, sub_text, checked, enabled));
    return GM_OK;
}

static int GM_CDECL imgui_label(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(text, 0);
    imguiLabel(text);
    return GM_OK;
}

static int GM_CDECL imgui_color_label(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_STRING_PARAM(text, 0);
    GM_CHECK_INT_PARAM(color, 0);
    imguiLabel(color, text);
    return GM_OK;
}

static int GM_CDECL imgui_value(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(text, 0);
    imguiValue(text);
    return GM_OK;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// DRAW
static int GM_CDECL graphics_draw(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(shading_env_addr, 0);
    Graphics::draw((ShadingEnviroment*)shading_env_addr);
    return GM_OK;
}

static int GM_CDECL debug_draw_add_line(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(8);
    GM_CHECK_FLOAT_OR_INT_PARAM(x0, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y0, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(z0, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(x1, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(y1, 4);
    GM_CHECK_FLOAT_OR_INT_PARAM(z1, 5);
    GM_CHECK_INT_PARAM(color, 6);
    GM_CHECK_FLOAT_PARAM(depth, 7);
    float start[] = {x0, y0, z0};
    float end[] = {x1, y1, z1};
    g_debugDrawMgr.add_line(start, end, color, depth);
    return GM_OK;
}

static int GM_CDECL debug_draw_add_aabb(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(8);
    GM_CHECK_FLOAT_OR_INT_PARAM(x0, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y0, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(z0, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(x1, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(y1, 4);
    GM_CHECK_FLOAT_OR_INT_PARAM(z1, 5);
    GM_CHECK_INT_PARAM(color, 6);
    GM_CHECK_INT_PARAM(depth, 7);
    float min[] = {x0, y0, z0};
    float max[] = {x1, y1, z1};
    g_debugDrawMgr.add_aabb(min, max, color, depth);
    return GM_OK;
}

static int GM_CDECL debug_draw_add_axis(gmThread* a_thread)
{
    //TODO
    GM_CHECK_NUM_PARAMS(8);
    GM_CHECK_FLOAT_OR_INT_PARAM(x0, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y0, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(z0, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(x1, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(y1, 4);
    GM_CHECK_FLOAT_OR_INT_PARAM(z1, 5);
    GM_CHECK_FLOAT_PARAM(size, 6);
    GM_CHECK_INT_PARAM(depth, 7);
    hkQsTransform t;
    t.m_translation.set(x0, y0, z0);
    t.m_rotation.setFromEulerAngles(x1, y1, z1);
    g_debugDrawMgr.add_axis(t, size, depth);
    return GM_OK;
}

static int GM_CDECL debug_draw_add_cross(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(6);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(z, 2);
    GM_CHECK_FLOAT_PARAM(size, 3);
    GM_CHECK_INT_PARAM(color, 4);
    GM_CHECK_INT_PARAM(depth, 5);
    float pos[] = {x, y, z};
    g_debugDrawMgr.add_cross(pos, size, color, depth);
    return GM_OK;
}

static int GM_CDECL debug_draw_add_3d_text(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(5);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(z, 2);
    GM_CHECK_STRING_PARAM(text, 3);
    GM_CHECK_INT_PARAM(color, 4);
    float pos[] = {x, y, z};
    g_debugDrawMgr.add_text_3d(pos, text, color);
    return GM_OK;
}

static int GM_CDECL debug_draw_add_sphere(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(6);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(z, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(radius, 3);
    GM_CHECK_INT_PARAM(color, 4);
    GM_CHECK_INT_PARAM(depth, 5);
    float pos[] = {x, y, z};
    g_debugDrawMgr.add_sphere(pos, radius, color, depth);
    return GM_OK;
}

static int GM_CDECL debug_draw_add_circle(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(9);
    GM_CHECK_FLOAT_OR_INT_PARAM(x0, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y0, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(z0, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(x1, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(y1, 4);
    GM_CHECK_FLOAT_OR_INT_PARAM(z1, 5);
    GM_CHECK_FLOAT_OR_INT_PARAM(radius, 6);
    GM_CHECK_INT_PARAM(color, 7);
    GM_CHECK_INT_PARAM(depth, 8);
    float pos[] = {x0, y0, z0};
    float normal[] = {x1, y1, z1};
    g_debugDrawMgr.add_cycle(pos, normal, radius, color, depth);
    return GM_OK;
}

static int GM_CDECL debug_draw_add_grid(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(4);
    GM_CHECK_INT_PARAM(grid_num, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(grid_width, 1);
    GM_CHECK_INT_PARAM(color, 2);
    GM_CHECK_INT_PARAM(depth, 3);
    g_debugDrawMgr.add_grid(grid_num, grid_width, color, depth);
    return GM_OK;
}

static int GM_CDECL graphics_set_debug_mode(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(mode, 0);
    static uint32_t debug_modes[] = 
    {
        BGFX_DEBUG_NONE, BGFX_DEBUG_TEXT, BGFX_DEBUG_STATS, BGFX_DEBUG_IFH, BGFX_DEBUG_WIREFRAME, 
    };
    bgfx::setDebug(debug_modes[mode]);
    return GM_OK;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// WORLD
static int GM_CDECL world_set_shading_enviroment(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(shading_env, 0);
    g_actorWorld.m_shading_env = (ShadingEnviroment*)shading_env;
    return GM_OK;
}
static int GM_CDECL world_num_of_actors(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(type, 0);
    a_thread->PushInt(g_actorWorld.num_actors(type));
    return GM_OK;
}
static int GM_CDECL world_create_actor(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(type, 0);
    //a_thread->PushInt();
    //ActorId acId = g_actorWorld.create_actor()
    return GM_OK;
}
static int GM_CDECL world_destroy_actor(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(id, 0);
    GM_CHECK_INT_PARAM(class_type, 0);
    ActorId id;
    id.m_id  = id;
    id.m_class = class_type;
    a_thread->PushInt(g_actorWorld.destroy_actor(id));
    return GM_OK;
}
static int GM_CDECL world_clear_actors(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(type, 0);
    g_actorWorld.clear_actors(type);
    return GM_OK;
}
static int GM_CDECL world_clear(gmThread* a_thread)
{
    g_actorWorld.clear();
    return GM_OK;
}
//-------------------------------------------------------------------------

void register_enum_values(gmMachine* machine, const char* libName, gmVariableEntry* entries, uint32_t numEntries)
{
    gmTableObject* table = machine->GetGlobals();
    if(libName) table = table->Get(machine, libName).GetTableObjectSafe();
    ENGINE_ASSERT(table, "can not find script table %s", libName);
    for(size_t i = 0; i < numEntries; ++i)
        table->Set(machine, entries[i].m_name, entries[i].m_value);
}

void register_script_api(gmMachine* machine)
{
    //----------------------------------------------------------
    // CORE
    static gmFunctionEntry s_core_binding[] =  
    {
        {"shut_down", script_shutdown_game },
        {"string_to_id", string_to_id},
        {"get_window_width", get_window_width },
        {"get_window_height", get_window_height },
        {"subsystems_ready", subsystems_ready},
        {"rgba_to_int", rgba_to_int },
        {"begin_profile", begin_profile},
        {"end_profile", end_profile},
        {"show_profile", show_profile},
#ifndef _RETAIL
        {"id_to_string", id_to_string},
#endif
    };
    machine->RegisterLibrary(s_core_binding, BX_COUNTOF(s_core_binding), 0, false);

    //----------------------------------------------------------
    // RESOURCE
    static gmFunctionEntry s_resource_binding[] =
    {
        {"get_package_status", resource_package_get_status},
        {"load_package", resource_package_load,},
        {"load_package_and_wait", resource_package_load_and_wait},
        {"unload_package", resource_package_unload},
        {"flush_package", resource_package_flush},
        {"find_resource", resource_find},
    };
    static gmVariableEntry s_resource_values[] =
    {
        {"LOADING", gmVariable(kResourceLoading)},
        {"OFFLINE", gmVariable(kResourceOffline)},
        {"ONLINE", gmVariable(kResourceOnline)},
        {"ERROR", gmVariable(kResourceError)},
        {"UNLOADING", gmVariable(kResourceRequestUnload)},
    };
    machine->RegisterLibrary(s_resource_binding, BX_COUNTOF(s_resource_binding), "resource");
    register_enum_values(machine, "resource", s_resource_values, BX_COUNTOF(s_resource_values));

    //----------------------------------------------------------
    // INPUT
    static gmFunctionEntry s_script_binding[] =  
    {
        {"is_key_down", input_is_key_down },
        {"is_key_just_pressed", input_is_key_just_pressed },
        {"is_mosue_down", input_is_mouse_down },
        {"is_mouse_just_pressed", input_is_mouse_just_pressed },
        {"mouse_pos", input_mouse_pos },
        {"mouse_last_pos", input_mouse_last_pos },
        {"is_mouse_moved", input_is_mouse_moved },
    };
    static gmVariableEntry s_input_values[] =
    {
        {"ESC", gmVariable(VK_ESCAPE)},
        {"ENTER", gmVariable(VK_RETURN)},
        {"SPACE", gmVariable(VK_SPACE)},
        {"F1", gmVariable(VK_F1)},
        {"F2", gmVariable(VK_F2)},
        {"F3", gmVariable(VK_F3)},
        {"F4", gmVariable(VK_F4)},
        {"F5", gmVariable(VK_F5)},
        {"F6", gmVariable(VK_F6)},
        {"F7", gmVariable(VK_F7)},
        {"F8", gmVariable(VK_F8)},
        {"F9", gmVariable(VK_F9)},
        {"F10", gmVariable(VK_F10)},
        {"F11", gmVariable(VK_F11)},
        {"F12", gmVariable(VK_F12)},
        {"LEFT", gmVariable(VK_LEFT)},
        {"RIGHT", gmVariable(VK_RIGHT)},
        {"UP", gmVariable(VK_UP)},
        {"DOWN", gmVariable(VK_DOWN)},
    };
    machine->RegisterLibrary(s_script_binding, BX_COUNTOF(s_script_binding), "input");
    register_enum_values(machine, "input", s_input_values, BX_COUNTOF(s_input_values));

    //----------------------------------------------------------
    // GUI
    static gmFunctionEntry s_gui_binding[] =
    {
        {"dbg_print", gui_dbg_print},
        {"draw_text", imgui_draw_text},
        {"draw_line", imgui_draw_line},
        {"draw_round_rect", imgui_draw_round_rect},
        {"draw_rect", imgui_draw_rect},
        {"border_button", imgui_border_button},
        {"begin_area", imgui_begin_area},
        {"end_area", imgui_end_area},
        {"indent", imgui_indent},
        {"unindent", imgui_unindent},
        {"separator", imgui_separator},
        {"separator_line", imgui_separator_line},
        {"button", imgui_button},
        {"item", imgui_item},
        {"check", imgui_check},
        {"collapse", imgui_collapse},
        {"label", imgui_label},
        {"color_label", imgui_color_label},
        {"value", imgui_value},
    };
    static gmVariableEntry s_gui_values[] =
    {
        {"TEXT_ALGIN_LEFT", gmVariable(ImguiTextAlign::Left)},
        {"TEXT_ALGIN_CENTER", gmVariable(ImguiTextAlign::Center)},
        {"TEXT_ALGIN_RIGHT", gmVariable(ImguiTextAlign::Right)},
        {"ALIGN_LEFT", gmVariable(ImguiAlign::Left)},
        {"ALIGN_LEFT_INDENTED", gmVariable(ImguiAlign::LeftIndented)},
        {"ALIGN_CENTER", gmVariable(ImguiAlign::Center)},
        {"ALIGN_CENTER_INDENTED", gmVariable(ImguiAlign::CenterIndented)},
        {"ALIGN_RIGHT", gmVariable(ImguiAlign::Right)},
        {"BORDER_LEFT", gmVariable(ImguiBorder::Left)},
        {"BORDER_RIGHT", gmVariable(ImguiBorder::Right)},
        {"BORDER_TOP", gmVariable(ImguiBorder::Top)},
        {"BORDER_BOTTOM", gmVariable(ImguiBorder::Bottom)},
    };
    machine->RegisterLibrary(s_gui_binding, BX_COUNTOF(s_gui_binding), "gui");
    register_enum_values(machine, "gui", s_gui_values, BX_COUNTOF(s_gui_values));

    //----------------------------------------------------------
    // GRAPHICS
    static gmFunctionEntry s_graphics_binding[] =
    {
        {"draw", graphics_draw},
        {"debug_add_line", debug_draw_add_line},
        {"debug_add_aabb", debug_draw_add_aabb},
        {"debug_add_axis", debug_draw_add_axis},
        {"debug_add_3d_text", debug_draw_add_3d_text},
        {"debug_add_sphere", debug_draw_add_sphere},
        {"debug_add_sphere", debug_draw_add_circle},
        {"debug_add_grid", debug_draw_add_grid},
        {"set_debug_mode", graphics_set_debug_mode},
    };
    static gmVariableEntry s_graphics_values[] =
    {
        "dummy", gmVariable(0),
    };
    machine->RegisterLibrary(s_graphics_binding, BX_COUNTOF(s_graphics_binding), "graphics");
    register_enum_values(machine, "graphics", s_graphics_values, BX_COUNTOF(s_graphics_values));

    //----------------------------------------------------------
    // WORLD
    static gmFunctionEntry s_world_binding[] =
    {
        {"set_shading_enviroment", world_set_shading_enviroment},
        {"num_of_actors", world_num_of_actors},
        {"create_actor", world_create_actor},
        {"destroy_actor", world_destroy_actor},
        {"clear_actors", world_clear_actors},
        {"clear", world_clear},
    };
    static gmVariableEntry s_world_values[] =
    {
        "LEVEL_GEOMETRY", gmVariable(kLevelGeometry),
        "PROP", gmVariable(kProp),
        "CHARACTER", gmVariable(kCharacter),
        "CLASS_NUM", gmVariable(kActorClassNum),
    };
    machine->RegisterLibrary(s_world_binding, BX_COUNTOF(s_world_binding), "world");
    register_enum_values(machine, "world", s_world_values, BX_COUNTOF(s_world_values));
}