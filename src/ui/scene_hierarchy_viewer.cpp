#include "scene_hierarchy_viewer.h"

void SceneHierarchyViewer::draw()
{
    ImGui::Begin("Scene Hierarchy", &is_active, ImGuiWindowFlags_MenuBar);
   
    ImGui::TextColored(ImVec4(1, 1, 0, 1), "Important Stuff");
    ImGui::BeginChild("Scrolling");
    for (int n = 0; n < 50; n++)
        ImGui::Text("%04d: Some text", n);
    ImGui::EndChild();
    ImGui::End();
}
