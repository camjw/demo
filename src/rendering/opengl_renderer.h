#ifndef DEMO_OPENGL_RENDERER_HPP
#define DEMO_OPENGL_RENDERER_HPP

#include <context/demo_context.h>
#include <ecs/components/camera_component.h>
#include <ecs/ecs.h>
#include <ecs/signature_builder.h>
#include <ecs/system.h>
#include <ecs/world.h>
#include <imgui/bindings/imgui_impl_glfw.h>
#include <imgui/bindings/imgui_impl_opengl3.h>
#include <imgui/imgui.h>
#include <maths/transform.h>
#include <rendering/cube_map.h>
#include <rendering/directional_light.h>
#include <rendering/material.h>
#include <rendering/point_light.h>
#include <rendering/shader.h>
#include <rendering/shader_commands/shader_commands.h>
#include <rendering/texture.h>
#include <resources/mesh_repository.h>
#include <resources/shader_repository.h>
#include <resources/texture_repository.h>
#include <scene/scene.h>
#include <scene/scene_graph.h>
#include <utils/opengl_helpers.h>
#include <window.h>

class OpenGLRenderer
{
public:
    OpenGLRenderer(std::shared_ptr<DemoContext> context, Window* window, std::shared_ptr<World> world);
    void draw_scene(const Time time, const Scene* scene);

private:
    void begin_draw(const Time time);
    void set_camera(const Entity camera_entity);
    void process_lights() const;
    void process_point_lights(const std::vector<Entity> point_lights) const ;
    void process_directional_lights(const std::vector<Entity> directional_lights) const;
    void draw_scene_graph(const Scene* scene);
    void draw_node(const SceneNode* scene_node, glm::mat4 parent_transform) const;
    void draw_entity(const Entity entity, glm::mat4 parent_transform) const;
    void draw_skybox() const;
    void end_draw() const ;
    glm::mat4 get_view_matrix(const CameraComponent& cameraComponent, const Transform& transform) const;

    Window* window {};

    std::shared_ptr<World> world;
    std::shared_ptr<MeshRepository> mesh_repository;
    std::shared_ptr<TextureRepository> texture_repository;
    std::shared_ptr<ShaderRepository> shader_repository;


    bool isCameraSet;
};

#endif
