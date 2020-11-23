#include <ecs/components/hierarchy_component.h>
#include <ecs/components/mesh_renderer.h>
#include <ecs/components/name_component.h>
#include <ecs/systems/first_person_camera_system.h>
#include <engine.h>
#include <maths/transform.h>
#include <rendering/data/material.h>
#include <rendering/lighting/directional_light.h>
#include <rendering/lighting/point_light.h>
#include <rendering/lighting/spot_light.h>
#include <utils/opengl_helpers.h>

Engine::Engine()
{
    window = std::make_shared<Window>("Estuary King");
    #ifdef WINDOWS
    window->load_icon("./assets/icon.png");
    #endif

    IMGUI_CHECKVERSION();
    imgui_context = ImGui::CreateContext();
    assert(imgui_context != nullptr && "Failed to create ImGui context");

    input = std::make_unique<InputProcessor>(window);

    world = std::make_shared<World>();
    world->init(world);

    // Build context
    context = std::make_shared<DemoContext>(world);

    // Register components
    world->register_component<Transform>();
    world->register_component<MeshRenderer>();
    world->register_component<Camera>();
    world->register_component<HierarchyComponent>();
    world->register_component<NameComponent>();
    world->register_component<PointLight>();
    world->register_component<DirectionalLight>();
    world->register_component<CubeMapRenderer>();
    world->register_component<SpotLight>();

    // Register systems
    world->register_system<FirstPersonCameraSystem>();
    Signature camera_system_signature;
    camera_system_signature.set(world->get_component_type<Camera>());
    camera_system_signature.set(world->get_component_type<Transform>());
    world->set_system_signature<FirstPersonCameraSystem>(camera_system_signature);

    // Init scene manager
    scene_manager = std::make_shared<SceneManager>(context, world);

    ui_root = std::make_shared<UIRoot>(world, window, context, scene_manager, imgui_context);

    // Init renderer
    renderer = std::make_unique<OpenGLRenderer>(context, window, world, ui_root);
}

Engine::~Engine()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
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
    window->update(time, input.get());
    scene_manager->update(time, input.get());
    world->update_systems(time, input.get());
    ui_root->update();
}

void Engine::late_update(Time time)
{
    scene_manager->late_update(time, input.get());
    world->late_update_systems(time, input.get());
    ui_root->late_update();
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
