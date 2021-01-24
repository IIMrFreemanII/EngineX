#pragma once

#include "glm/glm.hpp"

namespace EngineX {
    class OpenGLRendererAPI {
    public:
        OpenGLRendererAPI();
        ~OpenGLRendererAPI();

        void SetClearColor(const glm::vec4& color);
        void Clear();
    };
}