#ifndef DEMO_WREN_SCRIPTING_SYSTEM_H
#define DEMO_WREN_SCRIPTING_SYSTEM_H

#include <ecs/world.h>
#include <wren.hpp>

class WrenScriptingSystem : public System
{
public:
    WrenScriptingSystem(World* world);
    virtual ~WrenScriptingSystem() { }
    void update(Time time, InputState* input) override;

private:
    static void wren_logger(WrenVM* vm, const char* text);
    static void wren_error(WrenVM* vm, WrenErrorType errorType, const char* module, const int line, const char* msg);
    static char* wren_load_module(WrenVM* vm, const char* name);

    static std::unordered_map<std::string, std::string> script_contents;

    static const char* get_or_load_script(const std::string& filename);
    static void handle_wren_result(WrenInterpretResult result);

    WrenVM* wren_vm;
};

#endif //DEMO_WREN_SCRIPTING_SYSTEM_H
