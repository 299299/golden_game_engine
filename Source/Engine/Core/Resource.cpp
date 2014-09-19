#include "Resource.h"
#include "Log.h"
#include "MemorySystem.h"
#include "linear_allocator.h"
#include "DataDef.h"
#include "Utils.h"
#include "EngineAssert.h"
#include "config.h"
//=====================================================
#include <bx/readerwriter.h>
//=====================================================
#include <Common/Base/Thread/Thread/hkThread.h>
#include <Common/Base/Thread/Semaphore/hkSemaphore.h>
#include <Common/Base/Memory/System/hkMemorySystem.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/System/hkBaseSystem.h>
#include <Common/Base/Thread/Thread/hkWorkerThreadContext.h>
#include <Common/Serialize/Util/hkLoader.h>
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
#include <Common/Base/Container/PointerMap/hkPointerMap.h>

ResourceManager                 g_resourceMgr;
static hkCriticalSection        g_runningCS;
static hkCriticalSection        g_queueCS;
static hkCriticalSection        g_resourceCS;
static hkCriticalSection        g_statusCS;
static volatile bool            g_running = true;

#define RESOURCE_WORKER_THREAD_ID                   (1)
typedef hkPointerMap<hkUint64, void*> ResourceMap;
static  ResourceMap*            g_resourceMap = 0;

static bool checkRunning()
{
    hkCriticalSectionLock _l(&g_runningCS);
    return g_running;
}
static void setRunning(bool bRunning)
{
    hkCriticalSectionLock _l(&g_runningCS);
    g_running = bRunning;
}
inline hkUint64 packId(const StringId& type, const StringId& name)
{
    return ((hkUint64)type.value() << 32) | (hkUint64)name.value();
}
inline void unpackId(const hkUint64& key, StringId& type, StringId& name)
{
    name = StringId((uint32_t)(key));
    type = StringId((uint32_t)(key >> 32));
}

char* ResourcePackage::allocMemory(uint32_t size)
{
    return (char*)m_allocator->allocate(size);
}

void ResourcePackage::init()
{
    memset(this, 0x00, sizeof(ResourcePackage));
}

void ResourcePackage::load()
{
    TIMELOG(__FUNCTION__);
    m_groups = (ResourceGroup*)((char*)this + sizeof(ResourcePackage));

    //=======================================================
    // TODO FOR RESOURCE STACK ALLOC
    if(m_memBudget > 0)
    {
        char* p = (char*)COMMON_ALLOC(char, m_memBudget);
        memset(p, 0x00, m_memBudget);
        m_allocator = new (m_allocator_buffer) LinearAllocator(p, m_memBudget);
    }
    
    if(m_bundled)
    {
        for (uint32_t i=0; i<m_numGroups; ++i)
        {
            loadGroupBundled(i);
        }
    }
    else
    {
        for (uint32_t i=0; i<m_numGroups; ++i)
        {
            loadGroup(i);
        }
    }
    
    
    lookupAllResources();
    setStatus(kResourceOffline);
}

void ResourcePackage::destroy()
{
    COMMON_DEALLOC(m_allocator->get_start());
}

void ResourcePackage::loadGroup(int index)
{
    TIMELOG(__FUNCTION__" load group %d.", index);

    if(!checkRunning())
        return;
        
    ResourceGroup& group = m_groups[index];
    StringId type = group.m_type;
    ResourceFactory* fac = g_resourceMgr.findFactory(type);
    ENGINE_ASSERT(fac, "ResourceFactory not found.");

    char* pThis = (char*)this;
    group.m_factory = fac;
    group.m_resources = (ResourceInfo*)(pThis + group.m_resourceInfoOffset);

    char fileName[256];
    __RESOURCE_LOAD loadFunc = group.m_factory->m_loadFunc;

    for (uint32_t i=0; i<group.m_numResources; ++i)
    {
        if(!checkRunning())
            return;

        if(getStatus() == kResourceRequestUnload)
            return;

        ResourceInfo& info = group.m_resources[i];
        char* name = pThis + info.m_offset;
        memcpy(fileName, name, info.m_size);
        fileName[info.m_size] = '\0';
        bx::CrtFileReader reader;
        int32_t ret = reader.open(fileName);
        if(ret) {
            LOGE("can not open resource %s.", fileName);
            continue;
        }

        uint32_t fileSize = (uint32_t)reader.seek(0, bx::Whence::End);
        reader.seek(0, bx::Whence::Begin);
        char* buffer = allocMemory(fileSize);
        if(!buffer) continue;
        
        reader.read(buffer, fileSize);
        reader.close();
        
        if(loadFunc) info.m_ptr = loadFunc(buffer, fileSize);
        else info.m_ptr = buffer; //---> MAGIC !

        if(info.m_ptr) g_resourceMgr.insertResource(type, info.m_name, info.m_ptr);
        else LOGE("resource load error !!!! resource id = %d", i);
    }
}

