#pragma once
#include "Platform/OpenGL/OpenGLFrameBuffer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Mesh.h"
#include "EngineX/Camera.h"
#include "Material.h"
#include "DirectionLight.h"

namespace EngineX {

    class Scene {

    public:
        Scene();
        ~Scene() = default;

        void Begin();
        void End();

        void OnUpdate();

        inline OpenGLFrameBuffer& GetFrameBuffer() const { return *m_FrameBuffer; }
        inline Camera& GetCamera() const { return *m_Camera; }

    private:
        Scope<OpenGLFrameBuffer> m_FrameBuffer;

    private:
        Ref<OpenGLShader> m_Shader;
        Ref<Mesh> m_Mesh;
        Ref<Camera> m_Camera;

        Ref<Material> m_Material;
        Ref<DirectionLight> m_DirLight;
    };

}
