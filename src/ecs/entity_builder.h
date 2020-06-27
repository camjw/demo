#ifndef DEMO_ENTITY_BUILDER_H
#define DEMO_ENTITY_BUILDER_H

#include <ecs/components/camera_component.h>
#include <ecs/components/hierarchy_component.h>
#include <maths/transform.h>
#include <memory>
#include <rendering/mesh.h>
#include <rendering/shader.h>
#include <rendering/texture.h>

class World;
class EntityBuilder
{
public:
    EntityBuilder(std::shared_ptr<World> world)
        : m_world(world)
    {
    }

    EntityBuilder with(Transform data)
    {
        m_transform = data;
        transform_set = true;
        return *this;
    }

    EntityBuilder with(MeshComponent data)
    {
        m_mesh = data;
        mesh_set = true;
        return *this;
    };

    EntityBuilder with(ShaderComponent data)
    {
        m_shader = data;
        shader_set = true;
        return *this;
    };

    EntityBuilder with(CameraComponent data)
    {
        m_camera = data;
        camera_set = true;
        return *this;
    };

    EntityBuilder with(TextureComponent data)
    {
        m_texture = data;
        texture_set = true;
        return *this;
    };

    EntityBuilder with(HierarchyComponent data)
    {
        m_hierarchy = data;
        hierarchy_set = true;
        return *this;
    };

    EntityBuilder with_parent(Entity parent)
    {
        HierarchyComponent hierarchy_component = HierarchyComponent { .parent = parent };
        m_hierarchy = hierarchy_component;
        hierarchy_set = true;
        return *this;
    }

    Entity build();

private:
    std::shared_ptr<World> m_world;

    Transform m_transform;
    TextureComponent m_texture;
    MeshComponent m_mesh;
    ShaderComponent m_shader;
    CameraComponent m_camera;
    HierarchyComponent m_hierarchy;

    bool transform_set = false;
    bool texture_set = false;
    bool mesh_set = false;
    bool shader_set = false;
    bool camera_set = false;
    bool hierarchy_set = false;
};

#endif //DEMO_ENTITY_BUILDER_H
