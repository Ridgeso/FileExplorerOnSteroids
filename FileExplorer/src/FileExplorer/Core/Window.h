#pragma once

#include "feospch.h"
#include "FileExplorer/Events/Event.h"


namespace FEOS
{
    
    struct WindowProps
    {
        std::string Title;
        uint32_t Width;
        uint32_t Height;

        WindowProps(const std::string& title = "File Explorer",
                    uint32_t width = 800,
                    uint32_t height = 600)
            : Title(title), Width(width), Height(height)
        { }
    };

    class Window
    {
    public:
        virtual ~Window() = default;

        static std::unique_ptr<Window> Create(const WindowProps& props);

        virtual void OnUpdate() = 0;

        virtual void* GetNativeWindow() const = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        using EventCallbackFn = std::function<void(Event::Event&)>;
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    };


}