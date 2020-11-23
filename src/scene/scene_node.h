#ifndef DEMO_SCENE_NODE_H
#define DEMO_SCENE_NODE_H

#include "scene_id.h"
#include <ecs/ecs.h>
#include <rendering/data/mesh.h>
#include <vector>

class Scene;
class SceneNode
{
public:
    SceneNode(SceneNode* parent_node, Scene& scene, SceneID scene_id)
        : parent_node(parent_node), scene(scene), scene_id(scene_id)
    {
    }

    inline SceneNode* get_root_node()
    {
        if (parent_node == nullptr)
        {
            return this;
        }

        return parent_node->get_root_node();
    };

    inline void set_entity(const Entity entity)
    {
        m_entity = entity;
        // TODO: maybe should notify children here or something
    }

    inline Entity get_entity() const
    {
        return m_entity;
    }

    SceneNode* find_entity(const Entity entity)
    {
        if (m_entity == entity)
        {
            return this;
        }

        for (SceneNode* child : m_child_nodes)
        {
            SceneNode* find_in_child = child->find_entity(entity);
            if (find_in_child != nullptr)
            {
                return find_in_child;
            }
        }

        return nullptr;
    }

    inline SceneNode* add_child()
    {
        SceneNode* new_node = new SceneNode(this, scene, scene_id);
        m_child_nodes.push_back(new_node);
        return new_node;
    }

    inline SceneNode* add_child(const Entity entity)
    {
        SceneNode* new_node = new SceneNode(this, scene, scene_id);
        new_node->set_entity(entity);
        m_child_nodes.push_back(new_node);
        return new_node;
    }

    inline const std::vector<SceneNode*> get_children() const
    {
        return m_child_nodes;
    }

    inline const SceneID get_scene_id() const
    {
        return scene_id;
    }

    inline const Scene& get_scene() const
    {
        return scene;
    }

private:
    Entity m_entity;
    std::vector<SceneNode*> m_child_nodes;
    SceneNode* parent_node = nullptr;
    Scene& scene;
    SceneID scene_id;
};

#endif // DEMO_SCENE_NODE_H
