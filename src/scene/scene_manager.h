#ifndef DEMO_SCENE_MANAGER_H
#define DEMO_SCENE_MANAGER_H

#include "scene.h"
#include "scene_graph.h"
#include "scene_id.h"
#include <context/demo_context.h>
#include <ecs/world.h>
#include <input/input_processor.h>
#include <memory>
#include <timer.h>

class SceneManager
{
public:
    SceneManager(std::shared_ptr<DemoContext> context, std::shared_ptr<World> world);

    void update(Time time, InputState* input);
    void late_update(Time time, InputState* input);

    Scene* get_current_scene();
    Scene* get_scene(SceneID scene_id);

private:
    SceneID next_scene_id = 0;
    SceneID current_scene_id = 0;

    std::unordered_map<SceneID, Scene*> scenes;

    std::shared_ptr<DemoContext> context;
    std::shared_ptr<World> world;
};

#endif // DEMO_SCENE_LOADER_H
