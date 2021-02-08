#pragma once

#include "OpenGLRendererAPI.h"
#include "glm/glm.hpp"
#include "OpenGLFrameBuffer.h"

namespace EngineX {

    class OpenGLRenderer {
    public:
        OpenGLRenderer();
        ~OpenGLRenderer();

        void BeginScene();
        void EndScene();
        void OnUpdate();

        inline OpenGLFrameBuffer& GetFrameBuffer() { return *m_FrameBuffer; }

    private:
        OpenGLRendererAPI m_RenderAPI;
        Scope<OpenGLFrameBuffer> m_FrameBuffer;

        glm::vec4 m_ClearColor;
        unsigned int shaderProgram;
        unsigned int VBO, VAO;
    };
}