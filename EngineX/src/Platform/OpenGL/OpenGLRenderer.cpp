#include "OpenGLRenderer.h"

#include "EngineX/Application.h"
#include <glad/glad.h>

namespace EngineX {

    void OpenGLRenderer::Begin()
    {
        // init scene data
    }

    void OpenGLRenderer::End()
    {
        // render submitted objects
    }

    void OpenGLRenderer::Init()
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRenderer::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderer::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderer::SetViewport(int x, int y, int width, int height)
    {
        glViewport(x, y, width, height);
    }

    void OpenGLRenderer::DrawIndexed(const Ref <OpenGLVertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRenderer::Submit(
            const Ref <OpenGLShader>& shader,
            const Ref <OpenGLVertexArray>& vertexArray,
            const glm::mat4& transform
    )
    {
        shader->Bind();
        // set view and projection matrix for shader
        // set transform matrix for shader

        vertexArray->Bind();
        DrawIndexed(vertexArray);
    }

}
