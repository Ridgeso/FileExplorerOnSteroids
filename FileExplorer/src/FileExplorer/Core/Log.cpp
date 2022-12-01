#include "FileExplorer/Core/Log.h"

#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>



namespace FEOS
{
    std::shared_ptr<spdlog::logger> Log::s_ExplorerLogger;
    std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

    void Log::Init()
    {
        std::array<spdlog::sink_ptr, 2> logSinks = {
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
            std::make_shared<spdlog::sinks::basic_file_sink_mt>("FILE_EXPLORER.log", true)
        };
        
        logSinks[0]->set_pattern("%^[%T] %n: %v%$");
        logSinks[1]->set_pattern("[%T] [%l] %n: %v");

        s_ExplorerLogger = std::make_shared<spdlog::logger>(
            "Explorer",
            logSinks.begin(),
            logSinks.end()
        );
        spdlog::register_logger(s_ExplorerLogger);
        s_ExplorerLogger->set_level(spdlog::level::trace);
        s_ExplorerLogger->flush_on(spdlog::level::trace);


        s_ClientLogger = std::make_shared<spdlog::logger>(
            "Application",
            logSinks.begin(),
            logSinks.end()
        );
        spdlog::register_logger(s_ClientLogger);
        s_ClientLogger->set_level(spdlog::level::trace);
        s_ClientLogger->flush_on(spdlog::level::trace);
    }

    void Log::Shutdown()
    {
        spdlog::shutdown();
    }
}