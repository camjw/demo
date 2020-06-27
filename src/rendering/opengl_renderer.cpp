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
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set common variables for shaders
    // TODO: set uniform struct rather than individual params
    shader_repository->for_all(new SetShaderTime(time));
    shader_repository->for_all(new SetShaderProjection(window->get_projection_matrix()));

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
    for (SceneNode* const& child_node: scene_node->get_children())
    {
        draw_node(child_node, node_transform.get_model_matrix());
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

    std::string shader_name = world->get_component<ShaderComponent>(entity).name;
    std::shared_ptr<Shader> shader = shader_repository->get_shader(shader_name);
    shader->bind();

    Transform transform = world->get_component<Transform>(entity);
    shader->setMat4("model", transform.get_model_matrix() * parent_transform);

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
    shader_repository->for_all(new SetShaderCamera(
        camera_transform.position,
        camera.forward,
        get_view_matrix(camera, camera_transform)));

    isCameraSet = true;
}

void OpenGLRenderer::draw_scene(Time time, Scene* scene)
{
    begin_draw(time);
    draw_scene_graph(scene);
    end_draw();
}

glm::mat4 OpenGLRenderer::get_view_matrix(CameraComponent& cameraComponent, Transform& transform)
{
    return glm::lookAt(transform.position.to_glm(), cameraComponent.forward.to_glm(), cameraComponent.up.to_glm());
}
