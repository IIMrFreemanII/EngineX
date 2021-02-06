#include "Editor.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "EngineX/Log.h"

#include "EngineX/Application.h"

namespace EngineX
{

    Editor::Editor()
    {
        EX_PROFILE_FUNCTION();

// Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        (void) io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
        //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
        //io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsClassic();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        Application& app = Application::Get();
        GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

        // Setup Platform/Renderer bindings
        ImGui_ImplGlfw_InitForOpenGL(window, true);
        ImGui_ImplOpenGL3_Init("#version 410");

        sceneEditor = std::make_unique<SceneEditor>();
    }

    Editor::~Editor()
    {
        EX_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
    }

    void Editor::OnImGuiRender()
    {
        EX_PROFILE_FUNCTION();

//        ImGuiID dockSpaceId = ImGui::GetID("MyDockSpace");
//        ImGui::DockSpace(dockSpaceId);

        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Scene");
        {
            sceneEditor->Width = (int)ImGui::GetWindowWidth();
            sceneEditor->Height = (int)ImGui::GetWindowHeight();

//            EX_CORE_INFO("Scene width: {0}, height: {1}", sceneEditor->Width, sceneEditor->Height);

            ImVec2 pos = ImGui::GetCursorScreenPos();

            ImDrawList* drawList = ImGui::GetWindowDrawList();
            drawList->AddImage((void*)Application::Get().GetRenderer().GetTextureColorBuffer(),
                               pos,
                               ImVec2(pos.x + (float)sceneEditor->Width, pos.y + (float)sceneEditor->Height),
                               ImVec2(0, 1),
                               ImVec2(1, 0)
            );
        }
        ImGui::End();
        ImGui::PopStyleVar(1);
    }

    void Editor::Begin()
    {
        EX_PROFILE_FUNCTION();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
    }

    void Editor::End()
    {
        EX_PROFILE_FUNCTION();

        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        io.DisplaySize = ImVec2((float) app.GetWindow().GetWidth(), (float) app.GetWindow().GetHeight());

        // Rendering
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }
    }
}