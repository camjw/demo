#include "first_scene.h"
#include <maths/transform.h>
#include <scripts/components/rotating_cube.h>
#include <utils/opengl_helpers.h>

FirstScene::FirstScene(std::shared_ptr<DemoContext> context, std::shared_ptr<World> world, SceneID scene_id)
    : Scene(context, world, scene_id)
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

    world->register_component<RotatingCubeComponent>();
    world->register_system<RotatingCubeSystem>();

    Signature rotating_cube_signature;
    rotating_cube_signature.set(world->get_component_type<Transform>());
    rotating_cube_signature.set(world->get_component_type<RotatingCubeComponent>());
    world->set_system_signature<RotatingCubeSystem>(rotating_cube_signature);

    for (int i = 0; i < 1; i++)
    {
        Entity entity = world->create_entity()
                            ->with(Transform {
                                .position = float3(0, 0, 0),
                                .scale = float3(0.1),
                            })
                            ->with(TextureComponent { .id = texture_id })
                            ->with(MeshComponent { .id = cube_id })
                            ->with(ShaderComponent { .id = shader_id })
                            ->build();

        world->add_component(entity, RotatingCubeComponent {});
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
    camera = world->create_entity()
                 ->with(CameraComponent {
                     .up = float3(0.0, 1.0, 0.0),
                     .forward = float3(0.0, 0.0, -1.0),
                 })
                 ->with(Transform {
                     .position = float3(0.0, 0.0, 10.0),
                 })
                 ->build();
}

void FirstScene::on_destroy()
{
    // Dump all of those here
}
