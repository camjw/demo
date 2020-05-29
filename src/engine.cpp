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

    rendering_system = coordinator->register_system<RenderingSystem>();
    rendering_system->init(context, window, coordinator);

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
    rendering_system->draw(time, scene_manager->get_current_scene());
}

void Engine::process_input()
{
    input->process_input();
}

bool Engine::is_running() { return !window->should_close(); }
