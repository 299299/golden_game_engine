#include "CopyCompiler.h"

CopyCompiler::CopyCompiler()
{

}

CopyCompiler::~CopyCompiler()
{

}

bool CopyCompiler::process(const std::string& input, const std::string& output)
{
    if(!fileSystemCopy(input, getFilePath(output))) return false;
    m_processed = true;
    return true;
}
