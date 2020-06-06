#include "rotating_cube.h"
#include <demo/ecs/coordinator.h>

void RotatingCubeSystem::update(Time time, InputState* input)
{
    quaternion cube_rotation = quaternion::angle_axis(time.delta_time, float3(0, 1, 0));

    for (Entity const& entity: entities)
    {
        TransformComponent transformComponent = coordinator->get_component<TransformComponent>(entity);

        transformComponent.rotation *= cube_rotation;
    }
}
