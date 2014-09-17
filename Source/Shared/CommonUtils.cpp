#include "CommonUtils.h"
#include <ShlObj.h>
#include <algorithm>
#include <io.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <direct.h>
#include "StringId.h"
#include "Log.h"
#include "Prerequisites.h"
#include "EngineAssert.h"
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>

static hkCriticalSection g_errorCS;
//static hkCriticalSection g_dbCS;

//=======================================================
//  ERROR processing code.
//
#define MAX_ERROR_TO_SHOW (20)
static char msgBuffer[2048];
static std::vector<std::string> g_errorMsg;
int g_errorNum = 0;
void showErrorMessage(const char* title)
{
    if(!g_errorNum)
       return;
    std::stringstream ss;
    ss << "error occurs times =  " << g_errorNum << "\n";
    for(size_t i=0; i<g_errorMsg.size(); ++i)
    {
        ss << g_errorMsg[i] << "\n";
    }
    msgBox(ss.str().c_str(), title);
}
void addError(const char* fmt, ...)
{
    hkCriticalSectionLock _l(&g_errorCS);
    ++g_errorNum;
    if(g_errorMsg.size() >= MAX_ERROR_TO_SHOW)
    {
        return;
    }
    va_list args;
    va_start(args, fmt);
    vsprintf_s(msgBuffer, fmt, args);
    va_end(args);
    LOGE(msgBuffer);
    g_errorMsg.push_back(msgBuffer);
}
//=======================================================

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
        addError("SHCreateDirectoryEx = %d", ret);
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
    //LOGD("file system copy from %s to %s", src.c_str(), destFolder.c_str()); 
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
        addError("file copy aborted!");
    }
    if (!ret) 
        return true;
    else
    {
        LOGE("file system copy failed = %d, 0x%X!", ret, ret);
        return false; 
    }
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
        addError("ERROR: CreateProcess failed!");
        return;
    }
    else
    {
        WaitForSingleObject( processInformation.hProcess, INFINITE );
        CloseHandle( processInformation.hProcess );
        CloseHandle( processInformation.hThread );
    }
}

void findFiles(const std::string& folder, const std::string& ext, bool bRecursive, std::vector<std::string>& outFiles)
{
    std::string findPath = folder + "*." + ext;

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
}
void findFolders(const std::string& folder, bool bRecursive, std::vector<std::string>& outFolders)
{
    std::string findPath = folder + "*.*";

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
}


uint32_t read_file(const std::string& fileName, char** outBuf)
{
    HANDLE hFile = CreateFile(fileName.c_str(),GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if(hFile == INVALID_HANDLE_VALUE)
    {
        DWORD code = GetLastError();
        addError(__FUNCTION__" can not open file = %s, code = %d.",fileName.c_str(), code);
        return 0;
    }
    LARGE_INTEGER nFileLen;
    GetFileSizeEx(hFile, &nFileLen);
    DWORD fileSize = (DWORD)nFileLen.QuadPart;
    char* p = (char*)malloc(fileSize);
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
}

bool write_file(const std::string& fileName, void* buf, uint32_t bufSize)
{
    HANDLE hFile = CreateFile(fileName.c_str(),GENERIC_WRITE,0,NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
    if(hFile == INVALID_HANDLE_VALUE)
    {
        DWORD code = GetLastError();
        addError(__FUNCTION__" can not open file = %s, code = %d.",fileName.c_str(), code);
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
}

void addBackSlash( std::string& outStr )
{
    if(outStr.back() != '/')
        outStr += "/";
}

uint64_t get_file_size(const std::string& fileName)
{
    WIN32_FIND_DATA wfd;
    memset(&wfd, 0, sizeof(wfd));
    HANDLE hFind = FindFirstFile(fileName.c_str(), &wfd);  
    if (hFind == INVALID_HANDLE_VALUE) return 0;
    return MAKE_U64(wfd.nFileSizeHigh, wfd.nFileSizeLow);
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
}

std::string name_to_file_path( const std::string& resourceName, const std::string& ext )
{
    return std::string(ROOT_DATA_PATH) + resourceName + "." + ext;
}

void delete_file(const std::string& fileName)
{
    if(!isFileExist(fileName))
        return;
    //LOGD("deleting file %s", fileName.c_str());
    int nRet = ::DeleteFile(fileName.c_str());
    if(nRet != 0) return;
    LOGE(__FUNCTION__" failed, GetLastError() = %d", GetLastError());
}

bool delete_folder(const std::string& folderName)
{
    std::string pathName = folderName;
    string_replace(pathName, "/", "\\");
    std::string cmd = "rmdir /s /q ";
    cmd += pathName;
    ::system(cmd.c_str());
    return true;
}

void compile_shader(const std::string& src, const std::string& dst, const std::string& def, bool vs)
{
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

void msgBox(const char* text, const char* title)
{
    ::MessageBoxA(NULL, text, title, MB_TOPMOST);
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
    return str1.compare(0, str2.length(), str2) == 0;
}

void fixPathSlash( std::string& inout )
{
    string_replace(inout, "\\", "/");
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