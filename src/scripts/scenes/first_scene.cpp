#include "first_scene.h"
#include <demo/maths/transform.h>
#include <demo/utils/opengl_helpers.h>
#include <scripts/components/rotating_cube.h>

FirstScene::FirstScene(std::shared_ptr<DemoContext> context, std::shared_ptr<Coordinator> coordinator)
    : Scene(context, coordinator)
{
}

void FirstScene::on_create()
{
    load_textures();
    load_shaders();
    load_meshes();

    build_camera();

    MeshID cube_id = context->get_mesh_repository()->create_cube();
    ShaderID shader_id = context->get_shader_repository()->get_shader_id("simple");
    TextureID texture_id = context->get_texture_repository()->get_texture_id("uv_test");

    coordinator->register_component<RotatingCubeComponent>();
    coordinator->register_system<RotatingCubeSystem>();

    for (int i = 0; i < 100; i++)
    {
        Entity entity = coordinator->create_entity();
        coordinator->add_component(entity,
            TransformComponent {
                .position = float3(0, 0, 0),
                .scale = float3(0.1),
            });

        coordinator->add_component(entity, TextureComponent { .id = texture_id });
        coordinator->add_component(entity, MeshComponent { .id = cube_id });
        coordinator->add_component(entity, ShaderComponent { .id = shader_id });
        coordinator->add_component(entity, RotatingCubeComponent{});
    }
}

void FirstScene::load_textures()
{
    context->get_texture_repository()->create_texture("primal_scream", "../assets/textures/primal_scream.png");
    context->get_texture_repository()->create_texture("uv_test", "../assets/textures/uv_test.png");
}

void FirstScene::load_shaders()
{
    context->get_shader_repository()->create_shader(
        "simple",
        "../assets/shaders/simple_shader.vert",
        "../assets/shaders/simple_shader.frag");
}

void FirstScene::load_meshes()
{
    // Moved this back out just because CBA to add stupid functions now
}

void FirstScene::build_camera()
{
    camera = coordinator->create_entity();
    coordinator->add_component(camera,
        CameraComponent {
            .position = glm::vec3(1.0, -0.5, 10.0),
            .up = glm::vec3(0.0, 1.0, 0.0),
            .forward = glm::vec3(0.0, 0.0, -1.0),
        });
}

void FirstScene::on_destroy()
{
    // Dump all of those here
}

Entity FirstScene::get_active_camera()
{
    return camera;
}
