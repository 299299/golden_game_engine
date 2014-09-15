#pragma once
#include "Prerequisites.h"
#include "StringId.h"

struct ResourceFactory;
struct ResourcePackage;
class  hkThread;
class  hkSemaphore;

enum ResourceStatus
{
    kResourceLoading = 0,
    kResourceOffline,
    kResourceOnline,
    kResourceError,
    kResourceRequestUnload,
    kResourceStatusMax
};

typedef void* (*__RESOURCE_LOAD)(const char*, uint32_t);
typedef void  (*__RESOURCE_DESTROY)(void*);
typedef void  (*__RESOURCE_BRINGIN)(void*);
typedef void  (*__RESOURCE_LOOKUP)(void*);
typedef void  (*__RESOURCE_BRINGOUT)(void*);
typedef void  (*__RESOURCE_RELOAD)(void*, void*);

ENGINE_NATIVE_ALIGN struct ResourceInfo
{
    StringId                    m_name;
    void*                       m_ptr;
    uint32_t                    m_size;
    uint32_t                    m_offset;
};

ENGINE_NATIVE_ALIGN struct ResourceGroup
{
    ResourceInfo*               m_resources;
    ResourceFactory*            m_factory;
    StringId                    m_type;
    uint32_t                    m_numResources;
    uint32_t                    m_memUsed;
    uint32_t                    m_resourceInfoOffset;
};


struct ResourceFactory
{
    __RESOURCE_LOAD             m_loadFunc;
    __RESOURCE_DESTROY          m_destroyFunc;
    __RESOURCE_LOOKUP           m_lookupFunc;
    __RESOURCE_BRINGIN          m_bringInFunc;
    __RESOURCE_BRINGOUT         m_bringOutFunc;
    const char*                 m_name;
};

ENGINE_NATIVE_ALIGN struct ResourcePackage
{
    ResourceGroup*                      m_groups;
 
    StringId                            m_name;
    uint32_t                            m_numGroups;
    int                                 m_lastOnLineGroup;
    int                                 m_lastOnlineResource;

    char*                               m_head;
    char*                               m_offsetPtr;
    uint32_t                            m_memBudget;
    uint32_t                            m_lastAllocedMemSize;

    hkUint32                            m_status;
    bool                                m_bundled;
    
    void  init();
    void  destroy();

    char* allocMemory(uint32_t size);
    void  freeMemory(char* p);
    void  dump();

    void load();
    void unload();
    void flush(int maxNum);
    
    void lookupAllResources();
    void bringInAllResources(int maxNum);
    void bringOutAllresources();
    void destroyAllResources();
    void removeAllResources();

    int getStatus() const;
    void setStatus(int status);

    ResourceGroup* findGroup(const StringId& type) const;
    ResourceInfo* findResource(const StringId& type, const StringId& name) const;

private:
    void loadGroup(int index);
    void loadGroupBundled(int index);
    void bringInGroupResource(ResourceGroup& group, int start, int end);
};

struct ResourceRequest
{
    char*                       m_data;
    uint32_t                    m_dataLen;
    ResourceRequest*            m_next;
}; //I dont know the real size, decided by the package name length.

struct ResourceManager
{
    ResourcePackage**               m_packages;
    ResourceRequest*                m_requestListHead;

    uint32_t                        m_numPackages;
    uint32_t                        m_numRequests;

    ResourceFactory*                m_factories;
    StringId*                       m_types;
    uint32_t                        m_numFactories;
    uint32_t                        m_maxFactories;

    hkThread*                       m_thread;
    hkSemaphore*                    m_semaphore;

    void init(int maxFactories = 64);
    void quit();

    ResourceFactory* findFactory(const StringId& type);
    int findFactoryIndex(const StringId& type);
    void registerFactory(const ResourceFactory& factory);

    bool loadPackage(const char* packageName);
    void loadPackageAndWait(const char* packageName);
    bool unloadPackage(const StringId& packageName);
    int  getPackageStatus(const StringId& packageName);
    void flushPackage(const StringId& packageName, int maxNum = -1);

    void  insertResource(const StringId& type, const StringId& name, void* resource);
    void* findResource(const StringId& type, const StringId& name);
    void  removeResource(const StringId& type, const ResourceInfo& info);
    void  destroyAllResources();
    uint32_t  findResourcesTypeOf(const StringId& type, void** resourceArray, uint32_t arrayLen);
    uint32_t  findResourcesTypeOf(const StringId& type, ResourceInfo** resourceArray, uint32_t arrayLen);

    void  processRequests();

    void pushRequest(ResourceRequest* request);
    void  clearRequestQueue();

#ifdef RESOURCE_RELOAD
    void* reloadResource(const StringId& type, const StringId& name, const char* pathName, bool bFireCallbacks = true);
    void  destroyReloadResources();
    void  registerReloadCallback(const StringId& type, __RESOURCE_RELOAD func);
    void  reloadResource(const StringId& type, bool bFireCallbacks = true);
#endif

    static void* ioWorkLoop(void* p);

private:
    ResourcePackage* findPackage(const StringId& name);
};

extern ResourceManager      g_resourceMgr;

#define FIND_RESOURCE(className,name) ((className*)g_resourceMgr.findResource(className::getType(), name))


