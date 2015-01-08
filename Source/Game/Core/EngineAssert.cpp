#include "EngineAssert.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <windows.h>
#include <dbghelp.h>
#include "Log.h"

void error_abort( const char* file, int line, const char* message, ... )
{
    va_list ap;
    va_start(ap, message);
    char buf[256];
    vsprintf_s(buf, message, ap);
    va_end(ap);
    char buf2[1024];
    sprintf_s(buf2, "%s \tIn: %s:%d\n", buf, file, line);
    printf("%s\n", buf2);
    LOGE(buf2);
    MessageBox(NULL, buf2, "ENGINE ASSERT", MB_TOPMOST);
    //HK_ASSERT2(0, false, buf2);
    stacktrace();
    exit(EXIT_FAILURE);
}

void stacktrace()
{
    printf("Stacktrace:\n");
#if 0
    SymInitialize(GetCurrentProcess(), NULL, TRUE);
    SymSetOptions(SYMOPT_LOAD_LINES | SYMOPT_UNDNAME);
    DWORD mtype;
    CONTEXT ctx;
    ZeroMemory(&ctx, sizeof(CONTEXT));
    ctx.ContextFlags = CONTEXT_CONTROL;
    RtlCaptureContext(&ctx);

    STACKFRAME64 stack;
    ZeroMemory(&stack, sizeof(STACKFRAME64));
#ifdef _M_IX86
    mtype = IMAGE_FILE_MACHINE_I386;
    stack.AddrPC.Offset = ctx.Eip;
    stack.AddrPC.Mode = AddrModeFlat;
    stack.AddrFrame.Offset = ctx.Ebp;
    stack.AddrFrame.Mode = AddrModeFlat;
    stack.AddrStack.Offset = ctx.Esp;
    stack.AddrStack.Mode = AddrModeFlat;
#elif _M_X64
    mtype = IMAGE_FILE_MACHINE_AMD64;
    stack.AddrPC.Offset = ctx.Rip;
    stack.AddrPC.Mode = AddrModeFlat;
    stack.AddrFrame.Offset = ctx.Rsp;
    stack.AddrFrame.Mode = AddrModeFlat;
    stack.AddrStack.Offset = ctx.Rsp;
    stack.AddrStack.Mode = AddrModeFlat;
#endif

    DWORD ldsp = 0;
    IMAGEHLP_LINE64 line;
    ZeroMemory(&line, sizeof(IMAGEHLP_LINE64));
    line.SizeOfStruct = sizeof(IMAGEHLP_LINE64);

    char buf[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
    PSYMBOL_INFO sym = (PSYMBOL_INFO)buf;
    sym->SizeOfStruct = sizeof(SYMBOL_INFO);
    sym->MaxNameLen = MAX_SYM_NAME;

    UINT num = 0;
    while (StackWalk64(mtype,
        GetCurrentProcess(),
        GetCurrentThread(),
        &stack,
        &ctx,
        NULL,
        SymFunctionTableAccess64,
        SymGetModuleBase64,
        NULL))
    {

        if (stack.AddrPC.Offset == 0)
            break;

        ++num;
        BOOL res = SymGetLineFromAddr64(GetCurrentProcess(), stack.AddrPC.Offset, &ldsp, &line) &&
            SymFromAddr(GetCurrentProcess(), stack.AddrPC.Offset, 0, sym);

        if (res == TRUE)
            printf("\t[%i] %s (%s:%d)\n", num, sym->Name, line.FileName, line.LineNumber);
        else
            printf("\t[%i] 0x%p\n", num, stack.AddrPC.Offset);
    }

    SymCleanup(GetCurrentProcess());
#endif
}

