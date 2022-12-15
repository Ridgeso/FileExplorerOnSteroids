#pragma once

#include "FileExplorer/Core/Base.h"

#define SPDLOG_COMPILED_LIB
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>


namespace FEOS
{
    class Log
    {
    public:
        static void Init();
        static void Shutdown();

        static Object<spdlog::logger>& GetExplorerLogger() { return s_ExplorerLogger; }
        static Object<spdlog::logger>& GetClinetLogger() { return s_ClientLogger; }

    private:
        static Object<spdlog::logger> s_ExplorerLogger;
        static Object<spdlog::logger> s_ClientLogger;
    };
}

// Program Logs Macros
#define FEOS_LOG_CRITICAL(...)  ::FEOS::Log::GetExplorerLogger()->critical(__VA_ARGS__)
#define FEOS_LOG_ERROR(...)     ::FEOS::Log::GetExplorerLogger()->error(__VA_ARGS__)
#define FEOS_LOG_WARN(...)      ::FEOS::Log::GetExplorerLogger()->warn(__VA_ARGS__)
#define FEOS_LOG_INFO(...)      ::FEOS::Log::GetExplorerLogger()->info(__VA_ARGS__)
#define FEOS_LOG_DEBUG(...)     ::FEOS::Log::GetExplorerLogger()->debug(__VA_ARGS__)
#define FEOS_LOG_TRACE(...)     ::FEOS::Log::GetExplorerLogger()->trace(__VA_ARGS__)

// Clients Logs Macros
#define FEOS_CRITICAL(...)      ::FEOS::Log::GetClinetLogger()->critical(__VA_ARGS__)
#define FEOS_ERROR(...)         ::FEOS::Log::GetClinetLogger()->error(__VA_ARGS__)
#define FEOS_WARN(...)          ::FEOS::Log::GetClinetLogger()->warn(__VA_ARGS__)
#define FEOS_INFO(...)          ::FEOS::Log::GetClinetLogger()->info(__VA_ARGS__)
#define FEOS_DEBUG(...)         ::FEOS::Log::GetClinetLogger()->debug(__VA_ARGS__)
#define FEOS_TRACE(...)         ::FEOS::Log::GetClinetLogger()->trace(__VA_ARGS__)
