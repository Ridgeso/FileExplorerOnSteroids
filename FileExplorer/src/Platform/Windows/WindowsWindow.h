#pragma once
#include <string>
#include <cstdint>

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

        void* GetNativeWindow() const override { return m_GlfwWindow; } 

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

        static void GLFWErrorCallback(int32_t error, const char* description);
        static void CloseWindow(GLFWwindow* window);
        static void WindowResize(GLFWwindow* window, int32_t width, int32_t height);
        static void KeyCallback(GLFWwindow* window, int32_t key, int32_t scancode, int32_t action, int32_t mods);
        static void CharCallback(GLFWwindow* window, uint32_t keycode);
        static void MouseButton(GLFWwindow* window, int32_t button, int32_t action, int32_t mods);
        static void Scroll(GLFWwindow* window, double xOffset, double yOffset);
        static void CursorPos(GLFWwindow* window, double xPos, double yPos);

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