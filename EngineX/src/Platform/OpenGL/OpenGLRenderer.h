#pragma once

#include "glm/glm.hpp"
#include "OpenGLShader.h"
#include "OpenGLVertexArray.h"

namespace EngineX {

    class OpenGLRenderer {
    public:
        static void Init();
        static void SetClearColor(const glm::vec4& color);
        static void Clear();
        static void SetViewport(int x, int y, int width, int height);
        static void DrawIndexed(const Ref<OpenGLVertexArray>& vertexArray);
        static void BeginScene();
        static void EndScene();
        static void Submit(
                const Ref<OpenGLShader>& shader,
                const Ref<OpenGLVertexArray>& vertexArray,
                const glm::mat4& transform = glm::mat4(1.0f)
        );

//        inline OpenGLFrameBuffer& GetFrameBuffer() { return *m_FrameBuffer; }

//    private:
//        OpenGLRendererAPI m_RenderAPI;
//        Scope<OpenGLFrameBuffer> m_FrameBuffer;

//        glm::vec4 m_ClearColor;
//        unsigned int shaderProgram;
//        unsigned int VBO, VAO;
    };
}