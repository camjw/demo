#ifndef DEMO_ENGINE_HPP
#define DEMO_ENGINE_HPP

#include <demo/rendering/cube_map.hpp>
#include <demo/rendering/shader.hpp>
#include <demo/rendering/texture.hpp>
#include <demo/rendering/rendering_system.hpp>

#include <demo/camera.hpp>
#include <demo/input_processor.hpp>
#include <demo/timer.hpp>
#include <demo/window.hpp>

#include <demo/ecs/coordinator.hpp>
#include <demo/ecs/ecs.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb_image.h>

#include <vector>

class Engine
{

public:
    Engine();
    ~Engine();

    void process_input();

    void update(Time time);
    void late_update(Time time);
    void draw();

    bool is_running();

private:
    Window* window = nullptr;
    InputProcessor* input = nullptr;
    Camera* camera = nullptr;
    Coordinator* coordinator = nullptr;
    std::shared_ptr<RenderingSystem> rendering_system;
};
#endif
