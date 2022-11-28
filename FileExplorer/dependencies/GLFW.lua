project "GLFW"
    LOC = "GLFW/"
    location (LOC)
    

    kind "StaticLib"
    language "C"
    staticruntime "On"
    
    targetdir (LOC .. "bin/" .. outputdir .. "/")
    objdir (LOC .. "binInt/" .. outputdir .. "/")

    files
    {
        LOC .. "include/GLFW/glfw3.h",
        LOC .. "include/GLFW/glfw3native.h",
        LOC .. "src/glfw_config.h",
    
        LOC .. "src/context.c",
        LOC .. "src/init.c",
        LOC .. "src/input.c",
        LOC .. "src/monitor.c",
        LOC .. "src/platform.c",
        LOC .. "src/vulkan.c",
        LOC .. "src/window.c",
        LOC .. "src/egl_context.c",
        LOC .. "src/osmesa_context.c",

        LOC .. "src/null_init.c",
        LOC .. "src/null_monitor.c",
        LOC .. "src/null_window.c",
        LOC .. "src/null_joystick.c"
    }

    includedirs
    {
        LOC .. "include"
    }
    filter "action:gmake*"   
        includedirs { LOC .. "deps/mingw" }

    filter "system:windows"
        systemversion "latest"

        defines
        {
            "_GLFW_WIN32",
            "_CRT_SECURE_NO_WARNINGS"
        }

        files
        {
            LOC .. "src/win32_module.c",
            LOC .. "src/win32_time.c",
            LOC .. "src/win32_thread.c",

            LOC .. "src/win32_init.c",
            LOC .. "src/win32_joystick.c",
            LOC .. "src/win32_monitor.c",
            LOC .. "src/win32_window.c",
            LOC .. "src/wgl_context.c"
        }

    filter "configurations:Debug"
        runtime "Debug"
        symbols "on"
    
    filter "configurations:Release"
        runtime "Release"
        optimize "on"
