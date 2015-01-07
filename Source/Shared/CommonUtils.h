#pragma once
#include <stdint.h>
#include <string>
#include <windows.h>
#include <vector>
#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>

#define MAKE_U64(dwordHigh, dwordLow) (((uint64_t)(dwordHigh) << 32) | (uint64_t)(dwordLow))
#define COMMON_RESOURCE_PATH    ("core/common/")
#define INTERMEDIATE_PATH       "intermediate/"
#define COMMON_ASSET_PATH       INTERMEDIATE_PATH"core/common/"
#define ROOT_DATA               ("data")
#define ROOT_DATA_PATH          ("data/")
#define DDS_FORMAT              ("DXT1")
#define DDS_NM_FORMAT           ("DXT5")
#define DDS_ALPHA_FORMAT        ("DXT5")
#define NVTT_PATH               ("nvcompress.exe")
#define TEXCONV_PATH            ("texconv.exe")
#define SHADERC_PATH            ("shaderc.exe")
#define SHADER_INCLUDE_EXT      ("sc")
#define SHADER_SOURCE_PATH      INTERMEDIATE_PATH"core/shaders/"


std::string getFileNameAndExtension(const std::string& fileName);
std::string getFileName(const std::string& fileName);
std::string getFilePath(const std::string& fileName);
std::string getFileExt(const std::string& fileName);
std::string replaceExtension(const std::string& fileName, const std::string& ext);
void        removeExtension(std::string& outStr);
void        toLower(std::string& input);
void        addError(const char* fmt, ...);
bool        isFileExist(const std::string& fileName);
bool        isFolderExist(const std::string& folderName);
void        createFolder(const std::string& folderName);
void        string_replace(std::string& strBig, const std::string & strsrc, const std::string &strdst);
void        addBackSlash(std::string& outStr);
void        fixPathSlash(std::string& inout);
void        showErrorMessage(const char* title, const char* error_file, bool bSlient);
bool        fileSystemCopy(const std::string& src, const std::string& destFolder);
std::string getWorkingDir();
void        runProcess(const std::string& process, const std::string& workingDir, const std::string& args);
void        findFiles(const std::string& folder, const std::string& ext, bool bRecursive, std::vector<std::string>& outFiles);
uint32_t    read_file(const std::string& fileName, char** outBuf); //malloc need to free manually
void        delete_file_buffer(char* ptr);
bool        write_file(const std::string& fileName, const void* buf, uint32_t bufSize);
void        findFolders(const std::string& folder, bool bRecursive, std::vector<std::string>& outFolders);
uint64_t    get_file_size(const std::string& fileName);
std::string remove_top_folder(const std::string& fileName);
std::string get_top_folder(const std::string& dirName);
std::string relative_to_full_path(const std::string input);
void        shell_exec(const std::string& exe, const std::string& args, const std::string& workDir = "", bool bHide = true);
std::string name_to_file_path(const std::string& resourceName, const std::string& ext);
void        delete_file(const std::string& fileName);
bool        delete_folder(const std::string& folderName);
void        compile_shader(const std::string& src, const std::string& dst, const std::string& def, bool vs);
int         find_char(const char* data, uint32_t size, char c);
void        msgBox(const char* text, const char* title);
std::string get_last_string(const std::string& input, char c, int count);
bool        str_begin_with(const std::string& str1, const std::string& str2);
bool        str_end_with(const std::string& str1, const std::string& str2);

typedef tinystl::unordered_map<uint32_t, uint64_t> ResourceFileMap;
struct ResourceFileDataBase
{
    ResourceFileMap       m_files;
    void load(const char* fileName);
    void save(const char* fileName);
    bool isFileChanged(const std::string& fileName, uint64_t& modifyTime) const;
    void insertResourceFile(const std::string& fileName,  const uint64_t& modifyTime);
};

struct FileReader
{
    char*           m_buf;
    uint32_t        m_size;
    FileReader(const std::string& fileName);
    ~FileReader();
};

struct MemoryBuffer
{
    char*           m_buf;
    uint32_t        m_size;
    MemoryBuffer(uint32_t size);
    ~MemoryBuffer();
};