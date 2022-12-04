#include "FileExplorer/UI/UI.h"
#include "FileExplorer/Core/Application.h"

#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
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
        ImGui_ImplOpenGL3_Init("#version 410");

        // TODO: Fonts

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

    }

    void UI::Begin()
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // if (m_ShowDemo)
        //     ImGui::ShowDemoWindow(&m_ShowDemo);

        // {
        //     ImGui::Begin("Main Content!");

        //     ImGui::Text("Text Goes Here");
        //     ImGui::Checkbox("Demo Window", &m_ShowDemo);
        //     ImGui::Checkbox("Another Window", &m_ShowAnotherWindow);

        //     ImGui::SameLine();
         
        //     ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        //     ImGui::End();
        // }

        // if (m_ShowAnotherWindow)
        // {
        //     ImGui::Begin("Another Window", &m_ShowAnotherWindow);
        //     ImGui::Text("Hello ImGui!!!");
        //     if (ImGui::Button("Close Me"))
        //         m_ShowAnotherWindow = false;
        //     ImGui::End();
        // }
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

    void UI::SetTheme()
    {

    }
}