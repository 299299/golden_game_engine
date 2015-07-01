#pragma once
#include "Prerequisites.h"
#include "StringId.h"
#include "GameConfig.h"
#include <bx/mutex.h>

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

typedef void* (*func_load_resource_t)(void*, uint32_t);
typedef void  (*func_destroy_resource_t)(void*);
typedef int   (*func_bringin_resource_t)(void*);
typedef void  (*func_lookup_resource_t)(void*);
typedef void  (*func_bringout_resource_t)(void*);
typedef void  (*func_reload_resource_t)(void*, void*);

ENGINE_NATIVE_ALIGN(struct) ResourceInfo
{
    StringId                    m_name;
    void*                       m_ptr;
    uint32_t                    m_size;
    uint32_t                    m_offset;
};

ENGINE_NATIVE_ALIGN(struct) ResourceGroup
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
    func_load_resource_t        m_loadFunc;
    func_destroy_resource_t     m_destroyFunc;
    func_lookup_resource_t      m_lookupFunc;
    func_bringin_resource_t     m_bringInFunc;
    func_bringout_resource_t    m_bringOutFunc;
    const char*                 m_name;
    int                         m_order;
};

ENGINE_NATIVE_ALIGN(struct) ResourcePackage
{
    ResourceGroup*                      m_groups;

    StringId                            m_name;
    uint32_t                            m_numGroups;
    int                                 m_lastOnLineGroup;
    int                                 m_lastOnlineResource;

    uint32_t                            m_memBudget;
    LinearAllocator*                    m_allocator;
    char                                m_allocator_buffer[32];

    volatile uint32_t                   m_status;
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

    ResourceGroup* find_group(StringId type) const;
    ResourceInfo* find_resource(StringId type, StringId name) const;

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

    bx::LwMutex                     m_queueLock;
    bx::LwMutex                     m_resourceLock;
    volatile int                    m_running;

    void init();
    void shutdown();
    void offline_all_resources();

    //--------------------------------------------------------------------
    // Factory API
    ResourceFactory* find_factory(StringId type);
    void register_factory(const ResourceFactory& factory);
    int get_resource_order(StringId type);

    //--------------------------------------------------------------------
    // Package API
    bool load_package(const char* packageName);
    bool load_package_and_wait(const char* packageName);
    bool unload_package(StringId packageName);
    int  get_package_status(StringId packageName);
    void flush_package(StringId packageName, int maxNum = -1);

    //--------------------------------------------------------------------
    // Resource API
    void  insert_resource(StringId type, StringId name, void* resource);
    void* find_resource(StringId type, StringId name);
    void  remove_resource(StringId type, const ResourceInfo& info);
    uint32_t  find_resources_type_of(StringId type, ResourceInfo** resourceArray, uint32_t arrayLen);
    ResourceInfo* find_resource_info(StringId type, StringId name);
#ifdef RESOURCE_RELOAD
    void* reload_resource(StringId type, StringId name, const char* pathName, bool bFireCallbacks = true);
    void  destroy_reload_resources();
    void  register_reload_callback(StringId type, func_reload_resource_t func);
    void  reload_resource(StringId type, bool bFireCallbacks = true);
#endif

    //--------------------------------------------------------------------
    // Inner Thread API
    static void* io_work_loop(void* p);
    void  process_request();


private:
    ResourcePackage* find_package(StringId name);
    void push_request(ResourceRequest* request);

public:
    bool is_running() const { return m_running != 0; };
    void set_running(int r) { m_running = r;};
};

extern ResourceManager      g_resourceMgr;

#define FIND_RESOURCE(className,type,name) ((className*)g_resourceMgr.find_resource(type, name))
