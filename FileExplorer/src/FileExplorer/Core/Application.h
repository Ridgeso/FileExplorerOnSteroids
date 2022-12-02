#pragma once

#include "FileExplorer/Core/Base.h"

#include "FileExplorer/Core/Window.h"
#include "FileExplorer/Events/ApplicationEvent.h"
#include "FileExplorer/Core/Log.h"


namespace FEOS
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        Window& GetWindow() { return *m_Window; }
        static Application& Get() { return *s_Instance; }

        void run();
        void OnEvent(Event::Event& e);

    private:
        bool OnWindowClose(Event::WindowClose& e);

    private:
        bool m_IsRunning = true;
        Local<Window> m_Window;
        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication();
}