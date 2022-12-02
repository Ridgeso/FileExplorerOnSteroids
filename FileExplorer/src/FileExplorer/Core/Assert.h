#pragma once

#include "FileExplorer/Core/Log.h"

#ifdef FILE_EXPLORER_DEBUG
    #define FEOS_DEBUGBREAK() __debugbreak()

    #define FEOS_ASSERT_IMPL(type, cond, msg, ...) { if (!cond) { FEOS##type##ERROR(msg, __VA_ARGS__); FEOS_DEBUGBREAK(); } }
    #define FEOS_ASSERT_IMPL_WITH_MSG(type, cond, ...) FEOS_ASSERT_IMPL(type, cond, "Assertion: {0}", __VA_ARGS__)
    #define FEOS_ASSERT_IMPL_NO_MSG(type, cond, ...) FEOS_ASSERT_IMPL(type, cond, "Assertion ({0}): file {1}:{2}", #cond, __FILE__, __LINE__)

    // skipping impl_with_msg when only one argument
    #define FEOS_ASSERT_GET_IMPL(cond, msgOrMacro, macro, ...) macro

    // If there is more than one argument, message is detected
    #define FEOS_ASSERT(...) FEOS_ASSERT_GET_IMPL(__VA_ARGS__, FEOS_ASSERT_IMPL_WITH_MSG, FEOS_ASSERT_IMPL_NO_MSG)(_LOG_, __VA_ARGS__)
    #define FEOS_CLIENT_ASSERT(...) FEOS_ASSERT_GET_IMPL(__VA_ARGS__, FEOS_ASSERT_IMPL_WITH_MSG, FEOS_ASSERT_IMPL_NO_MSG)(_, __VA_ARGS__)
#else
    #define FEOS_DEBUGBREAK()

    #define FEOS_ASSERT(...)
    #define FEOS_CLIENT_ASSERT(...)
#endif
