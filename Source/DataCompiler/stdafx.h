#pragma once

#include <SDKDDKVer.h>
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include "SharedInc.h"
#include "CommonUtils.h"

#ifdef _DEBUG
//#define COMPILER_LOAD_TEST
#endif

#define     MSG_TITLE           ("DATA COMPILER")
#define     DC_DATABASE         ("data_compiler_database.txt")
#define     DC_RESULT           ("data_compiler_result.txt")

enum DCErrorCode
{
    kErrorArg = 1,
};

enum DC_Mode
{
    kDC_DataCompileAndPackageUpdate = 0,
    kDC_PackageUpdateOnly,
};

struct DC_Config
{
   DC_Config()
    :m_mode(0)
    ,m_exitCode(0)
    ,m_numThreads(0)
    ,m_ignoreTextures(false) //--> for speed up data compile
    ,m_slient(false)
    ,m_batchMode(false)
    ,m_bundled(false)
    {
    }
    
    std::string                 m_inputDir;
    std::string                 m_inputFile;
    std::string                 m_outputDir;
    std::string                 m_packageName;
    std::string                 m_topFolder;
    int                         m_mode;
    int                         m_exitCode;
    int                         m_numThreads;
    bool                        m_ignoreTextures;
    bool                        m_slient;
    bool                        m_batchMode;
    bool                        m_bundled;
};


