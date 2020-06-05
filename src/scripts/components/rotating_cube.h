#ifndef DEMO_ROTATING_CUBE_COMPONENT_H
#define DEMO_ROTATING_CUBE_COMPONENT_H

#include <demo/ecs/system.h>

// Just a label really
struct RotatingCubeComponent {};

class RotatingCubeSystem: public System
{
public:
    virtual ~RotatingCubeSystem() {}
    void update(Time time, InputState* input) override;
};
#endif // DEMO_ROTATING_CUBE_COMPONENT_H