void ResourcePackage::loadGroupBundled(int index)
{
    TIMELOG(__FUNCTION__" load group %d.", index);

    if(!checkRunning())
        return;
        
    ResourceGroup& group = m_groups[index];
    StringId type = group.m_type;
    ResourceFactory* fac = g_resourceMgr.findFactory(type);
    ENGINE_ASSERT(fac, "ResourceFactory not found.");

    char* pThis = (char*)this;
    group.m_factory = fac;
    group.m_resources = (ResourceInfo*)(pThis + group.m_resourceInfoOffset);
    __RESOURCE_LOAD loadFunc = group.m_factory->m_loadFunc;

    for (uint32_t i=0; i<group.m_numResources; ++i)
    {
        if(!checkRunning())
            return;
        if(getStatus() == kResourceRequestUnload)
            return;
        ResourceInfo& info = group.m_resources[i];
        char* buffer = pThis + info.m_offset;
        if(loadFunc) info.m_ptr = loadFunc(buffer, info.m_size);
        else info.m_ptr = buffer;
        if(info.m_ptr) g_resourceMgr.insertResource(type, info.m_name, info.m_ptr);
        else LOGE("resource load error !!!! resource id = %d", i);
    }
}

void ResourcePackage::flush(int maxNum)
{
    if(m_status == kResourceOnline)
        return;
    hkCriticalSection::waitForValueEqual(&m_status, kResourceOffline);
    bringInAllResources(maxNum);
}

void ResourcePackage::lookupAllResources()
{
    TimeAutoLog _log(__FUNCTION__);
    for(uint32_t i=0; i<m_numGroups; ++i)
    {
        ResourceGroup& group = m_groups[i];
        __RESOURCE_LOOKUP func_ = group.m_factory->m_lookupFunc;
        if(!func_) continue;
        for(uint32_t j=0; j<group.m_numResources; ++j)
        {
            ResourceInfo& info = group.m_resources[j];
            if(info.m_ptr)
                func_(info.m_ptr);
            else
                LOGE("resource lookup error, group id = %d!!!", i);
        }
    }
}

void ResourcePackage::destroyAllResources()
{
    TimeAutoLog _log(__FUNCTION__);
    for(uint32_t i=0; i<m_numGroups; ++i)
    {
        ResourceGroup& group = m_groups[i];
        __RESOURCE_DESTROY func_ = group.m_factory->m_destroyFunc;
        if(!func_) continue;
        for(uint32_t j=0; j<group.m_numResources; ++j)
        {
            ResourceInfo& info = group.m_resources[j];
            func_(info.m_ptr);
        }
    }
}

void ResourcePackage::bringInGroupResource(ResourceGroup& group, int start, int end)
{
    __RESOURCE_BRINGIN func_ = group.m_factory->m_bringInFunc;
    ResourceInfo* resources = group.m_resources;
    for(int i=start; i<end; ++i)
        func_(resources[i].m_ptr);
}

void ResourcePackage::bringInAllResources(int maxNum)
{
    if(maxNum < 0)
    {
        TIMELOG(__FUNCTION__);
        for(uint32_t i=0; i<m_numGroups; ++i)
        {
            ResourceGroup& group = m_groups[i];
            if(!group.m_factory->m_bringInFunc) continue;
            bringInGroupResource(group, 0, group.m_numResources);
        }
    }
    else
    {
        for(uint32_t i=m_lastOnLineGroup; i<m_numGroups; ++i)
        {
            ResourceGroup& group = m_groups[i];
            if(!group.m_factory->m_bringInFunc) continue;
            int numResources = group.m_numResources;
            int numNeedToBringIn = numResources - m_lastOnlineResource;
            if(maxNum < numNeedToBringIn)
            {
                int end = m_lastOnlineResource + maxNum;
                m_lastOnLineGroup = i;
                bringInGroupResource(group, m_lastOnlineResource, end);
                m_lastOnlineResource = end;
                //LOGD("resource package max bring-in num[%d] !! cur-stats group[%d] resource[%d]",
                //     maxNum, m_lastOnLineGroup, m_lastOnlineResource);
                return;
            }
            else
            {
                bringInGroupResource(group, m_lastOnlineResource, numResources);
                m_lastOnlineResource = 0;
                maxNum -= numNeedToBringIn;
            }
        }
    }
    setStatus(kResourceOnline);
}

