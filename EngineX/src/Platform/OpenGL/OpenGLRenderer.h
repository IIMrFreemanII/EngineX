#pragma once

#include "OpenGLRendererAPI.h"
#include <memory>
#include "glm/glm.hpp"

namespace EngineX {

    class OpenGLRenderer {
    public:
        OpenGLRenderer();
        ~OpenGLRenderer();

        void BeginScene();
        void EndScene();
        void OnUpdate();

        inline unsigned int GetTextureColorBuffer() const { return textureColorBuffer; };

    private:
        OpenGLRendererAPI m_RenderAPI;
        glm::vec4 m_ClearColor;
        unsigned int shaderProgram;
        unsigned int VBO, VAO;

        glm::vec2 framebufferSize = {0.0f, 0.0f};
        unsigned int framebuffer;
        unsigned int textureColorBuffer;
        unsigned int rbo;

    private:
        void ResizeFrameBuffer(const glm::vec2& size);
    };
}