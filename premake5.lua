workspace "FileExplorerOnSteroids"

    startproject "ProgramClient"
    configurations { "Debug", "Release" }
    platforms { "Win64", "Win32" }

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
    include "FileExplorer/dependencies/imgui.lua"
    include "FileExplorer/dependencies/spdlog.lua"
group ""

group "Program"
    include "FileExplorer"
group ""

group "Clients"
    include "ProgramClient"
group ""