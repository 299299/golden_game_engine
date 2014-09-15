#pragma once
#include "BaseTypes.h"
#include "config.h"

/// High-resolution operating system timer used in profiling.
class HiresTimer
{
public:
    /// Construct. Get the starting high-resolution clock value.
    HiresTimer();

    /// Return elapsed microseconds and optionally reset.
    long long GetUSec(bool reset);
    /// Reset the timer.
    void Reset();

    /// Return high-resolution timer frequency if supported.
    static long long GetFrequency() { return frequency; }
    static void Init();

private:
    /// Starting clock value in CPU ticks.
    long long startTime_;
    /// High-resolution timer frequency.
    static long long frequency;
};

/// Profiling data for one block in the profiling tree.
struct ProfilerBlock
{
    /// Begin timing.
    void Begin();
    
    /// End timing.
    void End();
    
    /// End profiling frame and update interval and total values.
    void EndFrame()
    {
        frameTime_ = time_;
        frameMaxTime_ = maxTime_;
        frameCount_ = count_;
        intervalTime_ += time_;
        if (maxTime_ > intervalMaxTime_)
            intervalMaxTime_ = maxTime_;
        intervalCount_ += count_;
        totalTime_ += time_;
        if (maxTime_ > totalMaxTime_)
            totalMaxTime_ = maxTime_;
        totalCount_ += count_;
        time_ = 0;
        maxTime_ = 0;
        count_ = 0;

        for (uint32_t i=0; i<numChildren_; ++i)
            children_[i]->EndFrame();
    }
    
    /// Begin new profiling interval.
    void BeginInterval()
    {
        intervalTime_ = 0;
        intervalMaxTime_ = 0;
        intervalCount_ = 0;
        
        for (uint32_t i=0; i<numChildren_; ++i)
            children_[i]->BeginInterval();
    }
    
    /// Return child block with the specified name.
    ProfilerBlock* GetChild(const char* name);

    /// Block name.
    const char* name_;
    /// High-resolution timer for measuring the block duration.
    HiresTimer timer_;
    /// Time on current frame.
    long long time_;
    /// Maximum time on current frame.
    long long maxTime_;
    /// Calls on current frame.
    unsigned count_;
    /// Parent block.
    ProfilerBlock* parent_;
    /// Child blocks.
    ProfilerBlock* children_[MAX_BLOCK_NUM];
    /// Num Childs
    uint32_t    numChildren_;

    /// Time on the previous frame.
    long long frameTime_;
    /// Maximum time on the previous frame.
    long long frameMaxTime_;
    /// Calls on the previous frame.
    unsigned frameCount_;
    /// Time during current profiler interval.
    long long intervalTime_;
    /// Maximum time during current profiler interval.
    long long intervalMaxTime_;
    /// Calls during current profiler interval.
    unsigned intervalCount_;
    /// Total accumulated time.
    long long totalTime_;
    /// All-time maximum time.
    long long totalMaxTime_;
    /// Total accumulated calls.
    unsigned totalCount_;

    /// start time for Begin blcok
    long long startTime_;
};


/// Hierarchical performance profiler subsystem.
class Profiler
{
public:
    /// Construct.
    Profiler();
    /// Destruct.
    ~Profiler();
    
    void Init();

    /// Begin timing a profiling block.
    void BeginBlock(const char* name)
    {
        current_ = current_->GetChild(name);
        current_->Begin();
    }
    
    /// End timing the current profiling block.
    void EndBlock()
    {
        if (current_ != root_)
        {
            current_->End();
            current_ = current_->parent_;
        }
    }
    
    /// Begin the profiling frame. Called by HandleBeginFrame().
    void BeginFrame();
    /// End the profiling frame. Called by HandleEndFrame().
    void EndFrame();
    /// Begin a new interval.
    void BeginInterval();

    /// Return the current profiling block.
    const ProfilerBlock* GetCurrentBlock() { return current_; }
    /// Return the root profiling block.
    const ProfilerBlock* GetRootBlock() { return root_; }
    
    ProfilerBlock* AllocBlock(const char* name);

    void Dump(bool showUnused = false, bool showTotal = false, unsigned maxDepth = -1) const;

private:
    void DumpData(ProfilerBlock* block, unsigned depth, unsigned maxDepth, bool showUnused, bool showTotal) const;

    /// Current profiling block.
    ProfilerBlock* current_;
    /// Root profiling block.
    ProfilerBlock* root_;

    ProfilerBlock  blocks_[TOTAL_BLOCK_NUM];
    uint32_t       numBlocks_; 

    /// Frames in the current interval.
    unsigned intervalFrames_;
    /// Total frames.
    unsigned totalFrames_;
};

extern Profiler g_profiler;

/// Helper class for automatically beginning and ending a profiling block
class AutoProfileBlock
{
public:
    AutoProfileBlock(const char* name)
    {
        g_profiler.BeginBlock(name);
    }
    ~AutoProfileBlock()
    {
        g_profiler.EndBlock();
    }
};


#define USE_PROFILING

#ifdef USE_PROFILING
#define PROFILE(name)       AutoProfileBlock profile_##name (#name)
#define PROFILE_BEGIN()     g_profiler.BeginFrame();
#define PROFILE_END()       g_profiler.EndFrame();
#else
#define PROFILE(name)
#define PROFILE_BEGIN()
#define PROFILE_END()
#endif
