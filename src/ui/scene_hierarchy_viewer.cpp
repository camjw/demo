#include "scene_hierarchy_viewer.h"

void SceneHierarchyViewer::draw()
{
    ImGui::Begin("Scene Hierarchy", &is_active, ImGuiWindowFlags_MenuBar);

    if (ImGui::TreeNode("Current Scene"))
    {
        Scene* current_scene = scene_manager->get_current_scene();
        SceneNode* root_node = current_scene->get_root_node();
        draw_scene_node_inspector(root_node);
        ImGui::TreePop();
    }

    ImGui::End();
}

void SceneHierarchyViewer::draw_scene_node_inspector(SceneNode* node)
{
    std::vector<SceneNode*> children = node->get_children();

    for (int i = 0; i < children.size(); i++)
    {
        std::string name = "MISSING NAME";
        if (world->has_component<NameComponent>(children[i]->get_entity()))
        {
            NameComponent name_component = world->get_component<NameComponent>(children[i]->get_entity());
            name = name_component.name;
        }

        ImGui::TreeNodeEx(name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick);
        draw_scene_node_inspector(children[i]);
    }
}