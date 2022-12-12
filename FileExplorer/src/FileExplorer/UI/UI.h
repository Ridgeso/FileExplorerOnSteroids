#pragma once

#include "FileExplorer/Core/Layer.h"
#include "FileExplorer/Events/ApplicationEvent.h"


namespace FEOS
{
    class UI : public Layer
    {
    public:
        UI();
        ~UI() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnEvent(Event::Event& e) override;

        void Begin();
        void End();
    
        void SetTheme();

    private:
    }; 
}
