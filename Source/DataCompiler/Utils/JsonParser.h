#pragma once
#include <cstring>
#include <cstdlib>
#include <string>
#include "jsmn.h"
#include "StringId.h"
#include "MathDefs.h"

class JsonParser;
class JsonValue
{
public:
    jsmntype_t          GetType() const;

    JsonValue           GetValue() const;
    JsonValue           GetValue(const char* key) const;

    bool                IsValid() const;
    bool                IsKey() const;

    unsigned            AsString(char* destBuff, unsigned maxLen) const;
    double              AsNumber() const;
    float               AsFloat() const { return (float)AsNumber();};
    bool                AsBool() const;
    bool                IsNull() const;

    unsigned            GetElementsCount() const;
    JsonValue           operator[](unsigned index) const;

    JsonValue           Next() const;
    const JsonValue&    operator++();

private:
    friend class        JsonParser;

    const JsonParser*   m_pParser;
    jsmn_uint_t         m_internalTokenIndex;
#ifndef JSMN_HUGE_FILES
    char                m_padding[2];
#endif

    static JsonValue    JSON_INVALID_VALUE;

    JsonValue(jsmn_uint_t index, const JsonParser* pParser);
};


class JsonParser
{
public:
    JsonParser();
    static jsmnerr_t    CalcSpaceRequired(const char* pJsonString, unsigned strSize, size_t& result);
    jsmnerr_t           ParseJsonString(const char* pJsonString, unsigned strSize, void* pMem, size_t memSize);

    const JsonValue&    GetRoot() const { return m_root; };

private:
    friend class        JsonValue;

    size_t              m_tokensCount;
    jsmntok*            m_pTokens;
    JsonValue           m_root;
    const char*         m_pJsonString;

    const jsmntok*      InternalGetToken(unsigned tokenIndex) const;
};



//-------------------------------------------------------------------------------------------
inline JsonParser::JsonParser()
    : m_tokensCount(0), m_pTokens(0), m_root(JsonValue::JSON_INVALID_VALUE), m_pJsonString(0)
{
}

//-------------------------------------------------------------------------------------------
inline const jsmntok* JsonParser::InternalGetToken(unsigned tokenIndex) const
{
    HK_ASSERT(0, tokenIndex < m_tokensCount);
    return &m_pTokens[tokenIndex];
}

//-------------------------------------------------------------------------------------------
inline JsonValue::JsonValue(jsmn_uint_t index, const JsonParser* pParser)
    : m_internalTokenIndex(index), m_pParser(pParser)
{
}

//-------------------------------------------------------------------------------------------
inline jsmntype_t JsonValue::GetType() const
{
    HK_ASSERT(0, m_internalTokenIndex != JSMN_INVALID_VALUE);
    HK_ASSERT(0, m_pParser);
    return (jsmntype_t)m_pParser->InternalGetToken(m_internalTokenIndex)->type;
}

//-------------------------------------------------------------------------------------------
inline JsonValue JsonValue::GetValue() const
{
    HK_ASSERT(0, m_internalTokenIndex != JSMN_INVALID_VALUE);
    HK_ASSERT(0, m_pParser);
    HK_ASSERT(0, m_pParser->InternalGetToken(m_internalTokenIndex)->is_key);
    return JsonValue(m_internalTokenIndex + 1, m_pParser);
}

//-------------------------------------------------------------------------------------------
inline JsonValue JsonValue::GetValue(const char* key) const
{
    HK_ASSERT(0, m_internalTokenIndex != JSMN_INVALID_VALUE);
    HK_ASSERT(0, m_pParser);
    HK_ASSERT(0, m_pParser->InternalGetToken(m_internalTokenIndex)->type == JSMN_OBJECT);

    const size_t kStrLen = strlen(key);
    jsmn_uint_t tokenIndex = m_internalTokenIndex + 1;
    while (tokenIndex != JSMN_INVALID_VALUE)
    {
        const jsmntok_t* kToken = m_pParser->InternalGetToken(tokenIndex);
        if ((jsmn_uint_t)kStrLen == kToken->end - kToken->start)
        {
            const char* jsonKey = &m_pParser->m_pJsonString[kToken->start];
            if(strncmp(key, jsonKey, kStrLen) == 0)
            {
                return JsonValue(tokenIndex + 1, m_pParser);
            }
        }
        tokenIndex = m_pParser->InternalGetToken(tokenIndex)->next;
    }

    return JSON_INVALID_VALUE;
}

