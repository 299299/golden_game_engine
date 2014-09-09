#include "JsonParser.h"
#include "Log.h"
#include "MathDefs.h"
#include "Utils.h"

JsonValue JsonValue::JSON_INVALID_VALUE(JSMN_INVALID_VALUE, 0);

jsmnerr_t JsonParser::CalcSpaceRequired(const char* pJsonString, unsigned strSize, size_t& result)
{
    jsmn_parser parser;
    jsmn_init(&parser);
    jsmnerr_t error = jsmn_pre_parse(&parser, pJsonString, strSize, &result);
    result *= sizeof(jsmntok_t);
    return error;
}


//-------------------------------------------------------------------------------------------
jsmnerr_t JsonParser::ParseJsonString(const char* pJsonString, unsigned strSize, void* pMem, size_t memSize)
{
    m_pTokens = (jsmntok_t*)pMem;
    m_tokensCount = memSize / sizeof(jsmntok_t);
    m_pJsonString = pJsonString;
    m_root = JsonValue(0, this);
    jsmn_parser parser;
    jsmn_init(&parser);
    return jsmn_parse(&parser, pJsonString, strSize, m_pTokens, (unsigned)m_tokensCount);
}


//-------------------------------------------------------------------------------------------
bool JsonValue::IsNull() const
{
    HK_ASSERT(0, m_internalTokenIndex != JSMN_INVALID_VALUE);
    HK_ASSERT(0, m_pParser);
    const jsmntok_t* kToken = m_pParser->InternalGetToken(m_internalTokenIndex);

    if (kToken->type == JSMN_PRIMITIVE)
    {
        return m_pParser->m_pJsonString[kToken->start] == 'n';
    }
    return false;
}

//-------------------------------------------------------------------------------------------
unsigned JsonValue::GetElementsCount() const
{
    HK_ASSERT(0, m_internalTokenIndex != JSMN_INVALID_VALUE);
    HK_ASSERT(0, m_pParser);

    const jsmntok_t* kToken = m_pParser->InternalGetToken(m_internalTokenIndex);
    HK_ASSERT(0, kToken->type == JSMN_OBJECT || kToken->type == JSMN_ARRAY);

    if (kToken->type == JSMN_OBJECT)
    {
        // both keys and values are counted as an elements of Object token
        return kToken->size / 2;    
    }
    return kToken->size;
}

//-------------------------------------------------------------------------------------------
JsonValue JsonValue::operator[](unsigned index) const
{
    HK_ASSERT(0, index < GetElementsCount());
    HK_ASSERT(0, m_internalTokenIndex != JSMN_INVALID_VALUE);
    HK_ASSERT(0, m_pParser);
    HK_ASSERT(0, m_pParser->InternalGetToken(m_internalTokenIndex)->type == JSMN_OBJECT || 
                 m_pParser->InternalGetToken(m_internalTokenIndex)->type == JSMN_ARRAY);

    jsmn_uint_t nextIndex = m_internalTokenIndex + 1;

    for (unsigned i = 0; i < index; ++i)
    {
        const jsmntok_t* kToken = m_pParser->InternalGetToken(nextIndex);
        nextIndex = kToken->next;
    }

    return JsonValue(nextIndex, m_pParser);
}





//===========================================================================
//
//          JSON SERIALIZE
//
//===========================================================================
#define CHECK_VALID() \
        if(!jsValue.IsValid())\
            return defaultValue;
float JSON_GetFloat(const JsonValue& jsValue, float defaultValue)
{
    CHECK_VALID();
    return jsValue.AsFloat();
}
bool JSON_GetBool(const JsonValue& jsValue, bool defaultValue)
{
    CHECK_VALID();
    return jsValue.AsBool();
}
uint32_t JSON_GetString(const JsonValue& jsValue, 
                        char* outString,
                        uint32_t maxLen,
                        const char* defaultValue)
{
    if(!jsValue.IsValid())
    {
        uint32_t strLen = strlen(defaultValue);
        HK_ASSERT(0, maxLen >= strLen);
        strcpy_s(outString, maxLen, defaultValue);
        return strLen;
    }
    else
    {
        return jsValue.AsString(outString, maxLen);
    }
}
std::string JSON_GetString(const JsonValue& jsValue, const std::string& defaultValue)
{
    CHECK_VALID();
    char outBuf[256];
    jsValue.AsString(outBuf, sizeof(outBuf));
    return outBuf;
}
int JSON_GetEnum(const JsonValue& jsValue, const char** enum_names, int defaultValue)
{
    char buffer[64];
    JSON_GetString(jsValue, buffer, sizeof(buffer));
    int iRet = findEnumIndex(buffer, enum_names);
    return (iRet >= 0) ? iRet : defaultValue;
}
int JSON_GetInt(const JsonValue& jsValue, int defaultValue)
{
    CHECK_VALID();
    return (int)jsValue.AsNumber();
}
int JSON_GetFloats(const JsonValue& jsValue, float* outData, unsigned maxNum)
{
    if(!jsValue.IsValid())
        return 0;
    unsigned jsonElemCount = jsValue.GetElementsCount();
    unsigned maxSize = jsonElemCount > maxNum ? maxNum : jsonElemCount;
    for(unsigned i=0; i<jsonElemCount; ++i)
    {
        outData[i] = jsValue[i].AsFloat();
    }
    return maxSize;
}

StringId JSON_GetStringId(const JsonValue& jsValue, const StringId& defaultValue)
{
    CHECK_VALID();
    char buffer[64];
    JSON_GetString(jsValue, buffer, sizeof(buffer));
    return StringId(buffer);
}

int JSON_GetFlags(const JsonValue& jsValue, const char** enum_names, int defaultValue)
{
    CHECK_VALID();
    int retValue = 0;
    char name[64];
    for(unsigned i = 0; i<jsValue.GetElementsCount(); ++i)
    {
        JSON_GetString(jsValue[i], name, sizeof(name));
        int index = findEnumIndex(name, enum_names);
        if(index < 0)
            continue;
        retValue |= ( 1 << index);
    }
    return retValue;
}

int JSON_GetFlags(const JsonValue& jsValue, const char** enum_names, int* flags, int defaultValue)
{
    CHECK_VALID();
    int retValue = 0;
    char name[64];
    for(unsigned i = 0; i<jsValue.GetElementsCount(); ++i)
    {
        JSON_GetString(jsValue[i], name, sizeof(name));
        int index = findEnumIndex(name, enum_names);
        if(index < 0)
            continue;
        retValue |= flags[index];
    }
    return retValue;
}

static const char* g_variantTypeNames[] = 
{
    "int", "float", "bool", "stringid", 0
};

int JSON_GetVariant(const JsonValue& jsValue, Variant& outValue)
{
    if(!jsValue.IsValid()) return -1;
    int type = JSON_GetEnum(jsValue.GetValue("type"), g_variantTypeNames, -1);
    if(type < 0) return -1;
    JsonValue value = jsValue.GetValue("value");
    switch(type)
    {
    case Variant::TYPE_INTEGER:
        outValue.m_int = JSON_GetInt(value);
        break;
    case Variant::TYPE_STRING_ID:
        outValue.m_uint = JSON_GetStringId(value).value();
        break;
    case Variant::TYPE_FLOAT:
        outValue.m_float = JSON_GetFloat(value);
        break;
    case Variant::TYPE_BOOL:
        outValue.m_bool = JSON_GetBool(value);
        break;
    default:
        break;
    }
    return type;
}
