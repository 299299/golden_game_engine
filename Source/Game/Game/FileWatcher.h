#pragma once
#include "Prerequisites.h"
#include "StringId.h"
#include "Profiler.h"
#include <bx/thread.h>
#include <bx/mutex.h>
#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>

struct ChangedFile
{
    char        m_fileName[64 - sizeof HiresTimer];
    HiresTimer  m_timer;
};

struct FileName
{
    char        m_buf[64];
};

/// Watches a directory and its subdirectories for files being modified.
class  FileWatcher
{
public:
    FileWatcher();
    ~FileWatcher();
    
    /// Start watching a directory. Return true if successful.
    bool start_watching(const char* pathName, bool watchSubDirs);
    /// Stop watching the directory.
    void stop_watching();
    /// Set the delay in seconds before file changes are notified. This (hopefully) avoids notifying when a file save is still in progress. Default 1 second.
    void set_delay(float interval);
    /// Add a file change into the changes queue.
    void add_change(const char* fileName);
    /// Return a file change (true if was found, false if not.)
    bool get_next_change(char* dest,  uint32_t buf_size);

    void thread_loop();

    static int32_t thread_func_file_watcher(void* userdata);
    
private:
#ifdef WIN32
    /// Directory handle for the path being watched.
    void* m_dirHandle;
#elif __linux__
    typedef tinystl::unordered_map<int, FileName> DirHandleMap;
    /// HashMap for the directory and sub-directories (needed for inotify's int handles).
    DirHandleMap m_dirHandle;
    /// Linux inotify needs a handle.
    int m_watchHandle;
#endif

    char                            m_path[256];
    typedef tinystl::unordered_map<uint32_t, ChangedFile> ChangeMap;
    ChangeMap                       m_changedFiles;        
    bx::Thread                      m_thread;
    bx::Mutex                       m_changesMutex;
    float                           m_delay;
    bool                            m_watchSubDirs;
    mutable bool                    m_running;
    mutable bool                    m_changed;
};
