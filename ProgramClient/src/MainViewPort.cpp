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
        FEOS_EXPLORER_ASSERT(ImGui::GetCurrentContext() != nullptr, "Missing dear imgui context. Refer to examples app!");

        static bool dockspaceOpen = true;
        static bool fullScreen = true;
        static ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

        // Disabling recursive docking
        ImGuiWindowFlags windowFlags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (fullScreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            windowFlags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            windowFlags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
            dockspaceFlags &= ~ImGuiDockNodeFlags_PassthruCentralNode;

        if (dockspaceFlags & ImGuiDockNodeFlags_PassthruCentralNode)
            windowFlags |= ImGuiWindowFlags_NoBackground;
        
        // Never collapsing DockSpace to prevent childe spaces to lost their parent
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("Background", &dockspaceOpen, windowFlags); // <- BEGIN
        ImGui::PopStyleVar();
        if (fullScreen)
            ImGui::PopStyleVar(2);
        
        // Submitting to ImGui
        ImGuiIO& io = ImGui::GetIO();
        ImGuiStyle& style = ImGui::GetStyle();

        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("Background");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);
        }
        
        // Windows
        static bool showDemo = true;
        ImGui::ShowDemoWindow(&showDemo);

        static bool showExplorer = true;
        static bool showContent = true;
        static bool showFooter = true;

        if (ImGui::BeginMainMenuBar()) // <- Menu Bar
        {   
            if (ImGui::BeginMenu("Organize"))
            {
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C")) {}
                if (ImGui::MenuItem("Paste", "CTRL+V")) {}
                if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Select All")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Layout")) {}
                if (ImGui::MenuItem("Folder and Search Options")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Delete", "Delete")) {}
                if (ImGui::MenuItem("Change Name", "F2")) {}
                if (ImGui::MenuItem("Properties")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Exit", "Alt+F4")) {}

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                if (ImGui::MenuItem("Explorer", "CTRL+SHIFT+E"))
                {
                    showExplorer = true;
                }
                
                if (ImGui::MenuItem("Footer"))
                {
                    showFooter = true;
                }
                if (ImGui::MenuItem("Search", "CTRL+F")) {}

                ImGui::EndMenu();
            }

            if (ImGui::SmallButton("New Folder")) {}
    
            ImGui::EndMainMenuBar();
        }

        if (showExplorer) // <- Explorer
        {
            static ImGuiWindowFlags explorerFlags = ImGuiWindowFlags_None;
            ImGui::Begin("Explorer", &showExplorer, explorerFlags);
                ImGui::Text("Explorer");
            ImGui::End();
        }
        
        // Main Content
        static ImGuiWindowFlags contentFlags =
              ImGuiWindowFlags_NoMove
            | ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("Content", &showContent, contentFlags);
            ImGui::Text("Content");
        ImGui::End();

        if (showFooter) // <- Footer
        {
            static ImGuiDockNodeFlags footerFlags = ImGuiDockNodeFlags_None;
            ImGui::Begin("Footer", &showFooter, footerFlags);
                ImGui::Text("Footer");
            ImGui::End();
        }

        ImGui::End(); // <- END
    }

    void ViewPort::OnEvent(Event::Event& e)
    {

    }
}
