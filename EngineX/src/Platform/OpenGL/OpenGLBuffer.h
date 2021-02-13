#pragma once

namespace EngineX {

    enum class ShaderDataType
    {
        Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch (type)
        {
            case ShaderDataType::Float:    return 4;
            case ShaderDataType::Float2:   return 4 * 2;
            case ShaderDataType::Float3:   return 4 * 3;
            case ShaderDataType::Float4:   return 4 * 4;
            case ShaderDataType::Mat3:     return 4 * 3 * 3;
            case ShaderDataType::Mat4:     return 4 * 4 * 4;
            case ShaderDataType::Int:      return 4;
            case ShaderDataType::Int2:     return 4 * 2;
            case ShaderDataType::Int3:     return 4 * 3;
            case ShaderDataType::Int4:     return 4 * 4;
            case ShaderDataType::Bool:     return 1;
        }

        EX_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

    struct OpenGLBufferElement {
        std::string Name;
        ShaderDataType Type;
        uint32_t Size;
        uint32_t Offset;
        bool Normalized;

        OpenGLBufferElement() {}

        OpenGLBufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
                : Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalized(normalized)
        {

        }

        uint32_t GetComponentCount() const {
            switch (Type)
            {
                case ShaderDataType::Float:   return 1;
                case ShaderDataType::Float2:  return 2;
                case ShaderDataType::Float3:  return 3;
                case ShaderDataType::Float4:  return 4;
                case ShaderDataType::Mat3:    return 3 * 3;
                case ShaderDataType::Mat4:    return 4 * 4;
                case ShaderDataType::Int:     return 1;
                case ShaderDataType::Int2:    return 2;
                case ShaderDataType::Int3:    return 3;
                case ShaderDataType::Int4:    return 4;
                case ShaderDataType::Bool:    return 1;
            }

            EX_CORE_ASSERT(false, "Unknown ShaderDataType!");
            return 0;
        }
    };

    class OpenGLBufferLayout
    {
    public:
        OpenGLBufferLayout() {}
        OpenGLBufferLayout(const std::initializer_list<OpenGLBufferElement>& elements)
            : m_Elements(elements)
        {
            CalculateOffsetsAndStride();
        }

        inline uint32_t GetStride() const { return m_Stride; }
        inline const std::vector<OpenGLBufferElement>& GetElements() const { return m_Elements; }

        std::vector<OpenGLBufferElement>::iterator begin() { return m_Elements.begin(); }
        std::vector<OpenGLBufferElement>::iterator end() { return m_Elements.end(); }
        std::vector<OpenGLBufferElement>::const_iterator begin() const { return m_Elements.begin(); }
        std::vector<OpenGLBufferElement>::const_iterator end() const { return m_Elements.end(); }

    private:
        void CalculateOffsetsAndStride()
        {
            uint32_t offset = 0;
            m_Stride = 0;
            for (auto& element : m_Elements)
            {
                element.Offset = offset;
                offset += element.Size;
                m_Stride += element.Size;
            }
        }
    private:
        std::vector<OpenGLBufferElement> m_Elements;
        uint32_t m_Stride;
    };

    class OpenGLVertexBuffer {

    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        ~OpenGLVertexBuffer();

        void Bind() const;
        void UnBind() const;

        const OpenGLBufferLayout& GetLayout() const { return m_Layout; }
        void SetLayout(const OpenGLBufferLayout& layout) { m_Layout = layout; }
        static OpenGLVertexBuffer* Create(float* vertices, uint32_t size);

    private:
        uint32_t m_RendererID;
        OpenGLBufferLayout m_Layout;

    };

    class OpenGLIndexBuffer {

    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        ~OpenGLIndexBuffer();

        void Bind() const;
        void UnBind() const;

        static OpenGLIndexBuffer* Create(uint32_t* indices, uint32_t size);
        uint32_t GetCount() const { return m_Count; }

    private:
        uint32_t m_RendererID;
        uint32_t m_Count;

    };

}