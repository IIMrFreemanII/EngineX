#include "SceneEditor.h"

namespace EngineX {

    SceneEditor::SceneEditor(const std::string& title, const glm::vec2& size)
            : Title(title), Size(size)
    {

    }

    void SceneEditor::SetSize(const glm::vec2& size)
    {
        Size = size;
    }

}
