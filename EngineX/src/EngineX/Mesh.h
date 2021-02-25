#pragma once

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <vector>
#include <glm/glm.hpp>

#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Core.h"
#include "Vertex.h"

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
                    { OpenGLShaderDataType::Float3, "aPosition" },
                    { OpenGLShaderDataType::Float3, "aNormal" }
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

        // Temp solution
        // Only works for object with single child with mesh inside
        static Mesh* LoadFromFile(const std::string& path)
        {
            Assimp::Importer importer;
            const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate);

            if (!scene || !scene->mRootNode) {
                EX_CORE_ASSERT(false, "Failed to load Mesh from path: " + path);
                return nullptr;
            }

            std::vector<Vertex> vertices;
            std::vector<uint32_t> indices;

            aiNode* node = scene->mRootNode->mChildren[0];
//            EX_CORE_INFO("Meshes amount: {0}", node->mNumMeshes);
//            EX_CORE_INFO("Node children: {0}", node->mNumChildren);
            aiMesh* mesh = scene->mMeshes[node->mMeshes[0]];
//            EX_CORE_INFO("Mesh vertices amount: {0}", mesh->mNumVertices);
//

            vertices.reserve(mesh->mNumVertices);
            for (uint32_t i = 0; i < mesh->mNumVertices; ++i) {
                Vertex vertex{};

                vertex.Position = *((glm::vec3*)&mesh->mVertices[i]);
                vertex.Normal = *((glm::vec3*)&mesh->mNormals[i]);

                vertices.push_back(vertex);
//                EX_CORE_INFO("Position x:{0} y:{1} z:{2}", vertex.Position.x, vertex.Position.y, vertex.Position.z);
//                EX_CORE_INFO("Normal x:{0} y:{1} z:{2}", vertex.Normal.x, vertex.Normal.y, vertex.Normal.z);
            }

//            EX_CORE_INFO("mNumFaces: {0}", mesh->mNumFaces);
//            EX_CORE_INFO("mNumIndices: {0}", mesh->mFaces[0].mNumIndices);

            indices.reserve(mesh->mNumFaces * mesh->mFaces[0].mNumIndices);
            for (uint32_t i = 0; i < mesh->mNumFaces; ++i) {
                aiFace face = mesh->mFaces[i];

                for (uint32_t j = 0; j < face.mNumIndices; ++j) {
                    indices.push_back(face.mIndices[j]);
                }
            }

            return Create(vertices, indices);
        }
    };

}