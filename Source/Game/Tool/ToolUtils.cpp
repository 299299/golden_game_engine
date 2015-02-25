#include "ToolUtils.h"

#ifdef WIN32
#include <windows.h>
#include <shellapi.h>
#include <direct.h>
#include <shlobj.h>
#include <sys/types.h>
#include <sys/utime.h>
#include <io.h>
#include <sys/stat.h>
#else
#include <dirent.h>
#include <errno.h>
#include <unistd.h>
#include <utime.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#define MAX_PATH 256
#endif

std::string getFileNameAndExtension( const std::string& fileName )
{
    size_t pos = fileName.find_last_of('\\');
    if(pos == std::string::npos)
        pos = fileName.find_last_of('/');
    if(pos == std::string::npos)
        return fileName;
    pos += 1;
    return fileName.substr(pos, fileName.length() - pos);
}
std::string getFilePath(const std::string& fileName)
{
    size_t pos = fileName.find_last_of('\\');
    if(pos == std::string::npos)
        pos = fileName.find_last_of('/');
    if(pos == std::string::npos)
        return fileName;
    std::string ret = fileName.substr(0, pos);
    add_trailing_slash(ret);
    return ret;
}
std::string getFileName(const std::string& fileName)
{
    std::string nameWithExt = getFileNameAndExtension(fileName);
    size_t pos = nameWithExt.find_last_of('.');
    if(pos == std::string::npos)
        return nameWithExt;
    return nameWithExt.substr(0, pos);
}
std::string getFileExt(const std::string& fileName)
{
    size_t pos = fileName.find_last_of('.') + 1;
    std::string ret = fileName.substr(pos, fileName.length() - pos);
    toLower(ret);
    return ret;
}
std::string replaceExtension(const std::string& fileName, const std::string& ext)
{
    std::string new_filename = fileName;
    std::string::size_type result = new_filename.find_last_of('.');
    // Does new_filename.erase(std::string::npos) working here in place of this following test?
    if (std::string::npos != result)
        new_filename.erase(result+1);
    // append extension:
    new_filename.append(ext);
    return new_filename;
}

void removeExtension( std::string& outStr )
{
    std::string::size_type result = outStr.find_last_of('.');
    if (std::string::npos != result)
        outStr.erase(result);
}
void toLower(std::string& input)
{
    std::transform(input.begin(), input.end(), input.begin(), tolower);
}

bool isFileExist( const std::string& fileName )
{
#ifdef WIN32
    return _access(fileName.c_str(), 0) == 0;
#else
    return access(fileName.c_str(), R_OK) == 0;
#endif
}
bool create_folder(const std::string& inPath)
{
    if(isFileExist(inPath) || inPath.empty())
        return true;

    std::string pathName = inPath;
    string_replace(pathName, "\\", "/");
    add_trailing_slash(pathName);

    #ifdef HAVOK_COMPILE
    bool success = (CreateDirectoryA(pathName.c_str(), 0) == TRUE) || (GetLastError() == ERROR_ALREADY_EXISTS);
    #else
    bool success = mkdir(pathName.c_str(), S_IRWXU) == 0 || errno == EEXIST;
    #endif

    if(success)
    {
        LOGD("Create Directory %s", pathName.c_str());
    }
    else
    {
        LOGE("Create Directory %s", pathName.c_str());
    }
    return success;
}
void string_replace( std::string &strBig, const std::string &strsrc, const std::string &strdst )
{
    std::string::size_type pos = 0;
    std::string::size_type srclen = strsrc.size();
    std::string::size_type dstlen = strdst.size();

    while( (pos=strBig.find(strsrc, pos)) != std::string::npos )
    {
        strBig.replace( pos, srclen, strdst );
        pos += dstlen;
    }
}

