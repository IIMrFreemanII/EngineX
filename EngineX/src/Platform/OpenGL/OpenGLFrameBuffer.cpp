#include "OpenGLFrameBuffer.h"

#include "glad/glad.h"

namespace EngineX {

    OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferConfiguration& configuration)
        : m_Config(configuration)
    {
        EX_PROFILE_FUNCTION();

        EX_CORE_INFO("Framebuffer constructor configuration");

        // framebuffer configuration
        // -------------------------
        glGenFramebuffers(1, &m_Config.frameBuffer);
        glBindFramebuffer(GL_FRAMEBUFFER, m_Config.frameBuffer);
        // create a color attachment texture
        glGenTextures(1, &m_Config.textureColorBuffer);
        glBindTexture(GL_TEXTURE_2D, m_Config.textureColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Config.size.x, m_Config.size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_Config.textureColorBuffer, 0);
        // create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
        glGenRenderbuffers(1, &m_Config.rbo);
        glBindRenderbuffer(GL_RENDERBUFFER, m_Config.rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_Config.size.x, m_Config.size.y); // use a single renderbuffer object for both a depth AND stencil buffer.
        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_Config.rbo); // now actually attach it
        // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now

        EX_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is not complete");
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    OpenGLFrameBuffer::~OpenGLFrameBuffer()
    {
        glDeleteFramebuffers(1, &m_Config.frameBuffer);
        glDeleteRenderbuffers(1, &m_Config.rbo);
        glDeleteTextures(1, &m_Config.textureColorBuffer);
    }

    void OpenGLFrameBuffer::Resize(const glm::vec2& size)
    {
        m_Config.size = size;

        glBindFramebuffer(GL_FRAMEBUFFER, m_Config.frameBuffer);

        glBindTexture(GL_TEXTURE_2D, m_Config.textureColorBuffer);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
        glBindTexture(GL_TEXTURE_2D, 0);

        glBindRenderbuffer(GL_RENDERBUFFER, m_Config.rbo);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, size.x, size.y);
        glBindRenderbuffer(GL_RENDERBUFFER, 0);

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_Config.frameBuffer);
    }

    void OpenGLFrameBuffer::UnBind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFrameBuffer::HandleResize(const glm::vec2& sceneSize)
    {
        if (sceneSize != m_Config.size) {
            Resize(sceneSize);
        }
    }
}