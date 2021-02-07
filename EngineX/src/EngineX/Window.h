#pragma once

#include "GLFW/glfw3.h"
#include "EngineX/Renderer/GraphicsContext.h"
#include <string>

namespace EngineX
{

    struct WindowProps
    {
        std::string Title;
        unsigned int Width;
        unsigned int Height;
        bool VSync;

        WindowProps(
                const std::string& title = "EngineX",
                unsigned int width = 1280,
                unsigned int height = 720
        ) : Title(title), Width(width), Height(height)
        {}
    };

    class Window {
    public:
        Window(const WindowProps& props);
        ~Window();

        void OnUpdate();

        inline unsigned int GetWidth() const { return m_Props.Width; };
        inline unsigned int GetHeight() const { return m_Props.Height; };
        inline GLFWwindow* GetNativeWindow() const { return m_Window; };

        void SetVSync(bool enabled);
        bool IsVSync() const;

    private:
        void Shutdown();

    private:
        GLFWwindow* m_Window;
        WindowProps m_Props;
        GraphicsContext* m_Context;
    };

}