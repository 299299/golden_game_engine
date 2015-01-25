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
    addBackSlash(ret);
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
bool createFolder(const std::string& inPath)
{
    if(isFileExist(inPath) || inPath.empty())
        return true;

    std::string pathName = inPath;
    string_replace(pathName, "/", "\\");
    if(pathName[pathName.length() - 1] == '/')
        pathName[pathName.length() - 1] = '/';

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

bool fileSystemCopy(const std::string& src, const std::string& destFolder)
{
    LOGD("file system copy from %s to %s", src.c_str(), destFolder.c_str());

#ifdef HAVOK_COMPILE
    SHFILEOPSTRUCT sfo;
    ZeroMemory(&sfo, sizeof(sfo));
    sfo.wFunc = FO_COPY;
    char szSrc[MAX_PATH];
    char szDest[MAX_PATH];
    ZeroMemory(szDest, sizeof(szDest));
    ZeroMemory(szSrc, sizeof(szSrc));
    strcpy_s(szDest, destFolder.c_str());
    strcpy_s(szSrc, src.c_str());
    int srcLen = strlen(szSrc);
    int dstLen = strlen(szDest);
    szSrc[srcLen] = '\0';
    szSrc[srcLen+1] = '\0';
    szDest[dstLen] = '\0';
    szDest[dstLen+1] = '\0';
    sfo.pFrom = szSrc;
    sfo.pTo = szDest;
    sfo.fFlags = FOF_SILENT | FOF_NOCONFIRMATION | FOF_NOCONFIRMMKDIR;
    int ret = SHFileOperationA(&sfo);
    if(sfo.fAnyOperationsAborted)
    {
        LOGE("file copy aborted!");
    }
    if (!ret)
        return true;
    else
    {
        LOGE("file system copy failed = %d, 0x%X!", ret, ret);
        return false;
    }
#else
    return false;
#endif
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
    addBackSlash(ret);
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

void findFiles(const std::string& folder, const std::string& ext, bool bRecursive, std::vector<std::string>& outFiles)
{
    std::string findPath = folder + "*." + ext;

#ifdef HAVOK_COMPILE
    WIN32_FIND_DATA wfd;
    HANDLE hFind = FindFirstFile(findPath.c_str(), &wfd);
    if (hFind == INVALID_HANDLE_VALUE)
        return;

    do
    {
        if (wfd.cFileName[0] == '.')
            continue;
        if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            std::string filePathName = folder + wfd.cFileName + "/";
            if(bRecursive) findFiles(filePathName, ext, bRecursive, outFiles);
        }
        else
        {
            std::string filePathName = folder + wfd.cFileName;
            outFiles.push_back(filePathName);
        }
    }
    while (FindNextFile(hFind, &wfd));
    FindClose(hFind);
#endif
}
void findFolders(const std::string& folder, bool bRecursive, std::vector<std::string>& outFolders)
{
    std::string findPath = folder + "*.*";

#ifdef HAVOK_COMPILE
    WIN32_FIND_DATA wfd;
    memset(&wfd, 0, sizeof(wfd));
    HANDLE hFind = FindFirstFile(findPath.c_str(), &wfd);
    if (hFind == INVALID_HANDLE_VALUE)
        return;

    do
    {
        if (wfd.cFileName[0] == '.')
            continue;
        if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            std::string filePathName = folder + wfd.cFileName + "/";
            if(bRecursive)
                findFolders(filePathName, bRecursive, outFolders);
            outFolders.push_back(folder + wfd.cFileName);
        }
    }
    while (FindNextFile(hFind, &wfd));
    FindClose(hFind);
#endif
}

bool write_file(const std::string& fileName, const void* buf, uint32_t bufSize)
{
    bx::CrtFileWriter writer;
    if(writer.open(fileName.c_str()))
        return false;
    int32_t ret = writer.write(buf, bufSize);
    writer.close();
    return ret != 0;
}

void addBackSlash( std::string& outStr )
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
    return ret.substr(npos, ret.length() - npos);
}

