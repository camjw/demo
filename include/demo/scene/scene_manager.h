#ifndef DEMO_SCENE_MANAGER_H
#define DEMO_SCENE_MANAGER_H

#include <demo/ecs/coordinator.h>
#include <demo/input_processor.h>
#include <demo/timer.h>
#include <memory>
#include <scripts/scenes/first_scene.h>

class SceneManager
{
public:
    SceneManager(std::shared_ptr<DemoContext> context, std::shared_ptr<Coordinator> coordinator);

    void update(Time time, InputState* input);
    void late_update(Time time, InputState* input);

    Scene* get_current_scene();

private:
    Scene* first_scene;

    std::shared_ptr<DemoContext> context;
    std::shared_ptr<Coordinator> coordinator;
};

#endif // DEMO_SCENE_LOADER_H
