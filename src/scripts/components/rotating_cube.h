#ifndef DEMO_ROTATING_CUBE_COMPONENT_H
#define DEMO_ROTATING_CUBE_COMPONENT_H

#include <ecs/system.h>
#include <input/input_processor.h>
#include <maths/transform.h>
#include <timer.h>

struct RotatingCubeComponent
{
    // speed is basically in radians per millisecond
    float speed;
    float3 axis;
};

REGISTER_COMPONENT(RotatingCube, RotatingCubeComponent)

class RotatingCubeSystem : public System
{
public:
    RotatingCubeSystem(World* world)
        : System(world)
    {
    }

    virtual ~RotatingCubeSystem() { }
    void update(Time time, InputState* input) override;
};

#endif // DEMO_ROTATING_CUBE_COMPONENT_H
