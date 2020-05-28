#include <demo/scene/scene_manager.h>

SceneManager::SceneManager()
{
    first_scene = new FirstScene();
}

void SceneManager::update(Time time, InputState* input) { }

void SceneManager::late_update(Time time, InputState* input) { }

Scene* SceneManager::get_current_scene()
{
    return first_scene;
}