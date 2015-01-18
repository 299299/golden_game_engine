#pragma once
#include "BaseCompiler.h"
#include "Level.h"
#include <tinystl/allocator.h>
#include <tinystl/unordered_map.h>


typedef tinystl::unordered_map<uint32_t, int> ResourceKeyMap;

class LevelCompiler : public BaseCompiler
{
public:
    LevelCompiler();
    ~LevelCompiler();

    virtual std::string getFormatExt() const { return Level::get_name(); };
    virtual bool parseWithJson() const { return true; };
    virtual bool readJSON(const jsonxx::Object& root);

    ResourceKeyMap           m_resourceKeys;
};
