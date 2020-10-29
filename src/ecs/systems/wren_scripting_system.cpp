#include "wren_scripting_system.h"
#include <ecs/components/wren_script_component.h>
#include <fstream>

std::unordered_map<std::string, std::string> WrenScriptingSystem::script_contents;

WrenScriptingSystem::WrenScriptingSystem(World* world)
    : System(world)
{
    WrenConfiguration config;
    wrenInitConfiguration(&config);

    config.writeFn = &wren_logger;
    config.errorFn = &wren_error;
    config.loadModuleFn = &wren_load_module;

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

    for (Entity const& entity : entities)
    {
        // TODO: come back to this
//        WrenScriptComponent& script = world->get_component<WrenScriptComponent>(entity);
//        WrenInterpretResult result = wrenInterpret(wren_vm, module, get_or_load_script(script.script_filename));
//        handle_wren_result(result);
//
//        wrenEnsureSlots(wren_vm, 1);
//        wrenGetVariable(wren_vm, "main", "HelloWorld", 0);
//        WrenHandle* gameEngineClass = wrenGetSlotHandle(wren_vm, 0);
//        WrenHandle* method = wrenMakeCallHandle(wren_vm, "new()");
//        wrenSetSlotHandle(wren_vm, 0, gameEngineClass);
//        WrenInterpretResult result1 = wrenCall(wren_vm, method);
//        handle_wren_result(result1);
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

char* WrenScriptingSystem::wren_load_module(WrenVM* vm, const char* name)
{
    return const_cast<char*>(get_or_load_script("assets/scripts/" + std::string(name) + ".wren"));
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

const char* WrenScriptingSystem::get_or_load_script(const std::string& filename)
{
    if (script_contents.find(filename) == script_contents.end())
    {
        std::ifstream in(filename);
        std::string contents((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        script_contents.insert(std::pair<std::string, std::string>(filename, contents));
    }

    return script_contents.find(filename)->second.c_str();
}
