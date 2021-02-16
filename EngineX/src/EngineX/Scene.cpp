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

        const std::vector<Vertex> vertices = {
                { { -0.5f, -0.5f, 0.0f } }, // left
                { { 0.5f, -0.5f, 0.0f } }, // right
                { { 0.0f, 0.5f, 0.0f } }, // top
        };
        const std::vector<uint32_t> indices = { 0, 1, 2};

        m_Mesh.reset(Mesh::Create(vertices, indices));
        m_Shader = OpenGLShader::Create("asset/shader/basic.glsl");
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

        OpenGLRenderer::Submit(m_Shader, m_Mesh);

        End();
    }

}