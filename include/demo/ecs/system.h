#ifndef DEMO_ECS_SYSTEM_HPP
#define DEMO_ECS_SYSTEM_HPP

#include <set>

#include <demo/ecs/ecs.h>
#include <demo/input_processor.h>
#include <demo/timer.h>

class Coordinator;

class System
{
    public:
        std::set<Entity> entities;
};

class UpdatableSystem: public System
{
    public:
        virtual void update(Time time, InputState* input) {}
        virtual void late_update(Time time, InputState* input) {}
};

#endif
