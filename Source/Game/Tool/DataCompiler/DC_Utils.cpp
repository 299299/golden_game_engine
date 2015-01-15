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

