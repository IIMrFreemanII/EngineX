#include "Application.h"

#include <memory>
#include "Log.h"

namespace EngineX {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        EX_PROFILE_BEGIN_SESSION("EngineXSession", "EngineXProfile.json");

        if (s_Instance) {
            EX_CORE_ERROR("Application already exists!");
            return;
        }

        s_Instance = this;

        Log::Init();
        EX_CORE_INFO("Welcome to EngineX!");
        EX_WARN("Welcome to Sandbox App!");

        m_Window = std::make_unique<Window>(WindowProps());
        m_Renderer = std::make_unique<OpenGLRenderer>();
        m_Editor = std::make_unique<Editor>();
    }

    Application::~Application() {
        EX_PROFILE_END_SESSION();
    }

    void Application::Run() {
        while (!glfwWindowShouldClose((GLFWwindow*)m_Window->GetNativeWindow())) {
            // handle time
            float currentFrame = glfwGetTime();
            float deltaTime = currentFrame - m_LastFrameTime;
            m_LastFrameTime = currentFrame;
            //----------------

            // handle render
            m_Renderer->OnUpdate();
            //-----------------

            // handle editor
            m_Editor->Begin();
            m_Editor->OnImGuiRender();
            m_Editor->End();
            //--------------

            // handle window
            m_Window->OnUpdate();
            //---------------
        }
    }
}
