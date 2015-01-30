#include "AnimationStateCompiler.h"

AnimationStateCompiler::AnimationStateCompiler()
{

}

AnimationStateCompiler::~AnimationStateCompiler()
{

}

bool AnimationStateCompiler::readJSON(const jsonxx::Object& root)
{
    BaseCompiler::readJSON(root);


    return false;
    //return write_file(m_output, mem.m_buf, memSize);
}