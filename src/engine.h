#ifndef DEMO_ENGINE_HPP
#define DEMO_ENGINE_HPP

#include <rendering/cube_map.h>
#include <rendering/renderer.h>
#include <rendering/shader.h>
#include <rendering/texture.h>

#include <ecs/components/camera_component.h>
#include <input_processor.h>
#include <timer.h>
#include <window.h>

#include <ecs/ecs.h>
#include <ecs/world.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <context/demo_context.h>
#include <scene/scene_manager.h>
#include <vector>

class Engine
{

public:
    Engine();
    ~Engine();

    void process_input();

    void update(Time time);
    void late_update(Time time);
    void draw(Time time);

    bool is_running();

private:
    Window* window = nullptr;
    InputProcessor* input = nullptr;

    std::shared_ptr<World> world;
    std::shared_ptr<DemoContext> context;

    std::unique_ptr<SceneManager> scene_manager;
    std::unique_ptr<Renderer> renderer;
};
#endif
