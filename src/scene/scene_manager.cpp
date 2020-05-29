#include <demo/scene/scene_manager.h>

SceneManager::SceneManager(std::shared_ptr<DemoContext> context, std::shared_ptr<Coordinator> coordinator)
    : context(context), coordinator(coordinator)
{
    first_scene = new FirstScene(context, coordinator);
}

void SceneManager::update(Time time, InputState* input) { }

void SceneManager::late_update(Time time, InputState* input) { }

Scene* SceneManager::get_current_scene()
{
    return first_scene;
}