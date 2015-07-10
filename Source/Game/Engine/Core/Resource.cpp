#include "Resource.h"
#include "Log.h"
#include "MemorySystem.h"
#include "linear_allocator.h"
#include "DataDef.h"
#include "Utils.h"
#include <bx/readerwriter.h>
#ifdef HAVOK_COMPILE
#include <Common/Base/Thread/Thread/hkThread.h>
#include <Common/Base/Thread/Semaphore/hkSemaphore.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Thread/Thread/hkWorkerThreadContext.h>
#include <Common/Serialize/Util/hkLoader.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>
#endif

ResourceManager                 g_resourceMgr;
#define RESOURCE_WORKER_THREAD_ID                   (1)
#ifdef HAVOK_COMPILE
typedef hkPointerMap<hkUint64, void*> ResourceMap;
static  ResourceMap*            g_resourceMap = 0;
#endif

inline hkUint64 packId(StringId type, StringId name)
{
    return ((hkUint64)type << 32) | (hkUint64)name;
}
inline void unpackId(const hkUint64& key, StringId& type, StringId& name)
{
    name = (uint32_t)(key);
    type = (uint32_t)(key >> 32);
}

void ResourcePackage::init()
{
    memset(this, 0x00, sizeof(ResourcePackage));
}

void ResourcePackage::load()
{
    TIMELOG(BX_FUNCTION);
    m_groups = (ResourceGroup*)((char*)this + sizeof(ResourcePackage));

    //=======================================================
    // TODO FOR RESOURCE STACK ALLOC
    if(m_memBudget > 0)
    {
        char* p = (char*)COMMON_ALLOC(char, m_memBudget);
        m_allocator = new (m_allocator_buffer) LinearAllocator(p, m_memBudget);
    }

    uint32_t num = m_numGroups;
    if(m_bundled)
    {
        for (uint32_t i=0; i<num; ++i)
        {
            load_group_bundled(i);
        }
    }
    else
    {
        for (uint32_t i=0; i<num; ++i)
        {
            load_group(i);
        }
    }


    lookup_all_resources();
    set_status(kResourceOffline);
}

void ResourcePackage::destroy()
{
    COMMON_DEALLOC(m_allocator->get_start());
}

void ResourcePackage::load_group(int index)
{
    TIMELOG("%s %d", BX_FUNCTION, index);

    if(!g_resourceMgr.is_running())
        return;

    ResourceGroup& group = m_groups[index];
    StringId type = group.m_type;
    ResourceFactory* fac = g_resourceMgr.find_factory(type);
    ENGINE_ASSERT(fac, "ResourceFactory %s not found.", stringid_lookup(type));

    char* pThis = (char*)this;
    group.m_factory = fac;
    group.m_resources = (ResourceInfo*)(pThis + group.m_resourceInfoOffset);

    char fileName[256];
    func_load_resource_t loadFunc = group.m_factory->m_loadFunc;

    uint32_t num = group.m_numResources;
    ResourceInfo* resources = group.m_resources;
    LOGD("loading resource group %s num-of-resources=%d", stringid_lookup(group.m_type), num);

    for (uint32_t i=0; i<num; ++i)
    {
        if(!g_resourceMgr.is_running())
            return;

        if(get_status() == kResourceRequestUnload)
            return;

        ResourceInfo& info = resources[i];
        char* name = pThis + info.m_offset;
        memcpy(fileName, name, info.m_size);
        fileName[info.m_size] = '\0';
        bx::CrtFileReader reader;
        int32_t ret = reader.open(fileName);
        if(ret) {
            LOGE("can not open resource %s.", fileName);
            continue;
        }

        uint32_t fileSize = (uint32_t)bx::getSize(&reader);
        char* buffer = (char*)m_allocator->allocate(fileSize);
        if(!buffer)
            continue;

        reader.read(buffer, fileSize);
        reader.close();

        LOGD("loading file %s", fileName);

        if(loadFunc)
            info.m_ptr = loadFunc(buffer, fileSize);
        else
            info.m_ptr = buffer; //---> MAGIC !

        if(info.m_ptr)
            g_resourceMgr.insert_resource(type, info.m_name, info.m_ptr);
        else
            LOGE("resource load error !!!! resource id = %d", i);
    }
}

