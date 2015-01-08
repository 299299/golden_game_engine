#pragma once
#include <cstdlib>
#include <cstdio>

/// Aborts the program execution logging an error message and the stacktrace if
/// the platform supports it.
void error_abort(const char* file, int line, const char* message, ...);
void stacktrace();

#ifdef _DEBUG
#define ENGINE_ASSERT(condition, msg, ...) do { if (!(condition)) {\
    error_abort(__FILE__, __LINE__, "\nAssertion failed: %s\n\t" msg "\n", #condition, ##__VA_ARGS__); }} while (0)
#else
#define ENGINE_ASSERT(...) ((void)0)
#endif

#define ENGINE_ASSERT_NOT_NULL(x) ENGINE_ASSERT(x != NULL, #x "must be not null")
#define ENGINE_FATAL(msg) ENGINE_ASSERT(false, msg)

