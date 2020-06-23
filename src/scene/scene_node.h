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


    inline void set_entity(Entity entity)
    {
        m_entity = entity;
        // TODO: maybe should notify children here or something
    }

    SceneNode* find_entity(Entity entity)
    {
        if (m_entity == entity)
        {
            return this;
        }

        for (SceneNode* child: m_child_nodes)
        {
            SceneNode* find_in_child = child->find_entity(entity);
            if (find_in_child != nullptr)
            {
                return find_in_child;
            }
        }

        return nullptr;
    }

private:
    Entity m_entity;
    std::vector<SceneNode*> m_child_nodes;

};

#endif // DEMO_SCENE_NODE_H
