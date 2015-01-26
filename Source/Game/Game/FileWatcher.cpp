#include "FileWatcher.h"
#include "Log.h"
#include <bx/string.h>
#include "ToolUtils.h"

#ifdef WIN32
#include <windows.h>
#elif __linux__
#include <sys/inotify.h>
extern "C" {
// Need read/close for inotify
#include "unistd.h"
}
#endif

#define BUFFERSIZE 4096

FileWatcher::FileWatcher() :
#ifdef WIN32
    m_dirHandle(0),
#elif __linux__
    m_watchHandle(0),
#endif
    m_delay(1.0f),
    m_watchSubDirs(false),
    m_running(false),
    m_changed(false)
{
    memset(m_path, 0, sizeof(m_path));
#if defined(__linux__)
    m_watchHandle = inotify_init();
#endif
}

FileWatcher::~FileWatcher()
{
    stop_watching();
#if defined(__linux__)
    close(m_watchHandle);
#endif
}

int32_t FileWatcher::thread_func_file_watcher( void* userdata )
{
    FileWatcher* watcher = (FileWatcher*)userdata;
    watcher->thread_loop();
    return 0;
}

bool FileWatcher::start_watching( const char* pathName, bool watchSubDirs )
{
    stop_watching();

#if defined(WIN32)
    strncpy(m_path, pathName, sizeof(m_path));
    if(m_path[strlen(m_path) - 1] != '/')
        m_path[strlen(m_path)] = '/';

    m_dirHandle = (void*)CreateFileA(
        m_path,
        FILE_LIST_DIRECTORY,
        FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
        0,
        OPEN_EXISTING,
        FILE_FLAG_BACKUP_SEMANTICS,
        0);

    if (m_dirHandle != INVALID_HANDLE_VALUE)
    {
        m_watchSubDirs = watchSubDirs;
        m_running = true;
        m_thread.init(thread_func_file_watcher, this);
        LOGD("Started watching path %s", pathName);
        return true;
    }
    else
    {
        LOGE("Failed to start watching path %s", pathName);
        return false;
    }
#elif defined(__linux__)
    int flags = IN_CREATE|IN_DELETE|IN_MODIFY|IN_MOVED_FROM|IN_MOVED_TO;
    int handle = inotify_add_watch(m_watchHandle, pathName, flags);

    if (handle < 0)
    {
        LOGE("Failed to start watching path %s", pathName);
        return false;
    }
    else
    {
        // Store the root path here when reconstructed with inotify later
        m_watchSubDirs = watchSubDirs;

        if (m_watchSubDirs)
        {
            StringArray subDirs;
            scan_dir(subDirs, pathName, "*", SCAN_DIRS, true);

            for (unsigned i = 0; i < subDirs.size(); ++i)
            {
                std::string subDirFullPath = std::string(m_path) + subDirs[i];
                addBackSlash(subDirFullPath);

                // Don't watch ./ or ../ sub-directories
                if (!str_end_with(subDirFullPath, "./"))
                {
                    handle = inotify_add_watch(m_watchHandle, subDirFullPath.c_str(), flags);
                    if (handle < 0)
                    {
                        LOGE("Failed to start watching subdirectory path %s", subDirFullPath.c_str());
                    }
                    else
                    {
                        // Store sub-directory to reconstruct later from inotify
                        addBackSlash(subDirs[i]);
                        FileName& f = m_dirHandle[handle];
                        memset(f.m_buf, 0, sizeof(f.m_buf));
                        strncpy(f.m_buf, subDirs[i].c_str(), sizeof(f.m_buf));
                    }
                }
            }
        }
        m_thread.init(thread_func_file_watcher, this);

        LOGD("Started watching path %s", pathName);
        return true;
    }
#endif
}

void FileWatcher::stop_watching()
{
    if (!m_running)
    {
        return;
    }

    // Create and delete a dummy file to make sure the watcher loop terminates
    m_running = false;

    {
        char dummy_buf[256];
        bx::snprintf(dummy_buf, sizeof(dummy_buf), "%sdummy.tmp", m_path);
        FILE* dummy_fp = fopen(dummy_buf, "wb");
        fclose(dummy_fp);
        delete_file(dummy_buf);
    }

    m_thread.shutdown();

#if defined(WIN32)
    CloseHandle((HANDLE)m_dirHandle);
#elif defined(__linux__)
    for (DirHandleMap::iterator i = m_dirHandle.begin(); i != m_dirHandle.end(); ++i)
        inotify_rm_watch(m_watchHandle, i->first);
    m_dirHandle.clear();
#endif

    LOGD("Stopped watching path %s", m_path);
    memset(m_path, 0, sizeof(m_path));
}

