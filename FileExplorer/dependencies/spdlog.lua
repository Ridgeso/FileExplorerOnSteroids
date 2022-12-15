project "spdlog"
    
    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "Off"
    
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/binInt/" .. outputdir .. "/%{prj.name}")

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
        symbols "On"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "On"
