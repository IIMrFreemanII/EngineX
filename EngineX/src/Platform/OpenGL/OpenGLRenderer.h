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

        unsigned int framebuffer;
        unsigned int textureColorBuffer;
        unsigned int rbo;

    private:
        void ResizeFrameBuffer(unsigned int width, unsigned int height) const;
    };
}