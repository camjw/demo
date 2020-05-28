#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include <demo/scene/camera.h>
#include <memory>

class Scene
{
public:
    virtual void on_create() = 0;
    virtual void on_destroy() = 0;

    virtual void on_load() {};
    virtual void on_unload() {};

    virtual std::shared_ptr<Camera> get_active_camera() = 0;
};

#endif // DEMO_SCENE_H
