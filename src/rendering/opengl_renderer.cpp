#include "rendering/lighting/spot_light.h"
#include <constants/shader_constants.h>
#include <rendering/opengl_renderer.h>

OpenGLRenderer::OpenGLRenderer(std::shared_ptr<DemoContext> context,
    std::shared_ptr<Window> window, std::shared_ptr<World> world, std::shared_ptr<UIRoot> ui_root)
    : window(window)
    , world(world)
    , ui_root(ui_root)
{
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glCheckError();

    resource_manager = context->get_resource_manager();

    opaque_render_queue = std::make_unique<RenderQueue>();
    transparent_render_queue = std::make_unique<RenderQueue>();

    // Build framebuffer
    framebuffer = std::make_unique<Framebuffer>(window->width(), window->height());
}

void OpenGLRenderer::begin_draw(const Time time, const Scene* scene)
{
    glfwPollEvents();

    resource_manager->for_each<Shader>([time](Shader* shader) {
        shader->bind();
        shader->set_float(DEMO_CONSTANTS_TOTAL_TIME, time.total_time);
        shader->set_float(DEMO_CONSTANTS_DELTA_TIME, time.delta_time);
    });

    if (window->has_dirty_size)
    {
        resize_framebuffers();
        window->has_dirty_size = false;
    }

    is_camera_set = false;

    ui_root->new_frame();
}

void OpenGLRenderer::resize_framebuffers()
{
    framebuffer.reset();
    framebuffer = std::make_unique<Framebuffer>(window->width(), window->height());
}

void OpenGLRenderer::draw_scene_graph(const Scene* scene)
{
    opaque_render_queue->clear();
    set_camera(scene->get_camera());
    draw_skybox(scene->get_skybox());
    glm::mat4 transform = Transform::identity().get_model_matrix();
    draw_node(scene->get_root_node(), transform);
}

void OpenGLRenderer::draw_node(const SceneNode* scene_node, glm::mat4 parent_transform)
{
    Transform node_transform = Transform::identity();
    if (world->has_component<Transform>(scene_node->get_entity()))
    {
        // Can only draw something if it has a position in space
        draw_entity(scene_node->get_entity(), parent_transform);
        node_transform = world->get_component<Transform>(scene_node->get_entity());
    }

    // Draw child nodes
    for (SceneNode* const& child_node : scene_node->get_children())
    {
        draw_node(child_node, parent_transform * node_transform.get_model_matrix());
    }
}

void OpenGLRenderer::draw_entity(const Entity entity, glm::mat4 parent_transform)
{
    if (world->has_component<MeshRenderer>(entity))
    {
        enqueue_mesh(entity, parent_transform);
    }
}

void OpenGLRenderer::enqueue_mesh(const Entity entity, glm::mat4 parent_transform)
{
    MeshRenderer mesh_renderer = world->get_component<MeshRenderer>(entity);

    RenderCommand command;
    command.mesh = mesh_renderer.mesh;
    command.material = mesh_renderer.material;
    Transform transform = world->get_component<Transform>(entity);
    glm::mat4 model_matrix = parent_transform * transform.get_model_matrix();
    command.transform = model_matrix;

    opaque_render_queue->push_back(command);
}

void OpenGLRenderer::draw_skybox(const Entity entity) const
{
}

void OpenGLRenderer::process_render_commands(const Scene* scene) const
{
    framebuffer->bind();

    float3 clear_colour = scene->get_clear_colour();
    glClearColor(clear_colour.x, clear_colour.y, clear_colour.z, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_FRAMEBUFFER_SRGB);
    glDisable(GL_BLEND);
    glViewport(0, 0, window->width(), window->height());

    for (const RenderCommand& command : opaque_render_queue->commands)
    {
        process_command(command);
    }

    framebuffer->unbind();
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int2 viewportDimensions = window->get_viewport_dimensions();
    glViewport(0, 0, viewportDimensions.x, viewportDimensions.y);

    Shader* deferred_shader = resource_manager->get<Shader>("deferred_lighting");
    deferred_shader->bind();

    framebuffer->bind_textures();
    deferred_shader->set_int("gPosition", 0);
    deferred_shader->set_int("gNormal", 1);
    deferred_shader->set_int("gAlbedoSpec", 2);
    glCheckError();

    resource_manager->get<Mesh>("square")->bind_and_draw();
    glCheckError();
}

void OpenGLRenderer::end_draw()
{
    glfwSwapBuffers(window->get_glfw_window());
}

void OpenGLRenderer::set_camera(const Entity camera_entity)
{
    Camera& camera = world->get_component<Camera>(camera_entity);
    Transform& camera_transform = world->get_component<Transform>(camera_entity);

    float aspect_ratio = window->get_aspect_ratio();

    glm::mat4 projection_matrix;
    if (camera.projection_type == PERSPECTIVE)
    {
        projection_matrix = glm::perspective(glm::radians(camera.fov), aspect_ratio, camera.near_plane, camera.far_plane);
    }
    else
    {
        projection_matrix = glm::ortho(glm::radians(camera.fov), aspect_ratio, camera.near_plane, camera.far_plane);
    }

    glm::mat4 view_matrix = get_view_matrix(camera, camera_transform);
    resource_manager->for_each<Shader>([projection_matrix, camera_transform, camera, view_matrix](Shader* shader) {
        shader->bind();
        shader->set_mat4(DEMO_CONSTANTS_PROJECTION, projection_matrix);
        shader->set_float3(DEMO_CONSTANTS_CAMERA_POSITION, camera_transform.position);
        shader->set_float3(DEMO_CONSTANTS_CAMERA_FORWARD, camera_transform.position + camera.forward);
        shader->set_mat4(DEMO_CONSTANTS_VIEW, view_matrix);
    });

    is_camera_set = true;
}

