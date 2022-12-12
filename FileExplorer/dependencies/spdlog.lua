project "spdlog"
    
    kind "SharedLib"
    -- kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    -- staticruntime "On" -- On if it is StaticLib
    staticruntime "Off"
    
    -- targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    targetdir ("%{wks.location}/bin/" ..outputdir.. "/ProgramClient")
    objdir ("%{wks.location}/binInt/" .. outputdir .. "/%{prj.name}")

    -- postbuildcommands
    -- {
    --     "{COPY} %{cfg.buildtarget.relpath} \"%{wks.location}/bin/" .. outputdir.. "/ProgramClient\""
    -- }

    files
    {
		"%{prj.name}/src/async.cpp",
		"%{prj.name}/src/bundled_fmtlib_format.cpp",
		"%{prj.name}/src/cfg.cpp",
		"%{prj.name}/src/color_sinks.cpp",
		"%{prj.name}/src/file_sinks.cpp",
		"%{prj.name}/src/spdlog.cpp",
		"%{prj.name}/src/stdout_sinks.cpp"
    }

    includedirs
    {
        "%{prj.name}/include/"
    }

    defines
    {
        "SPDLOG_COMPILED_LIB"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "on"
