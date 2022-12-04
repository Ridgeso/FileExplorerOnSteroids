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

        m_UI = new UI;
        PushOverlay(m_UI);
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event::Event& e)
    {
        Event::Dispatcher dispatcher(e);

        dispatcher.Dispatch<Event::WindowClose>(FEOS_EVENT_FN(Application::OnWindowClose));

        auto it = m_LayerStack.GetStack().rbegin();
        while (it != m_LayerStack.GetStack().rend())
        {
            if (e.Handled)
                break;
            (*it++)->OnEvent(e);
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            m_Window->OnUpdate();

            for (Layer* layer : m_LayerStack.GetStack())
                layer->OnUpdate();
        }
    }

    bool Application::OnWindowClose(Event::WindowClose& e)
    {
        m_IsRunning = false;
        return true;
    }
}