#ifndef DEMO_FIRST_SCENE_H
#define DEMO_FIRST_SCENE_H

#include <context/demo_context.h>
#include <ecs/world.h>
#include <memory>
#include <scene/scene.h>

class FirstScene : public Scene
{
public:
    FirstScene(std::shared_ptr<DemoContext> context, std::shared_ptr<World> world, SceneID scene_id);

    void on_create() override;
    void on_destroy() override;

private:
    void build_camera();
};

#endif // DEMO_FIRST_SCENE_H
