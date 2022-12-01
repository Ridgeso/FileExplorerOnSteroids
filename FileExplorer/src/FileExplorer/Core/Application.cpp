#include "feospch.h"

#include "FileExplorer/Core/Application.h"


namespace FEOS
{
    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        s_Instance = this;

        m_Window = Window::Create(WindowProps("File Explorer", 800, 600));
        m_Window->SetEventCallback(FEOS_EVENT_FN(Application::OnEvent));
    }

    Application::~Application()
    {
        
    }

    void Application::OnEvent(Event::Event& e)
    {
        Event::Dispatcher dispatcher(e);

        dispatcher.Dispatch<Event::WindowClose>(FEOS_EVENT_FN(Application::OnWindowClose));
    }

    void Application::run()
    {
        while (m_IsRunning)
        {
            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(Event::WindowClose& e)
    {
        m_IsRunning = false;
        return true;
    }
}