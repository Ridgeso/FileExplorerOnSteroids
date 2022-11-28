#include "Platform/Windows/WindowsWindow.h"
#include "FileExplorer/Core/Log.h"

#include "FileExplorer/Events/ApplicationEvent.h"
#include "FileExplorer/Events/KeyEvent.h"
#include "FileExplorer/Events/MouseEvent.h"


namespace FEOS
{
    static uint8_t s_numberOfWindows = 0;

    static void GLFWErrorCallback(int32_t error, const char* description)
    {
        Info(error, description);
    }

    WindowsWindow::WindowsWindow(const WindowProps& data)
    {
        // Check if failed
        Init(data);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& data)
    {
        m_Data.Title = data.Title;
        m_Data.Width = data.Width;
        m_Data.Height = data.Height;
        m_Data.IsMinimized = false;
        
        if (s_numberOfWindows == 0)
        {
            bool success = glfwInit();
            if (!success)
                return;
            
            glfwSetErrorCallback(GLFWErrorCallback);
        }

        {
            m_GlfwWindow = glfwCreateWindow(m_Data.Width, m_Data.Height, m_Data.Title.c_str(), nullptr, nullptr);
            ++s_numberOfWindows;
        }

        glfwMakeContextCurrent(m_GlfwWindow);
        glfwSetWindowUserPointer(m_GlfwWindow, &m_Data);
        
        // VSync On
        glfwSwapInterval(1);

        // GLFW callbacks
        glfwSetWindowCloseCallback(m_GlfwWindow, [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            Event::WindowClose event;
            data.EventCallback(event);
        });

        glfwSetWindowSizeCallback(m_GlfwWindow, [](GLFWwindow* window, int32_t width, int32_t height) 
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            Event::WindowResize event(width, height);
            data.EventCallback(event);
        });

        glfwSetKeyCallback(m_GlfwWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_RELEASE:
                {
                    Event::KeyReleased event(key);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_PRESS:
                {
                    Event::KeyPressed event(key, true);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    Event::KeyPressed event(key, false);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetCharCallback(m_GlfwWindow, [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            
            Event::KeyType event(keycode);
            data.EventCallback(event);
        });

        glfwSetMouseButtonCallback(m_GlfwWindow, [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
                case GLFW_RELEASE:
                {
                    Event::MouseButtonReleased event(button);
                    data.EventCallback(event);
                    break;
                }
                case GLFW_PRESS:
                {
                    Event::MouseButtonPressed event(button);
                    data.EventCallback(event);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_GlfwWindow, [](GLFWwindow* window, double xOffset, double yOffset)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            Event::MouseScrolled event(xOffset, yOffset);
            data.EventCallback(event);
        });

        glfwSetCursorPosCallback(m_GlfwWindow, [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            Event::MouseMoved event(xPos, yPos);
            data.EventCallback(event);
        });
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_GlfwWindow);
        --s_numberOfWindows;

        if(s_numberOfWindows == 0)
            glfwTerminate();
    }

    void WindowsWindow::OnUpdate()
    {
        // glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor4f(1.0, 0.5, 0.5, 1.0);
        
        glVertex2f( 0.0,  0.5);
        glVertex2f(-0.5, -0.2);
        glVertex2f( 0.5,  0.2);

        glEnd();

        glfwSwapBuffers(m_GlfwWindow);

        glfwPollEvents();
    }
}