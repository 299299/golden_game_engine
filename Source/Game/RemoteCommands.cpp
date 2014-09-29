#include "Engine.h"
#include "MathDefs.h"
#include "MemorySystem.h"
#include "Log.h"
#include "Win32Context.h"
#include "Resource.h"
#include "Camera.h"
#include "ShadingEnviroment.h"
#include "Actor.h"
#include "Graphics.h"
#include "DebugDraw.h"
#include "WebServerTool.h"
#include "Utils.h"
#include "Level.h"
//======================================================
#include <bx/bx.h>
#include <Common/Base/Container/Array/hkArray.h>
#include <Common/Base/Container/String/hkString.h>

using namespace gamedevwebtools;

void str_chr_remove(const char* input, char* output, char flag)
{
    const char* find = strchr(input, flag);
    memcpy(output, input, find - input);
}
void find_package_path(const char* input, char* packagePath)
{
    char packageName[64];
    memset(packageName, 0x00, sizeof(packageName));
    str_chr_remove(input, packageName, '/');
    sprintf(packagePath, "data/%s.package", packageName);
    LOGI("package path = %s", packagePath);
}

//======================================================================
// reload functions
typedef void (*__command_func__)(const char* data1, const char* data2);
void add_actor(const char* data1, const char* data2)
{
    g_actorWorld.create_actor(StringId(data1), hkQsTransform::getIdentity());
}
void clear_actors(const char* data1, const char* data2)
{
    g_actorWorld.clear();
}
void reload_resource(const char* data1, const char* data2)
{
    StringId resType(data1);
    StringId resName(data2);
    if(!resType)
    {
        LOGE("reload resource error, resource type is zero");
        return;
    }
    if(!resName)
    {
        LOGI("reload resources of type %s", data1);
        g_resourceMgr.reload_resource(resType);
    }
    else
    {
        LOGI("reload resources type %s, name = %s", data1, data2);
        char pathBuf[256];
        sprintf_s(pathBuf, "data/%s.%s", data2, data1);
        g_resourceMgr.reload_resource(resType, resName, pathBuf);
    }
}
void reload_resource_file(const char* data1, const char* data2)
{
    //remove data folder
    const char* tmp = strchr(data1, '/') + 1;
    //get resource name
    char resourceName[256];
    memset(resourceName, 0x00, sizeof(resourceName));
    str_chr_remove(tmp, resourceName, '.');
    const char* ext = strchr(tmp, '.') + 1;
    g_resourceMgr.reload_resource(StringId(ext), StringId(resourceName), data1);
}
void list_resources(const char* data1, const char* data2)
{
    StringId resType(data1);
    uint32_t totalNum = 0; 
    char nameBuf[256];

    LOGD("start listing resources type %s", data1);
    for(uint32_t i=0; i<g_resourceMgr.m_numPackages; ++i)
    {
        const ResourcePackage* package = g_resourceMgr.m_packages[i];
        const ResourceGroup* group = package->find_group(resType);
        if(!group) continue;
        for(uint32_t j=0; j<group->m_numResources; ++j)
        {
            const ResourceInfo& info = group->m_resources[j];
            ++totalNum;
            memset(nameBuf, 0x00, sizeof(nameBuf));
            char* name = (char*)package + info.m_offset;
            memcpy(nameBuf, name, info.m_size);
            LOGD("resource name = %s", nameBuf);
        }
    }
    LOGD("end listing resources type of %s, total num = %d", data1, totalNum);
}
void exit_command(const char* data1, const char* data2)
{
    g_engine.shutdown();
}
void load_package(const char* data1, const char* data2)
{
    g_resourceMgr.load_package_and_wait(data1);
}

void list_command(const char* data1, const char* data2);
struct RemoteCommand
{
    __command_func__    m_func;
    const char*         m_name;
};
#define REMOTE_CMD(func) {func, #func}
static RemoteCommand gCommands[] = 
{
    REMOTE_CMD(clear_actors), 
    REMOTE_CMD(add_actor), 
    REMOTE_CMD(reload_resource),
    REMOTE_CMD(reload_resource_file),
    REMOTE_CMD(list_resources),
    REMOTE_CMD(load_package),
    REMOTE_CMD(list_command),
    REMOTE_CMD(exit_command),
};
void list_command(const char* data1, const char* data2)
{
    int numOfCommands = BX_COUNTOF(gCommands);
    LOGI("Avaiable commands count = %d.", numOfCommands);
    for(int i=0; i<numOfCommands; ++i)
    {
        LOGI("command[%d] = [%s]", i, gCommands[i].m_name);
    }
}
int parse_command(const char* cmd_name)
{
    for(int i=0; i<BX_COUNTOF(gCommands); ++i)
    {
        if(!hkString::strCasecmp(cmd_name, gCommands[i].m_name))
            return i;
    }
    return -1;
}
void console_command(const gamedevwebtools::Message &message)
{
    const char* cmd = message.fields()[0].asString();
    const char* data1 = message.fields()[1].asString();
    const char* data2 = message.fields()[2].asString();
    bool bLog = strcmp(cmd, "camera_transform") && strcmp(cmd, "object_transform");
    if(bLog) LOGD("onConsoleCommand cmd = %s, data1 = %s, data2 = %s", cmd, data1, data2);
    int command = parse_command(cmd);
    if(command < 0)
    {
        LOGE("unknown command.");
        return;
    }
    gCommands[command].m_func(data1, data2);   
}

void init_remote_commands()
{
    if(!g_webServerTool) return;
    g_webServerTool->connect("remote.command", console_command);
}
