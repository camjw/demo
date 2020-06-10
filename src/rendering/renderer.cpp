#include <demo/maths/transform.h>
#include <demo/rendering/renderer.h>
#include <demo/utils/opengl_helpers.h>

Renderer::Renderer(std::shared_ptr<DemoContext> context,
    Window* _window, std::shared_ptr<World> _coordinator)
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

void Renderer::begin_draw(Time time)
{
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Set common variables for shaders
    shader_repository->for_all(new SetShaderTime(time));
    shader_repository->for_all(new SetShaderProjection(window->get_projection_matrix()));
}

void Renderer::draw_entities()
{
//    for (Entity const& entity: entities)
//    {
//        draw_entity(entity);
//    }
}

void Renderer::draw_entity(Entity entity)
{
    if (coordinator->has_component<TextureComponent>(entity))
    {
        TextureComponent texture = coordinator->get_component<TextureComponent>(entity);
        texture_repository->get_texture(texture.id)->bind(texture.binding_index);
    }

    std::string shader_name = coordinator->get_component<ShaderComponent>(entity).name;
    std::shared_ptr<Shader> shader = shader_repository->get_shader(shader_name);
    shader->bind();

    TransformComponent transform = coordinator->get_component<TransformComponent>(entity);
    shader->setMat4("model", transform.get_model_matrix());

    MeshComponent mesh = coordinator->get_component<MeshComponent>(entity);
    std::shared_ptr<Mesh> render_mesh = mesh_repository->get_mesh(mesh.id);
    render_mesh->bind();
    render_mesh->draw();
}

void Renderer::draw_skybox()
{}


void Renderer::end_draw()
{
    glfwSwapBuffers(window->get_glfw_window());
    glfwPollEvents();
}

void Renderer::set_camera(Scene* scene)
{
    Entity camera_entity = scene->get_active_camera();

    if (!coordinator->has_component<CameraComponent>(camera_entity))
    {
        printf("Scene does not have a camera set\n");
        return;
    }

    CameraComponent& camera = coordinator->get_component<CameraComponent>(camera_entity);
    TransformComponent& camera_transform = coordinator->get_component<TransformComponent>(camera_entity);
    shader_repository->for_all(new SetShaderCamera(
        camera_transform.position,
        camera.forward,
        get_view_matrix(camera, camera_transform)));
}

void Renderer::draw_scene(Time time, Scene* scene)
{
    set_camera(scene);
    begin_draw(time);
    draw_entities();
    end_draw();
}

glm::mat4 Renderer::get_view_matrix(CameraComponent& camera, TransformComponent& transform)
{
    return glm::mat4();
}
