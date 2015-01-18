#include "ToolUtils.h"

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

std::string getCurDir()
{
    char szPath[256];
    GetCurrentDirectoryA(256,szPath);
    std::string ret(szPath);
    return ret;
}
bool isFileExist( const std::string& fileName )
{
    return _access(fileName.c_str(), 0) != -1;
}
bool isFolderExist(const std::string& folderName)
{
    WIN32_FIND_DATA  wfd;
    bool rValue = false;
    HANDLE hFind = FindFirstFileA(folderName.c_str(), &wfd);
    if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
    {
        rValue = true;
    }
    FindClose(hFind);
    return rValue;
}
void createFolder(const std::string& folderName)
{
    std::string workDir = getWorkingDir();
    std::string folder = workDir + folderName;
    string_replace(folder, "/", "\\");
    int ret = SHCreateDirectoryEx(0, folder.c_str(), 0);
    if(ret != ERROR_SUCCESS && ret != ERROR_ALREADY_EXISTS)
    {
        LOGE("SHCreateDirectoryEx = %d", ret);
    }
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
    char szBuffer[MAX_PATH];
    memset(szBuffer, 0x00, sizeof(szBuffer));
    GetCurrentDirectoryA(MAX_PATH, szBuffer);
    return std::string(szBuffer) + "\\";
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

    TCHAR tempCmdLine[MAX_PATH * 2];
    _tcscpy_s(tempCmdLine, MAX_PATH *2, args.c_str());

    TCHAR tempWorkDir[MAX_PATH * 2];
    _tcscpy_s(tempWorkDir, MAX_PATH *2, workingDir.c_str());

    TCHAR* workDir = 0;
    if(workingDir.length() > 0)
        workDir = tempWorkDir;

    BOOL result = ::CreateProcess(process.c_str(), tempCmdLine, NULL, NULL, FALSE,
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


uint32_t read_file(const std::string& fileName, char** outBuf)
{
    //PROFILE(read_file);

#ifdef HAVOK_COMPILE
    HANDLE hFile = CreateFile(fileName.c_str(),GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if(hFile == INVALID_HANDLE_VALUE)
    {
        DWORD code = GetLastError();
        LOGE(__FUNCTION__" can not open file = %s, code = %d.",fileName.c_str(), code);
        return 0;
    }
    LARGE_INTEGER nFileLen;
    GetFileSizeEx(hFile, &nFileLen);
    DWORD fileSize = (DWORD)nFileLen.QuadPart;
    char* p = (char*)_aligned_malloc(fileSize + 1, 16);
    memset(p, 0x00, fileSize + 1);
    DWORD readLen = 0;
    ReadFile(hFile, p, fileSize, &readLen, 0);
    if(readLen != fileSize)
    {
        DWORD code = GetLastError();
        LOGE("read error = %d.", code);
    }
    CloseHandle(hFile);
    *outBuf = p;
    return fileSize;
#else
    return false;
#endif
}

bool write_file(const std::string& fileName, const void* buf, uint32_t bufSize)
{
    //PROFILE(write_file);
#ifdef HAVOK_COMPILE
    HANDLE hFile = CreateFile(fileName.c_str(),GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    if(hFile == INVALID_HANDLE_VALUE)
    {
        DWORD code = GetLastError();
        LOGE(__FUNCTION__" can not open file = %s, code = %d.",fileName.c_str(), code);
        return false;
    }
    DWORD nBufWritten = 0;
    WriteFile(hFile, buf, bufSize, &nBufWritten, 0);
    if(nBufWritten != bufSize)
    {
        DWORD code = GetLastError();
        LOGE("write error = %d.", code);
    }
    CloseHandle(hFile);
    return true;
#else
    return false;
#endif
}

void delete_file_buffer( char* ptr )
{
    _aligned_free(ptr);
}

void addBackSlash( std::string& outStr )
{
    if(outStr.back() != '/')
        outStr += "/";
}

uint64_t get_file_size(const std::string& fileName)
{
#ifdef HAVOK_COMPILE
    WIN32_FIND_DATA wfd;
    memset(&wfd, 0, sizeof(wfd));
    HANDLE hFind = FindFirstFile(fileName.c_str(), &wfd);
    if (hFind == INVALID_HANDLE_VALUE) return 0;
    return MAKE_U64(wfd.nFileSizeHigh, wfd.nFileSizeLow);
#else
    return 0;
#endif
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

std::string relative_to_full_path( const std::string input )
{
    std::string ret = getWorkingDir();
    ret += input;
    string_replace(ret, "/", "\\");
    return ret;
}


void shell_exec(const std::string& exe, const std::string& args, const std::string& workDir, bool bHide)
{
#ifdef HAVOK_COMPILE
    SHELLEXECUTEINFO ShExecInfo = {0};
    ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFO);
    ShExecInfo.fMask = SEE_MASK_NOCLOSEPROCESS;
    ShExecInfo.hwnd = NULL;
    ShExecInfo.lpVerb = NULL;
    ShExecInfo.lpFile = exe.c_str();
    ShExecInfo.lpParameters = args.c_str();
    ShExecInfo.lpDirectory = workDir.length() ? workDir.c_str() : 0;
    ShExecInfo.nShow = bHide ? SW_HIDE : SW_SHOW;
    ShExecInfo.hInstApp = NULL;
    BOOL bRet = ShellExecuteEx(&ShExecInfo);
    if(!bRet)
    {
        LOGE("ShellExecuteEx error ");
        return;
    }
    WaitForSingleObject(ShExecInfo.hProcess,INFINITE);
#endif
}

std::string name_to_file_path( const std::string& resourceName, const std::string& ext )
{
    return std::string(ROOT_DATA_PATH) + resourceName + "." + ext;
}

void delete_file(const std::string& fileName)
{
#ifdef HAVOK_COMPILE
    if(!isFileExist(fileName)) return;
    int nRet = ::DeleteFile(fileName.c_str());
    if(nRet != 0) return;
    LOGE(__FUNCTION__" failed, GetLastError() = %d", GetLastError());
#endif
}

bool delete_folder(const std::string& folderName)
{
#ifdef HAVOK_COMPILE
    std::string pathName = folderName;
    string_replace(pathName, "/", "\\");
    std::string cmd = "rmdir /s /q ";
    cmd += pathName;
    ::system(cmd.c_str());
#endif
    return true;
}

void compile_shader(const std::string& src, const std::string& dst, const std::string& def, bool vs)
{
    //PROFILE(compile_shader);
    char buf[256];
    const char* type = vs ? "v" : "f";
    const char* target = vs ? "vs_5_0" : "ps_5_0";
    sprintf_s(buf, "-f %s -o %s --type %s --platform windows --verbose -p %s --varyingdef %s",
              src.c_str(), dst.c_str(), type, target, def.c_str());
    std::string folder = getFilePath(src);
    shell_exec(SHADERC_PATH, buf, "");
    //runProcess(SHADERC_PATH, "", buf);
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

std::string get_last_string( const std::string& input, char c, int count )
{
    int cCount = 0;
    int index = -1;
    for (int i=input.length()-1; i>=0; --i)
    {
        if(input[i] == c)
        {
            cCount++;
        }
        if(cCount == count)
        {
            index = i + 1;
            break;
        }
    }
    if(index < 0) return input;
    return input.substr(index, input.length() - index);
}

bool str_begin_with( const std::string& str1, const std::string& str2 )
{
    return hkString::beginsWithCase(str1.c_str(), str2.c_str());
}
bool str_end_with(const std::string& str1, const std::string& str2)
{
    return hkString::endsWithCase(str1.c_str(), str2.c_str());
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

void nvtt_compress(const std::string& src, const std::string& dst, const std::string& fmt)
{
    //PROFILE(nvtt_compress);
    std::string args = "-" + fmt + " ";
    if(fmt == DDS_NM_FORMAT) args += "-normal ";
    args += src;
    args += " ";
    args += dst;
    shell_exec(NVTT_PATH, args);
}

void texconv_compress( const std::string& src, const std::string& folder, const std::string& fmt )
{
    //PROFILE(texconv_compress);
    std::string srcFile = src;
    string_replace(srcFile, "/", "\\");
    std::string dstDir = folder;
    string_replace(dstDir, "/", "\\");
    std::string args = srcFile + " -ft DDS " + " -f " + fmt + " -o " + dstDir;
    shell_exec(TEXCONV_PATH, args);
}

uint32_t json_to_floats( const jsonxx::Array& array, float* p, uint32_t max_size )
{
    uint32_t copy_size = array.size() > max_size ? max_size : array.size();
    for (uint32_t i=0; i<copy_size; ++i)
    {
        p[i] = array.get<float>(i);
    }
    return copy_size;
}

uint32_t json_to_flags( const jsonxx::Array& array, const char** enum_names )
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

//========================================================================
//  RESOURCE DB
//
#define RESOURCE_FILE_FMT "%llu,%u\n"
void ResourceFileDataBase::load(const char* fileName)
{
    //hkCriticalSectionLock _l(&g_dbCS);
    FILE* fp = fopen(fileName, "r");
    if(!fp) {
        LOGW(__FUNCTION__ " can not open file %s", fileName);
        return;
    }
    TIMELOG("load data compiler data base.");
    uint64_t modifyTime = 0;
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
    //hkCriticalSectionLock _l(&g_dbCS);
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

bool ResourceFileDataBase::isFileChanged(const std::string& fileName, uint64_t& modifyTime) const
{
    //hkCriticalSectionLock _l(&g_dbCS);
    WIN32_FIND_DATA wfd;
    memset(&wfd, 0, sizeof(wfd));
    HANDLE hFind = FindFirstFile(fileName.c_str(), &wfd);
    if (hFind == INVALID_HANDLE_VALUE) return true;
    FILETIME ftWriteTime = wfd.ftLastWriteTime;
    modifyTime = MAKE_U64(ftWriteTime.dwHighDateTime, ftWriteTime.dwLowDateTime);
    ENGINE_ASSERT(modifyTime, "modifyTime");
    uint32_t key = StringId(fileName.c_str()).value();
    ResourceFileMap::const_iterator iter = m_files.find(key);
    if(iter == m_files.end()) return true;
    else return (iter->second != modifyTime);
}

void ResourceFileDataBase::insertResourceFile( const std::string& fileName,  const uint64_t& modifyTime )
{
    //hkCriticalSectionLock _l(&g_dbCS);
    uint32_t key = StringId(fileName.c_str()).value();
    m_files[key] = modifyTime;
    ENGINE_ASSERT(key && modifyTime, "key && modifyTime");
}

//========================================================================

FileReader::FileReader( const std::string& fileName )
:m_buf(0)
,m_size(0)
{
    m_size = read_file(fileName, &m_buf);
}

FileReader::~FileReader()
{
    delete_file_buffer(m_buf);
}

MemoryBuffer::MemoryBuffer( uint32_t size )
:m_size(size)
{
    m_buf = (char*)_aligned_malloc(size, 16);
    memset(m_buf, 0x00, size);
}

MemoryBuffer::~MemoryBuffer()
{
    _aligned_free(m_buf);
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
    vsprintf_s(buffer, fmt, args);
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
