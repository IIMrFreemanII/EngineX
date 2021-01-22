#include "OpenGLContext.h"
#include "EngineX/Log.h"
#include "glad/glad.h"

namespace EngineX {

    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        if (!windowHandle) {
            EX_CORE_ERROR("Window handle is null!");
        }
    }

    void OpenGLContext::Init() {
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
        if (!status) {
            EX_CORE_ERROR("Failed to initialize Glad!");
        }

        EX_CORE_INFO("OpenGL Info:");
        EX_CORE_INFO("  Vendor: {0}", glGetString(GL_VENDOR));
        EX_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
        EX_CORE_INFO("  Version: {0}", glGetString(GL_VERSION));
    }

    void OpenGLContext::SwapBuffers() {
        glfwSwapBuffers(m_WindowHandle);
    }
}