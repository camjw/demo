#include <rendering/opengl_renderer.h>

OpenGLRenderer::OpenGLRenderer(std::shared_ptr<DemoContext> context,
    Window* _window, std::shared_ptr<World> _world)
{
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    glCheckError();

    this->window = _window;
    this->world = _world;

    mesh_repository = context->get_mesh_repository();
    texture_repository = context->get_texture_repository();
    shader_repository = context->get_shader_repository();
}

void OpenGLRenderer::begin_draw(const Time time)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set common variables for shaders
    // TODO: set uniform struct rather than individual params
    shader_repository->for_each(SetShaderTime(time));
    shader_repository->for_each(SetShaderProjection(window->get_projection_matrix()));

    is_camera_set = false;
}

void OpenGLRenderer::draw_scene_graph(const Scene* scene)
{
    set_camera(scene->get_camera());
    draw_skybox(scene->get_skybox());
    glm::mat4 transform = Transform::identity().get_model_matrix();
    draw_node(scene->get_root_node(), transform);
}

void OpenGLRenderer::draw_node(const SceneNode* scene_node, glm::mat4 parent_transform) const
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

void OpenGLRenderer::search_for_point_lights(const SceneNode* scene_node, glm::mat4 parent_transform)
{
    Transform node_transform = Transform::identity();
    if (world->has_component<Transform>(scene_node->get_entity()))
    {
        // Can only draw something if it has a position in space
        populate_point_light(scene_node->get_entity());
        node_transform = world->get_component<Transform>(scene_node->get_entity());
    }

    // Draw child nodes
    for (SceneNode* const& child_node : scene_node->get_children())
    {
        search_for_point_lights(child_node, parent_transform * node_transform.get_model_matrix());
    }
}

void OpenGLRenderer::draw_entity(const Entity entity, glm::mat4 parent_transform) const
{
    if (world->has_component<Material>(entity) && world->has_component<MeshComponent>(entity))
    {
        draw_mesh(entity, parent_transform);
    }
}

void OpenGLRenderer::draw_mesh(const Entity entity, glm::mat4 parent_transform) const
{
    Material material = world->get_component<Material>(entity);
    std::shared_ptr<Shader> shader = shader_repository->get_shader(material.shader);
    shader->bind();
    glCheckError();

    if (material.diffuse_texture != INVALID_TEXTURE)
    {
        std::shared_ptr<Texture> diffuse_texture = texture_repository->get_texture(material.diffuse_texture);
        std::shared_ptr<Texture> specular_texture = texture_repository->get_texture(material.specular_texture);
        diffuse_texture->bind(0);
        specular_texture->bind(1);
        shader->set_int("material.diffuse_texture", 0);
        shader->set_int("material.specular_texture", 1);
    }

    shader->set_float3("material.ambient_colour", material.ambient_colour);
    shader->set_float3("material.diffuse_colour", material.diffuse_colour);
    shader->set_float3("material.specular_colour", material.specular_colour);
    shader->set_float("material.shininess", material.shininess);

    Transform transform = world->get_component<Transform>(entity);
    glm::mat4 model_matrix = parent_transform * transform.get_model_matrix();
    glm::mat3 normal_model_matrix = glm::transpose(glm::inverse(model_matrix));
    shader->set_mat4(DEMO_CONSTANTS_MODEL, model_matrix);
    shader->set_mat3(DEMO_CONSTANTS_NORMAL_MODEL, normal_model_matrix);

    MeshComponent mesh = world->get_component<MeshComponent>(entity);
    std::shared_ptr<Mesh> render_mesh = mesh_repository->get_mesh(mesh.id);
    render_mesh->bind();
    render_mesh->draw();
    glCheckError();
}

void OpenGLRenderer::draw_skybox(const Entity entity) const
{
}

void OpenGLRenderer::end_draw() const
{
    glfwSwapBuffers(window->get_glfw_window());
    glfwPollEvents();
}

void OpenGLRenderer::set_camera(const Entity camera_entity)
{
    CameraComponent& camera = world->get_component<CameraComponent>(camera_entity);
    Transform& camera_transform = world->get_component<Transform>(camera_entity);
    shader_repository->for_each(SetShaderCamera(
        camera_transform.position,
        camera_transform.position + camera.forward,
        get_view_matrix(camera, camera_transform)));

    is_camera_set = true;
}

void OpenGLRenderer::draw_scene(const Time time, const Scene* scene)
{
    begin_draw(time);
    process_lights(scene);
    draw_scene_graph(scene);
    end_draw();
}

glm::mat4 OpenGLRenderer::get_view_matrix(const CameraComponent& cameraComponent, const Transform& transform) const
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
    Signature point_light_and_transform = world->get_signature_builder()
                                              .with<Transform>()
                                              .with<PointLight>()
                                              .build();

    std::vector<Entity> point_lights = world->get_entities_with_signature(point_light_and_transform);

    process_point_lights(point_lights);
    glm::mat4 transform = Transform::identity().get_model_matrix();
    search_for_point_lights(scene->get_root_node(), transform);

    Signature directional_light = world->get_signature_builder()
                                      .with<DirectionalLight>()
                                      .build();

    std::vector<Entity> directional_lights = world->get_entities_with_signature(directional_light);

    process_directional_lights(directional_lights);
}

void OpenGLRenderer::process_point_lights(const std::vector<Entity> point_lights) const
{
    std::shared_ptr<Shader> lighting_shader = shader_repository->get_shader("lighting");

    for (int i = 0; i < point_lights.size(); i++)
    {
        PointLight point_light = world->get_component<PointLight>(point_lights[i]);
        Transform transform = world->get_component<Transform>(point_lights[i]);

        point_light.bind(lighting_shader, i, transform.position);
    }

    lighting_shader->bind();
    lighting_shader->set_int(DEMO_NUM_ACTIVE_POINT_LIGHTS, point_lights.size());
}

void OpenGLRenderer::process_directional_lights(const std::vector<Entity> directional_lights) const
{
    std::vector<DirectionalLight> directional_light_components;
    for (int i = 0; i < directional_lights.size(); i++)
    {
        directional_light_components.push_back(world->get_component<DirectionalLight>(directional_lights[i]));
    }

    assert(directional_light_components.size() < MAX_NUM_DIRECTIONAL_LIGHTS && "trying to send too many point lights to GPU");

    shader_repository->for_each(SetShaderDirectionalLights(directional_light_components));
}

void OpenGLRenderer::populate_point_light(Entity entity)
{
    assert(current_light_index < MAX_NUM_POINT_LIGHTS && "trying to send too many point lights to GPU");
    if (!world->has_component<PointLight>(entity))
    {
        return;
    }

    shader_repository->for_each(SetShaderPointLight(world->get_component<PointLight>(entity), current_light_index++));
}
