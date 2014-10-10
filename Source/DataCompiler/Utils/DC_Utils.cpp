#include "DC_Utils.h"
#include <ShlObj.h>
#include "Profiler.h"
#include "Prerequisites.h"
#include "LevelCompiler.h"
#include <Common/Base/Thread/CriticalSection/hkCriticalSection.h>
#include <Common/Base/Container/Array/hkArray.h>
#include <Common/Base/Algorithm/Sort/hkSort.h>

static hkCriticalSection g_jsonCS;
static hkCriticalSection g_childCS;
extern DC_Config    g_config;

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

struct JsonMemBuffer
{
    DWORD       m_threadId;
    char*       m_ioBuffer;
    char*       m_parseBuffer;
    uint32_t    m_ioSize;
    uint32_t    m_parseSize;
    void alloc_io_buffer(uint32_t size)
    {
        if(m_ioSize >= size) return;
        delete []m_ioBuffer;
        m_ioBuffer = new char[size];
        m_ioSize = size;
    }
    void alloc_parse_buffer(uint32_t size)
    {
        if(m_parseSize >= size) return;
        delete []m_parseBuffer;
        m_parseBuffer = new char[size];
        memset(m_parseBuffer, 0x00, size);
        m_parseSize = size;
    }
    JsonMemBuffer::JsonMemBuffer()
    {
        m_ioBuffer = m_parseBuffer = 0;
        m_ioSize = m_parseSize = 0;
    }
    JsonMemBuffer::~JsonMemBuffer()
    {
        delete []m_ioBuffer;m_ioBuffer = 0;
        delete []m_parseBuffer;m_parseBuffer = 0;
    }
};

struct JsonMemMgr
{
    std::vector<JsonMemBuffer*> m_buffers;
    ~JsonMemMgr()
    {
        for (size_t i=0; i<m_buffers.size(); ++i)
        {
            delete m_buffers[i];
        }
    }
    JsonMemBuffer* allocBuffer(uint32_t size)
    {
        DWORD threadId = ::GetCurrentThreadId();

        hkCriticalSectionLock _l(&g_jsonCS);
        for (size_t i=0; i<m_buffers.size(); ++i)
        {
            JsonMemBuffer* buffer = m_buffers[i];
            if(buffer->m_threadId == threadId)
            {
                return buffer;
            }
        }

        JsonMemBuffer* buffer = new JsonMemBuffer;
        buffer->m_threadId = threadId;
        m_buffers.push_back(buffer);
        return buffer;
    }
};

static JsonMemMgr g_jsonMgr;
bool parse_json(const std::string& fileName, JsonParser& parser)
{
    //PROFILE(parse_json);
    HANDLE hFile = CreateFile(fileName.c_str(),GENERIC_READ,0,NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);
    if(hFile == INVALID_HANDLE_VALUE)
    {
        DWORD code = GetLastError();
        addError(__FUNCTION__" can not open file = %s, code = %d.",fileName.c_str(), code);
        return 0;
    }
    LARGE_INTEGER nFileLen;
    DWORD readLen = 0;
    BOOL bOK = GetFileSizeEx(hFile, &nFileLen);
    DWORD fileSize = (DWORD)nFileLen.QuadPart;

    if(bOK == FALSE) {
        DWORD code = GetLastError();
        addError(__FUNCTION__" read file error = %s, code = %d.",fileName.c_str(), code);
        return 0;
    }

    JsonMemBuffer* buffer = g_jsonMgr.allocBuffer(fileSize);
    buffer->alloc_io_buffer(fileSize);
    ReadFile(hFile, buffer->m_ioBuffer, fileSize, &readLen, 0);
    if(readLen != fileSize)
    {
        DWORD code = GetLastError();
        LOGE("read error = %d.", code);
        CloseHandle(hFile);
        return 0;
    }
    
    size_t jsonBufferSize = 0;
    jsmnerr_t result = JsonParser::CalcSpaceRequired(buffer->m_ioBuffer, fileSize, jsonBufferSize);
    if (result != JSMN_SUCCESS)
    {
        addError(__FUNCTION__"JsonParser::CalcSpaceRequired failed.");
        CloseHandle(hFile);
        return false;
    }

    buffer->alloc_parse_buffer(jsonBufferSize);
    result = parser.ParseJsonString(buffer->m_ioBuffer, fileSize, buffer->m_parseBuffer, jsonBufferSize);
    if(result != JSMN_SUCCESS && result != JSMN_ERROR_PART)
    {
        addError(__FUNCTION__"JsonParser::ParseJsonString failed.");
        CloseHandle(hFile);
        return false;
    }
    CloseHandle(hFile);
    return true;
}

std::string input_to_output(const std::string& inputName)
{
    std::string output = inputName;
    string_replace(output, g_config.m_topFolder, ROOT_DATA);
    return output;
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

void addChildCompiler( BaseCompiler* compiler )
{
    extern std::vector<class BaseCompiler*> g_childCompilers;
    hkCriticalSectionLock _l(&g_childCS);
    g_childCompilers.push_back(compiler);
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

void saveCompileResult(const std::string& fileName)
{
    extern std::vector<class BaseCompiler*>        g_compilers;
    extern std::vector<class LevelCompiler*>       g_levels;
    extern std::vector<class BaseCompiler*>        g_childCompilers;

    std::vector<std::string> resultfiles;
    for(size_t i=0; i<g_compilers.size(); ++i)
    {
        BaseCompiler* compiler = g_compilers[i];
        const std::string& output = compiler->m_output;
        if(output.length() == 0 || compiler->m_skipped || !compiler->addToResult()) continue;
        resultfiles.push_back(output);
    }
    for(size_t i=0; i<g_childCompilers.size(); ++i)
    {
        BaseCompiler* compiler = g_childCompilers[i];
        const std::string& output = compiler->m_output;
        if(output.length() == 0 || compiler->m_skipped || !compiler->addToResult()) continue;
        resultfiles.push_back(output);
    }
    for(size_t i=0; i<g_levels.size(); ++i)
    {
        const std::string& output = g_levels[i]->m_output;
        if(output.length() == 0 || g_levels[i]->m_skipped) continue;
        resultfiles.push_back(output);
    }
    if(resultfiles.empty()) return;

    FILE* fp = fopen(fileName.c_str(), "w");
    if(!fp)
    {
        LOGE(__FUNCTION__" open file [%s] error.", fileName.c_str());
        return;
    }
    hkSort(&resultfiles[0], resultfiles.size(), compare_filename_less);
    for(size_t i=0; i<resultfiles.size(); ++i)
    {
        const std::string& fileName = resultfiles[i];
        //std::string output = remove_top_folder(fileName);
        fprintf(fp, "%s\n", fileName.c_str());
    }
    fclose(fp);
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