void ResourcePackage::bringOutAllresources()
{
    TimeAutoLog _log(__FUNCTION__);
    for(uint32_t i=0; i<m_numGroups; ++i)
    {
        ResourceGroup& group = m_groups[i];
        __RESOURCE_BRINGOUT func_ = group.m_factory->m_bringOutFunc;
        if(!func_) continue;
        for(uint32_t j=0; j<group.m_numResources; ++j)
        {
            ResourceInfo& info = group.m_resources[j];
            func_(info.m_ptr);
        }
    }
}

int ResourcePackage::getStatus() const
{
    hkCriticalSectionLock _l(&g_statusCS);
    return m_status;
}

void ResourcePackage::setStatus( int status )
{
    hkCriticalSectionLock _l(&g_statusCS);
    m_status = status;
}

void ResourcePackage::removeAllResources()
{
    TimeAutoLog _log(__FUNCTION__);
    for(uint32_t i=0; i<m_numGroups; ++i)
    {
        ResourceGroup& group = m_groups[i];
        for(uint32_t j=0; j<group.m_numResources; ++j)
        {
            g_resourceMgr.removeResource(group.m_type, group.m_resources[j]);
        }
    }
}

void ResourcePackage::unload()
{
    removeAllResources();
    bringOutAllresources();
    destroyAllResources();
    m_numGroups = 0;
}

ResourceGroup* ResourcePackage::findGroup( const StringId& type ) const
{
    for (uint32_t i=0; i<m_numGroups;++i)
    {
        if(m_groups[i].m_type == type)
            return &m_groups[i];
    }
    return 0;
}

ResourceInfo* ResourcePackage::findResource( const StringId& type, const StringId& name ) const
{
    ResourceGroup* group = findGroup(type);
    if(!group) return 0;
    for (uint32_t i=0; i<group->m_numResources; ++i)
    {
        if(name == group->m_resources[i].m_name)
            return &group->m_resources[i];
    }
    return 0;
}

//=================================================================================
//          RESOURCE MANAGER
//=================================================================================

void ResourceManager::init()
{
    m_numFactories = 0;
    m_numPackages = 0;
    m_numRequests = 0;
    m_requestListHead = 0;

    m_semaphore = new hkSemaphore;
    m_thread = new hkThread;
    m_thread->startThread(ioWorkLoop, this, "io_work_thread");
    uint32_t pairSize = sizeof(hkUint64) * 2;
    uint32_t memSize = RESOURCE_MAP_NUM*pairSize;
    m_resMapBuffer = COMMON_ALLOC(char, memSize);
    g_resourceMap = new ResourceMap(m_resMapBuffer, memSize);
}

void ResourceManager::quit()
{
    setRunning(false);
    m_semaphore->release();
    m_thread->joinThread();

    for(size_t i=0; i<m_numPackages; ++i)
    {
        m_packages[i]->destroy();
        COMMON_DEALLOC(m_packages[i]);
    }
    clearRequestQueue(); 
    COMMON_DEALLOC(m_resMapBuffer);
    SAFE_DELETE(g_resourceMap);
    SAFE_DELETE(m_thread);
    SAFE_DELETE(m_semaphore);
}


ResourceFactory* ResourceManager::findFactory(const StringId& type)
{ 
    int index = findFactoryIndex(type);
    return index >= 0 ? &m_factories[index] : 0;
}

int ResourceManager::findFactoryIndex( const StringId& type )
{
    for(uint32_t i=0; i<m_numFactories; ++i)
    {
        if(type == m_types[i])
            return i;
    }
    return -1;
}

void ResourceManager::registerFactory(const ResourceFactory& factory)
{
    m_types[m_numFactories] = StringId(factory.m_name); 
    m_factories[m_numFactories++] = factory;
    ENGINE_ASSERT(m_numFactories < MAX_RESOURCE_TYPES, "resource manager factories overflow.");
}

