#include "Application.h"

#include <memory>
#include "Log.h"

namespace EngineX {

    Application* Application::s_Instance = nullptr;

    Application::Application()
    {
        if (s_Instance) {
            EX_CORE_ERROR("Application already exists!");
            return;
        }

        s_Instance = this;

        Log::Init();
        EX_CORE_INFO("Welcome to EngineX!");
        EX_WARN("Welcome to Sandbox App!");

        m_Window = std::make_unique<Window>(WindowProps());
    }

    Application::~Application() {}

    void Application::Run() {
        while (!glfwWindowShouldClose((GLFWwindow*)m_Window->GetNativeWindow())) {
            // handle time
            float currentFrame = glfwGetTime();
            float deltaTime = currentFrame - m_LastFrameTime;
            m_LastFrameTime = currentFrame;
            //----------------

            // handle window
            m_Window->OnUpdate();
            //---------------
        }
    }
}
