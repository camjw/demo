#ifndef DEMO_SCENE_NODE_H
#define DEMO_SCENE_NODE_H

#include <ecs/ecs.h>
#include <rendering/mesh.h>
#include <vector>

class SceneNode
{
public:
    SceneNode* parent_node;

    inline SceneNode* get_root_node()
    {
        if (parent_node == nullptr)
        {
            return this;
        }

        return parent_node->get_root_node();
    };

    Entity entity;

    std::vector<SceneNode*> child_nodes;
};

#endif // DEMO_SCENE_NODE_H
