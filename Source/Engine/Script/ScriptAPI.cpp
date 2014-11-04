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
#include "Level.h"
#include "DataDef.h"
#include "PhysicsWorld.h"
#include "Texture.h"
#include "Camera.h"
#include "Script.h"
#include "AnimRig.h"
#include "Movement.h"
#include "CommandAPI.h"
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

extern int find_component_type(const StringId& typeName);
extern uint32_t num_components(uint32_t type);
extern void* get_components(uint32_t type);

#define SIMPLE_FUNC_REG(func_name, script_name) \
        static int GM_CDECL script_name(gmThread* a_thread) { func_name; return GM_OK; }

gmTableNode* find_table_node(gmTableObject* table, const char* key)
{
    gmTableIterator iter;
    gmTableNode* node = table->GetFirst(iter);
    while(node)
    {
        if(node->m_key.m_type != GM_STRING) continue;
        const char* key_name = ((gmStringObject*)node->m_key.m_value.m_ref)->GetString();
        if(!strcmp(key, key_name)) return node;
        node = table->GetNext(iter);
    }
    return 0;
}

//-------------------------------------------------------------------------
// CORE
SIMPLE_FUNC_REG(g_engine.shutdown(), script_shutdown_game);
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
    GM_CHECK_FLOAT_OR_INT_PARAM(r, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(g, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(b, 2);
    GM_FLOAT_OR_INT_PARAM(a, 3, 255);
    a_thread->PushInt(imguiRGBA((uint8_t)r,(uint8_t)g,(uint8_t)b,(uint8_t)a));
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
SIMPLE_FUNC_REG(g_profiler.end_block(), end_profile);
static int GM_CDECL script_draw_profile(gmThread* a_thread)
{
    GM_INT_PARAM(show_unused, 0, 0);
    GM_INT_PARAM(show_total, 1, 0);
    GM_INT_PARAM(max_depth, 2, -1);
    g_profiler.dump((bool)show_unused, (bool)show_total, (uint32_t)max_depth);
    return GM_OK;
}
static int GM_CDECL script_require(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(script_file, 0);
    ScriptResource* res = FIND_RESOURCE(ScriptResource, StringId(script_file));
    if(!res) return GM_OK;
    res->pre_load();
    return GM_OK;
}
static int GM_CDECL get_component_instance_num(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(comp_name, 0);
    int type = find_component_type(StringId(comp_name));
    int nRet = 0;
    if(type >= 0) nRet = num_components(type);
    a_thread->PushInt(nRet);
    return GM_OK;
}
static int GM_CDECL script_msg_box(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_STRING_PARAM(text, 0);
    GM_CHECK_STRING_PARAM(title, 1);
    msg_box(text, title);
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
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(border, 0);
    GM_CHECK_INT_PARAM(checked, 1);
    GM_INT_PARAM(enabled, 1, 2);
    a_thread->PushInt(imguiBorderButton((ImguiBorder::Enum)border, checked, enabled));
    return GM_OK;
}
static int GM_CDECL imgui_begin_area(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(4);
    GM_CHECK_STRING_PARAM(name, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(w, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(h, 4);
    GM_INT_PARAM(enabled, 5, 1);
    imguiBeginArea(name, (int)x, (int)y, (int)w, (int)h, enabled);
    return GM_OK;
}
SIMPLE_FUNC_REG(imguiEndArea(), imgui_end_area);
SIMPLE_FUNC_REG(imguiIndent(), imgui_indent);
SIMPLE_FUNC_REG(imguiUnindent(), imgui_unindent);
SIMPLE_FUNC_REG(imguiSeparator(), imgui_separator);
SIMPLE_FUNC_REG(imguiSeparatorLine(), imgui_separator_line);
static int GM_CDECL imgui_button(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(text, 0);
    GM_INT_PARAM(enabled, 1, 1);
    GM_INT_PARAM(align, 2, ImguiAlign::LeftIndented);
    a_thread->PushInt(imguiButton(text, enabled, (ImguiAlign::Enum)align));
    return GM_OK;
}
static int GM_CDECL imgui_item(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(text, 0);
    GM_INT_PARAM(enabled, 1, 1);
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
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_STRING_PARAM(text, 0);
    GM_CHECK_STRING_PARAM(sub_text, 1);
    GM_CHECK_INT_PARAM(checked, 2);
    GM_INT_PARAM(enabled, 3, 1);
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
static int GM_CDECL imgui_get_text_length(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_STRING_PARAM(text, 0);
    a_thread->PushFloat(imguiGetTextLength(text, imguiGetCurrentFont()));
    return GM_OK;
}
static int GM_CDECL imgui_begin_scroll(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_FLOAT_OR_INT_PARAM(height, 0);
    GM_CHECK_STRING_PARAM(var_name, 1);
    GM_CHECK_TABLE_PARAM(table, 2);
    GM_INT_PARAM(enabled, 3, 1);
    gmTableNode* node = find_table_node(table, var_name);
    if(!node) 
    {
        GM_EXCEPTION_MSG("table has no variable named %s", var_name);
        return GM_EXCEPTION;
    }
    int32_t* fp = &node->m_value.m_value.m_int;
    a_thread->PushInt(imguiBeginScroll((int32_t)height, fp, enabled));
    return GM_OK;
}
SIMPLE_FUNC_REG(imguiEndScroll(), imgui_end_scroll);
static int GM_CDECL imgui_begin_scroll_area(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(6);
    GM_CHECK_STRING_PARAM(name, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(x, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(y, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(w, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(h, 4);
    GM_CHECK_STRING_PARAM(var_name, 5);
    GM_CHECK_TABLE_PARAM(table, 6);
    GM_INT_PARAM(enabled, 7, 1);
    gmTableNode* node = find_table_node(table, var_name);
    if(!node) 
    {
        GM_EXCEPTION_MSG("table has no variable named %s", var_name);
        return GM_EXCEPTION;
    }
    int32_t* fp = &node->m_value.m_value.m_int;
    a_thread->PushInt(imguiBeginScrollArea(name, (int32_t)x, (int32_t)y, (int32_t)w, (int32_t)h, fp));
    return GM_OK;
}
SIMPLE_FUNC_REG(imguiEndScrollArea(), imgui_end_scroll_area);
static int GM_CDECL imgui_float_slider(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(6);
    GM_CHECK_STRING_PARAM(text, 0);
    GM_CHECK_STRING_PARAM(var_name, 1);
    GM_CHECK_TABLE_PARAM(table, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(vmin, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(vmax, 4);
    GM_CHECK_FLOAT_OR_INT_PARAM(inc, 5);
    GM_INT_PARAM(enabled, 6, 1);
    GM_INT_PARAM(align, 7, ImguiAlign::LeftIndented);
    gmTableNode* node = find_table_node(table, var_name);
    if(!node) 
    {
        GM_EXCEPTION_MSG("table has no variable named %s", var_name);
        return GM_EXCEPTION;
    }
    if(node->m_value.m_type != GM_FLOAT)
    {
        GM_EXCEPTION_MSG("except float variable named %s", var_name);
        return GM_EXCEPTION;
    }
    float& f = node->m_value.m_value.m_float;
    a_thread->PushInt(imguiSlider(text, f, vmin, vmax, inc, (bool)enabled, (ImguiAlign::Enum)align));
    return GM_OK;
}
static int GM_CDECL imgui_int_slider(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(5);
    GM_CHECK_STRING_PARAM(text, 0);
    GM_CHECK_STRING_PARAM(var_name, 1);
    GM_CHECK_TABLE_PARAM(table, 2);
    GM_CHECK_INT_PARAM(vmin, 3);
    GM_CHECK_INT_PARAM(vmax, 4);
    GM_INT_PARAM(enabled, 5, 1);
    GM_INT_PARAM(align, 6, ImguiAlign::LeftIndented);
    gmTableNode* node = find_table_node(table, var_name);
    if(!node) 
    {
        GM_EXCEPTION_MSG("table has no variable named %s", var_name);
        return GM_EXCEPTION;
    }
    if(node->m_value.m_type != GM_INT)
    {
        GM_EXCEPTION_MSG("except int variable named %s", var_name);
        return GM_EXCEPTION;
    }
    int& i = node->m_value.m_value.m_int;
    a_thread->PushInt(imguiSlider(text, i, vmin, vmax, (bool)enabled, (ImguiAlign::Enum)align));
    return GM_OK;
}
static int GM_CDECL imgui_bool(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_STRING_PARAM(text, 0);
    GM_CHECK_STRING_PARAM(var_name, 1);
    GM_CHECK_TABLE_PARAM(table, 2);
    GM_INT_PARAM(enabled, 3, 1);
    gmTableNode* node = find_table_node(table, var_name);
    if(!node) 
    {
        GM_EXCEPTION_MSG("table has no variable named %s", var_name);
        return GM_EXCEPTION;
    }
    if(node->m_value.m_type != GM_INT)
    {
        GM_EXCEPTION_MSG("except int variable named %s", var_name);
        return GM_EXCEPTION;
    }
    int& i = node->m_value.m_value.m_int;
    imguiBool(text, (bool &)i, (bool)enabled);
    return GM_OK;
}
static int GM_CDECL imgui_color_wheel(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_FLOAT_OR_INT_PARAM(r, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(g, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(b, 2);
    GM_INT_PARAM(respectIndentation, 3, 0);
    GM_INT_PARAM(enabled, 4, 1);
    float rgb[] = {r,g,b};
    imguiColorWheel(rgb, respectIndentation, enabled);
    return GM_OK;
}
static int GM_CDECL imgui_color_wheel_named(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(7);
    GM_CHECK_STRING_PARAM(str, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(r, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(g, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(b, 3);
    GM_CHECK_STRING_PARAM(var_name, 4);
    GM_CHECK_TABLE_PARAM(table, 5);
    GM_INT_PARAM(enabled, 6, 1);
    gmTableNode* node = find_table_node(table, var_name);
    if(!node) 
    {
        GM_EXCEPTION_MSG("table has no variable named %s", var_name);
        return GM_EXCEPTION;
    }
    if(node->m_value.m_type != GM_INT)
    {
        GM_EXCEPTION_MSG("except int variable named %s", var_name);
        return GM_EXCEPTION;
    }
    int& i = node->m_value.m_value.m_int;
    float rgb[] = {r,g,b};
    imguiColorWheel(str, rgb, (bool&)i, enabled);
    return GM_OK;
}
static int GM_CDECL imgui_is_mouse_over_area(gmThread* a_thread)
{
    a_thread->PushInt((int)imguiMouseOverArea());
    return GM_OK;
}
static int GM_CDECL imgui_draw_image(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(4);
    GM_CHECK_INT_PARAM(image_name, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(lod, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(width, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(height, 3);
    GM_INT_PARAM(align, 4, ImguiAlign::LeftIndented);
    Texture* tex = FIND_RESOURCE(Texture, StringId(image_name));
    if(!tex) return GM_OK;
    tex->bringin(0);
    imguiImage(tex->m_handle, lod, (int)width, (int)height, (ImguiAlign::Enum)align);
    return GM_OK;
}
static int GM_CDECL imgui_draw_image_scaled(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(4);
    GM_CHECK_INT_PARAM(image_name, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(lod, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(scale, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(aspect, 3);
    GM_INT_PARAM(align, 4, ImguiAlign::LeftIndented);
    Texture* tex = FIND_RESOURCE(Texture, StringId(image_name));
    if(!tex) return GM_OK;
    tex->bringin(0);
    imguiImage(tex->m_handle, lod, scale, aspect, (ImguiAlign::Enum)align);
    return GM_OK;
}
static int GM_CDECL imgui_draw_image_channel(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(5);
    GM_CHECK_INT_PARAM(image_name, 0);
    GM_CHECK_INT_PARAM(channel, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(lod, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(width, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(height, 4);
    GM_INT_PARAM(align, 5, ImguiAlign::LeftIndented);
    Texture* tex = FIND_RESOURCE(Texture, StringId(image_name));
    if(!tex) return GM_OK;
    tex->bringin(0);
    imguiImageChannel(tex->m_handle, (uint8_t)channel, lod, (int)width, (int)height, (ImguiAlign::Enum)align);
    return GM_OK;
}
static int GM_CDECL imgui_draw_image_channel_scaled(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(5);
    GM_CHECK_INT_PARAM(image_name, 0);
    GM_CHECK_INT_PARAM(channel, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(lod, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(scale, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(aspect, 4);
    GM_INT_PARAM(align, 5, ImguiAlign::LeftIndented);
    Texture* tex = FIND_RESOURCE(Texture, StringId(image_name));
    if(!tex) return GM_OK;
    tex->bringin(0);
    imguiImageChannel(tex->m_handle, (uint8_t)channel, lod, scale, aspect, (ImguiAlign::Enum)align);
    return GM_OK;
}
static int GM_CDECL imgui_get_widget_x(gmThread* a_thread)
{
    a_thread->PushInt(imguiGetWidgetX());
    return GM_OK;
}
static int GM_CDECL imgui_get_widget_y(gmThread* a_thread)
{
    a_thread->PushInt(imguiGetWidgetY());
    return GM_OK;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// DRAW
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
    GM_CHECK_NUM_PARAMS(6);
    GM_CHECK_FLOAT_OR_INT_PARAM(x0, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(y0, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(z0, 2);
    GM_CHECK_FLOAT_OR_INT_PARAM(x1, 3);
    GM_CHECK_FLOAT_OR_INT_PARAM(y1, 4);
    GM_CHECK_FLOAT_OR_INT_PARAM(z1, 5);
    GM_FLOAT_OR_INT_PARAM(size, 6, 0.25f);
    GM_INT_PARAM(depth, 7, 0);
    hkQsTransform t;
    t.setIdentity();
    t.m_translation.set(x0, y0, z0);
    t.m_rotation.setFromEulerAngles(x1, y1, z1);
    g_debugDrawMgr.add_axis(t, size, (bool)depth);
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
static uint32_t g_debug_mode = BGFX_DEBUG_TEXT;
static uint32_t modes[] = {BGFX_DEBUG_IFH, BGFX_DEBUG_STATS, BGFX_DEBUG_TEXT};
static int GM_CDECL graphics_set_debug_mode(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(index, 0);
    uint32_t mode = modes[index];
    bool wireframe = HAS_BITS(g_debug_mode, BGFX_DEBUG_WIREFRAME);
    g_debug_mode = mode;
    if(wireframe) ADD_BITS(g_debug_mode, BGFX_DEBUG_WIREFRAME);
    else REMOVE_BITS(g_debug_mode, BGFX_DEBUG_WIREFRAME);
    bgfx::setDebug(g_debug_mode);
    return GM_OK;
}
static int GM_CDECL graphics_set_wireframe(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(wireframe, 0);
    if(wireframe) ADD_BITS(g_debug_mode, BGFX_DEBUG_WIREFRAME);
    else REMOVE_BITS(g_debug_mode, BGFX_DEBUG_WIREFRAME);
    bgfx::setDebug(g_debug_mode);
    return GM_OK;
}
static int GM_CDECL graphics_update_debug_camera(gmThread* a_thread)
{
    extern DebugFPSCamera g_fpsCamera;
    GM_FLOAT_PARAM(dt, 0, 1.0f/60.0f);
    g_fpsCamera.update(dt);
    return GM_OK;
}
extern void draw_debug_models();
extern void draw_debug_lights();
extern void draw_debug_animation();
SIMPLE_FUNC_REG(draw_debug_models(), debug_draw_models);
SIMPLE_FUNC_REG(draw_debug_lights(), debug_draw_lights);
SIMPLE_FUNC_REG(draw_debug_animation(), debug_draw_animation);
static int GM_CDECL camera_set_position(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_FLOAT_OR_INT_PARAM(pos_x, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(pos_y, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(pos_z, 2);
    float pos[] = {pos_x, pos_y, pos_z};
    float at[3];
    bx::vec3Move(at, g_camera.m_at);
    g_camera.update(pos, at);
    extern DebugFPSCamera g_fpsCamera;
    g_fpsCamera.set(pos, at);
    return GM_OK;
}
static int GM_CDECL camera_set_lookat(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_FLOAT_OR_INT_PARAM(pos_x, 0);
    GM_CHECK_FLOAT_OR_INT_PARAM(pos_y, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(pos_z, 2);
    float pos[] = {pos_x, pos_y, pos_z};
    float eye[3];
    bx::vec3Move(eye, g_camera.m_eye);
    g_camera.update(eye, pos);
    extern DebugFPSCamera g_fpsCamera;
    g_fpsCamera.set(eye, pos);
    return GM_OK;
}
//-------------------------------------------------------------------------

//-------------------------------------------------------------------------
// PHYSICS
static int GM_CDECL physics_create_world(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(physics_config, 0);
    bool b_ok = false;
    PhysicsConfig* config = FIND_RESOURCE(PhysicsConfig, StringId(physics_config));
    if(config)
    {
        g_physicsWorld.create_world(config);
        b_ok = true;
    }
    a_thread->PushInt(b_ok);
    return GM_OK;
}
static int GM_CDECL physics_create_plane(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_FLOAT_OR_INT_PARAM(size, 0);
    g_physicsWorld.create_plane(size);
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
    GM_FLOAT_OR_INT_PARAM(t0, 1, 0);
    GM_FLOAT_OR_INT_PARAM(t1, 2, 0);
    GM_FLOAT_OR_INT_PARAM(t2, 3, 0);
    GM_FLOAT_OR_INT_PARAM(t3, 4, 0);
    GM_FLOAT_OR_INT_PARAM(t4, 5, 0);
    GM_FLOAT_OR_INT_PARAM(t5, 6, 0);
    GM_FLOAT_OR_INT_PARAM(t6, 7, 1);
    GM_FLOAT_OR_INT_PARAM(t7, 8, 1);
    GM_FLOAT_OR_INT_PARAM(t8, 9, 1);
    GM_FLOAT_OR_INT_PARAM(when, 10, 0);
    float transform[] = {t0, t1, t2, t3, t4, t5, t6, t7, t8};
    command_create_actor(StringId(type), transform, when);
    return GM_OK;
}
static int GM_CDECL world_destroy_actor(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_FLOAT_OR_INT_PARAM(when, 1, 0);
    command_destroy_actor(actor_id, when);
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
#define GET_ACTOR() Actor* actor = g_actorWorld.get_actor((uint32_t)packed_id);
        
static int GM_CDECL actor_has_key(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(packed_id, 0);
    GM_CHECK_INT_PARAM(key_name, 1);
    GET_ACTOR();
    bool b_has = false;
    if(actor) b_has = actor->has_key(StringId(key_name));
    a_thread->PushInt(b_has);
    return GM_OK;
}
static int GM_CDECL actor_get_float(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(packed_id, 0);
    GM_CHECK_INT_PARAM(key_name, 1);
    GET_ACTOR();
    float ret = 0;
    actor->get_key(StringId(key_name), ret);
    a_thread->PushFloat(ret);
    return GM_OK;
}
static int GM_CDECL actor_get_string(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(packed_id, 0);
    GM_CHECK_INT_PARAM(key_name, 1);
    GET_ACTOR();
    StringId ret;
    actor->get_key(StringId(key_name), ret);
    a_thread->PushInt(ret.value());
    return GM_OK;
}
static int GM_CDECL actor_get_int(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(packed_id, 0);
    GM_CHECK_INT_PARAM(key_name, 1);
    GET_ACTOR();
    int ret = 0;
    actor->get_key(StringId(key_name), ret);
    a_thread->PushInt(ret);
    return GM_OK;
}
static int GM_CDECL actor_set_float(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_INT_PARAM(packed_id, 0);
    GM_CHECK_INT_PARAM(key_name, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(key_value, 2);
    GET_ACTOR();
    a_thread->PushInt(actor->set_key(StringId(key_name), key_value));
    return GM_OK;
}
static int GM_CDECL actor_set_string(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_INT_PARAM(packed_id, 0);
    GM_CHECK_INT_PARAM(key_name, 1);
    GM_CHECK_INT_PARAM(key_value, 2);
    GET_ACTOR();
    a_thread->PushInt(actor->set_key(StringId(key_name), StringId(key_value)));
    return GM_OK;
}
static int GM_CDECL actor_set_int(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_INT_PARAM(packed_id, 0);
    GM_CHECK_INT_PARAM(key_name, 1);
    GM_CHECK_FLOAT_OR_INT_PARAM(key_value, 2);
    GET_ACTOR();
    a_thread->PushInt(actor->set_key(StringId(key_name), (int)key_value));
    return GM_OK;
}
static int GM_CDECL level_load(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(level_name, 0);
    GM_FLOAT_OR_INT_PARAM(when, 1, 0.0f);
    command_load_level(StringId(level_name), when);
    return GM_OK;
}
static int GM_CDECL level_unload(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(level_name, 0);
    GM_FLOAT_OR_INT_PARAM(when, 1, 0.0f);
    command_unload_level(StringId(level_name), when);
    return GM_OK;
}
#define SCRIPT_GET_ANIM_RIG()\
        Actor* actor = g_actorWorld.get_actor((uint32_t)actor_id);\
        if(!actor) { a_thread->PushInt(-1); return GM_OK; }\
        extern void* get_anim_rig(Id);\
        AnimRigInstance* rig = (AnimRigInstance*)get_anim_rig(actor->m_components[kComponentAnimRig]);\
        if(!rig) { a_thread->PushInt(-1); return GM_OK; }

static int GM_CDECL actor_get_joint_index(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_CHECK_INT_PARAM(joint_name, 1);
    SCRIPT_GET_ANIM_RIG();
    a_thread->PushInt(rig->m_resource->find_joint_index(StringId(joint_name)));
    return GM_OK;
}
static int GM_CDECL actor_get_animation_index(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_CHECK_INT_PARAM(anim_name, 1);
    SCRIPT_GET_ANIM_RIG();
    a_thread->PushInt(rig->m_resource->find_animation_index(StringId(anim_name)));
    return GM_OK;
}
static int GM_CDECL actor_ease_in_animation(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_CHECK_INT_PARAM(index, 1);
    GM_FLOAT_PARAM(blend_time, 2, 0.2f);
    GM_INT_PARAM(looped, 3, 1);
    GM_INT_PARAM(layer, 4, 0);
    GM_FLOAT_PARAM(when, 5, 0.0f);
    GM_INT_PARAM(type, 6, kEaseCurveSmooth);
    command_easein_animation(actor_id, index, blend_time, layer, looped, type, when);
    return GM_OK;
}
static int GM_CDECL actor_ease_out_animation(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(3);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_CHECK_INT_PARAM(index, 1);
    GM_CHECK_FLOAT_PARAM(blend_time, 2);
    GM_FLOAT_PARAM(when, 3, 0.0f);
    GM_INT_PARAM(type, 4, kEaseCurveSmooth);
    command_easeout_animation(actor_id, index, blend_time, type, when);
    return GM_OK;
}
static int GM_CDECL actor_is_playing_animation(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_INT_PARAM(index, 1, -1);
    SCRIPT_GET_ANIM_RIG();
    if(index < 0) a_thread->PushInt(rig->is_playing_animation() ? 1 : 0);
    else a_thread->PushInt(rig->is_playing_animation(index) ? 1 : 0);
    return GM_OK;
}
static int GM_CDECL actor_easeout_layers(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_CHECK_INT_PARAM(layer, 1);
    GM_FLOAT_PARAM(blend_time, 2, 0.2f);
    GM_FLOAT_PARAM(when, 3, 0.0f);
    GM_INT_PARAM(type, 4, kEaseCurveSmooth);
    command_easeout_layers(actor_id, layer, blend_time, type, when);
    return GM_OK;
}
static int GM_CDECL actor_set_animation_weight(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_CHECK_INT_PARAM(index, 1);
    GM_CHECK_FLOAT_PARAM(weight, 2);
    GM_FLOAT_PARAM(when, 2, 0.0f);
    command_set_animation_weight(actor_id, index, weight, when);
    return GM_OK;
}
static int GM_CDECL actor_set_animation_speed(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_CHECK_INT_PARAM(index, 1);
    GM_CHECK_FLOAT_PARAM(speed, 2);
    GM_FLOAT_PARAM(when, 2, 0.0f);
    command_set_animation_speed(actor_id, index, speed, when);
    return GM_OK;
}
static int GM_CDECL actor_set_animation_time(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_CHECK_INT_PARAM(index, 1);
    GM_CHECK_FLOAT_PARAM(time, 2);
    GM_FLOAT_PARAM(when, 2, 0.0f);
    SCRIPT_GET_ANIM_RIG();
    command_set_animation_time(actor_id, index, time, when);
    return GM_OK;
}
#define ACTOR_ANIM_GET(param_num)\
        GM_CHECK_NUM_PARAMS(param_num);\
        GM_CHECK_INT_PARAM(actor_id, 0);\
        GM_CHECK_INT_PARAM(index, 1);\
        SCRIPT_GET_ANIM_RIG();\
        return GM_OK;

static int GM_CDECL actor_get_animation_weight(gmThread* a_thread)
{
    ACTOR_ANIM_GET(2);
    a_thread->PushFloat(rig->get_animation_weight(index));
    return GM_OK;
}
static int GM_CDECL actor_get_animation_speed(gmThread* a_thread)
{
    ACTOR_ANIM_GET(2);
    a_thread->PushFloat(rig->get_animation_speed(index));
    return GM_OK;
}
static int GM_CDECL actor_get_animation_time(gmThread* a_thread)
{
    ACTOR_ANIM_GET(2);
    a_thread->PushFloat(rig->get_animation_time(index));
    return GM_OK;
}
static int GM_CDECL actor_get_animation_closest_beat(gmThread* a_thread)
{
    ACTOR_ANIM_GET(2);
    a_thread->PushInt(rig->get_closest_beat(index));
    return GM_OK;
}
static int GM_CDECL actor_get_animation_first_beat(gmThread* a_thread)
{
    ACTOR_ANIM_GET(3);
    GM_CHECK_INT_PARAM(type, 2);
    a_thread->PushInt(rig->get_first_beat(index, type));
    return GM_OK;
}
static int GM_CDECL actor_get_animation_beat_time(gmThread* a_thread)
{
    ACTOR_ANIM_GET(3);
    GM_CHECK_INT_PARAM(beat_index, 2);
    a_thread->PushFloat(rig->get_beat_time(index, beat_index));
    return GM_OK;
}
static int GM_CDECL actor_get_animation_beat_type(gmThread* a_thread)
{
    ACTOR_ANIM_GET(3);
    GM_CHECK_INT_PARAM(beat_index, 2);
    a_thread->PushInt(rig->get_beat_type(index, beat_index));
    return GM_OK;
}
static int GM_CDECL actor_get_animation_next_sync_time(gmThread* a_thread)
{
    ACTOR_ANIM_GET(3);
    GM_CHECK_INT_PARAM(index_1, 2);
    a_thread->PushFloat(rig->next_anim_sync_time(index, index_1));
    return GM_OK;
}
#define SCRIPT_GET_MOVEMENT()\
        Actor* actor = g_actorWorld.get_actor((uint32_t)actor_id);\
        if(!actor) { a_thread->PushInt(-1); return GM_OK; }\
        extern void* get_movement(Id);\
        MovementInstance* move = (MovementInstance*)get_movement(actor->m_components[kComponentMovement]);\
        if(!move) { a_thread->PushInt(-1); return GM_OK; }
static int GM_CDECL actor_set_movement_motion_weight(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_CHECK_FLOAT_PARAM(weight, 1);
    SCRIPT_GET_MOVEMENT();
    move->m_motionWeight = weight;
    return GM_OK;
}
static int GM_CDECL actor_get_movement_motion_weight(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(actor_id, 0);
    SCRIPT_GET_MOVEMENT();
    a_thread->PushFloat(move->m_motionWeight);
    return GM_OK;
}
static int GM_CDECL actor_set_movement_velocity_weight(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_CHECK_FLOAT_PARAM(weight, 1);
    SCRIPT_GET_MOVEMENT();
    move->m_velocityWeight = weight;
    return GM_OK;
}
static int GM_CDECL actor_get_movement_velocity_weight(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(actor_id, 0);
    SCRIPT_GET_MOVEMENT();
    a_thread->PushFloat(move->m_velocityWeight);
    return GM_OK;
}
static int GM_CDECL actor_set_movement_linear_velocity(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(4);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_CHECK_FLOAT_PARAM(velocity_x, 1);
    GM_CHECK_FLOAT_PARAM(velocity_y, 2);
    GM_CHECK_FLOAT_PARAM(velocity_z, 3);
    SCRIPT_GET_MOVEMENT();
    move->m_linearVelocity.set(velocity_x, velocity_y, velocity_z);
    return GM_OK;
}
static int GM_CDECL actor_set_movement_rotate_speed(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(2);
    GM_CHECK_INT_PARAM(actor_id, 0);
    GM_CHECK_FLOAT_PARAM(rotate_speed, 1);
    SCRIPT_GET_MOVEMENT();
    move->m_rotateSpeed = rotate_speed;
    return GM_OK;
}
static int GM_CDECL actor_get_movement_rotate_speed(gmThread* a_thread)
{
    GM_CHECK_NUM_PARAMS(1);
    GM_CHECK_INT_PARAM(actor_id, 0);
    SCRIPT_GET_MOVEMENT();
    a_thread->PushFloat(move->m_rotateSpeed);
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
    #define REG_LIB(name, binding) machine->RegisterLibrary(binding, BX_COUNTOF(binding), #name);
    #define REG_ENUM(name, values) register_enum_values(machine, #name, values, BX_COUNTOF(values));

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
        {"draw_profile", script_draw_profile},
        {"require", script_require},
        {"num_components", get_component_instance_num},
        {"msg_box", script_msg_box},
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
    REG_LIB(resource, s_resource_binding);
    REG_ENUM(resource, s_resource_values);

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
    REG_LIB(input, s_script_binding);
    REG_ENUM(input, s_input_values);
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
        {"get_text_length", imgui_get_text_length},
        {"begin_scroll", imgui_begin_scroll},
        {"end_scroll", imgui_end_scroll},
        {"begin_scroll_area", imgui_begin_scroll_area},
        {"end_scroll_area", imgui_end_scroll_area},
        {"float_slider", imgui_float_slider},
        {"int_slider", imgui_int_slider},
        {"bool", imgui_bool},
        {"color_wheel", imgui_color_wheel},
        {"color_wheel_named", imgui_color_wheel_named},
        {"is_mouse_over_area", imgui_is_mouse_over_area},
        {"draw_image", imgui_draw_image},
        {"draw_image_scaled", imgui_draw_image_scaled},
        {"draw_image_channel", imgui_draw_image_channel},
        {"draw_image_channel_scaled", imgui_draw_image_channel_scaled},
        {"get_widget_x", imgui_get_widget_x},
        {"get_widget_y", imgui_get_widget_y}
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
    REG_LIB(gui, s_gui_binding);
    REG_ENUM(gui, s_gui_values);
    //----------------------------------------------------------
    // GRAPHICS
    static gmFunctionEntry s_graphics_binding[] =
    {
        {"debug_add_line", debug_draw_add_line},
        {"debug_add_aabb", debug_draw_add_aabb},
        {"debug_add_axis", debug_draw_add_axis},
        {"debug_add_3d_text", debug_draw_add_3d_text},
        {"debug_add_sphere", debug_draw_add_sphere},
        {"debug_add_sphere", debug_draw_add_circle},
        {"debug_add_grid", debug_draw_add_grid},
        {"set_debug_mode", graphics_set_debug_mode},
        {"set_wireframe", graphics_set_wireframe},
        {"update_debug_camera", graphics_update_debug_camera},
        {"debug_draw_models", debug_draw_models},
        {"debug_draw_lights", debug_draw_lights},
        {"debug_draw_animation", debug_draw_animation},
        {"camera_set_position", camera_set_position},
        {"camera_set_lookat", camera_set_lookat},
    };
    static gmVariableEntry s_graphics_values[] =
    {
        "dummy", gmVariable(0),
    };
    REG_LIB(graphics, s_graphics_binding);
    REG_ENUM(graphics, s_graphics_values);
    //----------------------------------------------------------
    // WORLD
    static gmFunctionEntry s_physics_binding[] =
    {
        {"create_world", physics_create_world},
        {"create_plane", physics_create_plane},
    };
    REG_LIB(physics, s_physics_binding);

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
        {"actor_has_key", actor_has_key},
        {"actor_get_float", actor_get_float},
        {"actor_get_string", actor_get_string},
        {"actor_get_int", actor_get_int},
        {"actor_set_float", actor_set_float},
        {"actor_set_int", actor_set_int},
        {"actor_set_string", actor_set_string},
        {"load_level", level_load},
        {"unload_level", level_unload},
        {"actor_get_joint_index", actor_get_joint_index},
        {"actor_get_animation_index", actor_get_animation_index},
        {"actor_ease_in_animation", actor_ease_in_animation},
        {"actor_ease_out_animation", actor_ease_out_animation},
        {"actor_is_playing_animation", actor_is_playing_animation},
        {"actor_easeout_layers", actor_easeout_layers},
        {"actor_set_animation_weight", actor_set_animation_weight},
        {"actor_set_animation_speed", actor_set_animation_speed},
        {"actor_set_animation_time", actor_set_animation_time},
        {"actor_get_animation_weight", actor_get_animation_weight},
        {"actor_get_animation_speed", actor_get_animation_speed},
        {"actor_get_animation_time", actor_get_animation_time},
        {"actor_get_animation_closest_beat", actor_get_animation_closest_beat},
        {"actor_get_animation_first_beat", actor_get_animation_first_beat},
        {"actor_get_animation_beat_time", actor_get_animation_beat_time},
        {"actor_get_animation_beat_type", actor_get_animation_beat_type},
        {"actor_get_animation_next_sync_time", actor_get_animation_next_sync_time},
        {"actor_set_movement_motion_weight", actor_set_movement_motion_weight},
        {"actor_get_movement_motion_weight", actor_get_movement_motion_weight},
        {"actor_set_movement_velocity_weight", actor_set_movement_velocity_weight},
        {"actor_get_movement_velocity_weight", actor_get_movement_velocity_weight},
        {"actor_set_movement_linear_velocity", actor_set_movement_linear_velocity},
        {"actor_set_movement_rotate_speed", actor_set_movement_rotate_speed},
        {"actor_get_movement_rotate_speed", actor_get_movement_rotate_speed},
    };
    static gmVariableEntry s_world_values[] =
    {
        "LEVEL_GEOMETRY", gmVariable(kLevelGeometry),
        "PROP", gmVariable(kProp),
        "CHARACTER", gmVariable(kCharacter),
        "CLASS_NUM", gmVariable(kActorClassNum),
    };
    REG_LIB(world, s_world_binding);
    REG_ENUM(world, s_world_values);
}