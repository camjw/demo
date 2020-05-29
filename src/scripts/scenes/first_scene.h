#ifndef DEMO_FIRST_SCENE_H
#define DEMO_FIRST_SCENE_H

#include <demo/context/demo_context.h>
#include <demo/ecs/coordinator.h>
#include <demo/scene/scene.h>
#include <memory>

class FirstScene : public Scene
{
public:
    FirstScene(std::shared_ptr<DemoContext> context, std::shared_ptr<Coordinator> coordinator);

    virtual void on_create() override;
    virtual void on_destroy() override;

    virtual std::shared_ptr<Camera> get_active_camera() override;

private:
    void load_textures();
    void load_shaders();
    void load_meshes();

    void build_entities();

    std::shared_ptr<Camera> camera;
};

#endif // DEMO_FIRST_SCENE_H
