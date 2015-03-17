#pragma once
#include "SharedInc.h"

class hkxNode;
class hkClass;
struct hkxAttributeGroup;
class hkxAttributeHolder;

#define COMMON_RESOURCE_PATH    ("core/common/")
#define INTERMEDIATE_PATH       "intermediate/"
#define COMMON_ASSET_PATH       INTERMEDIATE_PATH"core/common/"
#define ROOT_DATA               ("data")
#define ROOT_DATA_PATH          ("data/")
#define DDS_FORMAT              ("DXT5")
#define DDS_NM_FORMAT           ("DXT5")
#define DDS_ALPHA_FORMAT        ("DXT5")
#define TEXCONV_PATH            ("texconv.exe")
#define SHADERC_PATH            ("shaderc.exe")
#define SHADER_INCLUDE_EXT      ("sh")
#define SHADER_SOURCE_PATH      INTERMEDIATE_PATH"core/shaders/"
#define DC_RESULT               ("data_compiler_result.txt")
#define TEMP_PATH               ("temp/")
#define DEFAULT_SHADER          ("base")

typedef std::vector<std::string> StringArray;

enum ScanFlags
{
    SCAN_FILES  = 0x1,
    SCAN_DIRS   = 0x2,
    SCAN_HIDDEN = 0x4,
};

std::string getFileNameAndExtension(const std::string& fileName);
std::string getFileName(const std::string& fileName);
std::string getFilePath(const std::string& fileName);
std::string getFileExt(const std::string& fileName);
std::string replaceExtension(const std::string& fileName, const std::string& ext);
void        removeExtension(std::string& outStr);
void        toLower(std::string& input);
bool        isFileExist(const std::string& fileName);
bool        create_folder(const std::string& folderName);
void        string_replace(std::string& strBig, const std::string & strsrc, const std::string &strdst);
void        add_trailing_slash(std::string& outStr);
bool        copy_file(const std::string& src, const std::string& dst);
std::string getWorkingDir();
void        runProcess(const std::string& process, const std::string& workingDir, const std::string& args);
bool        write_file(const std::string& fileName, const void* buf, uint32_t bufSize);
uint32_t    get_file_size(const std::string& fileName);
std::string remove_top_folder(const std::string& fileName);
std::string get_top_folder(const std::string& dirName);
int         shell_exec(const std::string& exe, const StringArray& args, const std::string& workDir = "", bool bHide = true, std::string* output = 0);
std::string name_to_file_path(const std::string& resourceName, const std::string& ext);
bool        delete_file(const std::string& fileName);
void        compile_shader(const std::string& src, const std::string& dst, const std::string& def, bool vs);
int         find_char(const char* data, uint32_t size, char c);
void        msgBox(const char* text, const char* title);
bool        str_begin_with(const std::string& str1, const std::string& str2);
bool        str_end_with(const std::string& str1, const std::string& str2);
void        scan_dir(StringArray& result, const char* pathName, const char* filter, uint32_t flags, bool recursive);

void        dumpNodeRec(hkxNode* theNode);
void        findNodesRec(hkxNode* theNode, const hkClass* theClass, std::vector<hkxNode*>& outNodes);
void        findNodesRec(hkxNode* theNode, const std::string& preFix, std::vector<hkxNode*>& outNodes);
void        fill_object_attributes(jsonxx::Object& object, const hkxAttributeGroup* group);
void        fill_object_attributes(jsonxx::Object& object, const hkxAttributeHolder* holder);

void        texconv_compress(const std::string& src, const std::string& folder, const std::string& fmt);
void        lut2d_to_3d(const uint8_t* inData, uint8_t* outData);
std::string input_to_output(const std::string& inputName);
std::string get_package_name(const std::string& input);
std::string get_resource_name(const std::string& input);

//json utility functions
uint32_t    json_to_floats(const jsonxx::Object& o, const char* name, float* p, uint32_t max_size);
uint32_t    json_to_flags(const jsonxx::Object& o, const char* name, const char** enum_names);
float       json_to_float(const jsonxx::Object& o, const char* name, float def = 0.0f);
int         json_to_int(const jsonxx::Object& o, const char* name, int def = 0);
StringId    json_to_stringid(const jsonxx::Object& o, const char* name, StringId def=0);
int         json_to_enum(const jsonxx::Object& o, const char* name, const char** enumnames, int def = -1);
bool        json_to_bool(const jsonxx::Object& o,const char* name, bool def=false);

typedef uint32_t (*func_fact_object_mem_t)(const jsonxx::Object& o, char* p);
Fact*       json_to_fact(const jsonxx::Object& o, const char* name, func_fact_object_mem_t f);
bool        write_json_to_file(const jsonxx::Object& o, const std::string& fileName);
bool        read_json_from_file(jsonxx::Object& o, const std::string& fileName);
void        binary_to_string(const unsigned char* b, int len, std::string& s);
void        string_to_binary(const std::string& s, unsigned char* b, int capacity);

typedef tinystl::unordered_map<uint32_t, uint32_t> ResourceFileMap;
struct ResourceFileDataBase
{
    ResourceFileMap     m_files;
    bx::LwMutex         m_lock;

    void load(const char* fileName);
    void save(const char* fileName);
    bool isFileChanged(const std::string& fileName, uint32_t& modifyTime) const;
    void insertResourceFile(const std::string& fileName,  const uint32_t& modifyTime);
};

struct FileReader
{
    char*                   m_buf;
    uint32_t                m_size;
    bx::CrtFileReader       m_file;

    FileReader(const std::string& fileName);
    ~FileReader();
};

struct MemoryBuffer
{
    char*           m_buf;
    uint32_t        m_size;
    MemoryBuffer(uint32_t size);
    ~MemoryBuffer();
    void alloc(uint32_t size);
};

struct ToolError
{
    ToolError();
    void add_error(const char* fmt, ...);
    void show_error();

    StringArray                     m_error_msgs;
    bx::LwMutex                     m_lock;
    int                             m_num_error;
};