//-------------------------------------------------------------------------------------------
inline bool JsonValue::IsValid() const
{
    return (m_internalTokenIndex != JSMN_INVALID_VALUE) && (m_pParser != 0);
}

//-------------------------------------------------------------------------------------------
inline bool JsonValue::IsKey() const
{
    HK_ASSERT(0, m_internalTokenIndex != JSMN_INVALID_VALUE);
    HK_ASSERT(0, m_pParser);
    return m_pParser->InternalGetToken(m_internalTokenIndex)->is_key == 1;
}

//-------------------------------------------------------------------------------------------
inline unsigned JsonValue::AsString(char* destBuff, unsigned maxLen) const
{
    HK_ASSERT(0, m_internalTokenIndex != JSMN_INVALID_VALUE);
    HK_ASSERT(0, m_pParser);

    const jsmntok_t* kToken = m_pParser->InternalGetToken(m_internalTokenIndex);
    unsigned kSize = kToken->end - kToken->start;
    HK_ASSERT(0, kSize < maxLen);

    memcpy(destBuff, &m_pParser->m_pJsonString[kToken->start], kSize);
    destBuff[kSize] = '\0';

    return kSize;
}

//-------------------------------------------------------------------------------------------
inline double JsonValue::AsNumber() const
{
    if(!IsValid())
        return 0.0;

    HK_ASSERT(0, m_internalTokenIndex != JSMN_INVALID_VALUE);
    HK_ASSERT(0, m_pParser);

    const jsmntok_t* kToken = m_pParser->InternalGetToken(m_internalTokenIndex);
    HK_ASSERT(0, kToken->type == JSMN_PRIMITIVE);

    return fast_atof(&m_pParser->m_pJsonString[kToken->start]);
}

//-------------------------------------------------------------------------------------------
inline bool JsonValue::AsBool() const
{
    HK_ASSERT(0, m_internalTokenIndex != JSMN_INVALID_VALUE);
    HK_ASSERT(0, m_pParser);

    const jsmntok_t* kToken = m_pParser->InternalGetToken(m_internalTokenIndex);

    HK_ASSERT(0, kToken->type == JSMN_PRIMITIVE);
    HK_ASSERT(0, m_pParser->m_pJsonString[kToken->start] == 't' || 
                 m_pParser->m_pJsonString[kToken->start] == 'f');

    return m_pParser->m_pJsonString[kToken->start] == 't';
}

//-------------------------------------------------------------------------------------------
inline JsonValue JsonValue::Next() const
{
    HK_ASSERT(0, m_internalTokenIndex != JSMN_INVALID_VALUE);
    HK_ASSERT(0, m_pParser);

    return JsonValue(m_pParser->InternalGetToken(m_internalTokenIndex)->next, m_pParser);
}

//-------------------------------------------------------------------------------------------
inline const JsonValue& JsonValue::operator++()
{
    HK_ASSERT(0, m_internalTokenIndex != JSMN_INVALID_VALUE);
    HK_ASSERT(0, m_pParser);

    m_internalTokenIndex = m_pParser->InternalGetToken(m_internalTokenIndex)->next;
    return *this;
}

//================================================================================================
// Sealize And DeSealize
//================================================================================================
float JSON_GetFloat(const JsonValue& jsValue, float defaultValue = 0.0f);
bool  JSON_GetBool(const JsonValue& jsValue, bool defaultValue = false);
uint32_t JSON_GetString(const JsonValue& jsValue, 
                        char* outString,
                        uint32_t maxLen,
                        const char* defaultValue = "");
int JSON_GetEnum(const JsonValue& jsValue, const char** enum_names, int defaultValue = 0);
int JSON_GetInt(const JsonValue& jsValue, int defaultValue = 0);
int JSON_GetFloats(const JsonValue& jsValue, float* outData, unsigned maxNum);
StringId JSON_GetStringId(const JsonValue& jsValue, const StringId& defaultValue = StringId::ZERO);
int JSON_GetFlags(const JsonValue& jsValue, 
                  const char** enum_names, 
                  int* flags, 
                  int defaultValue = 0);
int JSON_GetFlags(const JsonValue& jsValue, 
                  const char** enum_names, 
                  int defaultValue = 0);
int JSON_GetVariant(const JsonValue& jsValue, Variant& outValue);
std::string JSON_GetString(const JsonValue& jsValue, const std::string& defaultValue="");

