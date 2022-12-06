#pragma once

#include "FileExplorer.h"

namespace FEOS
{
    class ViewPort : public Layer
    {
    public:
        ViewPort();
        virtual ~ViewPort() override;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUpdate() override;
        virtual void OnUIDraw() override;
        virtual void OnEvent(Event::Event& e) override;
    
    private:
    };
}