void* ResourceManager::findResource( const StringId& type, const StringId& name )
{
    if(name.isZero())
        return 0;

    hkCriticalSectionLock _l(&g_resourceCS);
    ResourceMap::Iterator it = g_resourceMap->findKey(packId(type, name));
    if(!g_resourceMap->isValid(it))
    {
        LOGE(__FUNCTION__" can not find resource %s, %s", stringid_lookup(type), stringid_lookup(name));
        return 0;
    }
    return g_resourceMap->getValue(it);
}

void ResourceManager::insertResource( const StringId& type, const StringId& name, void* resource )
{
    hkCriticalSectionLock _l(&g_resourceCS);
    g_resourceMap->insert(packId(type, name), resource);
}

void ResourceManager::removeResource( const StringId& type, const ResourceInfo& info )
{
    hkCriticalSectionLock _l(&g_resourceCS);
    g_resourceMap->remove(packId(type, info.m_name));
}

void ResourceManager::destroyAllResources()
{
    setRunning(false);
    for(size_t i=0; i<m_numPackages; ++i)
    {
        m_packages[i]->unload();
    }
#ifdef RESOURCE_RELOAD
    destroyReloadResources();
#endif
}

void* ResourceManager::ioWorkLoop( void* p )
{
    hkWorkerThreadContext context(RESOURCE_WORKER_THREAD_ID);
    ResourceManager* mgr = (ResourceManager*)p;
    hkSemaphore* pSemaphore = mgr->m_semaphore;
    while(checkRunning())
    {
        pSemaphore->acquire();
        mgr->processRequests();
    }
    return 0;
}

ResourcePackage* ResourceManager::findPackage(const StringId& name)
{
    for(size_t i=0; i<m_numPackages; ++i)
    {
        if(m_packages[i]->m_name == name)
            return m_packages[i];
    }
    return  0;
}

bool ResourceManager::loadPackage(const char* packageName)
{
    StringId packageNameId = StringId(packageName);
    ResourcePackage* package = findPackage(packageNameId);
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
    pushRequest(request); 
    m_semaphore->release();
    return true;
}

