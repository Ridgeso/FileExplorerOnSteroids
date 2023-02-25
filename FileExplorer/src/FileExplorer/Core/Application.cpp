#include "feospch.h"

#include "FileExplorer/Core/Application.h"


namespace FEOS
{
    Application* Application::s_Instance = nullptr;

    Application::Application(FileExplorerSpecifications spec)
        : m_Spec(spec)
    {
        s_Instance = this;

        m_Window = Window::Create(WindowProps("File Explorer", 800, 600));
        m_Window->SetEventCallback(FEOS_EVENT_FN(Application::OnEvent));

        m_UI = new UI;
        PushOverlay(m_UI);

        m_FileManager = Files::Create(Files::fs::current_path());
    }

    Application::~Application()
    {
    }

    void Application::OnEvent(Event::Event& e)
    {
        Event::Dispatcher dispatcher(e);

        dispatcher.Dispatch<Event::WindowClose>(FEOS_EVENT_FN(Application::OnWindowClose));
        dispatcher.Dispatch<Event::WindowResize>(FEOS_EVENT_FN(Application::OnWindowResize));

        const std::vector<Layer*>& layerStack = m_LayerStack.GetStack();
        for (auto it = layerStack.rbegin(); it != layerStack.rend(); ++it)
        {
            if (e.Handled)
                break;
            (*it)->OnEvent(e);
        }
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.PushLayer(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* overlay)
    {
        m_LayerStack.PushOverlay(overlay);
        overlay->OnAttach();
    }

    void Application::Run()
    {
        while (m_IsRunning)
        {
            for (Layer* layer : m_LayerStack.GetStack())
            {
                layer->OnUpdate();
            }

            m_UI->Begin();
            {
                for (Layer* layer : m_LayerStack.GetStack())
                {
                    layer->OnUIDraw();
                }
            }
            m_UI->End();

            m_Window->OnUpdate();
        }
    }

    bool Application::OnWindowClose(Event::WindowClose& e)
    {
        m_IsRunning = false;
        return true;
    }
    
    bool Application::OnWindowResize(Event::WindowResize& e)
    {
        if (e.GetWidth() == 0 && e.GetHeight() == 0)
        {
            m_Minimized = true;
            return false;
        }

        m_Minimized = false;
        return false;
    }
}