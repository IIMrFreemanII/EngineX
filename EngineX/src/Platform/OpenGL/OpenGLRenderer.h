#pragma once

#include "glm/glm.hpp"
#include "OpenGLShader.h"
#include "OpenGLVertexArray.h"
#include "EngineX/Mesh.h"

namespace EngineX {

    class OpenGLRenderer {
    public:
        static void Init();
        static void SetClearColor(const glm::vec4& color);
        static void Clear();
        static void SetViewport(int x, int y, int width, int height);
        static void DrawIndexed(const Ref<OpenGLVertexArray>& vertexArray);
        static void Begin();
        static void End();
        static void Submit(
                const Ref<OpenGLShader>& shader,
                const Ref<Mesh>& mesh,
                const glm::mat4& transform = glm::mat4(1.0f)
        );
    };
}