#include "menu_bar.h"
#include <imgui/imgui_internal.h>
#include <ui/event_processors/set_scene_hierarchy_viewer_visible.h>

MenuBar::MenuBar(EventRepository* event_repository)
    : UIWidget()
    , event_repository(event_repository)
{
    is_active = true;
}

void MenuBar::draw()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("Inspectors"))
        {
            ImGui::PushItemFlag(ImGuiItemFlags_SelectableDontClosePopup, true);
            if (ImGui::MenuItem("Scene Hierarchy Viewer"))
            {
                event_repository->add_event(new SetSceneHierarchyViewerVisibleEvent(true));
            }
            ImGui::PopItemFlag();
            ImGui::EndMenu();
        }
    }
}