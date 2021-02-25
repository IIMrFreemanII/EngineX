#include "Scene.h"
#include "Platform/OpenGL/OpenGLRenderer.h"
#include "Application.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glad/glad.h>

namespace EngineX {

    Scene::Scene()
    {
        Window& window = Application::Get().GetWindow();
        FrameBufferConfiguration configuration{};
        configuration.size = { window.GetWidth(), window.GetHeight() };

        m_FrameBuffer = std::make_unique<OpenGLFrameBuffer>(configuration);

        m_Shader = OpenGLShader::Create("asset/shader/basic.glsl");

        m_Mesh.reset(Mesh::LoadFromFile("asset/model/cube.fbx"));
        m_Camera.reset(new Camera({0.0f, 2.0f, -3.0f}));

        m_Material = std::make_shared<Material>(Material{
                glm::vec3(1.0f, 0.5f, 0.31f),
                0.5f,
                32.0f,
        });
        m_DirLight = std::make_shared<DirectionLight>(DirectionLight{
            glm::vec3(0.5f, -1.0f, 0.0f),
            glm::vec3(0.2f, 0.2f, 0.2f),
            glm::vec3(0.5f, 0.5f, 0.5f),
            glm::vec3(1.0f, 1.0f, 1.0f),
        });
    }

    void Scene::Begin()
    {
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_CULL_FACE);

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

        Application& app = Application::Get();
        Editor& editor = app.GetEditor();
        glm::vec2& sceneSize = editor.sceneEditor->Size;

        glm::mat4 projection = glm::perspective(glm::radians(90.0f), sceneSize.x / sceneSize.y, 0.1f, 100.0f);
        glm::mat4 view = m_Camera->GetViewMatrix();
        glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        glm::mat3 normalMat = glm::mat3(glm::transpose(glm::inverse(model)));

        m_Shader->Bind();

        m_Shader->UploadUniformFloat3("viewPos", m_Camera->Position);

        m_Shader->UploadUniformFloat3("material.diffuse", m_Material->Diffuse);
        m_Shader->UploadUniformFloat("material.specular", m_Material->Specular);
        m_Shader->UploadUniformFloat("material.shininess", m_Material->Shininess);

        m_Shader->UploadUniformFloat3("dirLight.direction", m_DirLight->Direction);
        m_Shader->UploadUniformFloat3("dirLight.ambient", m_DirLight->Ambient);
        m_Shader->UploadUniformFloat3("dirLight.diffuse", m_DirLight->Diffuse);
        m_Shader->UploadUniformFloat3("dirLight.specular", m_DirLight->Specular);

        m_Shader->UploadUniformMat4("model", model);
        m_Shader->UploadUniformMat4("view", view);
        m_Shader->UploadUniformMat4("projection", projection);
        m_Shader->UploadUniformMat3("normalMat", normalMat);

        OpenGLRenderer::Submit(m_Shader, m_Mesh);

        End();
    }

}