void FileWatcher::set_delay( float interval )
{
    m_delay = interval;
}

void FileWatcher::add_change( const char* fileName )
{
    int _len = strlen(fileName);
    bool _dot = false;
    //find dot first.
    for (int i=0; i<_len; ++i)
    {
        if(fileName[i] == '.')
        {
            _dot = true;
            break;
        }
    }

    if (!_dot)
    {
        //it`s a directory
        return;
    }

    //filter .tmp --> this is a sublime text file
    static const char* tmp_str = ".tmp";
    static int tmp_len = 4;

    if(_len > tmp_len)
    {
        bool _noteq = false;
        for (int i=_len-tmp_len, j=0; i<_len; ++i, ++j)
        {
            char src = tmp_str[j];
            char dst = tolower(fileName[i]);
            if(src != dst)
            {
                _noteq = true;
                break;
            }
        }

        if(!_noteq) // ends with .tmp
            return;
    }

    LOGD("%s has changed.", fileName);
    m_changed = true;
    uint32_t key = StringId::calculate(fileName);
    ChangedFile f;
    strncpy(f.m_fileName, fileName, sizeof(f.m_fileName));

    for (int i=0; i<_len; ++i)
    {
        if(f.m_fileName[i] == '\\')
        {
            f.m_fileName[i] = '/';
        }
    }

    bx::LwMutexScope _l(m_changesMutex);
    m_changedFiles[key] = f;
}

bool FileWatcher::get_next_change( char* dest, uint32_t buf_size)
{
    if(!m_changed)
        return false;

    unsigned delayMsec = (unsigned)(m_delay * 1000.0f);

    bx::LwMutexScope _l(m_changesMutex);
    if (m_changedFiles.empty())
        return false;
    else
    {
        for (ChangeMap::iterator i=m_changedFiles.begin();
             i != m_changedFiles.end(); ++i)
        {
            ChangedFile& f = i->second;
            if (f.m_timer.get_usec(false) >= delayMsec)
            {
                bx::snprintf(dest, buf_size, "%s%s", m_path, f.m_fileName);
                m_changedFiles.erase(i);
                m_changed = !m_changedFiles.empty();
                return true;
            }
        }

        return false;
    }
}

void FileWatcher::thread_loop()
{
#if defined(WIN32)
    unsigned char buffer[BUFFERSIZE];
    DWORD bytesFilled = 0;

    while (m_running)
    {
        if (ReadDirectoryChangesW((HANDLE)m_dirHandle,
            buffer,
            BUFFERSIZE,
            m_watchSubDirs,
            FILE_NOTIFY_CHANGE_LAST_WRITE | FILE_NOTIFY_CHANGE_FILE_NAME,
            &bytesFilled,
            0,
            0))
        {
            unsigned offset = 0;

            while (offset < bytesFilled)
            {
                FILE_NOTIFY_INFORMATION* record = (FILE_NOTIFY_INFORMATION*)&buffer[offset];

                if (record->Action == FILE_ACTION_MODIFIED || record->Action == FILE_ACTION_RENAMED_NEW_NAME)
                {
                    const wchar_t* src = record->FileName;
                    const wchar_t* end = src + record->FileNameLength / 2;
                    char _buf[64];
                    memset(_buf, 0, sizeof(_buf));
                    char* p = _buf;
                    while (src < end)
                    {
                        *(p++) = (char)*(src++);
                    }
                    add_change(_buf);
                }

                if (!record->NextEntryOffset)
                    break;
                else
                    offset += record->NextEntryOffset;
            }
        }
    }
#elif defined(__linux__)
    unsigned char buffer[BUFFERSIZE];

    while (m_running)
    {
        int i = 0;
        int length = read(m_watchHandle, buffer, sizeof(buffer));

        if (length < 0)
            return;

        while (i < length)
        {
            inotify_event* event = (inotify_event*)&buffer[i];

            if (event->len > 0)
            {
                if (event->mask & IN_MODIFY || event->mask & IN_MOVE)
                {
                    char _buf[256];
                    bx::snprintf(_buf, sizeof(_buf), "%s%s", m_dirHandle[event->wd].m_buf, event->name);
                    add_change(_buf);
                }
            }

            i += sizeof(inotify_event) + event->len;
        }
    }
#endif
}
