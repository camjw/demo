#include <demo/engine.hpp>

Engine::Engine()
{
    window = new Window("Estuary King");
    camera = new Camera();
    input = new InputProcessor(window);

    coordinator = new Coordinator();
    coordinator->init();

    rendering_system = coordinator->register_system<RenderingSystem>();
    rendering_system->init(window, camera, coordinator);
}

Engine::~Engine()
{
    rendering_system->destroy();

    delete input;
    delete coordinator;
    delete camera;
    delete window;
}

void Engine::update(Time time)
{
    window->update(time, input);
    camera->update(time, input);
}

void Engine::late_update(Time time)
{
}

void Engine::draw()
{
    rendering_system->draw();
}

void Engine::process_input()
{
    input->process_input();
}

bool Engine::is_running() { return !window->should_close(); }
