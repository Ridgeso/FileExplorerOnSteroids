#include "feospch.h"

#include "MainViewPort.h"

#include <imgui.h>


namespace FEOS
{
    ViewPort::ViewPort()
        : Layer("ViewPort")
    {

    }

    ViewPort::~ViewPort()
    {

    }

    void ViewPort::OnAttach()
    {

    }

    void ViewPort::OnDetach()
    {

    }

    void ViewPort::OnUpdate()
    {

    }

    void ViewPort::OnUIDraw()
    {
        FEOS_EXPLORER_ASSERT(ImGui::GetCurrentContext() != NULL, "Missing dear imgui context. Refer to examples app!");

        static bool menu = true;
        static bool shortCuts = true;
        static bool content = true;
        static bool footer = true;

        ImGui::Begin("Menu", &menu, 0);

            ImGui::Text("Menu");
        
        ImGui::End();

        ImGui::Begin("ShortCuts", &shortCuts, 0);

            ImGui::Text("Short Cuts");
        
        ImGui::End();
        
        ImGui::Begin("Content", &content, 0);

            ImGui::Text("Content");
        
        ImGui::End();

        ImGui::Begin("Footer", &footer, 0);

            ImGui::Text("Footer");
        
        ImGui::End();
    }

    void ViewPort::OnEvent(Event::Event& e)
    {

    }
}
