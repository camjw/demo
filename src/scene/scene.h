#ifndef DEMO_SCENE_H
#define DEMO_SCENE_H

#include "scene_graph.h"
#include "scene_id.h"
#include <ecs/components/camera_component.h>
#include <memory>
#include <utility>

class DemoContext;
class Scene
{
public:
    Scene(std::shared_ptr<DemoContext> context, const std::shared_ptr<World>& world, SceneID scene_id)
        : context(std::move(context))
        , world(world)
        , scene_id(scene_id)
    {
        graph = std::make_unique<SceneGraph>(world, this, scene_id);
    }

    virtual void on_create() = 0;
    virtual void on_destroy() = 0;

    virtual void on_load() {};
    virtual void on_unload() {};

    inline Entity get_camera() const
    {
        return camera;
    };

    inline void set_camera(Entity camera)
    {
        this->camera = camera;
    };

    inline SceneID get_scene_id() const
    {
        return scene_id;
    }

    inline SceneNode* get_root_node() const
    {
        return graph->root().get();
    }

protected:
    std::shared_ptr<DemoContext> context;
    std::shared_ptr<World> world;

    std::unique_ptr<SceneGraph> graph;

    Entity camera = INVALID_ENTITY;
    SceneID scene_id;
};

#endif // DEMO_SCENE_H