std::string get_top_folder(const std::string& dirName)
{
    std::string ret = dirName;
    if(ret[0] == '/')
        ret = ret.substr(0, ret.length() - 1);
    int npos = ret.find_first_of('/');
    return ret.substr(0, npos);
}

int shell_exec(const std::string& exe, const std::vector<std::string>& args, const std::string& workDir, bool bHide)
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
        for (unsigned i = 0; i < args.Size(); ++i)
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
    std::vector<std::string> args;
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

bool str_begin_with( const std::string& str1, const std::string& str2 )
{
#ifdef HAVOK_COMPILE
    return hkString::beginsWithCase(str1.c_str(), str2.c_str());
#else
    return false;
#endif
}
bool str_end_with(const std::string& str1, const std::string& str2)
{
#ifdef HAVOK_COMPILE
    return hkString::endsWithCase(str1.c_str(), str2.c_str());
#else
    return false;
#endif
}

void fixPathSlash( std::string& inout )
{
    string_replace(inout, "\\", "/");
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

static bool compare_filename_less(const std::string& fileName1, const std::string& fileName2)
{
    extern int get_resource_order(const StringId& type);
    std::string ext1 = getFileExt(fileName1);
    std::string ext2 = getFileExt(fileName2);
    StringId ext1Id(ext1.c_str());
    StringId ext2Id(ext2.c_str());
    int ext1index = get_resource_order(ext1Id);
    int ext2index = get_resource_order(ext2Id);
    return ext1index < ext2index;
}

void texconv_compress( const std::string& src, const std::string& folder, const std::string& fmt )
{
    //PROFILE(texconv_compress);
    std::string srcFile = src;
    string_replace(srcFile, "/", "\\");
    std::string dstDir = folder;
    string_replace(dstDir, "/", "\\");
    std::vector<std::string> args;
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
    return StringId(o.get<std::string>(name).c_str());
}

int json_to_enum( const jsonxx::Object& o, const char* name, const char** enumnames, int def )
{
    if(!o.has<std::string>(name))
        return def;
    const std::string& sname = o.get<std::string>(name);
    int index =  find_enum_index(sname.c_str(), enumnames);
    return index >= 0 ? index : def;
}

//========================================================================
//  RESOURCE DB
//
#define RESOURCE_FILE_FMT "%u,%u\n"
void ResourceFileDataBase::load(const char* fileName)
{
    FILE* fp = fopen(fileName, "r");
    if(!fp) {
        LOGW(__FUNCTION__ " can not open file %s", fileName);
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
        LOGE(__FUNCTION__ " can not open file %s", fileName);
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
    if (fileName.empty() || !isFileExist(fileName))
        return 0;

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
    uint32_t key = StringId(fileName.c_str()).value();
    ResourceFileMap::const_iterator iter = m_files.find(key);
    if(iter == m_files.end())
        return true;
    else
        return (iter->second != modifyTime);
}

void ResourceFileDataBase::insertResourceFile( const std::string& fileName,  const uint32_t& modifyTime )
{
    //bx::LwMutexScope _l(&m_lock);
    uint32_t key = StringId(fileName.c_str()).value();
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
    m_size = (uint32_t)m_file.seek(0, bx::Whence::End);
    m_file.seek(0, bx::Whence::Begin);
    m_buf = COMMON_ALLOC(char, m_size);
    m_file.read(m_buf, m_size);
}

FileReader::~FileReader()
{
    COMMON_DEALLOC(m_buf);
    m_file.close();
}

MemoryBuffer::MemoryBuffer( uint32_t size )
:m_size(size)
{
    m_buf = COMMON_ALLOC(char, size);
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
    if(m_error_msgs.size() >= 20) return;
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    bx::vsnprintf(buffer, sizeof(buffer), fmt, args);
    va_end(args);
    LOGE(buffer);
    m_error_msgs.push_back(buffer);
}

void ToolError::show_error()
{
    if(!m_num_error) return;
    std::string str;
    for(size_t i=0; i<m_error_msgs.size(); ++i)
    {
       str += m_error_msgs[i];
       str += "\n";
    }
    msg_box(str.c_str());
}
