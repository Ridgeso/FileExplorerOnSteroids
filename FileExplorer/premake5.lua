project "FileExplorer"
    DEP = "dependencies/"


    kind "StaticLib"
    language "C++"
    cppdialect "C++17"

    targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/binInt/" ..outputdir.. "/%{prj.name}")

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
    }

    links
    {
        "GLFW",
        "opengl32"
    }

    filter "system:windows"
        systemversion "latest"
        staticruntime "On"

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