#pragma once

#include "feospch.h"
// TODO: add spdlog submodule

namespace FEOS
{
    class Log
    {
    public:
        static void Init();
        static void Shutdown();

        template<typename T>
        static void Trace(const T& arg)
        {
            std::cout << arg << std::endl;
        }

        template<typename T, typename ... Args>
        static void Trace(const T& arg, const Args& ... args)
        {
            std::cout << arg << std::endl;
            Trace(args...);
        }

        template<typename T, typename ... Args>
        static void TraceC(const int32_t color, const T& arg, const Args& ... args)
        {
            SetConsoleTextAttribute(Console, color);

            std::cout << arg << " ";
            Trace(args...);

            SetConsoleTextAttribute(Console, 15);
        }

    private:
        static HANDLE Console;

    };
}


#define Error(...) ::FEOS::Log::TraceC(12, "[ERROR][" __TIME__ "]", __VA_ARGS__)
#define Warn(...)  ::FEOS::Log::TraceC( 5, "[WARN]["  __TIME__ "]", __VA_ARGS__)
#define Info(...)  ::FEOS::Log::TraceC( 6, "[INFO]["  __TIME__ "]", __VA_ARGS__)
#define Debug(...) ::FEOS::Log::TraceC( 1, "[DEBUG][" __TIME__ "]", __VA_ARGS__)
