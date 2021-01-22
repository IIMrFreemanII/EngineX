#pragma once

#include "EngineX/Renderer/GraphicsContext.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace EngineX
{

    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    private:
        GLFWwindow* m_WindowHandle;
    };

}