void ResourcePackage::load_group_bundled(int index)
{
    TIMELOG("%s load group %d", BX_FUNCTION, index);

    if(!g_resourceMgr.is_running())
        return;

    ResourceGroup& group = m_groups[index];
    StringId type = group.m_type;
    ResourceFactory* fac = g_resourceMgr.find_factory(type);
    ENGINE_ASSERT(fac, "ResourceFactory not found.");

    char* pThis = (char*)this;
    group.m_factory = fac;
    group.m_resources = (ResourceInfo*)(pThis + group.m_resourceInfoOffset);
    func_load_resource_t loadFunc = group.m_factory->m_loadFunc;
    uint32_t num = group.m_numResources;

    for (uint32_t i=0; i<num; ++i)
    {
        if(!g_resourceMgr.is_running())
            return;
        if(get_status() == kResourceRequestUnload)
            return;
        ResourceInfo& info = group.m_resources[i];
        char* buffer = pThis + info.m_offset;
        if(loadFunc)
            info.m_ptr = loadFunc(buffer, info.m_size);
        else
            info.m_ptr = buffer;
        if(info.m_ptr)
            g_resourceMgr.insert_resource(type, info.m_name, info.m_ptr);
        else
            LOGE("resource load error !!!! resource id = %d", i);
    }
}

void ResourcePackage::flush(int maxNum)
{
    if(m_status == kResourceOnline)
        return;
#ifdef HAVOK_COMPILE
    hkCriticalSection::waitForValueEqual((hkUint32*)&m_status, kResourceOffline);
#endif
    bringin_all_resources(maxNum);
}

void ResourcePackage::lookup_all_resources()
{
    TimeAutoLog _log(BX_FUNCTION);
    uint32_t num = m_numGroups;
    ResourceGroup* groups = m_groups;

    for(uint32_t i=0; i<num; ++i)
    {
        ResourceGroup& group = groups[i];
        func_lookup_resource_t func_ = group.m_factory->m_lookupFunc;
        if(!func_)
            continue;

        uint32_t num_res = group.m_numResources;
        ResourceInfo* resources = group.m_resources;

        for(uint32_t j=0; j<num_res; ++j)
        {
            if(resources[j].m_ptr)
                func_(resources[j].m_ptr);
            else
                LOGE("resource lookup error, group id = %d!!!", i);
        }
    }
}

void ResourcePackage::destroy_all_resources()
{
    TimeAutoLog _log(BX_FUNCTION);
    for(uint32_t i=0; i<m_numGroups; ++i)
    {
        ResourceGroup& group = m_groups[i];
        func_destroy_resource_t func_ = group.m_factory->m_destroyFunc;
        if(!func_) continue;

        uint32_t num = group.m_numResources;
        ResourceInfo* resources = group.m_resources;
        for(uint32_t j=0; j<num; ++j)
        {
            func_(resources[j].m_ptr);
        }
    }
}

void ResourcePackage::bringin_group_resource(ResourceGroup& group, int start, int end)
{
    func_bringin_resource_t func_ = group.m_factory->m_bringInFunc;
    ResourceInfo* resources = group.m_resources;
    for(int i=start; i<end; ++i) {
        int ret = func_(resources[i].m_ptr);
        if (ret < 0) {
			LOGE("resource %s bringin error", stringid_lookup(resources[i].m_name));
        }
    }
}

void ResourcePackage::bringin_all_resources(int maxNum)
{
    if(maxNum < 0)
    {
        TIMELOG(BX_FUNCTION);
        for(uint32_t i=0; i<m_numGroups; ++i)
        {
            ResourceGroup& group = m_groups[i];
            if(!group.m_factory->m_bringInFunc)
                continue;
            LOGD("bring group %s, num-of-resources=%d", stringid_lookup(group.m_type), group.m_numResources);
            bringin_group_resource(group, 0, group.m_numResources);
        }
    }
    else
    {
        uint32_t num = m_numGroups;
        ResourceGroup* groups = m_groups;

        for(uint32_t i=m_lastOnLineGroup; i<num; ++i)
        {
            ResourceGroup& group = groups[i];
            if(!group.m_factory->m_bringInFunc) continue;
            int numResources = group.m_numResources;
            int numNeedToBringIn = numResources - m_lastOnlineResource;
            if(maxNum < numNeedToBringIn)
            {
                int end = m_lastOnlineResource + maxNum;
                m_lastOnLineGroup = i;
                bringin_group_resource(group, m_lastOnlineResource, end);
                m_lastOnlineResource = end;
                //LOGD("resource package max bring-in num[%d] !! cur-stats group[%d] resource[%d]",
                //     maxNum, m_lastOnLineGroup, m_lastOnlineResource);
                return;
            }
            else
            {
                bringin_group_resource(group, m_lastOnlineResource, numResources);
                m_lastOnlineResource = 0;
                maxNum -= numNeedToBringIn;
            }
        }
    }
    set_status(kResourceOnline);
}

