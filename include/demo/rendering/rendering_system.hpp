#ifndef DEMO_RENDERING_RENDERING_SYSTEM_HPP
#define DEMO_RENDERING_RENDERING_SYSTEM_HPP

#include <demo/ecs/system.hpp>
#include <demo/ecs/coordinator.hpp>
#include <demo/ecs/ecs.hpp>

#include <demo/window.hpp>

class RenderingSystem : public System
{
    public:
        RenderingSystem(Window* window, Coordinator* coordinator);
        void draw();

    private:
        Entity camera;
};

#endif
