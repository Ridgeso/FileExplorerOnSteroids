#include "FileExplorer/UI/UI.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>


namespace FEOS
{
    UI::UI()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
    }

    void UI::OnEvent(Event::Event& e)
    {

    }

    void UI::Begin()
    {

    }

    void UI::End()
    {

    }

    void UI::SetTheme()
    {

    }
}