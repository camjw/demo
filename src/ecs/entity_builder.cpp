#include "entity_builder.h"
#include <ecs/world.h>

Entity EntityBuilder::build()
{
    Entity entity = m_world->create_empty_entity();

    if (transform_set)
    {
        m_world->add_component(entity, m_transform);
    }

    if (texture_set)
    {
        m_world->add_component(entity, m_texture);
    }

    if (material_set)
    {
        m_world->add_component(entity, m_material);
    }

    if (mesh_set)
    {
        m_world->add_component(entity, m_mesh);
    }

    if (shader_set)
    {
        m_world->add_component(entity, m_shader);
    }

    if (camera_set)
    {
        m_world->add_component(entity, m_camera);
    }

    if (hierarchy_set)
    {
        m_world->add_component(entity, m_hierarchy);
    }

    return entity;
}

