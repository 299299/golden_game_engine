#include "Profiler.h"
#include "Memory.h"
#include "Prerequisites.h"
#include "Graphics.h"
#include <cstdio>
#include <cstring>
#include <Windows.h>
#include <bx/timer.h>

long long HiresTimer::frequency = 0;
static const int LINE_MAX_LENGTH = 256;
static const int NAME_MAX_LENGTH = 30;
//static const int64_t hpFreq = bx::getHPFrequency();
//static const double freq = double(hpFreq);
//static const double toMs = 1000.0/freq;

void HiresTimer::Init()
{
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    HiresTimer::frequency = frequency.QuadPart;
}

long long HiresTimer::GetUSec( bool reset )
{
    long long currentTime;
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    currentTime = counter.QuadPart;

    long long elapsedTime = currentTime - startTime_;

    // Correct for possible weirdness with changing internal frequency
    if (elapsedTime < 0)
        elapsedTime = 0;

    if (reset)
        startTime_ = currentTime;

    return (elapsedTime * 1000000LL) / frequency;
}

void HiresTimer::Reset()
{
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    startTime_ = counter.QuadPart;
}

HiresTimer::HiresTimer()
{

}



Profiler g_profiler;
Profiler::Profiler() :
    current_(0),
    root_(0),
    intervalFrames_(0),
    totalFrames_(0)
{
    
}

Profiler::~Profiler()
{
    
}

void Profiler::BeginFrame()
{
    // End the previous frame if any
    EndFrame();
    
    BeginBlock("RunFrame");
}

void Profiler::EndFrame()
{
    if (current_ != root_)
    {
        EndBlock();
        ++intervalFrames_;
        ++totalFrames_;
        if (!totalFrames_)
            ++totalFrames_;
        root_->EndFrame();
        current_ = root_;
    }
}

void Profiler::BeginInterval()
{
    root_->BeginInterval();
    intervalFrames_ = 0;
}

void Profiler::Init()
{
    numBlocks_ = 0;
    blocks_ = STATIC_ALLOC(ProfilerBlock, TOTAL_BLOCK_NUM);
    root_ = AllocBlock("Root");
    current_ = root_;
}

ProfilerBlock* Profiler::AllocBlock( const char* name )
{
    HK_ASSERT(0, numBlocks_ < TOTAL_BLOCK_NUM - 1);
    ProfilerBlock* newBlock = blocks_ + (numBlocks_++);
    newBlock->name_ = name;
    return newBlock;
}

void Profiler::Dump( bool showUnused, bool showTotal, unsigned maxDepth ) const
{
    if (!maxDepth)
        maxDepth = 1;
    const uint8_t color = 0x1f;
    if (!showTotal)
    {
        DBG_TEX_PRINTF(color, "Block                            Cnt     Avg      Max     Frame     Total");
    }
    else
    {
        DBG_TEX_PRINTF(color, "Block                                       Last frame                       Whole execution time");
        DBG_TEX_PRINTF(color, "                                 Cnt     Avg      Max      Total      Cnt      Avg       Max        Total");
    }
    DumpData(root_, 0, maxDepth, showUnused, showTotal);
}

void Profiler::DumpData( ProfilerBlock* block, unsigned depth, unsigned maxDepth, bool showUnused, bool showTotal ) const
{
    char indentedName[LINE_MAX_LENGTH];

    unsigned intervalFrames = max(intervalFrames_, 1);

    const uint8_t color = 0x8f;

    if (depth >= maxDepth)
        return;

    // Do not print the root block as it does not collect any actual data
    if (block != root_)
    {
        if (showUnused || block->intervalCount_ || (showTotal && block->totalCount_))
        {
            memset(indentedName, ' ', NAME_MAX_LENGTH);
            indentedName[depth] = 0;
            strcat(indentedName, block->name_);
            indentedName[strlen(indentedName)] = ' ';
            indentedName[NAME_MAX_LENGTH] = 0;

            if (!showTotal)
            {
                float avg = (block->intervalCount_ ? block->intervalTime_ / block->intervalCount_ : 0.0f) / 1000.0f;
                float max = block->intervalMaxTime_ / 1000.0f;
                float frame = block->intervalTime_ / intervalFrames / 1000.0f;
                float all = block->intervalTime_ / 1000.0f;
                DBG_TEX_PRINTF( color, "%s %5u %8.3f %8.3f %8.3f %9.3f", 
                                indentedName, 
                                min(block->intervalCount_, 99999),
                                avg, 
                                max, 
                                frame, 
                                all);
            }
            else
            {
                float avg = (block->frameCount_ ? block->frameTime_ / block->frameCount_ : 0.0f) / 1000.0f;
                float max = block->frameMaxTime_ / 1000.0f;
                float all = block->frameTime_ / 1000.0f;

                float totalAvg = (block->totalCount_ ? block->totalTime_ / block->totalCount_ : 0.0f) / 1000.0f;
                float totalMax = block->totalMaxTime_ / 1000.0f;
                float totalAll = block->totalTime_ / 1000.0f;

                DBG_TEX_PRINTF(color, "%s %5u %8.3f %8.3f %9.3f  %7u %9.3f %9.3f %11.3f", 
                                indentedName, 
                                min(block->frameCount_, 99999),
                                avg, 
                                max, 
                                all, 
                                min(block->totalCount_, 99999), 
                                totalAvg, 
                                totalMax, 
                                totalAll);
            }
        }

        ++depth;
    }

    for (uint32_t i=0; i<block->numChildren_; ++i)
    {
        DumpData(block->children_[i], depth, maxDepth, showUnused, showTotal);
    }
}

ProfilerBlock* ProfilerBlock::GetChild( const char* name )
{
    for (uint32_t i=0; i<numChildren_; ++i)
    {
        ProfilerBlock* child = children_[i];
        if(name == child->name_)
            return child;
    }
    for (uint32_t i=0; i<numChildren_; ++i)
    {
        ProfilerBlock* child = children_[i];
        if(!strcmp(name, child->name_))
            return child;
    }
    ProfilerBlock* newBlock = g_profiler.AllocBlock(name);
    children_[numChildren_++] = newBlock;
    newBlock->parent_ = this;
    return newBlock;
}

void ProfilerBlock::Begin()
{
    timer_.Reset();
    ++count_;
}

void ProfilerBlock::End()
{
    long long time = timer_.GetUSec(false);
    if (time > maxTime_)
        maxTime_ = time;
    time_ += time;
}