#include "rotating_cube.h"
#include <ecs/world.h>

void RotatingCubeSystem::update(Time time, InputState* input)
{

    for (Entity const& entity : entities)
    {
        Transform* transform = &world->get_component<Transform>(entity);
        RotatingCubeComponent rotating_cube = world->get_component<RotatingCubeComponent>(entity);

        quaternion cube_rotation = quaternion::angle_axis(rotating_cube.speed * time.delta_time, rotating_cube.axis.normalise());

        transform->rotation *= cube_rotation;
        transform->rotation.normalise();
    }
}
