#include "rotating_cube.h"
#include <ecs/world.h>

void RotatingCubeSystem::update(Time time, InputState* input)
{
    quaternion cube_rotation = quaternion::angle_axis(time.delta_time, float3(0, 1, 0));

    for (Entity const& entity : entities)
    {
        Transform* transformComponent = &world->get_component<Transform>(entity);

        transformComponent->rotation *= cube_rotation;
        transformComponent->rotation.normalise();

        printf("transform quaternion: %s\n", transformComponent->rotation.to_string().c_str());
        printf("cube rotation: %s\n", cube_rotation.to_string().c_str());
        printf("quaternion norm %f\n", transformComponent->rotation.length());
    }
}
