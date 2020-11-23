#ifndef DEMO_OPENGL_RENDERER_HPP
#define DEMO_OPENGL_RENDERER_HPP

#include "render_queue.h"
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
#include <rendering/data/cube_map.h>
#include <rendering/data/material.h>
#include <rendering/data/shader.h>
#include <rendering/data/texture.h>
#include <rendering/framebuffer.h>
#include <rendering/lighting/directional_light.h>
#include <rendering/lighting/point_light.h>
#include <rendering/renderbuffer.h>
    #include <scene/scene.h>
#include <scene/scene_graph.h>
#include <ui/ui_root.h>
#include <utils/opengl_helpers.h>
#include <window.h>

class OpenGLRenderer
{
public:
    OpenGLRenderer(std::shared_ptr<DemoContext> context, std::shared_ptr<Window> window,
        std::shared_ptr<World> world, std::shared_ptr<UIRoot> ui_root);
    void draw_scene(const Time time, const Scene* scene);

private:
    void begin_draw(const Time time, const Scene* scene);
    void set_camera(const Entity camera_entity);
    void process_lights(const Scene* scene);
    void process_directional_lights(const std::vector<Entity> directional_lights) const;
    void process_point_lights(const std::vector<Entity> point_lights) const;
    void process_spot_lights(const std::vector<Entity> spot_lights) const;
    void draw_scene_graph(const Scene* scene);
    void draw_node(const SceneNode* scene_node, glm::mat4 parent_transform);
    void draw_entity(const Entity entity, glm::mat4 parent_transform);
    void enqueue_mesh(const Entity entity, glm::mat4 parent_transform);
    void draw_skybox(const Entity entity) const;
    void process_render_commands(const Scene* scene) const;
    void resize_framebuffers();
    glm::mat4 get_view_matrix(const Camera& cameraComponent, const Transform& transform) const;

    std::shared_ptr<Window> window;

    std::shared_ptr<World> world;
    std::shared_ptr<ResourceManager> resource_manager;

    std::unique_ptr<RenderQueue> opaque_render_queue;
    std::unique_ptr<RenderQueue> transparent_render_queue;

    std::unique_ptr<Framebuffer> framebuffer;

    std::shared_ptr<UIRoot> ui_root;

    bool is_camera_set = false;
    int current_light_index = 0;

    std::vector<float3> lightPositions;
    std::vector<float3> lightColors;
    void process_command(const RenderCommand& command) const;
    void end_draw();
};

#endif