bool copy_file(const std::string& src, const std::string& dst)
{
    LOGD("file system copy from %s to %s", src.c_str(), dst.c_str());

    bx::CrtFileReader reader;
    bx::CrtFileWriter writer;

    if(reader.open(src.c_str()))
        return false;

    if(writer.open(dst.c_str()))
        return false;

    uint32_t size = bx::getSize(&reader);
    void* p = malloc(size);
    reader.read(p, size);
    reader.close();

    writer.write(p, size);
    writer.close();
    free(p);
    return true;
}

std::string getWorkingDir()
{
    char path[MAX_PATH];
    path[0] = 0;
#ifdef HAVOK_COMPILE
    GetCurrentDirectoryA(MAX_PATH, path);
#else
    getcwd(path, MAX_PATH);
#endif
    std::string ret(path);
    add_trailing_slash(ret);
    return ret;
}

void runProcess(const std::string& process, const std::string& workingDir, const std::string& args)
{
#ifdef HAVOK_COMPILE
    PROCESS_INFORMATION processInformation;
    STARTUPINFO startupInfo;
    memset(&processInformation, 0, sizeof(processInformation));
    memset(&startupInfo, 0, sizeof(startupInfo));
    startupInfo.cb = sizeof(startupInfo);
    startupInfo.hStdError = GetStdHandle(STD_INPUT_HANDLE);
    startupInfo.hStdOutput = GetStdHandle(STD_INPUT_HANDLE);
    startupInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    startupInfo.dwFlags |= STARTF_USESTDHANDLES;

    char tempCmdLine[MAX_PATH * 2];
    strncpy(tempCmdLine, args.c_str(), sizeof(tempCmdLine));

    char tempWorkDir[MAX_PATH * 2];
    strncpy(tempWorkDir, workingDir.c_str(), sizeof(tempCmdLine));

    const char* workDir = 0;
    if(workingDir.length() > 0)
        workDir = tempWorkDir;

    BOOL result = ::CreateProcessA(process.c_str(), tempCmdLine, NULL, NULL, FALSE,
                                  NORMAL_PRIORITY_CLASS, NULL, workDir,
                                  &startupInfo, &processInformation);
    if (result == 0)
    {
        LOGE("ERROR: CreateProcess failed!");
        return;
    }
    else
    {
        WaitForSingleObject( processInformation.hProcess, INFINITE );
        CloseHandle( processInformation.hProcess );
        CloseHandle( processInformation.hThread );
    }
#endif
}

static std::string sub_string(const std::string& str, unsigned pos)
{
    if (pos < str.length())
        return str.substr(pos, str.length() - pos);
    else
        return "";
}

