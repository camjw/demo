#include <demo/maths/transform.h>
#include <demo/rendering/rendering_system.h>
#include <demo/utils/opengl_helpers.h>

void RendererSystem::init(std::shared_ptr<DemoContext> context,
    Window* _window, std::shared_ptr<Coordinator> _coordinator)
{
    glEnable(GL_CULL_FACE);
    glDepthFunc(GL_LESS);

    glCheckError();

    this->window = _window;
    this->coordinator = _coordinator;

    mesh_repository = context->get_mesh_repository();
    texture_repository = context->get_texture_repository();
    shader_repository = context->get_shader_repository();
}

void RendererSystem::begin_draw(Time time)
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set common variables for shaders
    shader_repository->for_all(new SetShaderTime(time));
    glCheckError();
    shader_repository->for_all(new SetShaderProjection(window->get_projection_matrix()));
    glCheckError();
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

    ShaderID shader_id = coordinator->get_component<ShaderComponent>(entity).id;
    std::shared_ptr<Shader> shader = shader_repository->get_shader(shader_id);
    shader->bind();

    TransformComponent transform = coordinator->get_component<TransformComponent>(entity);
    shader->setMat4("model", transform.get_model_matrix());

    MeshComponent mesh = coordinator->get_component<MeshComponent>(entity);
    std::shared_ptr<Mesh> render_mesh = mesh_repository->get_mesh(mesh.id);
    render_mesh->bind();
    render_mesh->draw();
}

void RendererSystem::end_draw()
{
    glfwSwapBuffers(window->get_glfw_window());
    glfwPollEvents();
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
