#pragma once

#include "FileExplorer/Core/Base.h"

#include "FileExplorer/Core/Window.h"
#include "FileExplorer/Events/ApplicationEvent.h"
#include "FileExplorer/Core/Layer.h"
#include "FileExplorer/UI/UI.h"


namespace FEOS
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        Window& GetWindow() { return *m_Window; }
        static Application& Get() { return *s_Instance; }

        void OnEvent(Event::Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        void Run();
        
    private:
        bool OnWindowClose(Event::WindowClose& e);

    private:
        bool m_IsRunning = true;
        Local<Window> m_Window;
        LayerStack m_LayerStack;
        UI* m_UI;
        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}