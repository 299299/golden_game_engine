

solution "game"
    configurations {
        "Debug",
        "Release",
    }

    platforms {
        "x32",
        "x64",
    }

    language "C++"
    startproject "game"

NAGA_SRC_DIR = (path.getabsolute("..") .. "/")
local NAGA_BUILD_DIR = (NAGA_SRC_DIR .. ".build/")
BGFX_DIR = ("C:/Project/bgfx/")
BX_DIR = ("C:/Project/bx/")
HAVOK_DIR = ("C:/Project/hk2014_1_0_r1/Source/")
GAME_SRC_DIR = (NAGA_SRC_DIR .. "Game/")

defines {
    "HK_PLATFORM_SIM",
    "HK_CONFIG_SIMD=1"
}

dofile (BX_DIR .. "scripts/toolchain.lua")
if not toolchain(NAGA_BUILD_DIR, "") then
    return -- no action specified
end

function exeProject(_name, _incdirs, _files)

    project (_name)
        uuid (os.uuid(_name))
        kind "WindowedApp"

    configuration {}

    includedirs {
        _incdirs
    }
    files {
        _files
    }

    configuration { "vs*" }
        linkoptions {
            "/ignore:4199", -- LNK4199: /DELAYLOAD:*.dll ignored; no imports found from *.dll
        }
        links { -- this is needed only for testing with GLES2/3 on Windows with VS2008
            "DelayImp",
        }

    configuration { "vs201*" }
        linkoptions { -- this is needed only for testing with GLES2/3 on Windows with VS201x
            "/DELAYLOAD:\"libEGL.dll\"",
            "/DELAYLOAD:\"libGLESv2.dll\"",
        }

    configuration { "mingw*" }
        targetextension ".exe"

    configuration { "vs20* or mingw*" }
        links {
            "gdi32",
            "psapi",
        }

    configuration { "linux-*" }
        links {
            "X11",
            "GL",
            "pthread",
        }

    configuration {"Debug"}
        defines {
            "_DEBUG",
            "BGFX_CONFIG_DEBUG"
        }

    configuration {"Release"}
        defines {
            "NDEBUG",
        }


    configuration {}

end

game_inc_dirs = {
    BX_DIR .. "include",
    BGFX_DIR .. "include",
    BGFX_DIR .. "examples/common",
    HAVOK_DIR,
    GAME_SRC_DIR,
    GAME_SRC_DIR .. "Core",
    GAME_SRC_DIR .. "Animation",
    GAME_SRC_DIR .. "Engine",
    GAME_SRC_DIR .. "Game",
    GAME_SRC_DIR .. "Graphics",
    GAME_SRC_DIR .. "Physics",
}

game_files = {
    GAME_SRC_DIR .. "Core/*",
    GAME_SRC_DIR .. "Animation/*",
    GAME_SRC_DIR .. "Engine/*",
    GAME_SRC_DIR .. "Game/*",
    GAME_SRC_DIR .. "Graphics/*",
    GAME_SRC_DIR .. "Physics/*",
    GAME_SRC_DIR .. "linkopt.cpp",
}
exeProject("game", game_inc_dirs, game_files)



