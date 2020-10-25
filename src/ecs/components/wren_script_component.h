#ifndef DEMO_WREN_SCRIPT_COMPONENT_H
#define DEMO_WREN_SCRIPT_COMPONENT_H

#include <ecs/world.h>

struct WrenScriptComponent
{
    std::string script_filename;
};

REGISTER_COMPONENT(WrenScript, WrenScriptComponent)

#endif // DEMO_WREN_SCRIPT_COMPONENT_H
