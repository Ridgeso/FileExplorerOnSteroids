project "FileExplorer"
    DEP = "dependencies/"

    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "Off"

    targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/binInt/" ..outputdir.. "/%{prj.name}")

    pchheader "feospch.h"
    pchsource "src/feospch.cpp"

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        DEP .. "GLFW/include",
        DEP .. "imgui",

        DEP .. "spdlog/include",
        DEP .. "dirent/"
    }

    links
    {
        "GLFW",
        "imgui",
        "spdlog",
        
        "opengl32",

        "Shlwapi"
    }

    defines
    {
        "_CRT_SECURE_NO_WARNINGS"
    }

    characterset("MBCS")

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
            "FILE_EXPLORER_DEBUG"
        }

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

        defines
        {
            "FILE_EXPLORER_RELEASE"
        }