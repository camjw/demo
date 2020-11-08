#ifndef DEMO_ENGINE_HPP
#define DEMO_ENGINE_HPP

#include <chrono>
#include <context/demo_context.h>
#include <cstdio>
#include <ecs/components/camera_component.h>
#include <ecs/ecs.h>
#include <ecs/world.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <input/event_repository.h>
#include <input/input_processor.h>
#include <rendering/cube_map.h>
#include <rendering/opengl_renderer.h>
#include <rendering/shader.h>
#include <rendering/texture.h>
#include <scene/scene_manager.h>
#include <stb_image.h>
#include <thread>
#include <timer.h>
#include <ui/ui_root.h>
#include <vector>
#include <window.h>

class Engine
{

public:
    Engine();
    ~Engine();

    void run();

private:
    void process_input();

    void update(Time time);
    void late_update(Time time);
    void draw(Time time);

    bool is_running();

    std::shared_ptr<Window> window;
    std::unique_ptr<InputProcessor> input;
    std::unique_ptr<EventRepository> event_repository;

    std::shared_ptr<UIRoot> ui_root;

    std::shared_ptr<World> world;
    std::shared_ptr<DemoContext> context;

    std::shared_ptr<SceneManager> scene_manager;
    std::unique_ptr<OpenGLRenderer> renderer;

    ImGuiContext* imgui_context = nullptr;
};
#endif
