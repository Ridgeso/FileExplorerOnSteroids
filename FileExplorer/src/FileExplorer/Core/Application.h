#pragma once
#include <string>
#include <cstdint>

#include "FileExplorer/Core/Base.h"

#include "FileExplorer/Core/Window.h"
#include "FileExplorer/Events/ApplicationEvent.h"
#include "FileExplorer/Core/Layer.h"
#include "FileExplorer/UI/UI.h"
#include "FileExplorer/FileManager/Manager.h"


namespace FEOS
{
    struct FileExplorerCommandLineArgs
    {
        int32_t Count;
        char** Args;

        const char* operator[](int32_t ind) const
        {
            FEOS_EXPLORER_ASSERT(ind < Count);
            return Args[ind];
        }
    };
    
    struct FileExplorerSpecifications
    {
        std::string Name;
        FileExplorerCommandLineArgs CommandLineArgs;
    };
    
    class Application
    {
    public:
        Application(FileExplorerSpecifications spec);
        virtual ~Application();

        Window& GetWindow() const { return *m_Window; }
        static Application& Get() { return *s_Instance; }
        Files::Manager& GetFileManager() const { return *m_FileManager; }
        FileExplorerSpecifications& GetSpecifications() { return m_Spec; }

        void OnEvent(Event::Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        void Run();
        
    private:
        bool OnWindowClose(Event::WindowClose& e);
        bool OnWindowResize(Event::WindowResize& e);

    private:
        FileExplorerSpecifications m_Spec;

        bool m_IsRunning = true;
        bool m_Minimized = false;
        
        Local<Window> m_Window;
        LayerStack m_LayerStack;
        UI* m_UI;
        Local<Files::Manager> m_FileManager;
        static Application* s_Instance;
    };

    // To be defined in CLIENT
    Application* CreateApplication(FileExplorerCommandLineArgs args);
}