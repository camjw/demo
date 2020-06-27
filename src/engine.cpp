#include <ecs/components/hierarchy_component.h>
#include <engine.h>
#include <maths/transform.h>
#include <scene/orbit_camera_system.h>
#include <utils/opengl_helpers.h>

Engine::Engine()
{
    context = std::make_shared<DemoContext>();
    window = new Window("Estuary King");
    input = new InputProcessor(window);

    world = std::make_shared<World>();
    world->init(world);

    // Register components
    world->register_component<Transform>();
    world->register_component<TextureComponent>();
    world->register_component<MeshComponent>();
    world->register_component<ShaderComponent>();
    world->register_component<CameraComponent>();
    world->register_component<HierarchyComponent>();

    // Init systems
    world->register_system<OrbitCameraSystem>();
    Signature camera_system_signature;
    camera_system_signature.set(world->get_component_type<CameraComponent>());
    camera_system_signature.set(world->get_component_type<Transform>());
    world->set_system_signature<OrbitCameraSystem>(camera_system_signature);

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
