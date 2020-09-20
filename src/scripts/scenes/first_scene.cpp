#include "first_scene.h"
#include <maths/transform.h>
#include <rendering/point_light.h>
#include <utils/opengl_helpers.h>

#include <utility>

FirstScene::FirstScene(std::shared_ptr<DemoContext> context, const std::shared_ptr<World>& world, SceneID scene_id)
    : Scene(std::move(context), world, scene_id)
{
}

void FirstScene::on_create()
{
    build_camera();

    context->get_fbx_importer()->load_fbx("../assets/models/fountain.fbx", graph->root().get());

//    MeshID cube_id = context->get_mesh_repository()->create_cube();
//    ShaderID simple_shader_id = context->get_shader_repository()->get_shader_id("simple");
//
//    graph->add_child(world->create_entity()
//        .with(Transform::identity())
//        .with(MeshComponent(cube_id))
//        .with(ShaderComponent(simple_shader_id))
//        .build());
}

void FirstScene::on_destroy()
{
    printf("Exiting scene\n");
}

void FirstScene::build_camera()
{
    camera = world->create_entity()
                 .with(CameraComponent {
                     .up = float3(0.0, 1.0, 0.0),
                     .forward = float3(-1.0, -1.0, -3.0).normalise(),
                 })
                 .with(Transform {
                     .position = float3(1.0, 1.0, 3.0),
                 })
                 .build();
}
