#pragma once

#include "FileExplorer/Events/ApplicationEvent.h"


namespace FEOS
{

    class UI
    {
    public:
        UI();
        ~UI() = default;

        void OnEvent(Event::Event& e);

        void Begin();
        void End();
    
        void SetTheme();
    private:
    }; 

}
