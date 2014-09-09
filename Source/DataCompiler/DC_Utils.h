#pragma once
#include "stdafx.h"
#include "CommonUtils.h"

void        nvtt_compress(const std::string& src, const std::string& dst, const std::string& fmt);
void        texconv_compress(const std::string& src, const std::string& folder, const std::string& fmt);
void        lut2d_to_3d(const uint8_t* inData, uint8_t* outData);
bool        parse_json(const std::string& fileName, JsonParser& parser);
std::string input_to_output(const std::string& inputName);
std::string get_package_name(const std::string& input);
std::string get_resource_name(const std::string& input);
void        addChildCompiler(class BaseCompiler* compiler);
void        saveCompileResult(const std::string& fileName);

extern ResourceFileDataBase             g_database;
