#include "OpenGLVertexArray.h"
#include <glad/glad.h>

namespace EngineX {

    static GLenum ShaderDataTypeToOpenGLBaseType(OpenGLShaderDataType type)
    {
        switch (type)
        {
            case OpenGLShaderDataType::Float:    return GL_FLOAT;
            case OpenGLShaderDataType::Float2:   return GL_FLOAT;
            case OpenGLShaderDataType::Float3:   return GL_FLOAT;
            case OpenGLShaderDataType::Float4:   return GL_FLOAT;
            case OpenGLShaderDataType::Mat3:     return GL_FLOAT;
            case OpenGLShaderDataType::Mat4:     return GL_FLOAT;
            case OpenGLShaderDataType::Int:      return GL_INT;
            case OpenGLShaderDataType::Int2:     return GL_INT;
            case OpenGLShaderDataType::Int3:     return GL_INT;
            case OpenGLShaderDataType::Int4:     return GL_INT;
            case OpenGLShaderDataType::Bool:     return GL_BOOL;
        }

        EX_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_RendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_RendererID);
    }
    
    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_RendererID);
    }

    void OpenGLVertexArray::UnBind() const
    {
        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<OpenGLVertexBuffer>& vertexBuffer)
    {
        EX_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

        glBindVertexArray(m_RendererID);
        vertexBuffer->Bind();

        const auto& layout = vertexBuffer->GetLayout();
        for (const auto& element : layout) {
            glEnableVertexAttribArray(m_VertexBufferIndex);
            glVertexAttribPointer(
                    m_VertexBufferIndex,
                    element.GetComponentCount(),
                    ShaderDataTypeToOpenGLBaseType(element.Type),
                    element.Normalized ? GL_TRUE : GL_FALSE,
                    layout.GetStride(),
                    (const void*) (intptr_t) element.Offset
            );
            m_VertexBufferIndex++;
        }
        m_VertexBuffers.push_back(vertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const Ref<OpenGLIndexBuffer>& indexBuffer)
    {
        glBindVertexArray(m_RendererID);
        indexBuffer->Bind();

        m_IndexBuffer = indexBuffer;
    }

    OpenGLVertexArray* OpenGLVertexArray::Create()
    {
        return new OpenGLVertexArray();
    }

}
