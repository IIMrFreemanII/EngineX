#pragma once

#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Core.h"
#include "Vertex.h"
#include <glm/glm.hpp>
#include <vector>

namespace EngineX
{

    class Mesh
    {

    public:
        std::vector<Vertex> Vertices;
        std::vector<uint32_t> Indices;

        Ref<OpenGLVertexArray> m_VertexArray;

        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
                : Vertices(vertices), Indices(indices)
        {
            m_VertexArray.reset(OpenGLVertexArray::Create());

            Ref<OpenGLVertexBuffer> vertexBuffer;
            // size = bytes
            vertexBuffer.reset(OpenGLVertexBuffer::Create(vertices.data(), vertices.size() * sizeof(Vertex)));
            OpenGLBufferLayout layout = {
                    { OpenGLShaderDataType::Float3, "aPos" }
            };
            vertexBuffer->SetLayout(layout);
            m_VertexArray->AddVertexBuffer(vertexBuffer);

            Ref<OpenGLIndexBuffer> indexBuffer;
            // size = count
            indexBuffer.reset(OpenGLIndexBuffer::Create(indices.data(), indices.size()));
            m_VertexArray->SetIndexBuffer(indexBuffer);
        }

        // temp
        Mesh(const Mesh& mesh) = delete;
        // temp
        Mesh& operator= (const Mesh& mesh) = delete;

        static Mesh* Create(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
        {
            return new Mesh(vertices, indices);
        }

    };

}