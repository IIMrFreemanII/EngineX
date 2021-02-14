#include "SceneEditor.h"
#include "EngineX/Application.h"
#include "imgui.h"

namespace EngineX {

    SceneEditor::SceneEditor(const std::string& title, const glm::vec2& size)
            : Title(title), Size(size)
    {

    }

    void SceneEditor::SetSize(const glm::vec2& size)
    {
        Size = size;
    }

    void SceneEditor::OnImGuiRender()
    {
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Scene");
        {
            ImVec2 sceneSize = ImGui::GetContentRegionAvail();
            SetSize({ sceneSize.x, sceneSize.y });

            uint32_t textureID = Application::Get().GetScene().GetFrameBuffer().GetTextureColorBuffer();
            ImGui::Image((void*)(uintptr_t)textureID, sceneSize, ImVec2(0, 1), ImVec2(1, 0));

            // another way to do the same
//            ImVec2 pos = ImGui::GetCursorScreenPos();
//            ImDrawList* drawList = ImGui::GetWindowDrawList();
//            drawList->AddImage((void*)textureID,
//                               pos,
//                               ImVec2(pos.x + sceneSize.x, pos.y + sceneSize.y),
//                               ImVec2(0, 1),
//                               ImVec2(1, 0)
//            );
        }
        ImGui::End();
        ImGui::PopStyleVar(1);
    }

}
