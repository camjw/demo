#ifndef DEMO_ECS_SYSTEM_HPP
#define DEMO_ECS_SYSTEM_HPP

#include <set>

#include <ecs/ecs.h>
#include <input/input_processor.h>
#include <timer.h>

class World;

class System
{
public:
    System(World* world) : world(world) {}

    inline void set_world(World* _world)
    {
        this->world = _world;
    }

    virtual void update(Time time, InputState* input) { }
    virtual void late_update(Time time, InputState* input) { }

    std::set<Entity> entities;

protected:
    World* world;

};

#endif