void ResourcePackage::bringout_all_resources()
{
    TimeAutoLog _log(BX_FUNCTION);
    uint32_t num = m_numGroups;
    ResourceGroup* groups = m_groups;
    for(uint32_t i=0; i<num; ++i)
    {
        ResourceGroup& group = groups[i];
        func_bringout_resource_t func_ = group.m_factory->m_bringOutFunc;
        if(!func_) continue;

        uint32_t res_num = group.m_numResources;
        ResourceInfo* resources = group.m_resources;
        for(uint32_t j=0; j<res_num; ++j)
        {
            func_(resources[j].m_ptr);
        }
    }
}

int ResourcePackage::get_status() const
{
    return m_status;
}

void ResourcePackage::set_status( int status )
{
    m_status = status;
}

void ResourcePackage::remove_all_resources()
{
    TimeAutoLog _log(BX_FUNCTION);
    uint32_t num = m_numGroups;
    ResourceGroup* groups = m_groups;
    for(uint32_t i=0; i<num; ++i)
    {
        ResourceGroup& group = groups[i];

        uint32_t res_num = group.m_numResources;
        ResourceInfo* resources = group.m_resources;

        for(uint32_t j=0; j<res_num; ++j)
        {
            g_resourceMgr.remove_resource(group.m_type, resources[j]);
        }
    }
}

void ResourcePackage::unload()
{
    remove_all_resources();
    bringout_all_resources();
    destroy_all_resources();
    m_numGroups = 0;
}

ResourceGroup* ResourcePackage::find_group( StringId type ) const
{
    uint32_t num = m_numGroups;
    ResourceGroup* groups = m_groups;
    for (uint32_t i=0; i<num;++i)
    {
        if(groups[i].m_type == type)
            return &groups[i];
    }
    return 0;
}

ResourceInfo* ResourcePackage::find_resource( StringId type, StringId name ) const
{
    ResourceGroup* group = find_group(type);
    if(!group) return 0;
    uint32_t num = group->m_numResources;
    ResourceInfo* resources = group->m_resources;
    for (uint32_t i=0; i<num; ++i)
    {
        if(name == resources[i].m_name)
            return &resources[i];
    }
    return 0;
}

//=================================================================================
//          RESOURCE MANAGER
//=================================================================================

void ResourceManager::init()
{
    m_running = 1;
    m_numFactories = 0;
    m_numPackages = 0;
    m_numRequests = 0;
    m_requestListHead = 0;

#ifdef HAVOK_COMPILE
    m_semaphore = new hkSemaphore;
    m_thread = new hkThread;
    m_thread->startThread(io_work_loop, this, "io_work_thread");
    uint32_t pairSize = sizeof(hkUint64) * 2;
    uint32_t memSize = RESOURCE_MAP_NUM*pairSize;
    m_resMapBuffer = COMMON_ALLOC(char, memSize);
    g_resourceMap = new ResourceMap(m_resMapBuffer, memSize);
#endif
}

void ResourceManager::shutdown()
{
#ifdef HAVOK_COMPILE
    set_running(false);
    m_semaphore->release();
    m_thread->joinThread();
    for(size_t i=0; i<m_numPackages; ++i)
    {
        m_packages[i]->destroy_all_resources();
        m_packages[i]->destroy();
        COMMON_DEALLOC(m_packages[i]);
    }
    //clear request queue.
    m_requestListHead = 0;
    SAFE_DELETE(g_resourceMap);
    COMMON_DEALLOC(m_resMapBuffer);
    SAFE_DELETE(m_thread);
    SAFE_DELETE(m_semaphore);
#ifndef _RETAIL
    destroy_reload_resources();
#endif
#endif
}


