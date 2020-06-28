#ifndef DEMO_SCENE_GRAPH_H
#define DEMO_SCENE_GRAPH_H

#include "scene_node.h"
#include <ecs/entity_builder.h>
#include <ecs/world.h>

class SceneGraph
{
public:
    SceneGraph(std::shared_ptr<World> world)
        : m_root_node(std::make_shared<SceneNode>())
        , m_world(world)
    {
        // Set root node to have entity
        m_root_node->set_entity(
            m_world->create_entity()
                .with(Transform::identity())
                .build());
    }

    SceneNode* find_entity_in_graph(Entity entity)
    {
        return m_root_node->find_entity(entity);
    }

    inline std::shared_ptr<SceneNode> root()
    {
        return m_root_node;
    }

    inline SceneNode* add_child()
    {
        return m_root_node->add_child();
    }

    inline SceneNode* add_child(Entity entity)
    {
        return m_root_node->add_child(entity);
    }

private:
    std::shared_ptr<SceneNode> m_root_node;
    std::shared_ptr<World> m_world;
};

#endif //DEMO_SCENE_GRAPH_H
