#ifndef DEMO_HIERARCHY_COMPONENT_H
#define DEMO_HIERARCHY_COMPONENT_H

#include <ecs/world.h>
#include <maths/transform.h>

struct HierarchyComponent
{
    Entity parent = INVALID_ENTITY;
};

REGISTER_COMPONENT(Hierarchy, HierarchyComponent)

#endif // DEMO_HIERARCHY_COMPONENT_H