ResourceFactory* ResourceManager::find_factory(StringId type)
{
    int index = -1;
    uint32_t num = m_numFactories;
    StringId* types = m_types;
    for(uint32_t i=0; i<num; ++i)
    {
        if(type == types[i])
        {
            index = i;
            break;
        }
    }
    return index >= 0 ? &m_factories[index] : 0;
}

void ResourceManager::register_factory(const ResourceFactory& factory)
{
    m_types[m_numFactories] = stringid_caculate(factory.m_name);
    m_factories[m_numFactories++] = factory;
    ENGINE_ASSERT(m_numFactories < MAX_RESOURCE_TYPES, "resource manager factories overflow.");
}

void* ResourceManager::find_resource( StringId type, StringId name )
{
    if(!name) return 0;
    bx::LwMutexScope _l(m_resourceLock);
#ifdef HAVOK_COMPILE
    ResourceMap::Iterator it = g_resourceMap->findKey(packId(type, name));
    if(!g_resourceMap->isValid(it))
    {
        LOGE("%s can not find resource %s, %s", BX_FUNCTION, stringid_lookup(type), stringid_lookup(name));
        return 0;
    }
    return g_resourceMap->getValue(it);
#else
    return 0;
#endif
}

void ResourceManager::insert_resource( StringId type, StringId name, void* resource )
{
    bx::LwMutexScope _l(m_resourceLock);
#ifdef HAVOK_COMPILE
    g_resourceMap->insert(packId(type, name), resource);
#endif
}

void ResourceManager::remove_resource( StringId type, const ResourceInfo& info )
{
    bx::LwMutexScope _l(m_resourceLock);
#ifdef HAVOK_COMPILE
    g_resourceMap->remove(packId(type, info.m_name));
#endif
}

void* ResourceManager::io_work_loop( void* p )
{
#ifdef HAVOK_COMPILE
    hkWorkerThreadContext context(RESOURCE_WORKER_THREAD_ID);
    ResourceManager* mgr = (ResourceManager*)p;
    hkSemaphore* pSemaphore = mgr->m_semaphore;
    while(mgr->is_running())
    {
        pSemaphore->acquire();
        mgr->process_request();
    }
#endif
    return 0;
}

ResourcePackage* ResourceManager::find_package(StringId name)
{
    uint32_t num = m_numPackages;
    ResourcePackage** packages = m_packages;
    for(size_t i=0; i<num; ++i)
    {
        if(packages[i]->m_name == name)
            return packages[i];
    }
    return  0;
}

bool ResourceManager::load_package(const char* packageName)
{
    StringId packageNameId = stringid_caculate(packageName);
    ResourcePackage* package = find_package(packageNameId);
    if(package)
    {
        LOGW("package already exist --> %s", packageName);
        return false;
    }

    uint32_t packageNameLen = strlen(packageName) + 1;
    uint32_t memSize = packageNameLen + sizeof(ResourceRequest);
    char* blob = COMMON_ALLOC(char, memSize);
    memset(blob, 0x00, memSize);
    ResourceRequest* request = (ResourceRequest*)blob;
    request->m_data = blob + sizeof(ResourceRequest);
    request->m_dataLen = packageNameLen;
    memcpy(request->m_data, packageName, packageNameLen);
    push_request(request);
#ifdef HAVOK_COMPILE
    m_semaphore->release();
#endif
    return true;
}

bool ResourceManager::unload_package(StringId packageName)
{
    for(size_t i=0; i<m_numPackages; ++i)
    {
        ResourcePackage* package = m_packages[i];
        if(package->m_name == packageName)
        {
            if(package->get_status() == kResourceLoading)
            {
                LOGE("package %s is loading", stringid_lookup(package->m_name));
                package->set_status(kResourceRequestUnload);
                return false;
            }
            package->unload();
            package->destroy();
            COMMON_DEALLOC(package);
            m_packages[0] = m_packages[--m_numPackages];
            return true;
        }
    }
    return true;
}

int ResourceManager::get_package_status(StringId packageName)
{
    ResourcePackage* package = find_package(packageName);
    if(!package) return kResourceNotFound;
    return package->get_status();
}

