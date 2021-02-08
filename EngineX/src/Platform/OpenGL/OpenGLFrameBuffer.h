#pragma once

#include "glm/glm.hpp"

namespace EngineX {

    struct FrameBufferConfiguration {
        glm::vec2 size;
        uint32_t frameBuffer;
        uint32_t textureColorBuffer;
        uint32_t rbo;                   // render buffer object
    };

    class OpenGLFrameBuffer {

    public:
        OpenGLFrameBuffer(const FrameBufferConfiguration& specification);
        ~OpenGLFrameBuffer();

        void HandleResize(const glm::vec2& sceneSize);
        uint32_t GetTextureColorBuffer() const { return m_Config.textureColorBuffer; };
        void Bind();
        void UnBind();

    private:
        FrameBufferConfiguration m_Config;

    private:
        void Resize(const glm::vec2& size);

    };
}