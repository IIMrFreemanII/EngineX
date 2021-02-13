#pragma once
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace EngineX {

    class Scene {

    public:
        Scene();
        ~Scene() = default;

        void Begin();
        void End();

        void OnUpdate();

        inline OpenGLFrameBuffer& GetFrameBuffer() const { return *m_FrameBuffer; }

    private:
        Scope<OpenGLFrameBuffer> m_FrameBuffer;

    private:
        Ref<OpenGLShader> m_Shader;
        Ref<OpenGLVertexArray> m_VertexArray;

    };

}