void OpenGLRenderer::draw_scene(const Time time, const Scene* scene)
{
    begin_draw(time, scene);
    process_lights(scene);
    // TODO: add frustum culling here
    draw_scene_graph(scene);
    process_render_commands(scene);
    ui_root->draw();
    end_draw();
}

glm::mat4 OpenGLRenderer::get_view_matrix(const Camera& cameraComponent, const Transform& transform) const
{
    return glm::lookAt(
        transform.position.to_glm(),
        transform.position.to_glm() + cameraComponent.forward.to_glm(),
        cameraComponent.up.to_glm());
}

// TODO: should probably refactor this so that it only gets the active lights in a scene up to
// a maximum number
void OpenGLRenderer::process_lights(const Scene* scene)
{
    Signature directional_light = world->get_signature_builder()
                                      .with<DirectionalLight>()
                                      .build();
    std::vector<Entity> directional_lights = world->get_entities_with_signature(directional_light);
    process_directional_lights(directional_lights);

    Signature point_light_and_transform = world->get_signature_builder()
                                              .with<PointLight>()
                                              .with<Transform>()
                                              .build();
    std::vector<Entity> point_lights = world->get_entities_with_signature(point_light_and_transform);
    process_point_lights(point_lights);

    Signature spot_light_and_transform = world->get_signature_builder()
                                             .with<SpotLight>()
                                             .with<Transform>()
                                             .build();
    std::vector<Entity> spot_lights = world->get_entities_with_signature(spot_light_and_transform);
    process_spot_lights(spot_lights);
}

void OpenGLRenderer::process_point_lights(const std::vector<Entity> point_lights) const
{
    assert(point_lights.size() < MAX_NUM_POINT_LIGHTS && "trying to send too many point lights to GPU");

    Shader* lighting_shader = resource_manager->get<Shader>("deferred_lighting");
    lighting_shader->bind();
    lighting_shader->set_int(DEMO_NUM_ACTIVE_POINT_LIGHTS, point_lights.size());

    for (int i = 0; i < point_lights.size(); i++)
    {
        PointLight point_light = world->get_component<PointLight>(point_lights[i]);
        Transform transform = world->get_component<Transform>(point_lights[i]);

        point_light.bind(lighting_shader, i, transform.position);
    }
}

void OpenGLRenderer::process_spot_lights(const std::vector<Entity> spot_lights) const
{
    assert(spot_lights.size() < MAX_NUM_SPOT_LIGHTS && "trying to send too many spot lights to GPU");

    Shader* lighting_shader = resource_manager->get<Shader>("deferred_lighting");
    lighting_shader->bind();
    lighting_shader->set_int(DEMO_NUM_ACTIVE_SPOT_LIGHTS, spot_lights.size());

    for (int i = 0; i < spot_lights.size(); i++)
    {
        SpotLight spot_light = world->get_component<SpotLight>(spot_lights[i]);
        Transform transform = world->get_component<Transform>(spot_lights[i]);

        spot_light.bind(lighting_shader, i, transform.position);
    }
}

void OpenGLRenderer::process_directional_lights(const std::vector<Entity> directional_lights) const
{
    assert(directional_lights.size() < MAX_NUM_DIRECTIONAL_LIGHTS && "trying to send too many directional lights to GPU");

    Shader* lighting_shader = resource_manager->get<Shader>("deferred_lighting");
    lighting_shader->bind();
    lighting_shader->set_int(DEMO_NUM_ACTIVE_DIRECTIONAL_LIGHTS, directional_lights.size());

    for (int i = 0; i < directional_lights.size(); i++)
    {
        DirectionalLight directional_light = world->get_component<DirectionalLight>(directional_lights[i]);
        directional_light.bind(lighting_shader, i);
    }
}

void OpenGLRenderer::process_command(const RenderCommand& command) const
{
    Material* material = resource_manager->get<Material>(command.material);
    Shader* shader = resource_manager->get<Shader>(material->shader);

    glm::mat3 normal_model_matrix = glm::transpose(glm::inverse(command.transform));

    shader->bind();
    shader->set_mat4(DEMO_CONSTANTS_MODEL, command.transform);
    shader->set_mat3(DEMO_CONSTANTS_NORMAL_MODEL, normal_model_matrix);
    shader->set_int("material.diffuse_texture", 0);
    shader->set_int("material.specular_texture", 1);

    resource_manager->get<Texture>(material->diffuse_texture)->bind(0);
    if (material->specular_texture == ResourceHandle::invalid_handle<Texture>())
    {
        resource_manager->get<Texture>(material->diffuse_texture)->bind(1);
    }
    else
    {
        resource_manager->get<Texture>(material->specular_texture)->bind(1);
    }

    material->bind(shader);
    resource_manager->get<Mesh>(command.mesh)->bind_and_draw();
}
