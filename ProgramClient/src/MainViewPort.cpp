#include "feospch.h"

#include "MainViewPort.h"

#include <imgui.h>


namespace FEOS
{
    ViewPort::ViewPort()
        : Layer("ViewPort")
    { }

    ViewPort::~ViewPort()
    { }

    void ViewPort::OnAttach()
    {
        m_ShouldReloadFiles = false;
        m_AllFilesInDirectory = Application::Get().GetFileManager().GetAllFiles();

        m_SelectedFile = NONE_FILE_SELECTED;

        m_ActionType = NoneAction;
    }

    void ViewPort::OnDetach()
    {

    }

    void ViewPort::OnUpdate()
    {
        if (m_ShouldReloadFiles)
        {
            m_AllFilesInDirectory = Application::Get().GetFileManager().GetAllFiles();
        }

        if (ImGui::IsKeyPressed(ImGuiKey_Escape))
        {
            m_SelectedFile = NONE_FILE_SELECTED;
            m_ActionType = NoneAction;
        }
    }

    #define DISABLE_UI_ON_COND(cond, disableCode) \
        if (!(cond)) ImGui::BeginDisabled(); \
        disableCode; \
        if (!(cond)) ImGui::EndDisabled();

    void ViewPort::OnUIDraw()
    {
        FEOS_EXPLORER_ASSERT(ImGui::GetCurrentContext() != nullptr, "Missing dear imgui context. Refer to examples app!");
        Files::Manager& appFileManager = Application::Get().GetFileManager();

        static bool dockspaceOpen = true;
        static bool fullScreen = true;
        ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_None;

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

        if (ImGui::BeginMainMenuBar()) // <- Nav Bar
        {   
            if (ImGui::BeginMenu("Organize"))
            {
                if (ImGui::MenuItem("Cut", "CTRL+X")) {}
                if (ImGui::MenuItem("Copy", "CTRL+C", false, false)) {}
                if (ImGui::MenuItem("Paste", "CTRL+V", false, false)) {}
                if (ImGui::MenuItem("Undo", "CTRL+Z", false, false)) {}
                if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Select All")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Layout")) {}
                if (ImGui::MenuItem("Folder and Search Options")) {}
                ImGui::Separator();
                if (ImGui::MenuItem("Delete", "Delete", false, false)) {}
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

                if (ImGui::MenuItem("Search", "CTRL+F")) {}

                ImGui::EndMenu();
            }

            if (ImGui::SmallButton("New Folder")) {}
    
            ImGui::EndMainMenuBar();
        }

        if (showNavigationBar) // <- Nav Bar
        {
            ImGuiWindowFlags navigationFlags = ImGuiWindowFlags_None;
            ImGui::Begin("NavigationBar", &showNavigationBar, navigationFlags);
                ImGui::Text("Navigation Bar");
            ImGui::End();
        }
        
        ////// Explorer //////
        static float horizontalPadding = 16.0f;
        static float verticalPadding = 16.0f;
        static float thumbnailSize = 128.0f;
        float horizontalCellSize = thumbnailSize + horizontalPadding;
        float verticalCellSize = thumbnailSize + verticalPadding;
        float panelWidth = ImGui::GetContentRegionAvail().x;
        float panelHeight = ImGui::GetContentRegionAvail().y;
        int columnCount = std::max((int)(panelWidth / horizontalCellSize), 1);
        bool popSelectedStyle = false;

        ImGuiWindowFlags explorerFlags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse;
        ImGui::Begin("Explorer", &showExplorer, explorerFlags);
            ImGui::Columns(columnCount, 0, false); 
            bool wasAnyFileClicked = false;

            // Listing all files
            for (int32_t fileIt = 2; fileIt < m_AllFilesInDirectory.size(); fileIt++)
            {
                Files::File& currentFile = m_AllFilesInDirectory[fileIt];

                // ImGui::Button(content.name.c_str(), { horizontalCellSize, verticalCellSize });
                bool popSelectedStyle = false;
                if (m_SelectedFile == fileIt)
                {
                    ImGui::PushStyleColor(ImGuiCol_Button, style.Colors[ImGuiCol_ButtonHovered]);
                    popSelectedStyle = true;
                }
                ImGui::Button(currentFile.name.c_str(), { thumbnailSize, thumbnailSize });
                if (ImGui::IsItemHovered())
                {
                    if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
                    {
                        wasAnyFileClicked = true;
                        FEOS_INFO("Double Clicked at {}", currentFile.name.c_str());
                        m_SelectedFile = fileIt;
                    }
                    else if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                    {
                        wasAnyFileClicked = true;
                        FEOS_INFO("Selected file {}", currentFile.name.c_str());
                        m_SelectedFile = fileIt;
                    }
                    else if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                    {
                        wasAnyFileClicked = true;
                        FEOS_INFO("Right Clicked at {}", currentFile.name.c_str());
                        m_SelectedFile = fileIt;
                        ImGui::OpenPopup("RightClickFileMenu");
                    }
                }
                ImGui::Text(currentFile.name.c_str());
                
                if (popSelectedStyle)
                    ImGui::PopStyleColor();
                ImGui::NextColumn();
            }
            
            if (!wasAnyFileClicked && ImGui::IsWindowHovered())
            {
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
                {
                    FEOS_INFO("Left Clicked at Explorer");
                    m_SelectedFile = NONE_FILE_SELECTED;
                }
                else if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                {
                    FEOS_INFO("Right Clicked at Explorer");
                    m_SelectedFile = NONE_FILE_SELECTED;
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
                if (ImGui::Button("Copy"))
                {
                    m_ActionType = CopyAction;
                    m_ActionFile = m_AllFilesInDirectory[m_SelectedFile];
                }
                if (ImGui::Button("Cut"))
                {
                    m_ActionType = MoveAction;
                    m_ActionFile = m_AllFilesInDirectory[m_SelectedFile];
                }
                ImGui::Separator();
                if (ImGui::Button("Create shortcut")) { }
                if (ImGui::Button("Delete")) { }
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
                
                DISABLE_UI_ON_COND(m_ActionType != NoneAction,
                    if (ImGui::Button("Paste"))
                    {
                        switch (m_ActionType)
                        {
                        case CopyAction:
                            break;
                        case MoveAction:
                            break;
                        }
                    }
                )
                DISABLE_UI_ON_COND(m_ActionType == CopyAction,
                    if (ImGui::Button("Paste Shortcut"))
                    {
                    }
                )

                ImGui::Separator();
                
                if (ImGui::BeginMenu("Group by"))
                {
                    ImGui::EndMenu();
                }
                if (ImGui::BeginMenu("Create new"))
                {
                    if (ImGui::Button("Directory")) { }
                    if (ImGui::Button("File")) 
                    {
                        Files::File newFile = appFileManager.CreateFile_("New file.txt");
                        FEOS_WARN("Created New File: {}", newFile);
                        if (newFile.type != Files::FileType::NotFound)
                            m_AllFilesInDirectory.push_back(newFile);
                    }
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

        ImGui::End(); // <- END
    }

    void ViewPort::OnEvent(Event::Event& e)
    {

    }
}
