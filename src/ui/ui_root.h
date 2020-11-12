#ifndef DEMO_UI_ROOT_H
#define DEMO_UI_ROOT_H

#include "event_repository.h"
#include "material_editor.h"
#include "menu_bar.h"
#include "scene_hierarchy_viewer.h"
#include <context/demo_context.h>
#include <ecs/world.h>
#include <imgui/bindings/imgui_impl_glfw.h>
#include <imgui/bindings/imgui_impl_opengl3.h>
#include <imgui/imgui.h>
#include <scene/scene_manager.h>

class UIRoot
{
public:
    UIRoot(std::shared_ptr<World> world, std::shared_ptr<Window> window,
        std::shared_ptr<DemoContext> context, std::shared_ptr<SceneManager> scene_manager,
        ImGuiContext* imgui_context);
    inline void update()
    {
        event_repository->update();
    }

    inline void late_update()
    {
        event_repository->late_update();
    }

    void draw();
    void new_frame();

private:
    ImGuiIO& imgui_io;
    std::shared_ptr<World> world;
    std::shared_ptr<DemoContext> context;
    std::shared_ptr<SceneManager> scene_manager;
    ImGuiContext* imgui_context;

    std::unique_ptr<SceneHierarchyViewer> scene_hierarchy_viewer;
    std::unique_ptr<MenuBar> menu_bar;
    std::unique_ptr<MaterialEditor> material_editor;

    std::unique_ptr<EventRepository> event_repository;
};

#endif //DEMO_UI_ROOT_H
