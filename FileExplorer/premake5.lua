project "FileExplorer"
    kind "staticlib"
    language "C++"
    cppdialect "C++11"

    targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/binInt/" ..outputdir.. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "src",
        "dependencies/GLFW/include"
    }

    links
    {
        "GLFW",
        "opengl32.lib"
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