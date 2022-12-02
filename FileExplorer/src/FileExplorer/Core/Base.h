#pragma once

#ifndef FILE_EXPLORER_WINDOWS_PLATFOMR
    #error Only windows is supported
#endif

#include <memory>

namespace FEOS
{
    template<typename T> using Local = std::unique_ptr<T>;
    template<typename T, typename... Args>
    constexpr Local<T> CreateLocal(Args&& ...args)
    {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T> using Object = std::shared_ptr<T>;
    template<typename T, typename... Args>
    constexpr Object<T> CreateObject(Args&& ...args)
    {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }
}

#include "FileExplorer/Core/Assert.h"