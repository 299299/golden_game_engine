#pragma once
#include "Prerequisites.h"
#include "StringId.h"
#include "GameConfig.h"

struct ResourceFactory;
struct ResourcePackage;
class  hkThread;
class  hkSemaphore;
class  LinearAllocator;

enum ResourceStatus
{
    kResourceLoading = 0,
    kResourceOffline,
    kResourceOnline,
    kResourceRequestUnload,
    kResourceNotFound,
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

    uint32_t                            m_memBudget;
    LinearAllocator*                    m_allocator;
    char                                m_allocator_buffer[32];

    uint32_t                            m_status;
    bool                                m_bundled;

    void  init();
    void  destroy();

    void  load();
    void  unload();
    void  flush(int maxNum);


    void  bringin_all_resources(int maxNum);
    void  bringout_all_resources();
    void  destroy_all_resources();
    void  remove_all_resources();

    int  get_status() const;
    void set_status(int status);

    ResourceGroup* find_group(const StringId& type) const;
    ResourceInfo* find_resource(const StringId& type, const StringId& name) const;

private:
    void load_group(int index);
    void load_group_bundled(int index);
    void bringin_group_resource(ResourceGroup& group, int start, int end);
    void lookup_all_resources();
};

struct ResourceRequest
{
    char*                       m_data;
    uint32_t                    m_dataLen;
    ResourceRequest*            m_next;
}; //I dont know the real size, decided by the package name length.

struct ResourceManager
{
    ResourcePackage*                m_packages[MAX_RESOURCE_PACKAGES];
    ResourceRequest*                m_requestListHead;

    uint32_t                        m_numPackages;
    uint32_t                        m_numRequests;

    ResourceFactory                 m_factories[MAX_RESOURCE_TYPES];
    StringId                        m_types[MAX_RESOURCE_TYPES];
    uint32_t                        m_numFactories;
    char*                           m_resMapBuffer;

    hkThread*                       m_thread;
    hkSemaphore*                    m_semaphore;

    void init();
    void shutdown();
    void offline_all_resources();

    //--------------------------------------------------------------------
    // Factory API
    ResourceFactory* find_factory(const StringId& type);
    void register_factory(const ResourceFactory& factory);

    //--------------------------------------------------------------------
    // Package API
    bool load_package(const char* packageName);
    bool load_package_and_wait(const char* packageName);
    bool unload_package(const StringId& packageName);
    int  get_package_status(const StringId& packageName);
    void flush_package(const StringId& packageName, int maxNum = -1);

    //--------------------------------------------------------------------
    // Resource API
    void  insert_resource(const StringId& type, const StringId& name, void* resource);
    void* find_resource(const StringId& type, const StringId& name);
    void  remove_resource(const StringId& type, const ResourceInfo& info);
    uint32_t  find_resources_type_of(const StringId& type, ResourceInfo** resourceArray, uint32_t arrayLen);
    ResourceInfo* find_resource_info(const StringId& type, const StringId& name);
#ifdef RESOURCE_RELOAD
    void* reload_resource(const StringId& type, const StringId& name, const char* pathName, bool bFireCallbacks = true);
    void  destroy_reload_resources();
    void  register_reload_callback(const StringId& type, __RESOURCE_RELOAD func);
    void  reload_resource(const StringId& type, bool bFireCallbacks = true);
#endif

    //--------------------------------------------------------------------
    // Inner Thread API
    static void* io_work_loop(void* p);
    void  process_request();

private:
    ResourcePackage* find_package(const StringId& name);
    void push_request(ResourceRequest* request);
};

extern ResourceManager      g_resourceMgr;

#define FIND_RESOURCE(className,name) ((className*)g_resourceMgr.find_resource(className::get_type(), name))
#define FIND_RESOURCE_NAMED(className,name) ((className*)g_resourceMgr.find_resource(className::get_type(), StringId(name)))

