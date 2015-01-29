#include "Profiler.h"
#include "MemorySystem.h"
#include "Gui.h"
#include "Prerequisites.h"
#include <cstdio>
#include <cstring>
#include <bx/timer.h>

#ifndef max
#define max(a,b)    (((a) > (b)) ? (a) : (b))
#endif
#ifndef min
#define min(a,b)    (((a) < (b)) ? (a) : (b))
#endif

int64_t HiresTimer::frequency = 0;
static const int LINE_MAX_LENGTH = 256;
static const int NAME_MAX_LENGTH = 30;

void HiresTimer::init()
{
    HiresTimer::frequency = bx::getHPFrequency();
}

int64_t HiresTimer::get_usec( bool reset )
{
    int64_t currentTime = bx::getHPCounter();
    int64_t elapsedTime = currentTime - startTime_;

    // Correct for possible weirdness with changing internal frequency
    if (elapsedTime < 0)
        elapsedTime = 0;

    if (reset)
        startTime_ = currentTime;

    return (elapsedTime * 1000000LL) / frequency;
}

void HiresTimer::reset()
{
    startTime_ = bx::getHPCounter();
}

HiresTimer::HiresTimer()
{

}



Profiler g_profiler;
Profiler::Profiler() :
    current_(0),
    root_(0),
    numBlocks_(0),
    intervalFrames_(0),
    totalFrames_(0)
{

}

Profiler::~Profiler()
{

}

void Profiler::begin_frame()
{
    // End the previous frame if any
    end_frame();
    begin_block("RunFrame");
}

void Profiler::end_frame()
{
    if (current_ != root_)
    {
        end_block();
        ++intervalFrames_;
        ++totalFrames_;
        if (!totalFrames_)
            ++totalFrames_;
        root_->end_frame();
        current_ = root_;
    }
}

void Profiler::begin_interval()
{
    root_->begin_interval();
    intervalFrames_ = 0;
}


ProfilerBlock* Profiler::alloc_block( const char* name )
{
    ENGINE_ASSERT(numBlocks_ < TOTAL_BLOCK_NUM - 1, "profile blocks overflow.");
    ProfilerBlock* newBlock = blocks_ + (numBlocks_++);
    newBlock->name_ = name;
    return newBlock;
}

void Profiler::dump( bool showUnused, bool showTotal, unsigned maxDepth ) const
{
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
    dump_block(root_, 0, maxDepth, showUnused, showTotal);
}

void Profiler::dump_to_file(const char* fileName, bool showUnused, bool showTotal, unsigned maxDepth ) const
{
    FILE* fp = fopen(fileName, "w");
    if(!fp) return;
    if (!showTotal)
    {
        fprintf(fp, "Block                            Cnt     Avg      Max     Frame     Total\n");
    }
    else
    {
        fprintf(fp, "Block                                       Last frame                       Whole execution time\n");
        fprintf(fp, "                                 Cnt     Avg      Max      Total      Cnt      Avg       Max        Total\n");
    }
    dump_block_to_file(fp, root_, 0, maxDepth, showUnused, showTotal);
    fclose(fp);
}

void Profiler::dump_block(  ProfilerBlock* block,
                            unsigned depth,
                            unsigned maxDepth,
                            bool showUnused,
                            bool showTotal ) const
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

                DBG_TEX_PRINTF( color, "%s %5u %8.3f %8.3f %9.3f  %7u %9.3f %9.3f %11.3f",
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

    uint32_t num = block->numChildren_;
    for (uint32_t i=0; i<num; ++i)
    {
        dump_block(block->children_[i], depth, maxDepth, showUnused, showTotal);
    }
}

void Profiler::dump_block_to_file(  void* fp_,
                                    ProfilerBlock* block,
                                    unsigned depth,
                                    unsigned maxDepth,
                                    bool showUnused,
                                    bool showTotal ) const
{
    FILE* fp = (FILE*)fp_;
    char indentedName[LINE_MAX_LENGTH];
    unsigned intervalFrames = max(intervalFrames_, 1);

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
                fprintf( fp,    "%s %5u %8.3f %8.3f %8.3f %9.3f\n",
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

                fprintf( fp, "%s %5u %8.3f %8.3f %9.3f  %7u %9.3f %9.3f %11.3f\n",
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

    uint32_t num = block->numChildren_;
    for (uint32_t i=0; i<num; ++i)
    {
        dump_block_to_file(fp, block->children_[i], depth, maxDepth, showUnused, showTotal);
    }
}

void Profiler::init(int max_block_num)
{
    blocks_ = COMMON_ALLOC(ProfilerBlock, max_block_num);
    memset(blocks_, 0x00, sizeof(ProfilerBlock) * max_block_num);
    root_ = alloc_block("Root");
    current_ = root_;
}

void Profiler::shutdown()
{
    COMMON_DEALLOC(blocks_);
    blocks_ = NULL;
}

ProfilerBlock* ProfilerBlock::get_child( const char* name )
{
    uint32_t num = numChildren_;
    for (uint32_t i=0; i<num; ++i)
    {
        ProfilerBlock* child = children_[i];
        if(name == child->name_)
            return child;
    }
    for (uint32_t i=0; i<num; ++i)
    {
        ProfilerBlock* child = children_[i];
        if(!strcmp(name, child->name_))
            return child;
    }
    ProfilerBlock* newBlock = g_profiler.alloc_block(name);
    children_[numChildren_++] = newBlock;
    newBlock->parent_ = this;
    return newBlock;
}

void ProfilerBlock::begin()
{
    timer_.reset();
    ++count_;
}

void ProfilerBlock::end()
{
    long long time = timer_.get_usec(false);
    if (time > maxTime_) maxTime_ = time;
    time_ += time;
}