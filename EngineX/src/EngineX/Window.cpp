#include "Window.h"
#include "Log.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include <iostream>

namespace EngineX
{

    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int error, const char* description)
    {
        EX_CORE_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    Window::Window(const WindowProps& props)
    {
        m_Props = props;

        EX_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

        if (!s_GLFWInitialized) {
            int success = glfwInit();

            if (!success) {
                std::cout << "Could not initialize GLFW" << std::endl;
            }

            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, props.Title.c_str(), nullptr, nullptr);

        m_Context = new OpenGLContext(m_Window);
        m_Context->Init();

        glfwSetWindowUserPointer(m_Window, &m_Props);
        SetVSync(true);

        glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
            WindowProps& props = *(WindowProps*) glfwGetWindowUserPointer(window);

            props.Width = width;
            props.Height = height;
        });

//        glfwSetFramebufferSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
//        {
//            WindowProps& props = *(WindowProps*) glfwGetWindowUserPointer(window);
//            // make sure the viewport matches the new window dimensions; note that width and
//            // height will be significantly larger than specified on retina displays.
//            props.Width = width;
//            props.Height = height;
//            glViewport(0, 0, width, height);
//        });

        glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
            WindowProps& props = *(WindowProps*) glfwGetWindowUserPointer(window);
        });
    }

    Window::~Window()
    {
        Shutdown();
    }

    void Window::OnUpdate()
    {
        EX_PROFILE_FUNCTION();

        glfwPollEvents();
        m_Context->SwapBuffers();
    }

    bool Window::IsVSync() const
    {
        return m_Props.VSync;
    }

    void Window::Shutdown()
    {
        glfwDestroyWindow(m_Window);
        glfwTerminate();
    }

    void Window::SetVSync(bool enabled)
    {
        if (enabled) {
            glfwSwapInterval(1);
        } else {
            glfwSwapInterval(0);
        }

        m_Props.VSync = enabled;
    }

}
