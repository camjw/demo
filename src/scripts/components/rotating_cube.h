#ifndef DEMO_ROTATING_CUBE_COMPONENT_H
#define DEMO_ROTATING_CUBE_COMPONENT_H

#include <demo/ecs/system.h>
#include <demo/input_processor.h>
#include <demo/maths/transform.h>
#include <demo/timer.h>

// Just a label really
struct RotatingCubeComponent
{
};

class RotatingCubeSystem : public System
{
public:
    RotatingCubeSystem(std::shared_ptr<Coordinator> coordinator)
        : System()
        , coordinator(coordinator)
    {
    }

    virtual ~RotatingCubeSystem() { }
    void update(Time time, InputState* input) override;

private:
    std::shared_ptr<Coordinator> coordinator;
};

#endif // DEMO_ROTATING_CUBE_COMPONENT_H
