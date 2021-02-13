#pragma once

#include <functional>
#include "Platform/OpenGL/OpenGLRenderer.h"
#include "glm/glm.hpp"

namespace EngineX {

    class SceneEditor {

    public:
        std::string Title;
        glm::vec2 Size;

        SceneEditor(const std::string& title = "Scene", const glm::vec2& size = {0.0f, 0.0f});

        void SetSize(const glm::vec2& size);
        void OnImGuiRender();

    };

}