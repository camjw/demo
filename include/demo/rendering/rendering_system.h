#ifndef DEMO_RENDERING_RENDERING_SYSTEM_HPP
#define DEMO_RENDERING_RENDERING_SYSTEM_HPP

#include <demo/ecs/coordinator.h>
#include <demo/ecs/ecs.h>
#include <demo/ecs/system.h>

#include <demo/scene/camera.h>
#include <demo/window.h>

#include <demo/context/mesh_repository.h>
#include <demo/context/shader_repository.h>
#include <demo/context/texture_repository.h>
#include <demo/rendering/cube_map.h>
#include <demo/rendering/shader.h>
#include <demo/rendering/texture.h>

#include <demo/context/demo_context.h>
#include <demo/rendering/shader_commands/shader_commands.h>
#include <demo/scene/scene.h>
#include <imgui/bindings/imgui_impl_glfw.h>
#include <imgui/bindings/imgui_impl_opengl3.h>
#include <imgui/imgui.h>

class RenderingSystem : public System
{
public:
    void init(std::shared_ptr<DemoContext> context, Window* window, Coordinator* coordinator);
    void draw(Time time, Scene* scene);

private:
    void begin_draw(Time time);
    void set_camera(Scene* scene);
    void draw_entities();
    void end_draw();

    Camera* camera {};
    Window* window {};
    Coordinator* coordinator {};

    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<ShaderRepository> shader_repository;
};

#endif
