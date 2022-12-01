project "spdlog"
    LOC = "spdlog/"
    location (LOC)
    

    kind "StaticLib"
    language "C++"
    cppdialect "C++17"
    staticruntime "On"
    
    targetdir (LOC .. "bin/" .. outputdir .. "/")
    objdir (LOC .. "binInt/" .. outputdir .. "/")

    files
    {
		LOC .. "src/async.cpp",
		LOC .. "src/bundled_fmtlib_format.cpp",
		LOC .. "src/cfg.cpp",
		LOC .. "src/color_sinks.cpp",
		LOC .. "src/file_sinks.cpp",
		LOC .. "src/spdlog.cpp",
		LOC .. "src/stdout_sinks.cpp"
    }

    includedirs
    {
        LOC .. "include/"
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
