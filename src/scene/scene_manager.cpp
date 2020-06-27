#include "ecs/components/hierarchy_component.h"
#include <scene/scene_manager.h>
#include <scripts/scenes/first_scene.h>

SceneManager::SceneManager(std::shared_ptr<DemoContext> context, std::shared_ptr<World> world)
    : context(context)
    , world(world)
{
    Scene* first_scene = new FirstScene(context, world, next_scene_id);
    first_scene->on_create();

    scenes.insert(std::pair<SceneID, Scene*>(next_scene_id++, first_scene));
}

void SceneManager::update(Time time, InputState* input) { }

void SceneManager::late_update(Time time, InputState* input) { }

Scene* SceneManager::get_current_scene()
{
    return scenes[current_scene_id];
}