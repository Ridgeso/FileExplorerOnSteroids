#include "FileExplorer/Core/Window.h"

#include "Platform/Windows/WindowsWindow.h"


namespace FEOS
{
    Local<Window> Window::Create(const WindowProps& props)
    {
    #ifdef FILE_EXPLORER_WINDOWS_PLATFOMR
        return CreateLocal<WindowsWindow>(props);
    #else
        return nullptr;
    #endif
    }    
}