void ResourceManager::flush_package(StringId packageName, int maxNum)
{
    ResourcePackage* package = find_package(packageName);
    if(!package) return;
    package->flush(maxNum);
}

void ResourceManager::process_request()
{
    while(is_running())
    {
        if(!m_requestListHead)
            break;
        ResourceRequest* request;
        {
            bx::LwMutexScope _l(m_queueLock);
            request = m_requestListHead;
            m_requestListHead = request->m_next;
        }

        const char* fileName = request->m_data;
        LOGI("loading package %s.", fileName);

        bx::CrtFileReader reader;
        int32_t ret = reader.open(fileName);
        COMMON_DEALLOC(request);

        if(ret)
        {
            LOGE("load package failed");
            continue;
        }

        uint32_t fileSize = (uint32_t)bx::getSize(&reader);
        ResourcePackage* package = (ResourcePackage*)COMMON_ALLOC(char, fileSize);
        reader.read(package, fileSize);
        reader.close();
        m_packages[m_numPackages++] = package;
        package->load();
    }
}

void ResourceManager::push_request( ResourceRequest* request )
{
    bx::LwMutexScope _l(m_queueLock);
    if(!m_requestListHead)
    {
        m_requestListHead = request;
    }
    else
    {
        ResourceRequest* curRequest = m_requestListHead;
        ResourceRequest* nextRequest = m_requestListHead->m_next;
        while(nextRequest)
        {
            curRequest = nextRequest;
            nextRequest = curRequest->m_next;
        }
        curRequest->m_next = request;
    }
}

uint32_t  ResourceManager::find_resources_type_of(StringId type, ResourceInfo** resourceArray, uint32_t arrayLen)
{
    uint32_t num = m_numPackages;
    ResourcePackage** packages = m_packages;
    uint32_t retNum = 0;
    for (uint32_t i = 0; i < num; ++i)
    {
        ResourcePackage* package = packages[i];
        ResourceGroup* group = package->find_group(type);
        if(!group) continue;

        uint32_t res_num = group->m_numResources;
        ResourceInfo* resources = group->m_resources;
        for (uint32_t j=0; j<res_num; ++j)
        {
            resourceArray[retNum++] = &(resources[j]);
        }
    }
    return retNum;
}

ResourceInfo* ResourceManager::find_resource_info( StringId type, StringId name )
{
    uint32_t num = m_numPackages;
    ResourcePackage** packages = m_packages;
    for (uint32_t i = 0; i < num; ++i)
    {
        ResourcePackage* package = packages[i];
        ResourceGroup* group = package->find_group(type);
        if(!group) continue;

        uint32_t res_num = group->m_numResources;
        ResourceInfo* resources = group->m_resources;
        for (uint32_t j=0; j<res_num; ++j)
        {
            if(resources[j].m_name == name)
                return &resources[j];
        }
    }
    return 0;
}

bool ResourceManager::load_package_and_wait(const char* packageName)
{
    TIMELOG("load_package_and_wait %s", packageName);
    StringId name = stringid_caculate(packageName);
    if(load_package(packageName))
    {
        while(1)
        {
            int status = get_package_status(name);
            if(status == kResourceOffline) break;
            bx::sleep(0);
        }
    }
    flush_package(name);
    return true;
}


