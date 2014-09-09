#include "Engine.h"
#include "MathDefs.h"
#include "Memory.h"
#include "Log.h"
#include "Win32Context.h"
#include "Resource.h"
#include "Camera.h"
#include "ShadingEnviroment.h"
#include "EntityManager.h"
#include "Graphics.h"
#include "DebugDraw.h"
#include "Scene.h"
#include "WebServerTool.h"
#include "Utils.h"
#include "Entity.h"
#include "Level.h"
//======================================================
#include <bx/bx.h>
#include <Common/Base/Container/Array/hkArray.h>
#include <Common/Base/Container/String/hkString.h>

using namespace gamedevwebtools;
char            g_entityName[256] = {0};
char            g_levelName[256] = {0};

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
void add_entity(const char* data1, const char* data2)
{
    g_entityMgr.addInstance(StringId(data1), hkQsTransform::getIdentity());
}
void clear_scene(const char* data1, const char* data2)
{
    g_entityMgr.clearInstances(INVALID_U32);
}
void reload_resource(const char* data1, const char* data2)
{
    StringId resType(data1);
    StringId resName(data2);
    if(resType.isZero())
    {
        LOGE("reload resource error, resource type is zero");
        return;
    }
    if(resName.isZero())
    {
        LOGI("reload resources of type %s", data1);
        g_resourceMgr.reloadResource(resType);
    }
    else
    {
        LOGI("reload resources type %s, name = %s", data1, data2);
        char pathBuf[256];
        sprintf_s(pathBuf, "data/%s.%s", data2, data1);
        g_resourceMgr.reloadResource(resType, resName, pathBuf);
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
    g_resourceMgr.reloadResource(StringId(ext), StringId(resourceName), data1);
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
        const ResourceGroup* group = package->findGroup(resType);
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
void camera_transform(const char* data1, const char* data2)
{
    hkStringBuf dataStr(data1);
    hkArray<const char*>::Temp bits;
    int nSplit = dataStr.split(',', bits);
    if(nSplit != 7) return;
    float fov = hkString::atof(bits[0]);
    float translate[3] = {hkString::atof(bits[1]), hkString::atof(bits[2]), hkString::atof(bits[3])};
    float lookat[3] = {hkString::atof(bits[4]), hkString::atof(bits[5]), hkString::atof(bits[6])};
    g_camera.m_fov = fov;
    g_camera.update(translate, lookat);
    extern DebugFPSCamera g_fpsCamera;
    bx::vec3Move(g_fpsCamera.m_eye, g_camera.m_eye);
    bx::vec3Move(g_fpsCamera.m_at, g_camera.m_at);
    //LOGI("translation = %g,%g,%g", translate[12], translate[13], translate[14]);
}
void object_transform(const char* data1, const char* data2)
{
    if(strlen(g_levelName) == 0)
        return;

    Level* pLevel = FIND_RESOURCE(Level, StringId(g_levelName));
    if(!pLevel) return;
    StringId objectName(data1);
    LevelObject* object = pLevel->findObject(objectName);
    if(!object) return;
    EntityInstance* inst = g_entityMgr.lookupInstance(object->m_entityId);
    if(!inst) return;
    hkStringBuf dataStr(data2);
    hkArray<const char*>::Temp bits;
    int nSplit = dataStr.split(',', bits);
    if(nSplit != 16) return;
    float mtx[16];
    for (int i=0; i<16; ++i)
    {
        mtx[i] = hkString::atof(bits[i]);
    }
    mtx[12] *= 0.01f;
    mtx[13] *= 0.01f;
    mtx[14] *= 0.01f;
    hkQsTransform t;
    transform_matrix(t, mtx);
    hkTransform t1;
    t1.setRows4(hkVector4(-1,0,0,0), hkVector4(0,1,0,0), hkVector4(0,0,1,0), hkVector4(0,0,0,1));
    hkQsTransform t2;
    t2.setFromTransform(t1);
    t.setMulEq(t2);
    inst->setTransform(t);
}
void exit_command(const char* data1, const char* data2)
{
    g_engine.shutdown();
}
void load_package(const char* data1, const char* data2)
{
    g_resourceMgr.loadPackageAndWait(data1);
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
    REMOTE_CMD(clear_scene), 
    REMOTE_CMD(add_entity), 
    REMOTE_CMD(reload_resource),
    REMOTE_CMD(reload_resource_file),
    REMOTE_CMD(list_resources),
    REMOTE_CMD(camera_transform),
    REMOTE_CMD(object_transform),
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