static void scan_dir_internal(StringArray& result,
                              std::string path,
                              const std::string& startPath,
                              const std::string& filter,
                              uint32_t flags,
                              bool recursive)
{
    add_trailing_slash(path);
    std::string deltaPath;
    if (path.length() > startPath.length())
        deltaPath = sub_string(path, startPath.length());

    std::string filterExtension = filter;
    if (filterExtension.find_first_of('*') != std::string::npos)
        filterExtension.clear();

    LOGD("scan_dir_internal path=%s,startPath=%s,deltaPath=%s,filter=%s",
        path.c_str(), startPath.c_str(),
        deltaPath.c_str(), filterExtension.c_str());

    #ifdef WIN32
    WIN32_FIND_DATAA info;
    HANDLE handle = FindFirstFileA((path + "*").c_str(), &info);
    if (handle != INVALID_HANDLE_VALUE)
    {
        do
        {
            std::string fileName(info.cFileName);
            if(fileName == "." || fileName == "..")
                continue;
            std::string pathAndName = path + fileName;
            if (!fileName.empty())
            {
                if (info.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN && !(flags & SCAN_HIDDEN))
                    continue;
                if (info.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
                {
                    if (flags & SCAN_DIRS)
                        result.push_back(pathAndName);
                    if (recursive)
                        scan_dir_internal(result, path + fileName, startPath, filter, flags, recursive);
                }
                else if (flags & SCAN_FILES)
                {
                    if (filterExtension.empty() || str_end_with(fileName, filterExtension))
                        result.push_back(pathAndName);
                }
            }
        }
        while (FindNextFileA(handle, &info));
        FindClose(handle);
    }
    #else
    DIR *dir;
    struct dirent *de;
    struct stat st;
    dir = opendir(path.c_str());
    if (dir)
    {
        while ((de = readdir(dir)))
        {
            std::string fileName(de->d_name);
            if(fileName == "." || fileName == "..")
                continue;
            bool isDot = str_begin_with(fileName, ".");
            if (!(flags & SCAN_HIDDEN) && isDot)
                continue;
            std::string pathAndName = path + fileName;
            //LOGD("pathAndName=%s, fileName=%s", pathAndName.c_str(), fileName.c_str());
            if (!stat(pathAndName.c_str(), &st))
            {
                if (st.st_mode & S_IFDIR)
                {
                    if (flags & SCAN_DIRS)
                        result.push_back(pathAndName);
                    if (recursive)
                        scan_dir_internal(result, path + fileName, startPath, filter, flags, recursive);
                }
                else if (flags & SCAN_FILES)
                {
                    if (filterExtension.empty() || str_end_with(fileName, filterExtension))
                        result.push_back(pathAndName);
                }
            }
        }
        closedir(dir);
    }
    #endif
}

void scan_dir(StringArray& result, const char* pathName, const char* filter, uint32_t flags, bool recursive)
{
    LOGD("SCAN_DIR=%s, filter=%s, flags=%x, recursive=%d", pathName, filter, flags, recursive);
    std::string initialPath(pathName);
    add_trailing_slash(initialPath);
    scan_dir_internal(result, initialPath, initialPath, filter, flags, recursive);
}

bool write_file(const std::string& fileName, const void* buf, uint32_t bufSize)
{
    LOGI("write_file %s", fileName.c_str());
    bx::CrtFileWriter writer;
    if(writer.open(fileName.c_str())) {
        LOGE("write_file can not open %s", fileName.c_str());
        return false;
    }
    int32_t ret = writer.write(buf, bufSize);
    writer.close();
    bool bRet = ret != 0;
    if(!bRet)
        LOGE("write_file %s failed", fileName.c_str());
    return bRet;
}

void add_trailing_slash( std::string& outStr )
{
    if(outStr.back() != '/')
        outStr += "/";
}

uint32_t get_file_size(const std::string& fileName)
{
#ifdef WIN32
    struct _stat st;
    if (!_stat(fileName.c_str(), &st))
        return (unsigned)st.st_size;
#else
    struct stat st;
    if (!stat(fileName.c_str(), &st))
        return (unsigned)st.st_size;
#endif
    else
        return 0;
}

std::string remove_top_folder(const std::string& fileName)
{
    std::string ret = fileName;
    if(ret[0] == '/')
        ret = ret.substr(0, ret.length() - 1);
    int npos = ret.find_first_of('/') + 1;
    std::string s = ret.substr(npos, ret.length() - npos);
    if(s == ".")
        s = "";
    return s;
}

std::string get_top_folder(const std::string& dirName)
{
    std::string ret = dirName;
    if(ret[0] == '/')
        ret = ret.substr(0, ret.length() - 1);
    int npos = ret.find_first_of('/');
    return ret.substr(0, npos);
}

int shell_exec(const std::string& exe, const StringArray& args, const std::string& workDir, bool bHide)
{
#ifdef WIN32
    SHELLEXECUTEINFO ShExecInfo = {0};
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = exe.c_str();
    std::string arg_line;
    for (size_t i=0; i<args.size(); ++i)
    {
        arg_line += " " + args[i];
    }
    ShExecInfo.lpParameters = arg_line.c_str();
    ShExecInfo.lpDirectory = workDir.length() ? workDir.c_str() : 0;
    ShExecInfo.nShow = bHide ? SW_HIDE : SW_SHOW;
    ShExecInfo.hInstApp = NULL;
    BOOL bRet = ShellExecuteEx(&ShExecInfo);
    if(!bRet)
    {
        LOGE("ShellExecuteEx error ");
        return -1;
    }
    WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
    return bRet;
#else
    pid_t pid = fork();
    if (!pid)
    {
        std::vector<const char*> argPtrs;
        argPtrs.push_back(exe.c_str());
        for (unsigned i = 0; i < args.size(); ++i)
            argPtrs.push_back(args[i].c_str());
        argPtrs.push_back(0);

        execvp(argPtrs[0], (char**)&argPtrs[0]);
        return -1; // Return -1 if we could not spawn the process
    }
    else if (pid > 0)
    {
        int exitCode;
        wait(&exitCode);
        return exitCode;
    }
    else
        return -1;
#endif
}

std::string name_to_file_path( const std::string& resourceName, const std::string& ext )
{
    return std::string(ROOT_DATA_PATH) + resourceName + "." + ext;
}

bool delete_file(const std::string& fileName)
{
    if(!isFileExist(fileName))
        return false;
    return remove(fileName.c_str()) == 0;
}

void compile_shader(const std::string& src, const std::string& dst, const std::string& def, bool vs)
{
    char buf[256];
    const char* type = vs ? "v" : "f";
    const char* target = vs ? "vs_5_0" : "ps_5_0";
    bx::snprintf(buf, sizeof(buf),
                "-f %s -o %s --type %s --platform windows --verbose -p %s --varyingdef %s",
                src.c_str(), dst.c_str(), type, target, def.c_str());
    std::string folder = getFilePath(src);
    StringArray args;
    args.push_back(buf);
    shell_exec(SHADERC_PATH, args, "");
#if 1
    if(!isFileExist(dst))
    {
        LOGE("shader err --> \n %s %s \n", SHADERC_PATH, buf);
    }
#endif
}

int find_char(const char* data, uint32_t size, char c)
{
    for (uint32_t i = 0; i < size; ++i)
    {
        if(data[i] == c)
            return (int)i;
    }
    return -1;
}

bool str_begin_with( const std::string& s, const std::string& head )
{
    return s.compare(0, head.length(), head) == 0;
}
bool str_end_with(const std::string& s, const std::string& tail)
{
    return s.compare(s.length() - tail.length(), tail.length(), tail) == 0;
}

void dumpNodeRec(hkxNode* theNode)
{
#ifdef HAVOK_COMPILE
    hkVariant va = theNode->m_object;
    const char* className = "$No Class";
    if(va.m_class)
    {
        className = va.m_class->getName();
    }

    LOGD("node name=%s, object class=%s, properties=%s", theNode->m_name.cString(), className, theNode->m_userProperties.cString());
    LOGD("keyFrameSize=%d, childrenSize=%d, annotationSize=%d, linearKeyFrameSize=%d, selected=%s",
                        theNode->m_keyFrames.getSize(),
                        theNode->m_children.getSize(),
                        theNode->m_annotations.getSize(),
                        theNode->m_linearKeyFrameHints.getSize(),
                        theNode->m_selected ? "true" : "false");

    for (int i=0; i<theNode->m_annotations.getSize(); ++i)
    {
        const hkxNode::AnnotationData& annotation = theNode->m_annotations[i];
        LOGD("annotation[%d], time=%f, text=%s", i, annotation.m_time, annotation.m_description.cString());
    }

    for(int i=0; i<theNode->m_attributeGroups.getSize(); ++i)
    {
        const hkxAttributeGroup& attrGrp = theNode->m_attributeGroups[i];
        LOGD("attribute group name = %s, attributes = %d",
                            attrGrp.m_name.cString(),
                            attrGrp.m_attributes.getSize());
        for(int j=0; j<attrGrp.m_attributes.getSize(); ++j)
        {
            const hkxAttribute& attr = attrGrp.m_attributes[j];
            const hkClass* pClass = attr.m_value.getClass();
            LOGD("attribute = %s, class = %s",
                                attr.m_name.cString(),
                                pClass->getName());
        }
    }

    for(int i=0; i<theNode->m_children.getSize(); ++i)
    {
        dumpNodeRec(theNode->m_children[i]);
    }
#endif
}

void findNodesRec(  hkxNode* theNode,
                    const hkClass* theClass,
                    std::vector<hkxNode*>& outNodes)
{
#ifdef HAVOK_COMPILE
    hkVariant va = theNode->m_object;
    if (va.m_class == theClass) outNodes.push_back(theNode);
    for(int i=0; i<theNode->m_children.getSize(); ++i)
    {
        findNodesRec(theNode->m_children[i], theClass, outNodes);
    }
#endif
}

void findNodesRec(  hkxNode* theNode,
                    const std::string& preFix,
                    std::vector<hkxNode*>& outNodes)
{
#ifdef HAVOK_COMPILE
    if (theNode->m_name.startsWith(preFix.c_str()))
        outNodes.push_back(theNode);

    for(int i=0; i<theNode->m_children.getSize(); ++i)
    {
        findNodesRec(theNode->m_children[i], preFix, outNodes);
    }
#endif
}


void fill_object_attributes(jsonxx::Object& object, const hkxAttributeGroup* group)
{
#ifdef HAVOK_COMPILE
    if(!group) return;
    //TODO Animated Attributes
    for (int i=0; i<group->m_attributes.getSize(); ++i)
    {
        const hkxAttribute& attrib = group->m_attributes[i];
        std::string attrName(attrib.m_name.cString());
        hkVariant variant(attrib.m_value);
        if(variant.m_class == &hkxSparselyAnimatedStringClass)
        {
            hkxSparselyAnimatedString* hString = (hkxSparselyAnimatedString*)variant.m_object;
            object << attrName << std::string(hString->m_strings[0].cString());
        }
        else if(variant.m_class == &hkxAnimatedFloatClass)
        {
            hkxAnimatedFloat* hFloat = (hkxAnimatedFloat*)variant.m_object;
            object << attrName << hFloat->m_floats[0];
        }
        else if(variant.m_class == &hkxAnimatedVectorClass)
        {
            hkxAnimatedVector* hVector = (hkxAnimatedVector*)variant.m_object;
            jsonxx::Array vectorArray;
            for(int i=0; i<hVector->m_vectors.getSize(); ++i)
            {
                vectorArray << hVector->m_vectors[i];
            }
            object << attrName << vectorArray;
        }
        else if(variant.m_class == &hkxSparselyAnimatedBoolClass)
        {
            hkxSparselyAnimatedBool* hBool = (hkxSparselyAnimatedBool*)variant.m_object;
            object << attrName << (bool)hBool->m_bools[0];
        }
        else if(variant.m_class == &hkxSparselyAnimatedIntClass)
        {
            hkxSparselyAnimatedInt* hInt = (hkxSparselyAnimatedInt*)variant.m_object;
            object << attrName << (int)hInt->m_ints[0];
        }
        else if(variant.m_class == &hkxAnimatedQuaternionClass)
        {
            hkxAnimatedQuaternion* hQuat = (hkxAnimatedQuaternion*)variant.m_object;
            jsonxx::Array vectorArray;
            for(int i=0; i<hQuat->m_quaternions.getSize(); ++i)
            {
                vectorArray << hQuat->m_quaternions[i];
            }
            object << attrName << vectorArray;
        }
        else if(variant.m_class == &hkxAnimatedMatrixClass)
        {
            hkxAnimatedMatrix* hMatrix = (hkxAnimatedMatrix*)variant.m_object;
            jsonxx::Array vectorArray;
            for(int i=0; i<hMatrix->m_matrices.getSize(); ++i)
            {
                vectorArray << hMatrix->m_matrices[i];
            }
            object << attrName << vectorArray;
        }
    }
#endif
}


void lut2d_to_3d(const uint8_t* inData, uint8_t* outData)
{
    //PROFILE(lut2d_to_3d);
    for (int z = 0; z < COLOR_LUT_SIZE; ++z)
    {
        for (int y = 0; y < COLOR_LUT_SIZE; ++y)
        {
            const uint8_t* in = &inData[z * COLOR_LUT_SIZE * 4 + y * COLOR_LUT_SIZE * COLOR_LUT_SIZE * 4];
            uint8_t* out = &outData[z * COLOR_LUT_SIZE * COLOR_LUT_SIZE * 4 + y * COLOR_LUT_SIZE * 4];
            for (int x = 0; x < COLOR_LUT_SIZE * 4; x += 4)
            {
                out[x] = in[x+2];
                out[x+1] = in[x+1];
                out[x+2] = in[x];
                out[x+3] = in[x+3];
            }
        }
    }
}

std::string get_package_name( const std::string& input )
{
    std::string inputName = input;
    string_replace(inputName, INTERMEDIATE_PATH, "");
    size_t nPos = inputName.find_first_of("/");
    return inputName.substr(0, nPos);
}

std::string get_resource_name( const std::string& input )
{
    std::string inputName = input;
    string_replace(inputName, ROOT_DATA_PATH, "");
    removeExtension(inputName);
    return inputName;
}

void texconv_compress( const std::string& src, const std::string& folder, const std::string& fmt )
{
    //PROFILE(texconv_compress);
    std::string srcFile = src;
    string_replace(srcFile, "/", "\\");
    std::string dstDir = folder;
    string_replace(dstDir, "/", "\\");
    StringArray args;
    args.push_back(srcFile);
    args.push_back("-ft");
    args.push_back("DDS");
    args.push_back("-f");
    args.push_back(fmt);
    args.push_back("-o");
    args.push_back(dstDir);
    shell_exec(TEXCONV_PATH, args);
}

static uint32_t json_to_floats( const jsonxx::Array& array, float* p, uint32_t max_size )
{
    uint32_t copy_size = array.size() > max_size ? max_size : array.size();
    for (uint32_t i=0; i<copy_size; ++i)
    {
        jsonxx::Number n = array.get<jsonxx::Number>(i);
        p[i] = (float)n;
    }
    return copy_size;
}
uint32_t json_to_floats( const jsonxx::Object& o, const char* name, float* p, uint32_t max_size )
{
    if(!o.has<jsonxx::Array>(name))
        return 0;
    return json_to_floats(o.get<jsonxx::Array>(name), p, max_size);
}
static uint32_t json_to_flags( const jsonxx::Array& array, const char** enum_names )
{
    uint32_t flags = 0;
    uint32_t num = array.size();
    for (uint32_t i=0; i<num; ++i)
    {
        int index = find_enum_index(array.get<std::string>(i).c_str(), enum_names);
        flags |= (1 << index);
    }
    return flags;
}
uint32_t json_to_flags( const jsonxx::Object& o, const char* name, const char** enum_names )
{
    if(!o.has<jsonxx::Array>(name))
        return 0;
    return json_to_flags(o.get<jsonxx::Array>(name), enum_names);
}
float json_to_float( const jsonxx::Object& o, const char* name, float def )
{
    if(!o.has<jsonxx::Number>(name))
        return def;
    jsonxx::Number n = o.get<jsonxx::Number>(name);
    return static_cast<float>(n);
}

int json_to_int( const jsonxx::Object& o, const char* name, int def )
{
    if(!o.has<jsonxx::Number>(name))
        return def;
    jsonxx::Number n = o.get<jsonxx::Number>(name);
    return static_cast<int>(n);
}

StringId json_to_stringid( const jsonxx::Object& o, const char* name, StringId def )
{
    if(!o.has<std::string>(name))
        return def;
    return stringid_caculate(o.get<std::string>(name).c_str());
}

int json_to_enum( const jsonxx::Object& o, const char* name, const char** enumnames, int def )
{
    if(!o.has<std::string>(name))
        return def;
    const std::string& sname = o.get<std::string>(name);
    int index =  find_enum_index(sname.c_str(), enumnames);
    return index >= 0 ? index : def;
}


bool json_to_bool( const jsonxx::Object& o,const char* name, bool def/*=false*/ )
{
    if(!o.has<bool>(name))
        return def;
    return o.get<bool>(name);
}

Fact* json_to_fact(const jsonxx::Object& o, const char* name, func_fact_object_mem_t func)
{
    if(!o.has<jsonxx::Array>(name))
        return 0;

    const jsonxx::Array& array = o.get<jsonxx::Array>(name);
    uint32_t value_size = 0;
    const std::map<std::string, jsonxx::Value*>& kv = o.kv_map();
    std::map<std::string, jsonxx::Value*>::const_iterator it = kv.begin();
    for(; it != kv.end(); ++it)
    {
        jsonxx::Value* v = it->second;
        if(!v)
            continue;

        switch(v->type_)
        {
        case jsonxx::Value::NUMBER_:
            value_size += sizeof(int);
            break;
        case jsonxx::Value::STRING_:
            value_size += sizeof(StringId);
            break;
        case jsonxx::Value::BOOL_:
            value_size += sizeof(int);
            break;
        case jsonxx::Value::ARRAY_:
            // assume in this case all value is number
            value_size += (sizeof(int) * v->get<jsonxx::Array>().size());
            break;
        case jsonxx::Value::OBJECT_:
            if(func)
                value_size += func(v->get<jsonxx::Object>(), NULL);
            break;
        default:
            // TODO not supported types
            continue;
        }
    }

    uint32_t num_of_keys = array.size();
    uint32_t memory_size = sizeof(Fact) + num_of_keys * (sizeof(StringId) + sizeof(Key)) + value_size;
    char* p = (char*)malloc(memory_size);
    memset(p, 0x00, memory_size);

    Fact* f = (Fact*)p;
    f->m_num_keys = num_of_keys;
    f->m_value_size = value_size;
    f->m_name_offset = sizeof(Fact);
    f->m_key_offset = sizeof(Fact) + num_of_keys * (sizeof(StringId));
    f->m_value_offset = sizeof(Fact) + num_of_keys * (sizeof(StringId) + sizeof(Key));

    char* values = p + f->m_value_offset;
    StringId* names = (StringId*)(p + f->m_name_offset);
    Key* keys = (Key*)(p + f->m_key_offset);
    int index = 0;

    for(it = kv.begin(); it != kv.end(); ++it)
    {
        jsonxx::Value* v = it->second;
        const std::string& k = it->first;

        if(!v)
            continue;

        uint32_t size = 4;
        switch(v->type_)
        {
        case jsonxx::Value::NUMBER_:
            *((float*)values) = (float)v->get<jsonxx::Number>();
            break;
        case jsonxx::Value::STRING_:
            *((StringId*)values) = stringid_caculate(v->get<std::string>().c_str());
            break;
        case jsonxx::Value::BOOL_:
            *((int*)values) = v->get<bool>() == true;
            break;
        case jsonxx::Value::ARRAY_:
            {
                const jsonxx::Array& data_array = v->get<jsonxx::Array>();
                json_to_floats(data_array, (float*)values, data_array.size());
            }
            break;
        case jsonxx::Value::OBJECT_:
            size = func ? func(v->get<jsonxx::Object>(), values) : 0;
            break;
        default:
            // TODO not supported types
            continue;
        }

        names[index] = stringid_caculate(k.c_str());
        keys[index].m_size = size;
        keys[index].m_offset = values - p + f->m_value_offset;
        values += size;
        ++index;
    }

    return f;
}

//========================================================================
//  RESOURCE DB
//
#define RESOURCE_FILE_FMT "%u,%u\n"
void ResourceFileDataBase::load(const char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    if(!fp) {
        LOGW("%s can not open file %s", BX_FUNCTION, fileName);
        return;
    }
    TIMELOG("load data compiler data base.");
    uint32_t modifyTime = 0;
    uint32_t fileHash = 0;
    while(!feof(fp))
    {
        int argNum = fscanf(fp, RESOURCE_FILE_FMT, &modifyTime, &fileHash);
        if(argNum != 2) break;
        m_files[fileHash] = modifyTime;
        ENGINE_ASSERT(fileHash && modifyTime, "fileHash && modifyTime");
    }
    fclose(fp);
}

void ResourceFileDataBase::save(const char* fileName)
{
    FILE* fp = fopen(fileName, "w");
    if(!fp) {
        LOGE("%s can not open file %s", BX_FUNCTION, fileName);
        return;
    }
    TIMELOG("save data compiler data base.");
    ResourceFileMap::const_iterator iter = m_files.begin();
    for(; iter != m_files.end(); ++iter)
    {
        fprintf(fp, RESOURCE_FILE_FMT, iter->second, iter->first);
    }
    fclose(fp);
}

unsigned get_file_modified_time(const std::string& fileName)
{
    if (fileName.empty())
        return 0;

    if(!isFileExist(fileName))
    {
        LOGE("file not exist %s", fileName.c_str());
        return 0;
    }

#ifdef WIN32
    struct _stat st;
    if (!_stat(fileName.c_str(), &st))
        return (unsigned)st.st_mtime;
#else
    struct stat st;
    if (!stat(fileName.c_str(), &st))
        return (unsigned)st.st_mtime;
#endif
    else
        return 0;
}

std::string input_to_output( const std::string& inputName )
{
    std::string ret = inputName;
    string_replace(ret, INTERMEDIATE_PATH, ROOT_DATA_PATH);
    return ret;
}

bool ResourceFileDataBase::isFileChanged(const std::string& fileName, uint32_t& modifyTime) const
{
    //bx::LwMutexScope _l(&m_lock);
    modifyTime = get_file_modified_time(fileName);
    ENGINE_ASSERT(modifyTime, "modifyTime");
    uint32_t key = stringid_caculate(fileName.c_str());
    ResourceFileMap::const_iterator iter = m_files.find(key);
    if(iter == m_files.end())
        return true;
    else
        return (iter->second != modifyTime);
}

void ResourceFileDataBase::insertResourceFile( const std::string& fileName,  const uint32_t& modifyTime )
{
    //bx::LwMutexScope _l(&m_lock);
    uint32_t key = stringid_caculate(fileName.c_str());
    m_files[key] = modifyTime;
    ENGINE_ASSERT(key && modifyTime, "key && modifyTime");
}

//========================================================================

FileReader::FileReader( const std::string& fileName )
:m_buf(0)
,m_size(0)
{
    if(m_file.open(fileName.c_str()))
        return;
    m_size = (uint32_t)bx::getSize(&m_file);
    m_file.seek(0, bx::Whence::Begin);
    m_buf = COMMON_ALLOC(char, m_size);
    memset(m_buf, 0x00, m_size);
    m_file.read(m_buf, m_size);
}

FileReader::~FileReader()
{
    COMMON_DEALLOC(m_buf);
    if(m_size)
        m_file.close();
}

MemoryBuffer::MemoryBuffer( uint32_t size )
:m_size(size)
{
    m_buf = COMMON_ALLOC(char, size);
    memset(m_buf, 0x00, size);
}

MemoryBuffer::~MemoryBuffer()
{
    COMMON_DEALLOC(m_buf);
}

//=======================================================
//  ERROR processing code.
//
//=======================================================
ToolError::ToolError()
:m_num_error(0)
{

}

void ToolError::add_error( const char* fmt, ... )
{
    bx::LwMutexScope _l(m_lock);
    ++m_num_error;
    char buffer[1024];
    memset(buffer, 0x00, sizeof buffer);
    va_list args;
    va_start(args, fmt);
    bx::vsnprintf(buffer, sizeof buffer, fmt, args);
    va_end(args);
    LOGE(buffer);
    m_error_msgs.push_back(buffer);
}

void ToolError::show_error()
{
    if(!m_num_error) return;
    size_t show_num = m_num_error > 5 ? 5 : m_num_error;
    std::string str;
    for(size_t i=0; i<show_num; ++i)
    {
       str += m_error_msgs[i];
       str += "\n";
    }
    msg_box(str.c_str());
}
