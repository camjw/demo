#include "wren_scripting_system.h"
#include <ecs/components/wren_script_component.h>

WrenScriptingSystem::WrenScriptingSystem(World* world)
    : System(world)
{
    WrenConfiguration config;
    wrenInitConfiguration(&config);

    config.writeFn = &wren_logger;
    config.errorFn = &wren_error;
    wren_vm = wrenNewVM(&config);

    WrenInterpretResult result = wrenInterpret(
        wren_vm,
        "main",
        "System.print(\"WrenVM initialised successfully\")");

    handle_wren_result(result);
}

void WrenScriptingSystem::update(Time time, InputState* input)
{
    const char* module = "main";
    const char* script_content = "System.print(\"I am running in a VM!\")";

    for (Entity const& entity : entities)
    {
        WrenScriptComponent& script = world->get_component<WrenScriptComponent>(entity);

        WrenInterpretResult result = wrenInterpret(wren_vm, module, script_content);
        handle_wren_result(result);
    }
}

void WrenScriptingSystem::wren_logger(WrenVM* vm, const char* text)
{
    printf("%s", text);
}

void WrenScriptingSystem::wren_error(WrenVM* vm, WrenErrorType errorType,
    const char* module, const int line, const char* msg)
{
    switch (errorType)
    {
    case WREN_ERROR_COMPILE:
    {
        printf("Wren compile error: [%s line %d] [Error] %s\n", module, line, msg);
    }
    break;
    case WREN_ERROR_STACK_TRACE:
    {
        printf("Wren stack trace: [%s line %d] in %s\n", module, line, msg);
    }
    break;
    case WREN_ERROR_RUNTIME:
    {
        printf("Wren runtime error: [Runtime Error] %s\n", msg);
    }
    break;
    }
}

void WrenScriptingSystem::handle_wren_result(WrenInterpretResult result)
{
    switch (result)
    {
    case WREN_RESULT_COMPILE_ERROR:
    {
        printf("Compile Error!\n");
    }
    break;
    case WREN_RESULT_RUNTIME_ERROR:
    {
        printf("Runtime Error!\n");
    }
    break;
    case WREN_RESULT_SUCCESS:
        break;
    }
}
