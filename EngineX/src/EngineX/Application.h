#pragma once
#include "Window.h"
#include "Editor/Editor.h"
#include "Platform/OpenGL/OpenGLRenderer.h"
#include <memory>

namespace EngineX {

    class Application {
    public:
        Application();
        ~Application();

        void Run();

        inline Window& GetWindow() const { return *m_Window; }
        inline OpenGLRenderer& GetRenderer() const { return *m_Renderer; }
        inline Editor& GetEditor() const { return *m_Editor; }
        inline static Application& Get() { return *s_Instance; }

//    private:
//        void Terminate();

    private:
        std::unique_ptr<Window> m_Window;
        std::unique_ptr<Editor> m_Editor;
        std::unique_ptr<OpenGLRenderer> m_Renderer;

        float m_LastFrameTime = 0.0f;

    private:
        static Application* s_Instance;
    };

}