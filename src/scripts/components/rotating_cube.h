#ifndef DEMO_ROTATING_CUBE_COMPONENT_H
#define DEMO_ROTATING_CUBE_COMPONENT_H

#include <demo/ecs/system.h>
#include <demo/input_processor.h>
#include <demo/maths/transform.h>
#include <demo/timer.h>

// Just a label really
struct RotatingCubeComponent
{
    float rotation_speed;
};

class RotatingCubeSystem : public System
{
public:
    RotatingCubeSystem(World* coordinator) : System(coordinator) {}

    virtual ~RotatingCubeSystem() { }
    void update(Time time, InputState* input) override;

};

#endif // DEMO_ROTATING_CUBE_COMPONENT_H
