#ifndef DEMO_HIERARCHY_COMPONENT_H
#define DEMO_HIERARCHY_COMPONENT_H

#include <ecs/ecs.h>
#include <maths/transform.h>

struct HierarchyComponent : Component
{
    Entity parent = INVALID_ENTITY;
};

#endif // DEMO_HIERARCHY_COMPONENT_H
