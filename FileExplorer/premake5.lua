project "FileExplorer"
    DEP = "dependencies/"

    -- kind "SharedLib"
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "Off"

    targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    -- targetdir ("%{wks.location}/bin/" ..outputdir.. "/ProgramClient")
    objdir ("%{wks.location}/binInt/" ..outputdir.. "/%{prj.name}")

    -- postbuildcommands
    -- {
    --     "{COPY} %{cfg.buildtarget.relpath} \"%{wks.location}/bin/" .. outputdir.. "/ProgramClient\""
    -- }

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    pchheader "feospch.h"
    pchsource "FileExplorer/src/feospch.cpp"

    includedirs
    {
        "src",
        DEP .. "GLFW/include",
        DEP .. "imgui",
        DEP .. "spdlog/include",

        "fileManager"
    }

    links
    {
        "GLFW",
        "imgui",
        "spdlog",

        "FileManager",
        
        "opengl32"
    }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "FILE_EXPLORER_WINDOWS_PLATFOMR"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"

        defines
        {
            "FILE_EXPLORER_DEBUG",
            "GLFW_DLL"
        }

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

        defines
        {
            "FILE_EXPLORER_RELEASE"
        }