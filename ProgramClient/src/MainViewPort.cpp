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
        static Files::Manager& appFileManager = Application::Get().GetFileManager();

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

        static bool showNavigationBar = true;
        static bool showExplorer = true;
        static bool showFooter = true;

        if (ImGui::BeginMainMenuBar()) // <- Nav Bar
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

        if (showNavigationBar) // <- Nav Bar
        {
            static ImGuiWindowFlags navigationFlags = ImGuiWindowFlags_None;
            ImGui::Begin("NavigationBar", &showNavigationBar, navigationFlags);
                ImGui::Text("Navigation Bar");
            ImGui::End();
        }
        
        ////// Explorer //////
        static Files::File* selectedFile = nullptr;
        static float horizontalPadding = 16.0f;
        static float verticalPadding = 16.0f;
        static float thumbnailSize = 128.0f;
        float horizontalCellSize = thumbnailSize + horizontalPadding;
        float verticalCellSize = thumbnailSize + verticalPadding;
        float panelWidth = ImGui::GetContentRegionAvail().x;
        float panelHeight = ImGui::GetContentRegionAvail().y;
        int columnCount = std::max((int)(panelWidth / horizontalCellSize), 1);
        
        static ImGuiWindowFlags explorerFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("Explorer", &showExplorer, explorerFlags);
            ImGui::Columns(columnCount, 0, false); 
            bool wasAnyFileClicked = false;

            // Listing all files
            Files::FileList allFilesInDirectory = appFileManager.GetAllFiles();
            auto fileIt = allFilesInDirectory.begin();
            // for (Files::File content : appFileManager.GetAllFiles())
            for (fileIt; fileIt != allFilesInDirectory.end(); fileIt++)
            {
                // ImGui::Button(content.name.c_str(), { horizontalCellSize, verticalCellSize });
                // if (selectedFile == &content)
                //     ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_ButtonHovered]);
                // ImGui::Button(content.name.c_str(), { thumbnailSize, thumbnailSize });
                ImGui::Button((*fileIt).name.c_str(), { thumbnailSize, thumbnailSize });
                if (ImGui::IsItemHovered())
                {
                    if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                    {
                        wasAnyFileClicked = true;
                        FEOS_INFO("Selected file {}", (*fileIt).name.c_str());
                        selectedFile = &(*fileIt);
                    }
                    else if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                    {
                        wasAnyFileClicked = true;
                        FEOS_INFO("Right Clicked at {}", (*fileIt).name.c_str());
                        selectedFile = &(*fileIt);
                        ImGui::OpenPopup("RightClickFileMenu");
                    }

                    if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                    {
                        wasAnyFileClicked = true;
                        FEOS_INFO("Double Clicked at {}", (*fileIt).name.c_str());
                    }
                }
                ImGui::Text((*fileIt).name.c_str());
                
                // if (selectedFile == &content)
                //     ImGui::PopStyleColor();
                if (selectedFile)
                    // FEOS_DEBUG("selectedFile{}", selectedFile->name);
                    FEOS_DEBUG("selectedFile({}) == &content({}) {}", selectedFile->name, (*fileIt).name, selectedFile == &(*fileIt));
                ImGui::NextColumn();
                // ImGui::PopID();
            }
            
            if (!wasAnyFileClicked)
            {
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                {
                    FEOS_INFO("Left Clicked at Explorer");
                    selectedFile = nullptr;
                }
                else if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                {
                    FEOS_INFO("Right Clicked at Explorer");
                    selectedFile = nullptr;
                    ImGui::OpenPopup("RightClickMenu");
                }
            }
            
            if (ImGui::BeginPopup("RightClickFileMenu"))
            {
                if (ImGui::BeginMenu("View"))
                {
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Group by"))
                {
                    ImGui::EndMenu();
                }
                ImGui::Separator();
                if (ImGui::Button("Cut")) { }
                if (ImGui::Button("Move")) { }
                ImGui::Separator();
                if (ImGui::Button("Rename")) { }
                ImGui::EndPopup();
            }
            else if (ImGui::BeginPopup("RightClickMenu"))
            {
                if (ImGui::BeginMenu("View"))
                {
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Group by"))
                {
                    ImGui::EndMenu();
                }
                ImGui::Separator();
                // if (ImGui::Button("Paste", false, false)) { }
                if (ImGui::Button("Paste")) { }
                ImGui::Separator();
                if (ImGui::BeginMenu("Group by"))
                {
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Create new"))
                {
                    if (ImGui::Button("Directory")) { }
                    if (ImGui::Button("File")) { }
                    ImGui::EndMenu();
                }
                ImGui::EndPopup();
            }

            ImGui::Columns(1, 0, false);
            ImGui::SliderFloat("Thumbnail Size", &thumbnailSize, 16, 512);
		    ImGui::SliderFloat("Horizontal Padding", &horizontalPadding, 0, 32);
		    ImGui::SliderFloat("Vertical Padding", &verticalPadding, 0, 32);
        ImGui::End();
        ////////////

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
