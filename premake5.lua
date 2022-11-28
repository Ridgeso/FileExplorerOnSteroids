workspace "FileExplorerOnSteroids"
    startproject "ProgramClient"
    configurations { "Debug", "Release" }
    platforms { "Win32", "Win64" }

    flags
    {
        "MultiProcessorCompile"
    }

    filter "platforms:Win32"
        system "Windows"
        architecture "x86"

    filter "platforms:Win64"
        system "Windows"
        architecture "x64"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

group "Dependencies"
    include "FileExplorer/dependencies/GLFW.lua"
group ""

include "FileExplorer"
include "ProgramClient"