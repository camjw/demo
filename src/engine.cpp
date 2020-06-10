#include <demo/engine.h>
#include <demo/maths/transform.h>
#include <demo/scene/orbit_camera_system.h>
#include <demo/utils/opengl_helpers.h>

Engine::Engine()
{
    context = std::make_shared<DemoContext>();
    window = new Window("Estuary King");
    input = new InputProcessor(window);

    coordinator = std::make_shared<World>();
    coordinator->init();

    // Register components
    coordinator->register_component<TransformComponent>();
    coordinator->register_component<TextureComponent>();
    coordinator->register_component<MeshComponent>();
    coordinator->register_component<ShaderComponent>();
    coordinator->register_component<CameraComponent>();

    // Init systems
    coordinator->register_system<OrbitCameraSystem>();
    Signature camera_system_signature;
    camera_system_signature.set(coordinator->get_component_type<CameraComponent>());
    camera_system_signature.set(coordinator->get_component_type<TransformComponent>());
    coordinator->set_system_signature<OrbitCameraSystem>(camera_system_signature);

    // Init renderer
    renderer = std::make_unique<Renderer>(context, window, coordinator);

    // Init scene manager
    scene_manager = std::make_unique<SceneManager>(context, coordinator);
}

Engine::~Engine()
{
    delete input;
    delete window;
}

void Engine::update(Time time)
{
    window->update(time, input);
    scene_manager->update(time, input);
    coordinator->update_systems(time, input);
}

void Engine::late_update(Time time)
{
    scene_manager->late_update(time, input);
    coordinator->late_update_systems(time, input);
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
