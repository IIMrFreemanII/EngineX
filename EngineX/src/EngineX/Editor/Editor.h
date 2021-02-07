#pragma once

#include <string>
#include <memory>
#include "SceneEditor.h"

namespace EngineX {

    class Editor {
    public:
        Editor();
        ~Editor();

        void OnImGuiRender();

        void Begin();
        void End();

    public:
        std::unique_ptr<SceneEditor> sceneEditor;
    };
}