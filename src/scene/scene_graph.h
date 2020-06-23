#ifndef DEMO_SCENE_GRAPH_H
#define DEMO_SCENE_GRAPH_H

#include "scene_node.h"
#include <ecs/entity_builder.h>

class SceneGraph
{
public:
    SceneGraph(std::shared_ptr<World> world)
        : m_root_node(std::make_shared<SceneNode>())
        , m_world(world)
    {
        // Set root node to have entity
        m_root_node->set_entity(
            world->create_entity()
                ->with(Transform {})
                ->build());
    }

    SceneNode* find_entity_in_graph(Entity entity)
    {
        return m_root_node->find_entity(entity);
    }

    inline std::shared_ptr<SceneNode> get_root_node()
    {
        return m_root_node;
    }

    EntityBuilder with_entity();

private:
    std::shared_ptr<SceneNode> m_root_node;
    std::shared_ptr<World> m_world;
};

#endif //DEMO_SCENE_GRAPH_H
