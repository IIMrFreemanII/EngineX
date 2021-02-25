#pragma once
#include "Window.h"
#include "Editor/Editor.h"
#include "Scene.h"
#include "Platform/OpenGL/OpenGLRenderer.h"
#include <memory>

namespace EngineX {

    class Application {
    public:
        Application();
        ~Application();

        void Run();
        void Close();

        inline static Application& Get() { return *s_Instance; }

        inline Window& GetWindow() const { return *m_Window; }
        inline Scene& GetScene() const { return *m_Scene; }
        inline Editor& GetEditor() const { return *m_Editor; }

        void OnUpdate();

    public:
        float deltaTime;

    private:
        Scope<Window> m_Window;
        Scope<Editor> m_Editor;
        Scope<Scene> m_Scene;

        float m_LastFrameTime = 0.0f;

    private:
        static Application* s_Instance;
    };

}