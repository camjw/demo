#ifndef DEMO_FIRST_SCENE_H
#define DEMO_FIRST_SCENE_H

#include <demo/scene/scene.h>
#include <memory>

class FirstScene : public Scene
{
public:
    FirstScene();

    virtual void on_create() override;
    virtual void on_destroy() override;

    virtual std::shared_ptr<Camera> get_active_camera() override;
private:
    std::shared_ptr<Camera> camera;
};

#endif // DEMO_FIRST_SCENE_H
