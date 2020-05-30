#include <demo/engine.h>

Engine::Engine()
{
    context = std::make_shared<DemoContext>();
    window = new Window("Estuary King");
    input = new InputProcessor(window);

    coordinator = std::make_shared<Coordinator>();
    coordinator->init();

    coordinator->register_component<TextureComponent>();
    coordinator->register_component<MeshComponent>();
    coordinator->register_component<ShaderComponent>();
    coordinator->register_component<CameraComponent>();

    std::shared_ptr<CameraSystem> camera_system = coordinator->register_system<CameraSystem>();
    Signature camera_system_signature;
    camera_system_signature.set(coordinator->get_component_type<CameraComponent>());
    coordinator->set_system_signature<CameraSystem>(camera_system_signature);

    renderer = std::make_shared<Renderer>(context, window, coordinator);

    SceneManager sm = SceneManager(context, coordinator);
    scene_manager = std::make_shared<SceneManager>(sm);
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
}

void Engine::late_update(Time time)
{
    scene_manager->late_update(time, input);
}

void Engine::draw(Time time)
{
    renderer->draw(time, scene_manager->get_current_scene());
}

void Engine::process_input()
{
    input->process_input();
}

bool Engine::is_running() { return !window->should_close(); }
