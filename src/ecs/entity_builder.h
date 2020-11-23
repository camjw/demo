#ifndef DEMO_ENTITY_BUILDER_H
#define DEMO_ENTITY_BUILDER_H

#include <ecs/components/camera_component.h>
#include <ecs/components/cube_map_renderer.h>
#include <ecs/components/hierarchy_component.h>
#include <ecs/components/mesh_renderer.h>
#include <ecs/components/name_component.h>
#include <maths/transform.h>
#include <memory>
#include <rendering/data/cube_map.h>
#include <rendering/lighting/directional_light.h>
#include <rendering/lighting/point_light.h>

class World;
class EntityBuilder
{
public:
    EntityBuilder(std::shared_ptr<World> world)
        : m_world(world)
    {
    }

    EntityBuilder* with(Transform data)
    {
        m_transform = data;
        transform_set = true;
        return this;
    }

    EntityBuilder* with(MeshRenderer data)
    {
        m_mesh_renderer = data;
        mesh_renderer_set = true;
        return this;
    };

    EntityBuilder* with(CubeMapRenderer data)
    {
        m_cube_map_renderer = data;
        cube_map_renderer_set = true;
        return this;
    };

    EntityBuilder* with(NameComponent data)
    {
        m_name = data;
        name_set = true;
        return this;
    };

    EntityBuilder* with(Camera data)
    {
        m_camera = data;
        camera_set = true;
        return this;
    };

    EntityBuilder* with(HierarchyComponent data)
    {
        m_hierarchy = data;
        hierarchy_set = true;
        return this;
    };

    EntityBuilder* with(PointLight data)
    {
        m_point_light = data;
        point_light_set = true;
        return this;
    };

    EntityBuilder* with(DirectionalLight data)
    {
        m_directional_light = data;
        directional_light_set = true;
        return this;
    };

    EntityBuilder* with_parent(Entity parent)
    {
        HierarchyComponent hierarchy_component = HierarchyComponent { .parent = parent };
        m_hierarchy = hierarchy_component;
        hierarchy_set = true;
        return this;
    }

    Entity build();

private:
    std::shared_ptr<World> m_world;

    Transform m_transform;
    Camera m_camera;
    HierarchyComponent m_hierarchy;
    PointLight m_point_light;
    NameComponent m_name;
    DirectionalLight m_directional_light;
    MeshRenderer m_mesh_renderer;
    CubeMapRenderer m_cube_map_renderer;

    bool transform_set = false;
    bool mesh_renderer_set = false;
    bool camera_set = false;
    bool hierarchy_set = false;
    bool name_set = false;
    bool point_light_set = false;
    bool directional_light_set = false;
    bool cube_map_renderer_set = false;
};

#endif //DEMO_ENTITY_BUILDER_H
