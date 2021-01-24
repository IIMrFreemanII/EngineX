#pragma once

#include <string>
#include <memory>

namespace EngineX {

    struct SceneEditor {
        std::string Title;
        unsigned int Width;
        unsigned int Height;

        SceneEditor(
            const std::string& title = "Scene",
            unsigned int width = 0,
            unsigned int height = 0
        ) : Title(title), Width(width), Height(height)
        {}
    };

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