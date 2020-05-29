#include <demo/engine.h>

Engine::Engine()
{
    context = std::make_shared<DemoContext>();
    window = new Window("Estuary King");
    input = new InputProcessor(window);

    scene_manager = std::make_shared<SceneManager>();

    coordinator = new Coordinator();
    coordinator->init();

    rendering_system = coordinator->register_system<RenderingSystem>();
    rendering_system->init(context, window, coordinator);
}

Engine::~Engine()
{
    delete input;
    delete coordinator;
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
