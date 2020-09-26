#include <ecs/components/hierarchy_component.h>
#include <ecs/components/name_component.h>
#include <ecs/systems/first_person_camera_system.h>
#include <engine.h>
#include <maths/transform.h>
#include <rendering/directional_light.h>
#include <rendering/material.h>
#include <rendering/point_light.h>
#include <utils/opengl_helpers.h>

Engine::Engine()
{
    window = new Window("Estuary King");
    #ifdef WINDOWS
    window->load_icon("./assets/icon.png");
    #endif
    input = new InputProcessor(window);

    world = std::make_shared<World>();
    world->init(world);

    // Init shaders
    context = std::make_shared<DemoContext>(world);
    context->get_shader_repository()->create_shader("lamp");
    context->get_shader_repository()->create_shader("lighting");
    context->get_shader_repository()->create_shader(
        "simple_lighting",
        DEMO_CONSTANTS_SHADERS_FOLDER + "lighting_shader.vert",
        DEMO_CONSTANTS_SHADERS_FOLDER + "lighting_shader_no_textures.frag");
    context->get_shader_repository()->create_shader("pixel");
    context->get_shader_repository()->create_shader("simple");
    context->get_shader_repository()->create_shader("skybox");
    context->get_shader_repository()->create_shader("uv_test");

    // Register components
    world->register_component<Transform>();
    world->register_component<TextureComponent>();
    world->register_component<MeshComponent>();
    world->register_component<ShaderComponent>();
    world->register_component<CameraComponent>();
    world->register_component<HierarchyComponent>();
    world->register_component<NameComponent>();
    world->register_component<Material>();
    world->register_component<PointLight>();
    world->register_component<DirectionalLight>();

    // Init systems
    world->register_system<FirstPersonCameraSystem>();
    Signature camera_system_signature;
    camera_system_signature.set(world->get_component_type<CameraComponent>());
    camera_system_signature.set(world->get_component_type<Transform>());
    world->set_system_signature<FirstPersonCameraSystem>(camera_system_signature);

    // Init renderer
    renderer = std::make_unique<OpenGLRenderer>(context, window, world);

    // Init scene manager
    scene_manager = std::make_unique<SceneManager>(context, world);
}

Engine::~Engine()
{
    delete input;
    delete window;
}

void Engine::run()
{
    const int UPDATE_FREQUENCY = 60;
    const float CYCLE_TIME = 1000.0f / UPDATE_FREQUENCY;

    static Timer system_timer;
    static Timer physics_timer;

    float accumulated_milliseconds = 0.0f;

    while (is_running())
    {
        system_timer.tick();
        process_input();
        accumulated_milliseconds += system_timer.get_time().delta_time;

        if (accumulated_milliseconds >= CYCLE_TIME)
        {
            accumulated_milliseconds -= CYCLE_TIME;

            physics_timer.tick();

            Time time = physics_timer.get_time();
            update(time);

            late_update(time);

            draw(time);
        }
    }
}

void Engine::update(Time time)
{
    window->update(time, input);
    scene_manager->update(time, input);
    world->update_systems(time, input);
}

void Engine::late_update(Time time)
{
    scene_manager->late_update(time, input);
    world->late_update_systems(time, input);
}

void Engine::draw(Time time)
{
    renderer->draw_scene(time, scene_manager->get_current_scene());
}

void Engine::process_input()
{
    input->process_input();
}

bool Engine::is_running() { return !window->should_close(); }
