#pragma once
#include "Window.h"
#include <memory>

namespace EngineX {

    class Application {
    public:
        Application();
        ~Application();

        void Run();

        inline Window& GetWindow() const { return *m_Window; }
        inline static Application& Get() { return *s_Instance; }

    private:
        void Terminate();

    private:
        std::unique_ptr<Window> m_Window;
        float m_LastFrameTime = 0.0f;
    private:
        static Application* s_Instance;
    };

}