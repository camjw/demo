#include <demo/rendering/rendering_system.h>

void RendererSystem::init(std::shared_ptr<DemoContext> context,
    Window* _window, std::shared_ptr<Coordinator> _coordinator)
{
    glEnable(GL_CULL_FACE);

    this->window = _window;
    this->coordinator = _coordinator;

    mesh_repository = context->get_mesh_repository();
    texture_repository = context->get_texture_repository();
    shader_repository = context->get_shader_repository();
}

void RendererSystem::begin_draw(Time time)
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set common variables for shaders
    shader_repository->for_all(new SetShaderTime(time));
    shader_repository->for_all(new SetShaderProjection(window->get_projection_matrix()));
}

void RendererSystem::draw_entities()
{
    for (Entity const& entity: entities)
    {
        draw_entity(entity);
    }
}

void RendererSystem::draw_entity(Entity entity)
{
    if (coordinator->has_component<TextureComponent>(entity))
    {
        TextureComponent texture = coordinator->get_component<TextureComponent>(entity);
        texture_repository->get_texture(texture.id)->bind(texture.binding_index);
    }

    ShaderComponent shader = coordinator->get_component<ShaderComponent>(entity);
    shader_repository->get_shader(shader.id)->bind();

    MeshComponent mesh = coordinator->get_component<MeshComponent>(entity);
    std::shared_ptr<Mesh> render_mesh = mesh_repository->get_mesh(mesh.id);
    render_mesh->bind();
    render_mesh->draw();
}
//void RendererSystem::draw_skybox(Skybox* skybox)
//{
//    //draw skybox
//    glDepthFunc(GL_LEQUAL);
//    skybox_shader.use();
//    skybox_shader.setMat4("view", glm::mat4(glm::mat3(camera->get_view_matrix())));
//    skybox_shader.setMat4("projection", window->get_projection_matrix());
//
//    glBindVertexArray(skybox_VAO);
//    skybox.bind();
//    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
//    glBindVertexArray(0);
//    glDepthFunc(GL_LESS);
//}

void RendererSystem::end_draw()
{
    //    draw_skybox();
    glfwSwapBuffers(window->get_glfw_window());
}

void RendererSystem::set_camera(Scene* scene)
{
    Entity camera_entity = scene->get_active_camera();

    if (!coordinator->has_component<CameraComponent>(camera_entity))
    {
        printf("Scene does not have a camera set\n");
        return;
    }

    CameraComponent& camera = coordinator->get_component<CameraComponent>(camera_entity);

    shader_repository->for_all(new SetShaderCamera(
        camera.position,
        camera.forward,
        camera.get_view_matrix()));
}

void RendererSystem::draw(Time time, Scene* scene)
{
    set_camera(scene);
    begin_draw(time);
    draw_entities();
    end_draw();
}
