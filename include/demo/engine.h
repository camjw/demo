#ifndef DEMO_ENGINE_HPP
#define DEMO_ENGINE_HPP

#include <demo/rendering/cube_map.h>
#include <demo/rendering/rendering_system.h>
#include <demo/rendering/shader.h>
#include <demo/rendering/texture.h>

#include <demo/camera.h>
#include <demo/input_processor.h>
#include <demo/timer.h>
#include <demo/window.h>

#include <demo/ecs/coordinator.h>
#include <demo/ecs/ecs.h>

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
    void draw(Time time);

    bool is_running();

private:
    Window* window = nullptr;
    InputProcessor* input = nullptr;
    Camera* camera = nullptr;
    Coordinator* coordinator = nullptr;
    std::shared_ptr<RenderingSystem> rendering_system;
};
#endif
