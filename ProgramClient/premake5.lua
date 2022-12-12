project "ProgramClient"

    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "Off"

    targetdir ("%{wks.location}/bin/" ..outputdir.. "/%{prj.name}")
    objdir ("%{wks.location}/binInt/" ..outputdir.. "/%{prj.name}")

    files
    {
        "src/**.h",
        "src/**.cpp"
    }

    includedirs
    {
        "%{wks.location}/ProgramClient/src",

        "%{wks.location}/FileExplorer/src",

        "%{wks.location}/FileExplorer/dependencies/imgui",
        "%{wks.location}/FileExplorer/dependencies/spdlog/include"
    }

    links
    {
        "FileExplorer"
    }
    -- filter "action:gmake*"
    --     links { "GLFW", "spdlog", "imgui", "opengl32", "gdi32" }
 
    ignoredefaultlibraries
    {
        "LIBCMTD"
    }
 
    filter "system:windows"
        systemversion "latest"

        defines
        {
            "FILE_EXPLORER_WINDOWS_PLATFOMR"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

        defines
        {
            "FILE_EXPLORER_DEBUG"
        }

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

        defines
        {
            "FILE_EXPLORER_RELEASE"
        }