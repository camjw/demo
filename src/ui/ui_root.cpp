#include "ui_root.h"

UIRoot::UIRoot(std::shared_ptr<World> world, std::shared_ptr<Window> window, std::shared_ptr<DemoContext> context,
    std::shared_ptr<SceneManager> scene_manager, ImGuiContext* imgui_context)
    : imgui_io(ImGui::GetIO())
    , world(world)
    , context(context)
    , scene_manager(scene_manager)
    , imgui_context(imgui_context)

{
    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window->get_glfw_window(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    scene_hierarchy_viewer = std::make_unique<SceneHierarchyViewer>(scene_manager, world);
    menu_bar = std::make_unique<MenuBar>();
}

void UIRoot::new_frame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
}

void UIRoot::draw()
{
    ImGui::NewFrame();

    scene_hierarchy_viewer->draw_if_active();
    menu_bar->draw_if_active();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
