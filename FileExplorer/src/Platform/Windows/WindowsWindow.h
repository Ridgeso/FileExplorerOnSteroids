#pragma once

#include "feospch.h"

#include "FileExplorer/Core/Window.h"
#include "FileExplorer/Events/Event.h"

#include <GLFW/glfw3.h>


namespace FEOS
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& data);
        virtual ~WindowsWindow();

        void OnUpdate() override;

        virtual void* GetNativeWindow() const { return m_GlfwWindow; } 

        const std::string& GetTitle() const { return m_Data.Title; }
        uint32_t GetWidth() const override { return m_Data.Width; }
        uint32_t GetHeight() const override { return m_Data.Height; }
        bool IsMinimized() const { return m_Data.IsMinimized; }

        void SetEventCallback(const EventCallbackFn& callback) override
        {
            m_Data.EventCallback = callback;
        }

    private:
        virtual void Init(const WindowProps& data);
        virtual void Shutdown();

    private:
        GLFWwindow* m_GlfwWindow;
        
        struct WindowData
        {
            std::string Title;
            uint32_t Width, Height;
            bool IsMinimized;

            EventCallbackFn EventCallback;
        } m_Data;
    };
}