#include "feospch.h"

#include "FileExplorer/UI/UI.h"
#include "FileExplorer/Core/Application.h"

#include <imgui.h>
#include <backends/imgui_impl_opengl3.h>
#include <backends/imgui_impl_glfw.h>
#include <GLFW/glfw3.h>


namespace FEOS
{
    UI::UI()
        : Layer("UI")
    {
    }

    void UI::OnAttach()
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();

        ImGuiIO& io = ImGui::GetIO(); (void)io;

        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard
                        | ImGuiConfigFlags_DockingEnable
                        | ImGuiConfigFlags_ViewportsEnable;

        // TODO: Temporary
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }
        //

        GLFWwindow* window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 430 core");
        
        // TODO: Fonts
        io.Fonts->Build();
        //
    }

    void UI::OnDetach()
    {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void UI::OnEvent(Event::Event& e)
    {
        ImGuiIO& io = ImGui::GetIO();

        e.Handled = e.IsInCategory(Event::MouseCategory) & io.WantCaptureMouse;
        e.Handled = e.IsInCategory(Event::KeyboardCategory) & io.WantCaptureKeyboard;
    }

    void UI::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
     
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
    }

    void UI::End()
    {
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGuiIO& io = ImGui::GetIO(); (void)io;

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }

    void UI::OnUIDraw()
    {        
        static bool showDemo = true;

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
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("Background");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspaceFlags);
        }
        
        ImGui::ShowDemoWindow(&showDemo);

        if (ImGui::BeginMenuBar())
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

            if (ImGui::SmallButton("New Folder")) {}
    
            ImGui::EndMenuBar();
        }

        ImGui::End(); // <- END
    }

    void UI::SetTheme()
    {

    }
}