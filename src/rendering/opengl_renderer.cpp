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

void OpenGLRenderer::begin_draw(Time time)
{
    glClearColor(0, 0, 0, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set common variables for shaders
    // TODO: set uniform struct rather than individual params
    shader_repository->for_each(new SetShaderTime(time));
    shader_repository->for_each(new SetShaderProjection(window->get_projection_matrix()));

    isCameraSet = false;
}

void OpenGLRenderer::draw_scene_graph(Scene* scene)
{
    set_camera(scene->get_camera());
    glm::mat4 transform = Transform::identity().get_model_matrix();
    draw_node(scene->get_root_node(), transform);
}

void OpenGLRenderer::draw_node(SceneNode* scene_node, glm::mat4 parent_transform)
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

void OpenGLRenderer::draw_entity(Entity entity, glm::mat4 parent_transform)
{
    if (!world->has_component<ShaderComponent>(entity))
    {
        return;
    }

    if (world->has_component<TextureComponent>(entity))
    {
        TextureComponent texture = world->get_component<TextureComponent>(entity);
        texture_repository->get_texture(texture.id)->bind(texture.binding_index);
    }

    ShaderID shader_id = world->get_component<ShaderComponent>(entity).id;
    std::shared_ptr<Shader> shader = shader_repository->get_shader(shader_id);
    shader->bind();

    if (world->has_component<Material>(entity))
    {
        world->get_component<Material>(entity).bind(shader);
    }

    if (world->has_component<PointLight>(entity))
    {
        shader->set_float3("lightColour", world->get_component<PointLight>(entity).colour);
    }

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

void OpenGLRenderer::draw_skybox()
{
}

void OpenGLRenderer::end_draw()
{
    glfwSwapBuffers(window->get_glfw_window());
    glfwPollEvents();
}

void OpenGLRenderer::set_camera(Entity camera_entity)
{
    CameraComponent& camera = world->get_component<CameraComponent>(camera_entity);
    Transform& camera_transform = world->get_component<Transform>(camera_entity);
    shader_repository->for_each(new SetShaderCamera(
        camera_transform.position,
        camera_transform.position + camera.forward,
        get_view_matrix(camera, camera_transform)));

    isCameraSet = true;
}

void OpenGLRenderer::draw_scene(Time time, Scene* scene)
{
    begin_draw(time);
    process_lights();
    draw_scene_graph(scene);
    end_draw();
}

glm::mat4 OpenGLRenderer::get_view_matrix(CameraComponent& cameraComponent, Transform& transform)
{
    return glm::lookAt(
        transform.position.to_glm(),
        transform.position.to_glm() + cameraComponent.forward.to_glm(),
        cameraComponent.up.to_glm());
}

// TODO: should probably refactor this so that it only gets the active lights in a scene up to
// a maximum number
void OpenGLRenderer::process_lights()
{
    Signature point_light_and_transform = world->get_signature_builder()
                                              .with<Transform>()
                                              .with<PointLight>()
                                              .build();

    std::vector<Entity> point_lights = world->get_entities_with_signature(point_light_and_transform);

    process_point_lights(point_lights);

    Signature directional_light = world->get_signature_builder()
                                      .with<DirectionalLight>()
                                      .build();

    std::vector<Entity> directional_lights = world->get_entities_with_signature(directional_light);

    process_directional_lights(directional_lights);
}

void OpenGLRenderer::process_point_lights(std::vector<Entity> point_lights)
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

void OpenGLRenderer::process_directional_lights(std::vector<Entity> directional_lights)
{
    std::shared_ptr<Shader> lighting_shader = shader_repository->get_shader("lighting");

    for (int i = 0; i < directional_lights.size(); i++)
    {
        DirectionalLight directional_light = world->get_component<DirectionalLight>(directional_lights[i]);

        directional_light.bind(lighting_shader, i);
    }

    lighting_shader->bind();
    lighting_shader->set_int(DEMO_NUM_ACTIVE_DIRECTIONAL_LIGHTS, directional_lights.size());
}
