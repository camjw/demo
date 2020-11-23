#include "entity_builder.h"
#include <ecs/world.h>

Entity EntityBuilder::build()
{
    Entity entity = m_world->create_empty_entity();

    if (transform_set)
    {
        m_world->add_component(entity, m_transform);
    }

    if (camera_set)
    {
        m_world->add_component(entity, m_camera);
    }

    if (hierarchy_set)
    {
        m_world->add_component(entity, m_hierarchy);
    }

    if (name_set)
    {
        m_world->add_component(entity, m_name);
    }

    if (point_light_set)
    {
        m_world->add_component(entity, m_point_light);
    }

    if (directional_light_set)
    {
        m_world->add_component(entity, m_directional_light);
    }

    if (mesh_renderer_set)
    {
        m_world->add_component(entity, m_mesh_renderer);
    }

    if (cube_map_renderer_set)
    {
        m_world->add_component(entity, m_cube_map_renderer);
    }

    return entity;
}

