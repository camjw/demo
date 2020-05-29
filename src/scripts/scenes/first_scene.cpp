#include "first_scene.h"

FirstScene::FirstScene(std::shared_ptr<DemoContext> context, std::shared_ptr<Coordinator> coordinator)
    : Scene(context, coordinator)
{
    camera = std::make_shared<Camera>();
}

void FirstScene::on_create()
{
    load_textures();
    load_shaders();
    load_meshes();

    Entity entity = coordinator->create_entity();

    TextureID texture_id = context->get_texture_repository()->get_texture_id("uv_test");
    coordinator->add_component(entity, TextureComponent{ .id =  texture_id });

    MeshID cube_id = context->get_mesh_repository()->create_cube();
    coordinator->add_component(entity, MeshComponent{ .id =  cube_id });
}

void FirstScene::load_textures()
{
    context->get_texture_repository()->create_texture("primal_scream", "assets/textures/primal_scream.png");
    context->get_texture_repository()->create_texture("uv_test", "assets/textures/uv_test.png");
}

void FirstScene::load_shaders()
{
    context->get_shader_repository()->create_shader(
        "assets/shaders/simple_shader.vert",
        "assets/shaders/simple_shader.frag");
}

void FirstScene::load_meshes()
{
    // Moved this back out just because CBA to add stupid functions now
}


void FirstScene::on_destroy()
{
    // Dump all of those here
}

std::shared_ptr<Camera> FirstScene::get_active_camera()
{
    return camera;
}