void ResourceManager::offline_all_resources()
{
    set_running(false);
    uint32_t num = m_numPackages;
    ResourcePackage** packages = m_packages;
    for (uint32_t i=0; i<num; ++i)
    {
        packages[i]->remove_all_resources();
        packages[i]->bringout_all_resources();
    }
}
//==================================================================================
#ifdef RESOURCE_RELOAD
#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>
#include <vector>
struct ResouceData
{
    ResourceFactory* m_fac;
    void*            m_resource;
};
typedef tinystl::unordered_map<hkUint64, ResouceData> ReloadResourceMap;
ReloadResourceMap  g_reloadResources;
typedef tinystl::unordered_map<uint32_t, std::vector<func_reload_resource_t> > ReloadCallbackMap;
ReloadCallbackMap g_reloadCallbacks;
//===================================================================================
void ResourceManager::destroy_reload_resources()
{
    for(ReloadResourceMap::iterator iter = g_reloadResources.begin(); iter != g_reloadResources.end(); ++iter)
    {
        ResouceData& data = iter->second;
        if(data.m_fac->m_bringOutFunc) data.m_fac->m_bringOutFunc(data.m_resource);
        if(data.m_fac->m_destroyFunc) data.m_fac->m_destroyFunc(data.m_resource);
        COMMON_DEALLOC(data.m_resource);
    }
    g_reloadResources.clear();
}
void  ResourceManager::register_reload_callback(StringId type, func_reload_resource_t func)
{
    ReloadCallbackMap::iterator iter = g_reloadCallbacks.find(type);
    if(iter == g_reloadCallbacks.end())
    {
        std::vector<func_reload_resource_t> callbacks;
        callbacks.push_back(func);
        g_reloadCallbacks[type] = callbacks;
    }
    else {
        iter->second.push_back(func);
    }
}
void* ResourceManager::reload_resource( StringId type, StringId name, const char* pathName , bool bFireCallbacks)
{
    LOGD("start reloading resource path %s", pathName);

    void* oldResource = find_resource(type, name);
    if(!oldResource)
    {
        LOGW("%s old resource not exist ---> %s!", BX_FUNCTION, pathName);
        bFireCallbacks = false;
    }

    bx::CrtFileReader reader;
    int32_t ret = reader.open(pathName);
    if(ret)
    {
        LOGE("%s load file failed ---> %s!", BX_FUNCTION, pathName);
        return 0;
    }

    ResourceFactory* fac = find_factory(type);
    if(!fac) {
        LOGE("%s can not find factory = %x", BX_FUNCTION, stringid_lookup(type));
        return 0;
    }

    hkUint64 key = packId(type, name);
    void* ptrToFree = 0;

    ReloadResourceMap::iterator iter = g_reloadResources.find(key);
    if(iter != g_reloadResources.end())
    {
        ptrToFree = iter->second.m_resource;
    }

    void* newResource = 0;
    uint32_t fileSize = (uint32_t)bx::getSize(&reader);
    newResource = COMMON_ALLOC(char, fileSize);
    reader.read(newResource, fileSize);
    reader.close();

    LOGI("reload 0x%x ---> 0x%x", oldResource, newResource);
    if(fac->m_loadFunc) newResource = fac->m_loadFunc((char*)newResource, fileSize);
    if(fac->m_lookupFunc) fac->m_lookupFunc(newResource);
    if(fac->m_bringInFunc) fac->m_bringInFunc(newResource);

    ResouceData data;
    data.m_resource = newResource;
    data.m_fac = fac;
    g_reloadResources[key] = data;
    insert_resource(type, name, newResource);

    ResourceInfo* info = find_resource_info(type, name);
    if(info) info->m_ptr = newResource;

    if(bFireCallbacks)
    {
        ReloadCallbackMap::iterator iter1 = g_reloadCallbacks.find(type);
        if(iter1 != g_reloadCallbacks.end())
        {
            const std::vector<func_reload_resource_t>& callbacks = iter1->second;
            for(size_t i=0; i<callbacks.size(); ++i)
            {
                callbacks[i](oldResource, newResource);
            }
        }
    }

    if(oldResource)
    {
        if(fac->m_bringOutFunc) fac->m_bringOutFunc(oldResource);
        if(fac->m_destroyFunc) fac->m_destroyFunc(oldResource);
    }
    COMMON_DEALLOC(ptrToFree);
    return newResource;
}

void ResourceManager::reload_resource(StringId type, bool bFireCallbacks)
{
    char name[256];
    for (uint32_t i = 0; i < m_numPackages; ++i)
    {
        ResourcePackage* package = m_packages[i];
        if(package->m_bundled) continue; //bundled package can not reload.
        ResourceGroup* group = package->find_group(type);
        if(!group) continue;
        for (uint32_t j=0; j<group->m_numResources; ++j)
        {
            const ResourceInfo& info = group->m_resources[j];
            char* nameAddr = (char*)package + info.m_offset;
            memcpy(name, nameAddr, info.m_size);
            name[info.m_size] = '\0';
            reload_resource(type, info.m_name, name, bFireCallbacks);
        }
    }
}

int ResourceManager::get_resource_order( StringId type )
{
    ResourceFactory* fac = find_factory(type);
    return fac ? fac->m_order : -1;
}




#endif


