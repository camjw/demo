#include "rotating_cube.h"
#include <demo/ecs/coordinator.h>

void RotatingCubeSystem::update(Time time, InputState* input)
{
    for (Entity const& entity: entities)
    {
        TransformComponent transformComponent = coordinator->get_component<TransformComponent>(entity);
    }
}
