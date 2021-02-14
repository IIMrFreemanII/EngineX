#include "Scene.h"
#include "Platform/OpenGL/OpenGLRenderer.h"
#include "Application.h"

namespace EngineX {

    Scene::Scene()
    {
        Window& window = Application::Get().GetWindow();
        FrameBufferConfiguration configuration{};
        configuration.size = { window.GetWidth(), window.GetHeight() };

        m_FrameBuffer = std::make_unique<OpenGLFrameBuffer>(configuration);

        m_VertexArray.reset(OpenGLVertexArray::Create());

        float vertices[] =  {
                -0.5f, -0.5f, 0.0f, // left
                0.5f, -0.5f, 0.0f, // right
                0.0f, 0.5f, 0.0f  // top
        };

        Ref<OpenGLVertexBuffer> vertexBuffer;
        vertexBuffer.reset(OpenGLVertexBuffer::Create(vertices, sizeof(vertices)));
        OpenGLBufferLayout layout = {
                { OpenGLShaderDataType::Float3, "aPos" }
        };
        vertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        uint32_t indices[] = { 0, 1, 2};
        Ref<OpenGLIndexBuffer> indexBuffer;
        indexBuffer.reset(OpenGLIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        const char *vertexShaderSource = "#version 330 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";

        const char *fragmentShaderSource = "#version 330 core\n"
                                           "out vec4 FragColor;\n"
                                           "void main()\n"
                                           "{\n"
                                           "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                           "}\n\0";

        m_Shader = OpenGLShader::Create("Triangle", vertexShaderSource, fragmentShaderSource);

    }

    void Scene::Begin()
    {
        Application& app = Application::Get();
        Editor& editor = app.GetEditor();
        Window& window = app.GetWindow();
        glm::vec2& sceneSize = editor.sceneEditor->Size;

        m_FrameBuffer->HandleResize(sceneSize);

        m_FrameBuffer->Bind();
        OpenGLRenderer::SetViewport(0, 0, sceneSize.x, sceneSize.y);
        OpenGLRenderer::SetClearColor(glm::vec4(0.2f, 0.2f, 0.2f, 1.0f));
        OpenGLRenderer::Clear();

        OpenGLRenderer::Begin();
    }

    void Scene::End()
    {
        OpenGLRenderer::End();

        m_FrameBuffer->UnBind();
    }

    void Scene::OnUpdate()
    {
        Begin();

        OpenGLRenderer::Submit(m_Shader, m_VertexArray);

        End();
    }

}