bool ResourceManager::unloadPackage(const StringId& packageName)
{
    for(size_t i=0; i<m_numPackages; ++i)
    {
        ResourcePackage* package = m_packages[i];
        if(package->m_name == packageName)
        {
            if(package->getStatus() == kResourceLoading)
            {
                LOGE("package %s is loading", stringid_lookup(package->m_name));
                package->setStatus(kResourceRequestUnload);
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

int ResourceManager::getPackageStatus(const StringId& packageName)
{
    ResourcePackage* package = findPackage(packageName);
    if(!package)
        return kResourceError;
    return package->getStatus();
}

void ResourceManager::flushPackage(const StringId& packageName, int maxNum)
{
    ResourcePackage* package = findPackage(packageName);
    if(!package)
        return;
    package->flush(maxNum);
}

void ResourceManager::processRequests()
{
    while(checkRunning())
    {
        if(!m_requestListHead)
        {
            break;
        }
        ResourceRequest* request;
        {
            hkCriticalSectionLock _l(&g_queueCS);
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

        uint32_t fileSize = (uint32_t)reader.seek(0, bx::Whence::End);
        reader.seek(0, bx::Whence::Begin);
        ResourcePackage* package = (ResourcePackage*)COMMON_ALLOC(char, fileSize);
        memset(package, 0x00, fileSize);
        reader.read(package, fileSize);
        reader.close();
        m_packages[m_numPackages++] = package;
        package->load();
    }
}

void ResourceManager::pushRequest( ResourceRequest* request )
{
    hkCriticalSectionLock _l(&g_queueCS);
    if(!m_requestListHead) m_requestListHead = request;
    else {
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

void ResourceManager::clearRequestQueue()
{
    hkCriticalSectionLock _l(&g_queueCS);
    m_requestListHead = 0;
}

uint32_t  ResourceManager::findResourcesTypeOf(const StringId& type, void** resourceArray, uint32_t arrayLen)
{
    uint32_t retNum = 0;
    ResourceMap::Iterator iter = g_resourceMap->getIterator();
    while(g_resourceMap->isValid(iter))
    {   
        hkUint64 key = g_resourceMap->getKey(iter);
        void* value = g_resourceMap->getValue(iter);
        StringId resType, resName;
        unpackId(key, resType, resName);
        if(type == resType)
        {
            resourceArray[retNum++] = value;
            if(retNum >= arrayLen)
                return retNum;
        }
        iter = g_resourceMap->getNext(iter);
    }
    return retNum;
}

uint32_t  ResourceManager::findResourcesTypeOf(const StringId& type, ResourceInfo** resourceArray, uint32_t arrayLen)
{
    uint32_t retNum = 0;
    for (uint32_t i = 0; i < m_numPackages; ++i)
    {
        ResourcePackage* package = m_packages[i];
        ResourceGroup* group = package->findGroup(type);
        if(!group) continue;
        for (uint32_t j=0; j<group->m_numResources; ++j)
        {
            resourceArray[retNum++] = &(group->m_resources[j]);
        }
    }
    return retNum; 
}

void ResourceManager::loadPackageAndWait(const char* packageName)
{
    StringId name(packageName);
    if(loadPackage(packageName))
    {
        while(getPackageStatus(name) != kResourceOffline)
        {
            Sleep(0);
        }
    }
    flushPackage(name);
}

//==================================================================================
#ifdef RESOURCE_RELOAD
#include <unordered_map>
#include <vector>
struct ResouceData
{
    ResourceFactory* m_fac;
    void*            m_resource;
};
typedef std::unordered_map<hkUint64, ResouceData> ReloadResourceMap;
ReloadResourceMap  g_reloadResources;
typedef std::unordered_map<uint32_t, std::vector<__RESOURCE_RELOAD> > ReloadCallbackMap;
ReloadCallbackMap g_reloadCallbacks;
//===================================================================================
void ResourceManager::destroyReloadResources()
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
void  ResourceManager::registerReloadCallback(const StringId& type, __RESOURCE_RELOAD func)
{
    uint32_t key = type.value();
    ReloadCallbackMap::iterator iter = g_reloadCallbacks.find(key);
    if(iter == g_reloadCallbacks.end())
    {
        std::vector<__RESOURCE_RELOAD> callbacks;
        callbacks.push_back(func);
        g_reloadCallbacks[key] = callbacks;
    }
    else {
        iter->second.push_back(func);
    }
}
void* ResourceManager::reloadResource( const StringId& type, const StringId& name, const char* pathName , bool bFireCallbacks)
{
    LOGD("start reloading resource path %s", pathName);

    void* oldResource = findResource(type, name);
    if(!oldResource)
    {
        LOGW(__FUNCTION__" old resource not exist ---> %s!", pathName);
        bFireCallbacks = false;
    }
    
    bx::CrtFileReader reader;
    int32_t ret = reader.open(pathName);
    if(ret)
    {
        LOGE(__FUNCTION__" load file failed ---> %s!", pathName);
        return 0;
    }
    
    ResourceFactory* fac = findFactory(type);
    if(!fac) {
        LOGE("can not find factory = %x", stringid_lookup(type));
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
    uint32_t fileSize = (uint32_t)reader.seek(0, bx::Whence::End);
    reader.seek(0, bx::Whence::Begin);
    newResource = COMMON_ALLOC(char, fileSize);
    memset(newResource, 0x00, fileSize);
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
    insertResource(type, name, newResource);
    
    if(bFireCallbacks)
    {
        ReloadCallbackMap::iterator iter1 = g_reloadCallbacks.find(type.value());
        if(iter1 != g_reloadCallbacks.end())
        {
            const std::vector<__RESOURCE_RELOAD>& callbacks = iter1->second;
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

void ResourceManager::reloadResource(const StringId& type, bool bFireCallbacks)
{
    char name[256];
    for (uint32_t i = 0; i < m_numPackages; ++i)
    {
        ResourcePackage* package = m_packages[i];
        if(package->m_bundled) continue; //bundled package can not reload.
        ResourceGroup* group = package->findGroup(type);
        if(!group) continue;
        for (uint32_t j=0; j<group->m_numResources; ++j)
        {
            const ResourceInfo& info = group->m_resources[j];
            char* nameAddr = (char*)package + info.m_offset;
            memcpy(name, nameAddr, info.m_size);
            name[info.m_size] = '\0';
            reloadResource(type, info.m_name, name, bFireCallbacks);
        }
    }
}
#endif


