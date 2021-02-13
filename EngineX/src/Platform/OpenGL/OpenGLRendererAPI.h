#pragma once

#include "glm/glm.hpp"
#include "OpenGLVertexArray.h"

namespace EngineX {
    class OpenGLRendererAPI {

    public:
        OpenGLRendererAPI();
        ~OpenGLRendererAPI() = default;

        void SetClearColor(const glm::vec4& color);
        void Clear();
        void DrawIndexed(const Ref<OpenGLVertexArray>& vertexArray);

    };
}