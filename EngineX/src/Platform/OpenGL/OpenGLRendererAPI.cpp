#include "OpenGLRendererAPI.h"

#include "glad/glad.h"

namespace EngineX {

    OpenGLRendererAPI::OpenGLRendererAPI()
    {
        //  glEnable(GL_BLEND);
        //  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    OpenGLRendererAPI::~OpenGLRendererAPI()
    {

    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }
}