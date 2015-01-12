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
    int64_t get_usec(bool reset);
    /// Reset the timer.
    void reset();

    /// Return high-resolution timer frequency if supported.
    static int64_t getFrequency() { return frequency; }
    static void init();

private:
    /// Starting clock value in CPU ticks.
    int64_t startTime_;
    /// High-resolution timer frequency.
    static int64_t frequency;
};

/// Profiling data for one block in the profiling tree.
struct ProfilerBlock
{
    /// Begin timing.
    void begin();

    /// End timing.
    void end();

    /// End profiling frame and update interval and total values.
    void end_frame()
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

        uint32_t num = numChildren_;
        for (uint32_t i=0; i<num; ++i)
            children_[i]->end_frame();
    }

    /// Begin new profiling interval.
    void begin_interval()
    {
        intervalTime_ = 0;
        intervalMaxTime_ = 0;
        intervalCount_ = 0;

        uint32_t num = numChildren_;
        for (uint32_t i=0; i<num; ++i)
            children_[i]->begin_interval();
    }

    /// Return child block with the specified name.
    ProfilerBlock* get_child(const char* name);

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
};


/// Hierarchical performance profiler subsystem.
class Profiler
{
public:
    /// Construct.
    Profiler();
    /// Destruct.
    ~Profiler();

    void init();

    /// Begin timing a profiling block.
    void begin_block(const char* name)
    {
        current_ = current_->get_child(name);
        current_->begin();
    }

    /// End timing the current profiling block.
    void end_block()
    {
        if (current_ != root_)
        {
            current_->end();
            current_ = current_->parent_;
        }
    }

    /// Begin the profiling frame. Called by HandleBeginFrame().
    void begin_frame();
    /// End the profiling frame. Called by HandleEndFrame().
    void end_frame();
    /// Begin a new interval.
    void begin_interval();

    /// Return the current profiling block.
    const ProfilerBlock* get_current_block() const { return current_; }
    /// Return the root profiling block.
    const ProfilerBlock* get_root_block() const { return root_; }

    ProfilerBlock* alloc_block(const char* name);

    void dump(bool showUnused = false,
              bool showTotal = false,
              unsigned maxDepth = -1) const;

    void dump_to_file(const char* fileName,
                      bool showUnused = false,
                      bool showTotal = false,
                      unsigned maxDepth = -1) const;
private:
    void dump_block(ProfilerBlock* block,
                    unsigned depth,
                    unsigned maxDepth,
                    bool showUnused,
                    bool showTotal) const;

    void dump_block_to_file(void* fp,
                            ProfilerBlock* block,
                            unsigned depth,
                            unsigned maxDepth,
                            bool showUnused,
                            bool showTotal) const;

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
        g_profiler.begin_block(name);
    }
    ~AutoProfileBlock()
    {
        g_profiler.end_block();
    }
};


#define USE_PROFILING

#ifdef USE_PROFILING
#define PROFILE(name)       AutoProfileBlock profile_##name (#name)
#define PROFILE_BEGIN()     g_profiler.begin_frame();
#define PROFILE_END()       g_profiler.end_frame();
#else
#define PROFILE(name)
#define PROFILE_BEGIN()
#define PROFILE_END()
#endif
