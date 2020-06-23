#ifndef DEMO_ENTITY_BUILDER_H
#define DEMO_ENTITY_BUILDER_H

#include "world.h"
#include <ecs/components/camera_component.h>
#include <ecs/components/hierarchy_component.h>
#include <maths/transform.h>
#include <memory>
#include <rendering/mesh.h>
#include <rendering/shader.h>
#include <rendering/texture.h>

class EntityBuilder
{
public:
    EntityBuilder(std::shared_ptr<World> world)
        : m_world(world)
    {
    }

    EntityBuilder* with(Transform data)
    {
        m_texture = &data;
        return this;
    }

    EntityBuilder* with(MeshComponent data)
    {
        m_mesh = &data;
        return this;
    };

    EntityBuilder* with(ShaderComponent data)
    {
        m_shader = &data;
        return this;
    };

    EntityBuilder* with(CameraComponent data)
    {
        m_camera = &data;
        return this;
    };

    EntityBuilder* with(TextureComponent data)
    {
        m_texture = &data;
        return this;
    };

    EntityBuilder* with(HierarchyComponent data)
    {
        m_hierarchy = &data;
        return this;
    };

    EntityBuilder* with(RotatingCubeComponent data)
    {
        m_rotating_cube = &data;
        return this;
    };

    EntityBuilder* with_parent(Entity parent)
    {
        HierarchyComponent hierarchy_component = HierarchyComponent { .parent = parent };
        m_hierarchy = &hierarchy_component;
        return this;
    }

    Entity build()
    {
        Entity entity = m_world->create_empty_entity();

        if (m_transform != nullptr)
        {
            m_world->add_component(entity, *m_transform);
        }

        if (m_texture != nullptr)
        {
            m_world->add_component(entity, *m_texture);
        }

        if (m_mesh != nullptr)
        {
            m_world->add_component(entity, *m_mesh);
        }

        if (m_shader != nullptr)
        {
            m_world->add_component(entity, *m_shader);
        }

        if (m_camera != nullptr)
        {
            m_world->add_component(entity, *m_camera);
        }

        if (m_hierarchy != nullptr)
        {
            m_world->add_component(entity, *m_hierarchy);
        }

        if (m_rotating_cube != nullptr)
        {
            m_world->add_component(entity, *m_rotating_cube);
        }
    }

private:
    std::shared_ptr<World> m_world;

    Transform* m_transform = nullptr;
    TextureComponent* m_texture = nullptr;
    MeshComponent* m_mesh = nullptr;
    ShaderComponent* m_shader = nullptr;
    CameraComponent* m_camera = nullptr;
    HierarchyComponent* m_hierarchy = nullptr;
    RotatingCubeComponent* m_rotating_cube = nullptr;
};

#endif //DEMO_ENTITY_BUILDER_H
