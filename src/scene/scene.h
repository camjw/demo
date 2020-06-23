#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include "scene_graph.h"
#include <demo/scene/camera_component.h>
#include <memory>

class Scene
{
public:
    Scene(std::shared_ptr<DemoContext> context, std::shared_ptr<World> coordinator)
        : context(context), coordinator(coordinator)
    {
    }

    virtual SceneGraph get_scene_graph() {};
    virtual void on_create() = 0;
    virtual void on_destroy() = 0;

    virtual void on_load() {};
    virtual void on_unload() {};

    virtual Entity get_active_camera() = 0;

protected:
    std::shared_ptr<DemoContext> context;
    std::shared_ptr<World> coordinator;
};

#endif // DEMO_SCENE_H
