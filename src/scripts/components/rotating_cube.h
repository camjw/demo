#ifndef DEMO_ROTATING_CUBE_COMPONENT_H
#define DEMO_ROTATING_CUBE_COMPONENT_H

#include <ecs/system.h>
#include <maths/transform.h>
#include <input_processor.h>
#include <timer.h>

// Just a label really
struct RotatingCubeComponent
{
    // speed is basically in radians per millisecond
    float speed = 0.001f;
    float3 axis = float3(1, 1, 1);
};

class RotatingCubeSystem : public System
{
public:
    RotatingCubeSystem(World* world) : System(world) {}

    virtual ~RotatingCubeSystem() { }
    void update(Time time, InputState* input) override;

};

#endif // DEMO_ROTATING_CUBE_COMPONENT_H
