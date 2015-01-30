#pragma once
#include "BaseTypes.h"

typedef StringId32 StringId;
StringId stringid_caculate(const char* _str);
StringId stringid_caculate(const char* _str, uint32_t _len);

#ifndef _RETAIL
const char* stringid_lookup(StringId id);
void load_string_table(const char* fName);
void save_string_table(const char* fName);
#endif
