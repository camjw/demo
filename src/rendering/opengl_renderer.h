#ifndef DEMO_OPENGL_RENDERER_HPP
#define DEMO_OPENGL_RENDERER_HPP

#include <ecs/ecs.h>
#include <ecs/system.h>
#include <ecs/world.h>

#include <context/demo_context.h>
#include <context/mesh_repository.h>
#include <context/shader_repository.h>
#include <context/texture_repository.h>
#include <ecs/components/camera_component.h>
#include <imgui/bindings/imgui_impl_glfw.h>
#include <imgui/bindings/imgui_impl_opengl3.h>
#include <imgui/imgui.h>
#include <maths/transform.h>
#include <rendering/cube_map.h>
#include <rendering/shader.h>
#include <rendering/shader_commands/shader_commands.h>
#include <rendering/texture.h>
#include <scene/scene.h>
#include <scene/scene_graph.h>
#include <utils/opengl_helpers.h>
#include <window.h>

class OpenGLRenderer
{
public:
    OpenGLRenderer(std::shared_ptr<DemoContext> context, Window* window, std::shared_ptr<World> world);
    void draw_scene(Time time, Scene* scene);

private:
    void begin_draw(Time time);
    void set_camera(Entity camera_entity);
    void process_lights(Scene* scene);
    void process_point_lights(Scene* scene, std::vector<Entity> point_lights);
    void process_directional_lights(Scene* scene, std::vector<Entity> directional_lights);
    void draw_scene_graph(Scene* scene);
    void draw_node(SceneNode* scene_node, glm::mat4 parent_transform);
    void draw_entity(Entity entity, glm::mat4 parent_transform);
    void draw_skybox();
    void end_draw();

    Window* window {};

    std::shared_ptr<World> world;
    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<ShaderRepository> shader_repository;

    glm::mat4 get_view_matrix(CameraComponent& cameraComponent, Transform& transform);

    bool isCameraSet;
};

#endif
