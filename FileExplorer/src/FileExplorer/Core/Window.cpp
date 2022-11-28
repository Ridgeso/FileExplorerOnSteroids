#include "FileExplorer/Core/Window.h"

#include "Platform/Windows/WindowsWindow.h"


namespace FEOS
{
    std::unique_ptr<Window> Window::Create(const WindowProps& props)
    {
    #ifdef FILE_EXPLORER_WINDOWS_PLATFOMR
        return std::make_unique<WindowsWindow>(props);
    #else
        return nullptr;
    #endif
    }    
}