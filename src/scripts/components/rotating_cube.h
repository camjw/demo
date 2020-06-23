#ifndef DEMO_ROTATING_CUBE_COMPONENT_H
#define DEMO_ROTATING_CUBE_COMPONENT_H

#include <ecs/system.h>
#include <maths/transform.h>
#include <input_processor.h>
#include <timer.h>

// Just a label really
struct RotatingCubeComponent
{
    float rotation_speed;
};

class RotatingCubeSystem : public System
{
public:
    RotatingCubeSystem(World* world) : System(world) {}

    virtual ~RotatingCubeSystem() { }
    void update(Time time, InputState* input) override;

};

#endif // DEMO_ROTATING_CUBE_COMPONENT_H
