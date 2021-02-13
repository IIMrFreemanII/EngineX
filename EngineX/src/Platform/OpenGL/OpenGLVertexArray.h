#pragma once

#include "OpenGLBuffer.h"

namespace EngineX {

    class OpenGLVertexArray {

    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();

        void Bind() const;
        void UnBind() const;

        void AddVertexBuffer(const Ref<OpenGLVertexBuffer>& vertexBuffer);
        void SetIndexBuffer(const Ref<OpenGLIndexBuffer>& indexBuffer);

        const std::vector<Ref<OpenGLVertexBuffer>>& GetVertexBuffers() const { return m_VertexBuffers; };
        const Ref<OpenGLIndexBuffer>& GetIndexBuffer() const { return m_IndexBuffer; };

        static OpenGLVertexArray* Create();

    private:
        uint32_t m_RendererID;
        uint32_t m_VertexBufferIndex = 0;
        std::vector<Ref<OpenGLVertexBuffer>> m_VertexBuffers;
        Ref<OpenGLIndexBuffer> m_IndexBuffer;

    };

}
