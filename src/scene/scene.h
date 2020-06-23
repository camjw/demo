#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include "scene_graph.h"
#include "scene_id.h"
#include <context/demo_context.h>
#include <ecs/components/camera_component.h>
#include <memory>
#include <utility>

class Scene
{
public:
    Scene(std::shared_ptr<DemoContext> context, std::shared_ptr<World> world, SceneID scene_id)
        : context(std::move(context))
        , world(std::move(world))
        , graph(std::make_unique<SceneGraph>())
        , scene_id(scene_id)
    {
    }

    virtual void on_create() = 0;
    virtual void on_destroy() = 0;

    virtual void on_load() {};
    virtual void on_unload() {};

    inline Entity get_camera()
    {
        return camera;
    };

    inline Entity set_camera(Entity camera)
    {
        this->camera = camera;
    };

    inline SceneID get_scene_id() const
    {
        return scene_id;
    }

protected:
    std::shared_ptr<DemoContext> context;
    std::shared_ptr<World> world;

    std::unique_ptr<SceneGraph> graph;

    Entity camera = INVALID_ENTITY;
    SceneID scene_id;
};

#endif // DEMO_SCENE_H
