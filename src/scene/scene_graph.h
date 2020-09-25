#ifndef DEMO_SCENE_GRAPH_H
#define DEMO_SCENE_GRAPH_H

#include "scene_node.h"
#include <ecs/entity_builder.h>
#include <ecs/world.h>

#include <utility>

struct NameCheckerCallback
{
    std::string name;
    std::shared_ptr<World> world;

    NameCheckerCallback(const std::string& name, std::shared_ptr<World> world)
        : name(name)
        , world(world)
    {
    }

    bool operator()(const SceneNode* node)
    {
        return world->get_component<NameComponent>(node->get_entity()).name == name;
    }
};

class Scene;
class SceneGraph
{
public:
    explicit SceneGraph(std::shared_ptr<World> world, Scene* scene, SceneID scene_id)
        : root_node(std::make_shared<SceneNode>(nullptr, scene, scene_id))
        , world(world)
    {
        // Set root node to have entity
        root_node->set_entity(
            world->create_entity()
                .with(Transform::identity())
                .build());
    }

    SceneNode* find_entity_in_graph(Entity entity)
    {
        return root_node->find_entity(entity);
    }

    inline std::shared_ptr<SceneNode> root()
    {
        return root_node;
    }

    inline SceneNode* add_child()
    {
        return root_node->add_child();
    }

    inline SceneNode* add_child(Entity entity)
    {
        return root_node->add_child(entity);
    }

    SceneNode* find_named_node(const std::string& node_name) const;
    bool depth_first_search(SceneNode* current_node, const std::function<bool(const SceneNode*)> searcher, SceneNode* output) const;


private:

    std::shared_ptr<SceneNode> root_node;
    std::shared_ptr<World> world;
    bool node_has_matching_name(const std::string& name, const SceneNode* node) const;
};

#endif //DEMO_SCENE_GRAPH_H
