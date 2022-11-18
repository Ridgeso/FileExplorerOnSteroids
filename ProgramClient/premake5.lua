project "ProgramClient"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++11"
    staticruntime "off"

    targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/binInt/" ..outputdir.. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/FileExplorer/src"
    }

    links
    {
        "FileExplorer"
    }

    defines
    {
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
            "FILE_EXPLORER_DEBUG"
        }

    filter "configurations:Release"
        runtime "Release"
        optimize "on"

        defines
        {
            "FILE_EXPLORER_RELEASE"
        }